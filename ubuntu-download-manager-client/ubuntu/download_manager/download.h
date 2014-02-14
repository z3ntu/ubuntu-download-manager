/*
 * Copyright 2013-2014 Canonical Ltd.
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

#ifndef UBUNTU_DOWNLOADMANAGER_CLIENT_DOWNLOAD_H
#define UBUNTU_DOWNLOADMANAGER_CLIENT_DOWNLOAD_H

#include <QObject>
#include <QVariantMap>
#include <QString>
#include <ubuntu/download_manager/common.h>

class QDBusConnection;
class QDBusObjectPath;

namespace Ubuntu {

namespace DownloadManager {

class Error;
class HttpErrorStruct;
class NetworkErrorStruct;
class ProcessErrorStruct;
class ManagerPrivate;
class DownloadPrivate;
class DOWNLOAD_MANAGER_EXPORT Download : public QObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(Download)

    // allow the manager to create downloads
    friend class ManagerPrivate;
    friend class DownloadPendingCallWatcher;
    friend class DownloadManagerPendingCallWatcher;

 public:
    virtual ~Download();

    void start();
    void pause();
    void resume();
    void cancel();

    void allowMobileDownload(bool allowed);
    bool isMobileDownloadAllowed();

    void setThrottle(qulonglong speed);
    qulonglong throttle();

    QString id();
    QVariantMap metadata();
    qulonglong progress();
    qulonglong totalSize();

    bool isError();
    Error* error();

 protected:
    Download(const QDBusConnection& conn, Error* err, QObject* parent = 0);
    Download(const QDBusConnection& conn,
             const QString& servicePath,
             const QDBusObjectPath& objectPath,
             QObject* parent = 0);

 private:
    Q_PRIVATE_SLOT(d_func(), void onHttpError(HttpErrorStruct))
    Q_PRIVATE_SLOT(d_func(), void onNetworkError(NetworkErrorStruct))
    Q_PRIVATE_SLOT(d_func(), void onProcessError(ProcessErrorStruct))

 signals:
    void canceled(bool success);
    void error(Error* error);
    void finished(const QString& path);
    void paused(bool success);
    void processing(const QString &path);
    void progress(qulonglong received, qulonglong total);
    void resumed(bool success);
    void started(bool success);

 private:
    // use pimpl pattern so that users do not have to be recompiled
    DownloadPrivate* d_ptr;

};

}  // Ubuntu

}  // DownloadManager

#endif  // UBUNTU_DOWNLOADMANAGER_CLIENT_DOWNLOAD_H