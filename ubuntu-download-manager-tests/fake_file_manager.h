/*
 * Copyright 2013 2013 Canonical Ltd.
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

#ifndef FAKE_FILE_MANAGER_H
#define FAKE_FILE_MANAGER_H

#include <QObject>
#include <system/file_manager.h>
#include "fake.h"

using namespace Ubuntu::DownloadManager::System;

class FakeFileManager : public FileManager, public Fake {
    Q_OBJECT

 public:
    explicit FakeFileManager(QObject *parent = 0);

    bool remove(const QString& path) override;
};

#endif  // FAKE_FILE_MANAGER_H
