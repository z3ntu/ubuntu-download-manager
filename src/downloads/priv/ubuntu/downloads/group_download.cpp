/*
 * copyright 2013-2014 canonical ltd.
 *
 * this library is free software; you can redistribute it and/or
 * modify it under the terms of version 3 of the gnu lesser general public
 * license as published by the free software foundation.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the gnu
 * general public license for more details.
 *
 * you should have received a copy of the gnu lesser general public
 * license along with this library; if not, write to the
 * free software foundation, inc., 51 franklin street, fifth floor,
 * boston, ma 02110-1301, usa.
 */

#include <QDir>
#include <QFileInfo>
#include <glog/logging.h>
#include <ubuntu/transfers/i18n.h>
#include <ubuntu/transfers/metadata.h>
#include <ubuntu/transfers/system/hash_algorithm.h>
#include "ubuntu/transfers/system/logger.h"
#include "ubuntu/transfers/system/uuid_factory.h"
#include "download_adaptor.h"
#include "file_download.h"
#include "group_download.h"

#define GROUP_LOG(LEVEL) LOG(LEVEL) << "Group Download {" << objectName() << " } "

namespace Ubuntu {

namespace DownloadManager {

namespace Daemon {

GroupDownload::GroupDownload(const QString& id,
                  const QString& appId,
                  const QString& path,
                  bool isConfined,
                  const QString& rootPath,
                  QList<GroupDownloadStruct> downloads,
                  const QString& algo,
                  bool isGSMDownloadAllowed,
                  const QVariantMap& metadata,
                  const QMap<QString, QString>& headers,
                  Factory* downFactory,
                  QObject* parent)
    : Download(id, appId, path, isConfined, rootPath, metadata, headers,
            parent),
      _downloads(),
      _finishedDownloads(),
      _downloadsProgress(),
      _downFactory(downFactory) {
    init(downloads, algo, isGSMDownloadAllowed);
}

GroupDownload::~GroupDownload() {
    qDeleteAll(_downloads);
}

void
GroupDownload::connectToDownloadSignals(FileDownload* singleDownload) {
    CHECK(connect(singleDownload, static_cast<void(Download::*)
            (qulonglong, qulonglong)>(&Download::progress),
                this, &GroupDownload::onProgress))
                    << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::finished,
        this, &GroupDownload::onFinished))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::processing,
        this, &GroupDownload::processing))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::canceled,
        this, &GroupDownload::onCanceled))
            << "Could not connect to signal";

    // connect to the error signals
    CHECK(connect(singleDownload, &Download::error,
        this, &GroupDownload::onError))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::authError,
        this, &GroupDownload::onAuthError))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::httpError,
        this, &GroupDownload::onHttpError))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::networkError,
        this, &GroupDownload::onNetworkError))
            << "Could not connect to signal";
    CHECK(connect(singleDownload, &FileDownload::processError,
        this, &GroupDownload::onProcessError))
            << "Could not connect to signal";
}

void
GroupDownload::init(QList<GroupDownloadStruct> downloads,
              const QString& algo,
              bool isGSMDownloadAllowed) {
    _fileManager = FileManager::instance();
    QVariantMap metadataMap = metadata();
    QMap<QString, QString> headersMap = headers();
    QStringList localPaths;

    // build downloads and add them to the q, it will take care of
    // starting them etc..
    foreach(GroupDownloadStruct download, downloads) {
        QUrl url(download.getUrl());
        QString hash = download.getHash();

        FileDownload* singleDownload;
        QVariantMap downloadMetadata = QVariantMap(metadataMap);
        downloadMetadata[Metadata::LOCAL_PATH_KEY] = download.getLocalFile();

        if (hash.isEmpty()) {
            singleDownload = qobject_cast<FileDownload*>(
                _downFactory->createDownloadForGroup(isConfined(),
                    rootPath(), url, downloadMetadata, headersMap));
        } else {
            if (!HashAlgorithm::isValidAlgo(algo)) {
                setIsValid(false);
                setLastError(QString(_("Invalid hash algorithm: '%1'")).arg(algo));
                break;
            }

            singleDownload = qobject_cast<FileDownload*>(
                _downFactory->createDownloadForGroup(isConfined(),
                    rootPath(), url, hash, algo, downloadMetadata,
                    headersMap));
        }
        singleDownload->setParent(this);

        // ensure that the local path is not used by any other download
        // in this group.
        QString localFilePath = singleDownload->filePath();
        if (localPaths.contains(localFilePath)) {
            setIsValid(false);
            setLastError(_("Duplicated local path passed: ") + localFilePath);
            break;
        } else {
            localPaths.append(localFilePath);
        }

        // check that the download is valid, if it is not set to invalid
        // and use the last error from the download
        if (!singleDownload->isValid()) {
            setIsValid(false);
            setLastError(singleDownload->lastError());
            break;
        }

        singleDownload->allowGSMDownload(isGSMDownloadAllowed);
        _downloads.append(singleDownload);
        _downloadsProgress[singleDownload->url()] =
            QPair<qulonglong, qulonglong>(0, singleDownload->totalSize());
        // connect to signals to keep track of the download
        connectToDownloadSignals(singleDownload);
    }
}

