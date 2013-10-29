/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DownloadManagerAdaptor -a download_manager_adaptor.h:download_manager_adaptor.cpp -i metatypes.h com.canonical.applications.download_manager.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DOWNLOAD_MANAGER_ADAPTOR_H_1379689315
#define DOWNLOAD_MANAGER_ADAPTOR_H_1379689315

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "metatypes.h"
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE


namespace Ubuntu {

namespace DownloadManager {

/*
 * Adaptor class for interface com.canonical.applications.DownloadManager
 */
class DownloadManagerAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.canonical.applications.DownloadManager")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.canonical.applications.DownloadManager\">\n"
"    <method name=\"createDownload\">\n"
"      <annotation value=\"DownloadStruct\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <arg direction=\"in\" type=\"(sssa{sv}a{ss})\" name=\"download\"/>\n"
"      <arg direction=\"out\" type=\"o\" name=\"downloadPath\"/>\n"
"    </method>\n"
"    <method name=\"createDownloadGroup\">\n"
"      <annotation value=\"StructList\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <annotation value=\"QVariantMap\" name=\"org.qtproject.QtDBus.QtTypeName.In3\"/>\n"
"      <annotation value=\"StringMap\" name=\"org.qtproject.QtDBus.QtTypeName.In4\"/>\n"
"      <arg direction=\"in\" type=\"a(sss)\" name=\"downloads\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"algorithm\"/>\n"
"      <arg direction=\"in\" type=\"b\" name=\"allowed3G\"/>\n"
"      <arg direction=\"in\" type=\"a{sv}\" name=\"metadata\"/>\n"
"      <arg direction=\"in\" type=\"a{ss}\" name=\"headers\"/>\n"
"      <arg direction=\"out\" type=\"o\" name=\"download\"/>\n"
"    </method>\n"
"    <method name=\"getAllDownloads\">\n"
"      <arg direction=\"out\" type=\"ao\" name=\"downloads\"/>\n"
"    </method>\n"
"    <method name=\"getAllDownloadsWithMetadata\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"name\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"value\"/>\n"
"      <arg direction=\"out\" type=\"ao\" name=\"downloads\"/>\n"
"    </method>\n"
"    <method name=\"setDefaultThrottle\">\n"
"      <arg direction=\"in\" type=\"t\" name=\"speed\"/>\n"
"    </method>\n"
"    <method name=\"defaultThrottle\">\n"
"      <arg direction=\"out\" type=\"t\" name=\"speed\"/>\n"
"    </method>\n"
"    <method name=\"allowGSMDownload\">\n"
"      <arg direction=\"in\" type=\"b\" name=\"allowed\"/>\n"
"    </method>\n"
"    <method name=\"isGSMDownloadAllowed\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"allowed\"/>\n"
"    </method>\n"
"    <method name=\"exit\"/>\n"
"    <signal name=\"downloadCreated\">\n"
"      <arg direction=\"out\" type=\"o\" name=\"path\"/>\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    DownloadManagerAdaptor(QObject *parent);
    virtual ~DownloadManagerAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void allowGSMDownload(bool allowed);
    QDBusObjectPath createDownload(DownloadStruct download);
    QDBusObjectPath createDownloadGroup(StructList downloads, const QString &algorithm, bool allowed3G, const QVariantMap &metadata, StringMap headers);
    qulonglong defaultThrottle();
    void exit();
    QList<QDBusObjectPath> getAllDownloads();
    QList<QDBusObjectPath> getAllDownloadsWithMetadata(const QString &name, const QString &value);
    bool isGSMDownloadAllowed();
    void setDefaultThrottle(qulonglong speed);
Q_SIGNALS: // SIGNALS
    void downloadCreated(const QDBusObjectPath &path);
};

}  // DownloadManager

}  // Ubuntu
#endif
