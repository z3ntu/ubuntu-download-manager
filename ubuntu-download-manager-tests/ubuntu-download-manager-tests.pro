include( ../common-project-config.pri )
include( ../common-vars.pri )

QT       += network core testlib dbus systeminfo sql

QT       -= gui

TARGET = ubuntu-download-manager-tests
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    downloads/test_download.cpp \
    downloads/test_daemon.cpp \
    downloads/test_download_manager.cpp \
    downloads/test_download_queue.cpp \
    downloads/test_group_download.cpp \
    downloads/test_downloads_db.cpp \
    downloads/test_download_factory.cpp \
    main.cpp \
    downloads/state_machines/test_network_error_transition.cpp \
    downloads/state_machines/test_ssl_error_transition.cpp \
    downloads/state_machines/test_start_download_transition.cpp \
    downloads/state_machines/test_stop_request_transition.cpp \
    downloads/state_machines/test_cancel_download_transition.cpp \
    downloads/state_machines/test_resume_download_transition.cpp \
    downloads/state_machines/test_final_state.cpp \
    downloads/state_machines/test_file_download_sm.cpp \
    system/test_apn_request_factory.cpp \
    downloads/test_mms_download.cpp \
    downloads/test_base_download.cpp

HEADERS += \
    downloads/test_download.h \
    downloads/test_daemon.h \
    downloads/test_download_manager.h \
    downloads/test_download_queue.h \
    downloads/test_group_download.h \
    downloads/test_downloads_db.h \
    downloads/test_download_factory.h \
    downloads/state_machines/test_network_error_transition.h \
    downloads/state_machines/test_ssl_error_transition.h \
    downloads/state_machines/test_start_download_transition.h \
    downloads/state_machines/test_stop_request_transition.h \
    downloads/state_machines/test_cancel_download_transition.h \
    downloads/state_machines/test_resume_download_transition.h \
    downloads/state_machines/test_final_state.h \
    downloads/state_machines/test_file_download_sm.h \
    system/test_apn_request_factory.h \
    downloads/test_mms_download.h \
    downloads/test_base_download.h

LIBS += -L$$OUT_PWD/../ubuntu-download-manager-priv/ -lubuntu-download-manager-priv

INCLUDEPATH += $$PWD/../ubuntu-download-manager-priv
DEPENDPATH += $$PWD/../ubuntu-download-manager-priv

LIBS += -L$$OUT_PWD/../ubuntu-download-manager-common/ -lubuntu-download-manager-common

INCLUDEPATH += $$PWD/../ubuntu-download-manager-common
DEPENDPATH += $$PWD/../ubuntu-udownload-manager-common

LIBS += -L$$OUT_PWD/../ubuntu-download-manager-test-lib/ -lubuntu-download-manager-test-lib

INCLUDEPATH += $$PWD/../ubuntu-download-manager-test-lib
DEPENDPATH += $$PWD/../ubuntu-download-manager-test-lib

check.depends = $${TARGET}
check.commands = LD_LIBRARY_PATH=$$OUT_PWD/../ubuntu-download-manager-common:$$OUT_PWD/../ubuntu-download-manager-priv:$$OUT_PWD/../ubuntu-download-manager-test-lib ./$${TARGET}
QMAKE_EXTRA_TARGETS += check