void
GroupDownload::cancelAllDownloads() {
    TRACE;
    foreach(FileDownload* download, _downloads) {
        Download::State state = download->state();
        if (state != Download::FINISH && state != Download::ERROR
                && state != Download::CANCEL) {
            // disconnect from the canceled signal so that we do not react
            // to it
            CHECK(disconnect(download, &FileDownload::canceled,
                this, &GroupDownload::onCanceled))
                    << "Could not disconnect from signal";
            download->cancel();
            download->cancelTransfer();
        }
    }

    // loop over the finished downloads and remove the files
    foreach(const QString& path, _finishedDownloads) {
        GROUP_LOG(INFO) << "Removing file: " << path;
        _fileManager->remove(path);
    }
}

void
GroupDownload::cancelTransfer() {
    TRACE;
    cancelAllDownloads();
    GROUP_LOG(INFO) << "EMIT canceled";
    emit canceled(true);
}

void
GroupDownload::pauseTransfer() {
    foreach(FileDownload* download, _downloads) {
        Download::State state = download->state();
        if (state == Download::START || state == Download::RESUME) {
            GROUP_LOG(INFO) << "Pausing download of "
                << download->url();
            download->pause();
            download->pauseTransfer();
        }
    }
    GROUP_LOG(INFO) << "EMIT paused";
    emit paused(true);
}

void
GroupDownload::resumeTransfer() {
    foreach(FileDownload* download, _downloads) {
        Download::State state = download->state();
        if (state == Download::PAUSE) {
            download->resume();
            download->resumeTransfer();
        }
    }
    GROUP_LOG(INFO) << "EMIT resumed";
    emit resumed(true);
}

void
GroupDownload::startTransfer() {
    if (_downloads.count() > 0) {
        foreach(FileDownload* download, _downloads) {
            Download::State state = download->state();
            if (state == Download::IDLE) {
                download->start();
                download->startTransfer();
            }
        }
        GROUP_LOG(INFO) << "EMIT started";
        emit started(true);
    } else {
        GROUP_LOG(INFO) << "EMIT started";
        emit started(true);
        GROUP_LOG(INFO) << "EMIT finished " << _finishedDownloads.join(";");
        emit finished(_finishedDownloads);
    }
}

qulonglong
GroupDownload::progress() {
    qulonglong total = 0;
    foreach(FileDownload* download, _downloads) {
        total += download->progress();
    }
    return total;
}

qulonglong
GroupDownload::progress(qulonglong &started, qulonglong &paused,
        qulonglong &finished) {
    // due to an implementation detail on the phone, right now we
    // only have 1 download started if the group was started else 0,
    // all other paused, whatever finished and 0 errors.
    Download::State currentState = state();
    if (currentState == Download::START || currentState == Download::RESUME) {
        started = 1;
    } else {
        started = 0;
    }
    finished = _finishedDownloads.count();
    paused = _downloads.count() - finished - started;
    // no errors
    return 0;
}

qulonglong
GroupDownload::totalSize() {
    qulonglong total = 0;
    foreach(FileDownload* download, _downloads) {
        total += download->totalSize();
    }
    return total;
}

