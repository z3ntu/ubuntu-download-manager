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

#include "dbus_connection.h"

namespace Ubuntu {

namespace Transfers {

namespace System {

DBusConnection* DBusConnection::_instance = nullptr;
QMutex DBusConnection::_mutex;

DBusConnection::DBusConnection(QObject* parent)
    : DBusConnection(
         QDBusConnection::connectToBus(QDBusConnection::ActivationBus, "DBUS"),
         parent) {
}

DBusConnection::DBusConnection(QDBusConnection conn, QObject* parent)
    : QObject(parent),
      _conn(conn) {
}

bool
DBusConnection::registerService(const QString& serviceName) {
    return _conn.registerService(serviceName);
}

bool
DBusConnection::unregisterService(const QString& serviceName) {
    return _conn.unregisterService(serviceName);
}

bool
DBusConnection::registerObject(const QString& path,
                    QObject* object,
                    QDBusConnection::RegisterOptions options) {
    return _conn.registerObject(path, object, options);
}

void
DBusConnection::unregisterObject(const QString& path,
                      QDBusConnection::UnregisterMode mode) {
    return _conn.unregisterObject(path, mode);
}

bool
DBusConnection::send(const QDBusMessage& message) const {
    return _conn.send(message);
}

QDBusConnection
DBusConnection::connection() {
    return _conn;
}

DBusConnection*
DBusConnection::instance() {
    return instance(
        QDBusConnection::connectToBus(QDBusConnection::ActivationBus, "DBUS")
    );
}

DBusConnection*
DBusConnection::instance(QDBusConnection conn) {
    if(_instance == nullptr) {
        _mutex.lock();
        if(_instance == nullptr)
            _instance = new DBusConnection(conn);
        _mutex.unlock();
    }
    return _instance;
}

void
DBusConnection::setInstance(DBusConnection* instance) {
    _instance = instance;
}

void
DBusConnection::deleteInstance() {
    if(_instance != nullptr) {
        _mutex.lock();
        if(_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
        _mutex.unlock();
    }
}

}  // System

}  // Transfers

}  // Ubuntu
