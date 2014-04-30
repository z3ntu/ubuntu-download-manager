/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.canonical.applications.download_manager.xml -p manager_interface -c ManagerInterface
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MANAGER_INTERFACE_H_1386155846
#define MANAGER_INTERFACE_H_1386155846

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include <ubuntu/download_manager/metatypes.h>

namespace Ubuntu {

using namespace Transfers::Errors;

namespace DownloadManager {

/*
 * Proxy class for interface com.canonical.applications.DownloadManager
 */
class ManagerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.canonical.applications.DownloadManager"; }

public:
    ManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~ManagerInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> allowGSMDownload(bool allowed)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(allowed);
        return asyncCallWithArgumentList(QLatin1String("allowGSMDownload"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> createDownload(DownloadStruct download)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(download);
        return asyncCallWithArgumentList(QLatin1String("createDownload"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> createDownloadGroup(StructList downloads, const QString &algorithm, bool allowed3G, const QVariantMap &metadata, StringMap headers)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(downloads) << QVariant::fromValue(algorithm) << QVariant::fromValue(allowed3G) << QVariant::fromValue(metadata) << QVariant::fromValue(headers);
        return asyncCallWithArgumentList(QLatin1String("createDownloadGroup"), argumentList);
    }

    inline QDBusPendingReply<qulonglong> defaultThrottle()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("defaultThrottle"), argumentList);
    }

    inline QDBusPendingReply<> exit()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("exit"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> > getAllDownloads()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("getAllDownloads"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> > getAllDownloadsWithMetadata(const QString &name, const QString &value)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name) << QVariant::fromValue(value);
        return asyncCallWithArgumentList(QLatin1String("getAllDownloadsWithMetadata"), argumentList);
    }

    inline QDBusPendingReply<bool> isGSMDownloadAllowed()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("isGSMDownloadAllowed"), argumentList);
    }

    inline QDBusPendingReply<> setDefaultThrottle(qulonglong speed)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(speed);
        return asyncCallWithArgumentList(QLatin1String("setDefaultThrottle"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void downloadCreated(const QDBusObjectPath &path);
};

}  // DownloadManager

}  // Ubuntu

#endif
