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

#include <QDBusError>
#include <ubuntu/download_manager/metatypes.h>
#include "error.h"

namespace {
    const QString DBUS_ERROR_STRING = "DBusError: %1 - %2";
    const QString AUTH_ERROR_STRING = "AuthError: %1 - %2";
    const QString HTTP_ERROR_STRING = "HttpError: %1 - %2";
    const QString NETWORK_ERROR_STRING = "NetworkError: %1 - %2";
    const QString PROCESS_ERROR_STRING = "ProcessError: %1 - %2\nExit code: %3\nStdout: %4\nStderr:%5";
}

namespace Ubuntu {

namespace DownloadManager {

/*
 * PRIMATE IMPLEMENTATIONS
 */

class ErrorPrivate {
    Q_DECLARE_PUBLIC(Error)

 public:
    ErrorPrivate(Error::Type type, Error* parent)
        : _type(type),
          q_ptr(parent) {
    }

    Error::Type type() {
        return _type;
    }

    QString errorString() {
        switch(_type) {
            case Error::DBus:
                return "DBusError";
            case Error::Http:
                return "HttpError";
            case Error::Network:
                return "NetworkError";
            case Error::Process:
                return "ProcessError";
            default:
                return "";
        }
    }

 private:
    Error::Type _type;
    Error* q_ptr;
};

class DBusErrorPrivate {
    Q_DECLARE_PUBLIC(DBusError)

 public:
    DBusErrorPrivate(QDBusError err, DBusError* parent)
        : _err(err),
          q_ptr(parent) {
    }

    inline QString message() {
        return _err.message();
    }

    inline QString name() {
        return _err.name();
    }

    inline QString errorString() {
        return DBUS_ERROR_STRING.arg(_err.name(), _err.message());
    }

 private:
    QDBusError _err;
    DBusError* q_ptr;
};

class AuthErrorPrivate {
    Q_DECLARE_PUBLIC(AuthError)

 public:
    AuthErrorPrivate(Errors::AuthErrorStruct err, AuthError* parent)
        : _err(err),
          q_ptr(parent) {
    }

    inline AuthError::Type type() {
        switch(_err.getType()) {
	    case Errors::AuthErrorStruct::Proxy:
                return AuthError::Proxy;
            default:
                return AuthError::Server;
        }
    }

    inline QString getTypeString() {
        switch(_err.getType()) {
            case Errors::AuthErrorStruct::Proxy:
                return "Proxy";
            default:
                return "Server";
        }
    }

    inline QString phrase() {
        return _err.getPhrase();
    }

    inline QString errorString() {
        return AUTH_ERROR_STRING.arg(getTypeString(), _err.getPhrase());
    }

 private:
    Errors::AuthErrorStruct _err;
    AuthError* q_ptr;
};

class HttpErrorPrivate {
    Q_DECLARE_PUBLIC(HttpError)

 public:
    HttpErrorPrivate(Errors::HttpErrorStruct err, HttpError* parent)
        : _err(err),
          q_ptr(parent) {
    }

    inline int code() {
        return _err.getCode();
    }

    inline QString phrase() {
        return _err.getPhrase();
    }

    inline QString errorString() {
        return HTTP_ERROR_STRING.arg(QString::number(_err.getCode()),
            _err.getPhrase());
    }

 private:
    Errors::HttpErrorStruct _err;
    HttpError* q_ptr;
};

class NetworkErrorPrivate {
    Q_DECLARE_PUBLIC(NetworkError)

 public:
    NetworkErrorPrivate(Errors::NetworkErrorStruct err, NetworkError* parent)
        : _err(err),
          q_ptr(parent) {
    }

    inline NetworkError::ErrorCode code() {
        auto intCode = static_cast<NetworkError::ErrorCode>(_err.getCode());
        return intCode;
    }

    inline QString phrase() {
        return _err.getPhrase();
    }

    inline QString errorString() {
        return NETWORK_ERROR_STRING.arg(QString::number(_err.getCode()),
            _err.getPhrase());
    }

 private:
    Errors::NetworkErrorStruct _err;
    NetworkError* q_ptr;
};

class ProcessErrorPrivate {
    Q_DECLARE_PUBLIC(ProcessError)

 public:
    ProcessErrorPrivate(Errors::ProcessErrorStruct err, ProcessError* parent)
        : _err(err),
          q_ptr(parent) {
    }

