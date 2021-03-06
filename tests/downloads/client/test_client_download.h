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

#pragma once

#include <QObject>
#include <ubuntu/download_manager/manager.h>
#include <ubuntu/download_manager/download.h>
#include "local_tree_testcase.h"

using namespace Ubuntu::DownloadManager;

class TestDownload : public LocalTreeTestCase {
    Q_OBJECT

 public:
    explicit TestDownload(QObject *parent = 0);

 private slots:  // NOLINT(whitespace/indent)

    void init() override;
    void cleanup() override;
    void testAllowMobileDownload_data();
    void testAllowMobileDownload();
    void testAllowMobileDownloadError();
    void testSetThrottle_data();
    void testSetThrottle();
    void testSetThrottleError();
    void testHeaders();
    void testHeadersError();
    void testSetHeaders_data();
    void testSetHeaders();
    void testSetHeadersError();
    void testMetadata();
    void testMetadataError();
    void testSetMetadata_data();
    void testSetMetadata();
    void testProgressError();
    void testTotalSizeError();
    void testAuthErrorRaised_data();
    void testAuthErrorRaised();
    void testHttpErrorRaised_data();
    void testHttpErrorRaised();
    void testNetworkErroRaised_data();
    void testNetworkErroRaised();
    void testProcessErrorRaised_data();
    void testProcessErrorRaised();
    void testHashErrorRaised_data();
    void testHashErrorRaised();

    // set local dir tests
    void testSetLocalDirectory();
    void testSetLocalDirectoryNotAbsolute();
    void testSetLocalDirectoryNotPresent();
    void testSetLocalDirectoryNotDir();
    void testSetLocalDirectoryStarted();

 private:
    QString _url;
    QVariantMap _metadata;
    QMap<QString, QString> _headers;
    Manager* _man = nullptr;
    Download* _down = nullptr;
};

