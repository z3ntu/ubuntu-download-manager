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

#include <ubuntu/transfers/system/logger.h>
#include "network_reply.h"

namespace Ubuntu {

namespace Transfers {

namespace System {

NetworkReply::NetworkReply(QNetworkReply* reply, QObject* parent)
    : QObject(parent),
      _reply(reply) {
    // connect to all the signals so that we forward them
    if (_reply != nullptr) {
        connect(_reply, &QNetworkReply::downloadProgress,
            this, &NetworkReply::downloadProgress);
        connect(_reply, &QNetworkReply::uploadProgress,
            this, &NetworkReply::uploadProgress);
        connect(_reply, &QNetworkReply::finished,
            this, &NetworkReply::finished);
        connect(_reply, &QNetworkReply::sslErrors,
            this, &NetworkReply::sslErrors);
	// because error is overloaded we need to help the compiler
	connect(_reply, static_cast<void(QNetworkReply::*)
	    (QNetworkReply::NetworkError)>(&QNetworkReply::error),
		this, &NetworkReply::error);
    }
}

NetworkReply::~NetworkReply() {
    _reply->deleteLater();
}

QByteArray
NetworkReply::readAll() {
    return _reply->readAll();
}

void
NetworkReply::abort() {
    _reply->abort();
}

void
NetworkReply::setReadBufferSize(uint size) {
    _reply->setReadBufferSize(size);
}

void
NetworkReply::setAcceptedCertificates(const QList<QSslCertificate>& certs) {
    _certs = certs;
    // build possible errors
    foreach(const QSslCertificate& certificate, _certs) {
        QSslError error(QSslError::SelfSignedCertificate, certificate);
        _sslErrors.append(error);
    }
}

bool
NetworkReply::canIgnoreSslErrors(const QList<QSslError>& errors) {
    if (_sslErrors.count() > 0 && errors.count() > 0) {
        foreach(QSslError error, errors) {
            QSslError::SslError type = error.error();
            if (type != QSslError::NoError &&
                type != QSslError::SelfSignedCertificate) {
                // we only support self signed certificates all errors
                // will not be ignored
                LOG(INFO) << "SSL error type not ignored";
                return false;
            } else if (type == QSslError::SelfSignedCertificate) {
                // just ignore those errors of the added errors
                if (!_certs.contains(error.certificate())) {
                    LOG(INFO) << "SSL certificate not ignored";
                    return false;
                }
            }
        }

        if (_reply != nullptr) {
            _reply->ignoreSslErrors(_sslErrors);
        }

        return true;
    }
    return false;
}

QVariant
NetworkReply::attribute(QNetworkRequest::Attribute code) const {
    return _reply->attribute(code);
}

QString
NetworkReply::errorString() const {
    return _reply->errorString();
}

}  // System

}  // Transfers

}  // Ubuntu
