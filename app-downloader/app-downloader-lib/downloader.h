#ifndef APP_DOWNLOADER_LIB_DOWNLOADER_H
#define APP_DOWNLOADER_LIB_DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusObjectPath>
#include "app_download.h"

class DownloaderPrivate;
class Downloader : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Downloader)
public:
    explicit Downloader(QDBusConnection connection, QObject *parent = 0);


public slots:
    QDBusObjectPath createDownload(const QString &url);
    QDBusObjectPath createDownloadWithHash(const QString &url, const QString &algorithm, const QString &hash);
    QList<QDBusObjectPath> getAllDownloads();

Q_SIGNALS:
    void downloadCreated(const QDBusObjectPath &path);
    void downloads(const QList<QDBusObjectPath> &downloads);

private:
    Q_PRIVATE_SLOT(d_func(), void onDownloadStateChanged())

private:
    // use pimpl so that we can mantains ABI compatibility
    DownloaderPrivate* d_ptr;
};

#endif // DOWNLOADER_H
