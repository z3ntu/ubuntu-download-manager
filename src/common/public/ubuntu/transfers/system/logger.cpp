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

#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QDBusError>
#include <QMap>
#include <QStandardPaths>
#include <QStringList>
#include <QUrl>
#include <QVariantMap>
#include <QSslError>
#include <sys/types.h>
#include <unistd.h>
#include "logger.h"

std::ostream& operator<<(std::ostream &out, const QString& var) {
    out << " " << qPrintable(var);
    return out;
}

std::ostream& operator<<(std::ostream &out, const QByteArray& var) {
    out << " " << qPrintable(var);
    return out;
}

std::ostream& operator<<(std::ostream &out, const QStringList& var) {
    auto joined = var.join(" ");
    out << qPrintable(joined);
    return out;
}

std::ostream& operator<<(std::ostream &out, const QUrl& var) {
    out << " " << qPrintable(var.toString());
    return out;
}

std::ostream& operator<<(std::ostream &out, const QList<QSslError>& errors) {
    foreach(QSslError err, errors) {
        out << " " << err.errorString();
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, const QDBusError& error) {
    out << " " << qPrintable(error.name())
        << ":" << qPrintable(error.message());
    return out;
}

std::ostream& operator<<(std::ostream &out, const QVariantMap& map) {
    out << "{";
    foreach(const QString& key, map.keys()) {
            out << key << ":" << map[key].toString();
    }
    out << "}";
    return out;
}

std::ostream& operator<<(std::ostream &out, const QMap<QString, QString>& map) {
    out << "{";
    foreach(const QString& key, map.keys()) {
            out << key << ":" << map[key];
    }
    out << "}";
    return out;
}

std::ostream& operator<<(std::ostream &out, const QList<QByteArray>& strs) {
    foreach(QByteArray str, strs) {
        out << " " << QString(str).toStdString();
    }
    return out;
}

namespace {
    const QString LOG_NAME = QCoreApplication::instance()->applicationName() + ".log";
}

namespace Ubuntu {

namespace Transfers {

namespace System {

static bool _init = false;

void
Logger::setupLogging(const QString logDir) {
    auto path = logDir;
    QDir *dir;
    if (path == "" ){
        path = getLogDir() + QDir::separator() + LOG_NAME;
        dir = new QDir(getLogDir());
    } else {
        bool wasCreated = QDir().mkpath(logDir);
        if (wasCreated) {
            path = QDir(logDir).absoluteFilePath(LOG_NAME);
            dir = new QDir(logDir);
        } else {
            qCritical() << "Could not create the logging path" << logDir;
            path = getLogDir() + QDir::separator() + LOG_NAME;
            dir = new QDir(getLogDir());
        }
    }

    // Only keep the last 100 most recent logs
    QStringList nameFilter;
    nameFilter << LOG_NAME + "*";
    QStringList logFiles = dir->entryList(nameFilter, QDir::Files | QDir::Hidden | QDir::Writable, QDir::Time);
    for (int i = 99; i < logFiles.count(); i++) {
        QFile logFile(dir->absoluteFilePath(logFiles[i]));
        logFile.remove();
    }

    auto appName = QCoreApplication::instance()->applicationName();

    if (!_init) {
        _init = true;
        google::InitGoogleLogging(toStdString(appName).c_str());
        google::SetLogDestination(google::ERROR, toStdString(path).c_str());
        google::SetLogDestination(google::WARNING, toStdString(path).c_str());
        google::SetLogDestination(google::INFO, toStdString(path).c_str());
        google::SetLogDestination(google::FATAL, toStdString(path).c_str());
    }
}

bool
Logger::setLogLevel(QtMsgType level) {
    Q_UNUSED(level);
    return false;
}

QString
Logger::getLogDir() {
    QString path = ""; 
    if (getuid() == 0) {
        path = "/var/log/" + QCoreApplication::instance()->applicationName();
    } else {
        path = QStandardPaths::writableLocation(
            QStandardPaths::CacheLocation);
    }
    qDebug() << "Logging dir is" << path;

    bool wasCreated = QDir().mkpath(path);
    if (!wasCreated) {
        qCritical() << "Could not create the logging path" << path;
    }
    return path;
}

std::string
Logger::toStdString(const QString& str) {
    std::string utf8_text = str.toUtf8().constData();
    return utf8_text;
}

}  // System

}  // Transfers

}  // Ubuntu
