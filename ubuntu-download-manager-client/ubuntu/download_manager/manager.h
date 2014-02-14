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

#ifndef UBUNTU_DOWNLOADMANAGER_CLIENT_MANAGER_H
#define UBUNTU_DOWNLOADMANAGER_CLIENT_MANAGER_H

#include <functional>
#include <QList>
#include <QObject>
#include <ubuntu/download_manager/metatypes.h>
#include <ubuntu/download_manager/common.h>
#include <ubuntu/download_manager/download_struct.h>
#include <ubuntu/download_manager/group_download_struct.h>


class QDBusConnection;

namespace Ubuntu {

namespace DownloadManager {

class Download;
class Error;
class GroupDownload;
class ManagerInterface;

typedef std::function<void(Download*)> DownloadCb;
typedef std::function<void(GroupDownload*)> GroupCb;

class ManagerPrivate;
class DOWNLOAD_MANAGER_EXPORT Manager : public QObject {
    Q_DECLARE_PRIVATE(Manager)
    Q_OBJECT

    // allow watchers to emit the signals
    friend class DownloadManagerPendingCallWatcher;
    friend class GroupManagerPendingCallWatcher;

 public:
    virtual ~Manager();
    virtual void createDownload(DownloadStruct downStruct);
    virtual void createDownload(DownloadStruct downStruct,
                                DownloadCb cb,
                                DownloadCb errCb);
    virtual void createDownload(StructList downs,
                                const QString &algorithm,
                                bool allowed3G,
                                const QVariantMap &metadata,
                                StringMap headers);
    virtual void createDownload(StructList downs,
                                const QString &algorithm,
                                bool allowed3G,
                                const QVariantMap &metadata,
                                StringMap headers,
                                GroupCb cb,
                                GroupCb errCb);

    bool isError();
    Error* lastError();
    void allowMobileDataDownload(bool allowed);
    bool isMobileDataDownload();
    qulonglong defaultThrottle();
    void setDefaultThrottle(qulonglong speed);
    void exit();

    static Manager* createSessionManager(const QString& path = "", QObject* parent=0);
    static Manager* createSystemManager(const QString& path = "", QObject* parent=0);

 signals:
    void downloadCreated(Download* down);
    void groupCreated(GroupDownload* down);

 protected:
    Manager(const QDBusConnection& conn,
            const QString& path = "",
            QObject* parent= 0);
    // used for testing purposes
    Manager(const QDBusConnection& conn,
            const QString& path,
            ManagerInterface* interface,
            QObject* parent);

 private:
    Q_PRIVATE_SLOT(d_func(), void onWatcherDone())

 private:
    // use pimpl pattern so that users do not have to be recompiled
    ManagerPrivate* d_ptr;
};

}  // DownloadManager

}  // Ubuntu

#endif  // UBUNTU_DOWNLOADMANAGER_CLIENT_MANAGER_H