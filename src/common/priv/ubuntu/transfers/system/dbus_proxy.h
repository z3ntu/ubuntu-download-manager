/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p dbus_proxy.h:dbus_proxy.cpp -c DBusProxy -i metatypes.h org.freedesktop.DBus.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUS_PROXY_H_1378717910
#define DBUS_PROXY_H_1378717910

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "pending_reply.h"

typedef QMap<QString, QString> StringMap;
using namespace Ubuntu::Transfers::System;

/*
 * Proxy class for interface org.freedesktop.DBus
 */
class DBusProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.DBus"; }

public:
    DBusProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusProxy();

public Q_SLOTS: // METHODS
    virtual QDBusPendingReply<> AddMatch(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("AddMatch"), argumentList);
    }

    virtual QDBusPendingReply<QByteArray> GetAdtAuditSessionData(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("GetAdtAuditSessionData"), argumentList);
    }

    virtual PendingReply<QString>* GetConnectionAppArmorSecurityContext(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        QDBusPendingReply<QString> reply = asyncCallWithArgumentList(
            QLatin1String("GetConnectionAppArmorSecurityContext"),
            argumentList);
        auto wrapper = new PendingReply<QString>(reply);
        return wrapper;
    }

    virtual QDBusPendingReply<QByteArray> GetConnectionSELinuxSecurityContext(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("GetConnectionSELinuxSecurityContext"), argumentList);
    }

    virtual QDBusPendingReply<uint> GetConnectionUnixProcessID(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("GetConnectionUnixProcessID"), argumentList);
    }

    virtual QDBusPendingReply<uint> GetConnectionUnixUser(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("GetConnectionUnixUser"), argumentList);
    }

    virtual QDBusPendingReply<QString> GetId()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetId"), argumentList);
    }

    virtual QDBusPendingReply<QString> GetNameOwner(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("GetNameOwner"), argumentList);
    }

    virtual QDBusPendingReply<QString> Hello()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Hello"), argumentList);
    }

    virtual QDBusPendingReply<QStringList> ListActivatableNames()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ListActivatableNames"), argumentList);
    }

    virtual QDBusPendingReply<QStringList> ListNames()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ListNames"), argumentList);
    }

    virtual QDBusPendingReply<QStringList> ListQueuedOwners(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("ListQueuedOwners"), argumentList);
    }

    virtual QDBusPendingReply<bool> NameHasOwner(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("NameHasOwner"), argumentList);
    }

    virtual QDBusPendingReply<uint> ReleaseName(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("ReleaseName"), argumentList);
    }

    virtual QDBusPendingReply<> ReloadConfig()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ReloadConfig"), argumentList);
    }

    virtual QDBusPendingReply<> RemoveMatch(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("RemoveMatch"), argumentList);
    }

    virtual QDBusPendingReply<uint> RequestName(const QString &in0, uint in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QLatin1String("RequestName"), argumentList);
    }

    virtual QDBusPendingReply<uint> StartServiceByName(const QString &in0, uint in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QLatin1String("StartServiceByName"), argumentList);
    }

    virtual QDBusPendingReply<> UpdateActivationEnvironment(StringMap in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("UpdateActivationEnvironment"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void NameAcquired(const QString &in0);
    void NameLost(const QString &in0);
    void NameOwnerChanged(const QString &in0, const QString &in1, const QString &in2);
};

namespace org {
  namespace freedesktop {
    typedef ::DBusProxy DBusProxy;
  }
}
#endif
