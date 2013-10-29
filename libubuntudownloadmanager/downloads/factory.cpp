/*
 * Copyright 2013 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of version 3 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <QPair>
#include "downloads/download_adaptor.h"
#include "downloads/group_download.h"
#include "downloads/group_download_adaptor.h"
#include "downloads/file_download.h"
#include "downloads/factory.h"
#include "system/logger.h"

#define OBJECT_PATH_KEY "objectpath"

namespace Ubuntu {

namespace DownloadManager {

/*
 * PRIVATE IMPLEMENTATION
 */


class FactoryPrivate {
    Q_DECLARE_PUBLIC(Factory)

 public:
    FactoryPrivate(QSharedPointer<AppArmor> apparmor,
                   QSharedPointer<SystemNetworkInfo> networkInfo,
                   QSharedPointer<RequestFactory> nam,
                   QSharedPointer<ProcessFactory> processFactory,
                   Factory* parent)
        : _apparmor(apparmor),
          _networkInfo(networkInfo),
          _nam(nam),
          _processFactory(processFactory),
          _self(parent),
          q_ptr(parent) {
    }

    void getDownloadPath(const QString& dbusOwner,
                         const QVariantMap& metadata,
                         QString& id,
                         QString& dbusPath,
                         QString& rootPath,
                         bool& isConfined) {
        TRACE << dbusOwner << metadata;
        if (metadata.contains(OBJECT_PATH_KEY)) {
            // create a uuid using the string value form the metadata
            id = metadata[OBJECT_PATH_KEY].toString();
            if (id.isEmpty()) {
                qCritical() << "Id sent by client is ''";
                id = _apparmor->getSecurePath(dbusOwner, dbusPath, rootPath,
                    isConfined);
            } else {
                qDebug() << "Using the id from the client" << id;
                _apparmor->getSecurePath(dbusOwner, id, dbusPath, rootPath,
                    isConfined);
            }
        } else {
            qDebug() << "Factory assigns the Download Uuid.";
            id = _apparmor->getSecurePath(dbusOwner, dbusPath, rootPath,
                isConfined);
        }
    }

    Download* createDownload(const QString& dbusOwner,
                             const QUrl& url,
                             const QVariantMap& metadata,
                             const QMap<QString, QString>& headers) {
        QString id;
        QString dbusPath;
        QString rootPath;
        bool isConfined = false;
        getDownloadPath(dbusOwner, metadata, id, dbusPath, rootPath,
            isConfined);
        Download* down = new FileDownload(id, dbusPath, isConfined, rootPath,
            url, metadata, headers, _networkInfo, _nam, _processFactory);
        DownloadAdaptor* adaptor = new DownloadAdaptor(down);
        down->setAdaptor(adaptor);
        return down;
    }

    Download* createDownload(const QString& dbusOwner,
                             const QUrl& url,
                             const QString& hash,
                             const QString& algo,
                             const QVariantMap& metadata,
                             const QMap<QString, QString>& headers) {
        QString id;
        QString dbusPath;
        QString rootPath;
        bool isConfined = false;
        getDownloadPath(dbusOwner, metadata, id, dbusPath, rootPath,
            isConfined);
        Download* down = new FileDownload(id, dbusPath, isConfined,
            rootPath, url, hash, algo, metadata, headers, _networkInfo, _nam,
            _processFactory);
        DownloadAdaptor* adaptor = new DownloadAdaptor(down);
        down->setAdaptor(adaptor);
        return down;
    }

    Download* createDownload(const QString& dbusOwner,
                             StructList downloads,
                             const QString& algo,
                             bool allowed3G,
                             const QVariantMap& metadata,
                             StringMap headers) {
        QString id;
        QString dbusPath;
        QString rootPath;
        bool isConfined = false;
        getDownloadPath(dbusOwner, metadata, id, dbusPath, rootPath,
            isConfined);
        Download* down = new GroupDownload(id, dbusPath, isConfined, rootPath,
            downloads, algo, allowed3G, metadata, headers, _networkInfo,
            _self);
        GroupDownloadAdaptor* adaptor = new GroupDownloadAdaptor(down);
        down->setAdaptor(adaptor);
        return down;
    }

