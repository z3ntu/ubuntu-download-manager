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

#include <QSignalSpy>
#include "test_download_watch.h"

TestDownloadWatch::TestDownloadWatch(QObject *parent)
    : DaemonTestCase("TestDownloadWatch", parent) {
}

void
TestDownloadWatch::onSuccessCb(Download* down) {
    delete down;
}

void
TestDownloadWatch::onErrorCb(Error* err) {
    delete err;
}

void
TestDownloadWatch::init() {
    DaemonTestCase::init();
    _calledSuccess = false;
    _calledError = false;
    _manager = Manager::createSessionManager(daemonPath(), this);
}

void
TestDownloadWatch::cleanup() {
    DaemonTestCase::cleanup();
    delete _manager;
}

void
TestDownloadWatch::testCallbackIsExecuted() {
    QString url = "http://www.python.org/ftp/python/3.3.3/Python-3.3.3.tar.xz";
    QVariantMap metadata;
    QMap<QString, QString> headers;
    DownloadStruct down(url, metadata, headers);

    DownloadCreationCb cb = std::bind(&TestDownloadWatch::onSuccessCb, this,
        std::placeholders::_1);
    ErrorCb errCb = std::bind(&TestDownloadWatch::onErrorCb, this,
        std::placeholders::_1);

    QSignalSpy spy(_manager, SIGNAL(downloadCreated(Download*)));
    _manager->createDownload(down, cb, errCb);

    QTRY_COMPARE(spy.count(), 1);
    QVERIFY(_calledSuccess);
    QVERIFY(!_calledError);
}

void
TestDownloadWatch::testErrCallbackIsExecuted() {
    QString url = "";  // we should get an error with an empty string
    QVariantMap metadata;
    QMap<QString, QString> headers;
    DownloadStruct down(url, metadata, headers);

    DownloadCreationCb cb = std::bind(&TestDownloadWatch::onSuccessCb, this,
        std::placeholders::_1);
    ErrorCb errCb = std::bind(&TestDownloadWatch::onErrorCb, this,
        std::placeholders::_1);

    _manager->createDownload(down, cb, errCb);
    QVERIFY(!_calledSuccess);
    QVERIFY(_calledError);
}
