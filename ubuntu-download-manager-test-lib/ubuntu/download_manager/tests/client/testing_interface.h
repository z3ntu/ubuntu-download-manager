/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.canonical.applications.testing.download_manager.xml -p testing_interface -c TestingInterface
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef TESTING_INTERFACE_H_1391440734
#define TESTING_INTERFACE_H_1391440734

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include <ubuntu/download_manager/metatypes.h>

/*
 * Proxy class for interface com.canonical.applications.testing.DownloadManager
 */
class TestingInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.canonical.applications.testing.DownloadManager"; }

public:
    TestingInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~TestingInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> returnDBusErrors(bool returnErrors)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(returnErrors);
        return asyncCallWithArgumentList(QLatin1String("returnDBusErrors"), argumentList);
    }

    inline QDBusPendingReply<> returnHttpError(const QString &download, HttpErrorStruct error)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(download) << QVariant::fromValue(error);
        return asyncCallWithArgumentList(QLatin1String("returnHttpError"), argumentList);
    }

    inline QDBusPendingReply<> returnNetworkError(const QString &download, NetworkErrorStruct error)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(download) << QVariant::fromValue(error);
        return asyncCallWithArgumentList(QLatin1String("returnNetworkError"), argumentList);
    }

    inline QDBusPendingReply<> returnProcessError(const QString &download, ProcessErrorStruct error)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(download) << QVariant::fromValue(error);
        return asyncCallWithArgumentList(QLatin1String("returnProcessError"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace canonical {
    namespace applications {
      namespace testing {
        typedef ::TestingInterface DownloadManager;
      }
    }
  }
}
#endif