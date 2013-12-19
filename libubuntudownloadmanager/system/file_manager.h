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

#ifndef DOWNLOADER_LIB_FILE_MANAGER_H
#define DOWNLOADER_LIB_FILE_MANAGER_H

#include <QIODevice>
#include <QFile>
#include <QMutex>
#include <QObject>

namespace Ubuntu {

namespace DownloadManager {

namespace System {

class File : public QObject {
    Q_OBJECT

    // only allow the use of the file manager to create files
    friend class FileManager;
 public:
    virtual ~File();

    // wrappers around the used QFile methods
    void close();
    virtual QFile::FileError error() const;  // virtual for testing purposes
    QString fileName() const;
    virtual bool flush();  // virtual for testing purposes
    bool open(QIODevice::OpenMode mode);
    QByteArray readAll();
    bool remove();
    bool reset();
    qint64 size() const;
    qint64 write(const QByteArray& byteArray);

 protected:
    explicit File(const QString& name);

 private:
    QFile* _file = NULL;

};

class FileManager : public QObject {
    Q_OBJECT

 public:
    virtual File* createFile(const QString& name);
    virtual bool remove(const QString& path);
    virtual bool exists(const QString& path);

    static FileManager* instance();

    // only used for testing so that we can inject a fake
    static void setInstance(FileManager* instance);
    static void deleteInstance();

 protected:
    explicit FileManager(QObject *parent = 0) : QObject(parent) {}

 private:
    // used for the singleton
    static FileManager* _instance;
    static QMutex _mutex;

};

}  // System

}  // DownloadManager

}  // Ubuntu

#endif  // DOWNLOADER_LIB_FILE_MANAGER_H