    QProcess::ProcessError code() {
        auto code = static_cast<QProcess::ProcessError>(_err.getCode());
        return code;
    }

    QString phrase() {
        return _err.getPhrase();
    }

    inline int exitCode() {
        return _err.getExitCode();
    }

    inline QString standardOut() {
        return _err.getStandardOutput();
    }

    inline QString standardError() {
        return _err.getStandardError();
    }

    inline QString errorString() {
        return PROCESS_ERROR_STRING.arg(QString::number(_err.getCode()),
            _err.getPhrase(), QString::number(_err.getExitCode()),
            _err.getStandardOutput(), _err.getStandardError());
    }

 private:
    Errors::ProcessErrorStruct _err;
    ProcessError* q_ptr;
};

/*
 * PUBLIC IMPLEMENTATIONS
 */

Error::Error(Error::Type type, QObject* parent)
    : QObject(parent),
      d_ptr(new ErrorPrivate(type, this)) {
}

Error::~Error() {
    delete d_ptr;
}

Error::Type
Error::type() {
    Q_D(Error);
    return d->type();
}

QString
Error::errorString() {
    Q_D(Error);
    return d->errorString();
}

DBusError::DBusError(QDBusError err, QObject* parent)
    : Error(Error::DBus, parent),
      d_ptr(new DBusErrorPrivate(err, this)) {
}

DBusError::~DBusError() {
    delete d_ptr;
}

QString
DBusError::message() {
    Q_D(DBusError);
    return d->message();
}

QString
DBusError::name() {
    Q_D(DBusError);
    return d->name();
}

QString
DBusError::errorString() {
    Q_D(DBusError);
    return d->errorString();
}

AuthError::AuthError(Errors::AuthErrorStruct err, QObject* parent)
    : Error(Error::Auth, parent),
      d_ptr(new AuthErrorPrivate(err, this)) {
}

AuthError::~AuthError() {
    delete d_ptr;
}

AuthError::Type
AuthError::type() {
    Q_D(AuthError);
    return d->type();
}

QString
AuthError::phrase() {
    Q_D(AuthError);
    return d->phrase();
}

QString
AuthError::errorString() {
    Q_D(AuthError);
    return d->errorString();
}

HttpError::HttpError(Errors::HttpErrorStruct err, QObject* parent)
    : Error(Error::Http, parent),
      d_ptr(new HttpErrorPrivate(err, this)) {
}

HttpError::~HttpError() {
    delete d_ptr;
}

int
HttpError::code() {
    Q_D(HttpError);
    return d->code();
}

QString
HttpError::phrase() {
    Q_D(HttpError);
    return d->phrase();
}

QString
HttpError::errorString() {
    Q_D(HttpError);
    return d->errorString();
}

NetworkError::NetworkError(Errors::NetworkErrorStruct err, QObject* parent)
    : Error(Error::Network, parent),
      d_ptr(new NetworkErrorPrivate(err, this)) {
}

NetworkError::~NetworkError() {
    delete d_ptr;
}

NetworkError::ErrorCode
NetworkError::code() {
    Q_D(NetworkError);
    return d->code();
}

QString
NetworkError::phrase() {
    Q_D(NetworkError);
    return d->phrase();
}

QString
NetworkError::errorString() {
    Q_D(NetworkError);
    return d->errorString();
}

ProcessError::ProcessError(Errors::ProcessErrorStruct err, QObject* parent)
    : Error(Error::Process, parent),
      d_ptr(new ProcessErrorPrivate(err, this)) {
}

ProcessError::~ProcessError() {
    delete d_ptr;
}

QString
ProcessError::phrase() {
    Q_D(ProcessError);
    return d->phrase();
}

QProcess::ProcessError
ProcessError::code() {
    Q_D(ProcessError);
    return d->code();
}

int
ProcessError::exitCode() {
    Q_D(ProcessError);
    return d->exitCode();
}

QString
ProcessError::standardOut() {
    Q_D(ProcessError);
    return d->standardOut();
}

QString
ProcessError::standardError() {
    Q_D(ProcessError);
    return d->standardError();
}

QString
ProcessError::errorString() {
    Q_D(ProcessError);
    return d->errorString();
}

}  // DownloadManager

}  // Ubuntu
