/*
 * Copyright 2014-2015 Canonical Ltd.
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

#include <QDBusArgument>
#include "http_error_struct.h"

namespace Ubuntu {

namespace Transfers {

namespace Errors {

HttpErrorStruct::HttpErrorStruct()
    : _code(200),
      _phrase("OK"){
}

HttpErrorStruct::HttpErrorStruct(int code, const QString& phrase)
    : _code(code),
      _phrase(phrase) {
}

HttpErrorStruct::HttpErrorStruct(const HttpErrorStruct& other)
    : _code(other._code),
      _phrase(other._phrase) {
}

HttpErrorStruct& HttpErrorStruct::operator=(const HttpErrorStruct& other) {
    _code = other._code;
    _phrase = other._phrase;

    return *this;
}

QDBusArgument &operator<<(QDBusArgument &argument,
                          const HttpErrorStruct& error) {
    argument.beginStructure();
    argument << error._code;
    argument << error._phrase;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument,
                          HttpErrorStruct& error) {
    argument.beginStructure();
    argument >> error._code;
    argument >> error._phrase;
    argument.endStructure();

    return argument;
}

int
HttpErrorStruct::getCode() const {
    return _code;
}

QString
HttpErrorStruct::getPhrase() const {
    return _phrase;
}

}  // Errors

}  // Transfers

}  // Ubuntu
