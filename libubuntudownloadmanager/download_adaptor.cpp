/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DownloadAdaptor -a download_adaptor.h:download_adaptor.cpp com.canonical.applications.download.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "download_adaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class DownloadAdaptor
 */

DownloadAdaptor::DownloadAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DownloadAdaptor::~DownloadAdaptor()
{
    // destructor
}

void DownloadAdaptor::cancel()
{
    // handle method call com.canonical.applications.Download.cancel
    QMetaObject::invokeMethod(parent(), "cancel");
}

QVariantMap DownloadAdaptor::metadata()
{
    // handle method call com.canonical.applications.Download.metadata
    QVariantMap data;
    QMetaObject::invokeMethod(parent(), "metadata", Q_RETURN_ARG(QVariantMap, data));
    return data;
}

void DownloadAdaptor::pause()
{
    // handle method call com.canonical.applications.Download.pause
    QMetaObject::invokeMethod(parent(), "pause");
}

uint DownloadAdaptor::progress()
{
    // handle method call com.canonical.applications.Download.progress
    uint received;
    QMetaObject::invokeMethod(parent(), "progress", Q_RETURN_ARG(uint, received));
    return received;
}

void DownloadAdaptor::resume()
{
    // handle method call com.canonical.applications.Download.resume
    QMetaObject::invokeMethod(parent(), "resume");
}

void DownloadAdaptor::setThrottle(uint speed)
{
    // handle method call com.canonical.applications.Download.setThrottle
    QMetaObject::invokeMethod(parent(), "setThrottle", Q_ARG(uint, speed));
}

void DownloadAdaptor::start()
{
    // handle method call com.canonical.applications.Download.start
    QMetaObject::invokeMethod(parent(), "start");
}

uint DownloadAdaptor::throttle()
{
    // handle method call com.canonical.applications.Download.throttle
    uint speed;
    QMetaObject::invokeMethod(parent(), "throttle", Q_RETURN_ARG(uint, speed));
    return speed;
}

uint DownloadAdaptor::totalSize()
{
    // handle method call com.canonical.applications.Download.totalSize
    uint total;
    QMetaObject::invokeMethod(parent(), "totalSize", Q_RETURN_ARG(uint, total));
    return total;
}