    Download* createDownloadForGroup(bool isConfined,
                                     const QString& rootPath,
                                     const QUrl& url,
                                     const QVariantMap& metadata,
                                     const QMap<QString, QString>& headers) {
        QString id;
        QString dbusPath;
        _apparmor->getDBusPath(id, dbusPath);
        Download* down = new FileDownload(id, dbusPath, isConfined, rootPath,
            url, metadata, headers, _networkInfo, _nam, _processFactory);
        DownloadAdaptor* adaptor = new DownloadAdaptor(down);
        down->setAdaptor(adaptor);
        return down;
    }

    Download* createDownloadForGroup(bool isConfined,
                                     const QString& rootPath,
                                     const QUrl& url,
                                     const QString& hash,
                                     const QString& algo,
                                     const QVariantMap& metadata,
                                     const QMap<QString, QString>& headers) {
        QString id;
        QString dbusPath;
        _apparmor->getDBusPath(id, dbusPath);
        Download* down = new FileDownload(id, dbusPath, isConfined,
            rootPath, url, hash, algo, metadata, headers, _networkInfo, _nam,
            _processFactory);
        DownloadAdaptor* adaptor = new DownloadAdaptor(down);
        down->setAdaptor(adaptor);
        return down;
    }

    QList<QSslCertificate> acceptedCertificates() {
        return _nam->acceptedCertificates();
    }

    void setAcceptedCertificates(const QList<QSslCertificate>& certs) {
        _nam->setAcceptedCertificates(certs);
    }

 private:
    QSharedPointer<AppArmor> _apparmor;
    QSharedPointer<SystemNetworkInfo> _networkInfo;
    QSharedPointer<RequestFactory> _nam;
    QSharedPointer<ProcessFactory> _processFactory;
    QSharedPointer<Factory> _self;
    Factory* q_ptr;
};

/*
 * PUBLIC IMPLEMENTATION
 */

Factory::Factory(QSharedPointer<AppArmor> apparmor,
                 QSharedPointer<SystemNetworkInfo> networkInfo,
                 QSharedPointer<RequestFactory> nam,
                 QSharedPointer<ProcessFactory> processFactory,
                 QObject* parent)
    : QObject(parent),
      d_ptr(new FactoryPrivate(apparmor, networkInfo, nam,
        processFactory, this)) {
}


Download*
Factory::createDownload(const QString& dbusOwner,
                        const QUrl& url,
                        const QVariantMap& metadata,
                        const QMap<QString, QString>& headers) {
    Q_D(Factory);
    return d->createDownload(dbusOwner, url, metadata, headers);
}

Download*
Factory::createDownload(const QString& dbusOwner,
                        const QUrl& url,
                        const QString& hash,
                        const QString& algo,
                        const QVariantMap& metadata,
                        const QMap<QString, QString>& headers) {
    Q_D(Factory);
    return d->createDownload(dbusOwner, url, hash, algo, metadata, headers);
}

Download*
Factory::createDownload(const QString& dbusOwner,
                        StructList downloads,
                        const QString& algo,
                        bool allowed3G,
                        const QVariantMap& metadata,
                        StringMap headers) {
    Q_D(Factory);
    return d->createDownload(dbusOwner, downloads, algo, allowed3G, metadata,
        headers);
}

Download*
Factory::createDownloadForGroup(bool isConfined,
                                const QString& rootPath,
                                const QUrl& url,
                                const QVariantMap& metadata,
                                const QMap<QString, QString>& headers) {
    Q_D(Factory);
    return d->createDownloadForGroup(isConfined, rootPath, url, metadata,
        headers);
}

Download*
Factory::createDownloadForGroup(bool isConfined,
                                const QString& rootPath,
                                const QUrl& url,
                                const QString& hash,
                                const QString& algo,
                                const QVariantMap& metadata,
                                const QMap<QString, QString>& headers) {
    Q_D(Factory);
    return d->createDownloadForGroup(isConfined, rootPath, url, hash, algo,
        metadata, headers);
}

QList<QSslCertificate>
Factory::acceptedCertificates() {
    Q_D(Factory);
    return d->acceptedCertificates();
}

void
Factory::setAcceptedCertificates(const QList<QSslCertificate>& certs) {
    Q_D(Factory);
    d->setAcceptedCertificates(certs);
}

}  // DownloadManager

}  // Ubuntu
