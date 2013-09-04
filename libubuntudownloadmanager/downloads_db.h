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

#ifndef DOWNLOADER_LIB_DOWNLOADS_DATABASE_H
#define DOWNLOADER_LIB_DOWNLOADS_DATABASE_H

#include <QSqlDatabase>
#include <QObject>
#include "./file_manager.h"

class DownloadsDbPrivate;
class DownloadsDb : public QObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DownloadsDb)

 public:
    explicit DownloadsDb(QObject *parent = 0);
    DownloadsDb(FileManager* fileManager, QObject *parent = 0);

    QSqlDatabase db();
    QString filename();
    bool dbExists();  // return if the db is present and valid
    bool init();  // init or update the db

 private:
    // use pimpl so that we can mantains ABI compatibility
    DownloadsDbPrivate* d_ptr;
};

#endif  // DOWNLOADER_LIB_DOWNLOADS_DATABASE_H