QString
GroupDownload::filePath() {
    // A group download never has a file path of its own, each individual
    // download within the group has its own path
    return "";
}

void
GroupDownload::onError(const QString& error) {
    TRACE;
    FileDownload* down = qobject_cast<FileDownload*>(sender());
    // we got an error, cancel all downloads and later remove all the
    // files that we managed to download
    cancelAllDownloads();
    QString errorMsg = down->url().toString() + ":" + error;

    GROUP_LOG(INFO) << "EMIT error " << errorMsg;
    emitError(errorMsg);
}

void
GroupDownload::onCanceled() {
    // one of the file was canceled therefore we are going to
    // cancel all of them
    cancelTransfer();
}

QString
GroupDownload::getUrlFromSender(QObject* sender) {
    auto down = qobject_cast<FileDownload*>(sender);
    if (down != nullptr) {
        return down->url().toString();
    } else {
        return "";
    }
}

void
GroupDownload::onAuthError(AuthErrorStruct err) {
    auto url = getUrlFromSender(sender());
    if (!url.isEmpty()) {
        emit authError(url, err);
    }
}

void
GroupDownload::onHttpError(HttpErrorStruct err) {
    auto url = getUrlFromSender(sender());
    if (!url.isEmpty()) {
        emit httpError(url, err);
    }
}

void
GroupDownload::onNetworkError(NetworkErrorStruct err) {
    auto url = getUrlFromSender(sender());
    if (!url.isEmpty()) {
        emit networkError(url, err);
    }
}

void
GroupDownload::onProcessError(ProcessErrorStruct err) {
    auto url = getUrlFromSender(sender());
    if (!url.isEmpty()) {
        emit processError(url, err);
    }
}

void
GroupDownload::onProgress(qulonglong received, qulonglong total) {
    FileDownload* down = qobject_cast<FileDownload*>(sender());
    TRACE;
    // TODO(mandel): the result is not real, we need to be smarter make
    // a head request get size and name and the do all this, but atm is
    // 'good enough' get the sender and check if we received
    // progress from it, update its data and recalculate
    QUrl url = down->url();
    if (_downloadsProgress.contains(url)) {
        QPair<qulonglong, qulonglong>& data = _downloadsProgress[url];
        data.first = received;
        if (data.second != total) {
            data.second = total;
        }
    } else {
        _downloadsProgress[url] = QPair<qulonglong, qulonglong>(received,
            total);
    }
    // calculate progress and total using all the downloads, if one of the
    // progress is equal to the total and is not in the finishedDownloads
    // it means that the total is not known and we have to return received
    // == total
    qulonglong totalReceived = 0;
    qulonglong totalTotal = 0;
    QList<QPair<qulonglong, qulonglong> > progressList =
        _downloadsProgress.values();

    for (int index = 0; index < progressList.count(); index++) {
        totalReceived += progressList[index].first;
        totalTotal += progressList[index].second;
    }

    emit Download::progress(totalReceived, totalTotal);
}

void
GroupDownload::onFinished(const QString& file) {
    TRACE << file;
    FileDownload* down = qobject_cast<FileDownload*>(sender());
    _downloadsProgress[down->url()] = QPair<qulonglong, qulonglong>(
        down->totalSize(), down->totalSize());
    _finishedDownloads.append(file);
    GROUP_LOG(INFO) << "Finished downloads "
        << _finishedDownloads;
    // if we have the same number of downloads finished
    // that downloads we are done :)
    if (_downloads.count() == _finishedDownloads.count()) {
        setState(Download::FINISH);
#ifndef NDEBUG
        foreach(const QString& file, _finishedDownloads) {
           auto parentDir = QFileInfo(file).dir();
           DLOG(INFO) << "Files for path dir '" << parentDir.absolutePath() << "' :";
           auto children = parentDir.entryList();
           foreach(const QString& child, children) {
               DLOG(INFO) << "\t" << child;
           }
        }
#endif
        GROUP_LOG(INFO) << "EMIT finished " << _finishedDownloads.join(";");
        emit finished(_finishedDownloads);
    }
}

}  // Daemon

}  // DownloadManager

}  // Ubuntu
