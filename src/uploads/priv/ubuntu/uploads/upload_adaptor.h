/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c UploadAdaptor -a upload_adaptor.h:upload_adaptor.cpp com.canonical.applications.upload.xml
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef UPLOAD_ADAPTOR_H_1405435125
#define UPLOAD_ADAPTOR_H_1405435125

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include <ubuntu/upload_manager/metatypes.h>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

namespace Ubuntu {

using namespace Transfers::Errors;

namespace UploadManager {

/*
 * Adaptor class for interface com.canonical.applications.Upload
 */
class UploadAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.canonical.applications.Upload")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.canonical.applications.Upload\">\n"
"    <method name=\"progress\">\n"
"      <arg direction=\"out\" type=\"t\" name=\"uploaded\"/>\n"
"    </method>\n"
"    <method name=\"metadata\">\n"
"      <annotation value=\"QVariantMap\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
"      <arg direction=\"out\" type=\"a{sv}\" name=\"data\"/>\n"
"    </method>\n"
"    <method name=\"setThrottle\">\n"
"      <arg direction=\"in\" type=\"t\" name=\"speed\"/>\n"
"    </method>\n"
"    <method name=\"throttle\">\n"
"      <arg direction=\"out\" type=\"t\" name=\"speed\"/>\n"
"    </method>\n"
"    <method name=\"allowMobileUpload\">\n"
"      <arg direction=\"in\" type=\"b\" name=\"allowed\"/>\n"
"    </method>\n"
"    <method name=\"isMobileUploadAllowed\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"allowed\"/>\n"
"    </method>\n"
"    <method name=\"start\"/>\n"
"    <method name=\"cancel\"/>\n"
"    <signal name=\"started\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"success\"/>\n"
"    </signal>\n"
"    <signal name=\"canceled\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"success\"/>\n"
"    </signal>\n"
"    <signal name=\"finished\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"path\"/>\n"
"    </signal>\n"
"    <signal name=\"error\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"error\"/>\n"
"    </signal>\n"
"    <signal name=\"authError\">\n"
"      <annotation value=\"AuthErrorStruct\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <arg direction=\"out\" type=\"(is)\" name=\"error\"/>\n"
"    </signal>\n"
"    <signal name=\"httpError\">\n"
"      <annotation value=\"HttpErrorStruct\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <arg direction=\"out\" type=\"(is)\" name=\"error\"/>\n"
"    </signal>\n"
"    <signal name=\"networkError\">\n"
"      <annotation value=\"NetworkErrorStruct\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <arg direction=\"out\" type=\"(is)\" name=\"error\"/>\n"
"    </signal>\n"
"    <signal name=\"processError\">\n"
"      <annotation value=\"ProcessErrorStruct\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"      <arg direction=\"out\" type=\"(isiss)\" name=\"error\"/>\n"
"    </signal>\n"
"    <signal name=\"progress\">\n"
"      <arg direction=\"out\" type=\"t\" name=\"uploded\"/>\n"
"      <arg direction=\"out\" type=\"t\" name=\"total\"/>\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    UploadAdaptor(QObject *parent);
    virtual ~UploadAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void allowMobileUpload(bool allowed);
    void cancel();
    bool isMobileUploadAllowed();
    QVariantMap metadata();
    qulonglong progress();
    void setThrottle(qulonglong speed);
    void start();
    qulonglong throttle();
Q_SIGNALS: // SIGNALS
    void authError(AuthErrorStruct error);
    void canceled(bool success);
    void error(const QString &error);
    void finished(const QString &path);
    void httpError(HttpErrorStruct error);
    void networkError(NetworkErrorStruct error);
    void processError(ProcessErrorStruct error);
    void progress(qulonglong uploded, qulonglong total);
    void started(bool success);
};

}  // UploadManager

}  // Ubuntu
#endif
