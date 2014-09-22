/*
 * Copyright 2014 Canonical Ltd.
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

#include "test_metadata.h"

using namespace Ubuntu::Transfers;

void
TestMetadata::testCommnad_data() {
    QTest::addColumn<QString>("command");

    QTest::newRow("mkdir") << "mkdir test";
    QTest::newRow("cd") << "cd test";
    QTest::newRow("ls") << "ls -la";
}

void
TestMetadata::testCommnad() {
    QFETCH(QString, command);

    Metadata metadata;
    metadata[Metadata::COMMAND_KEY] = command;
    QCOMPARE(command, metadata.command());
}

void
TestMetadata::testSetCommnad_data() {
    QTest::addColumn<QString>("command");

    QTest::newRow("mkdir") << "mkdir test";
    QTest::newRow("cd") << "cd test";
    QTest::newRow("ls") << "ls -la";
}

void
TestMetadata::testSetCommnad() {
    QFETCH(QString, command);

    Metadata metadata;
    metadata.setCommand(command);
    QCOMPARE(metadata[Metadata::COMMAND_KEY].toString(), command);
}

void
TestMetadata::testHasCommnadTrue() {
    Metadata metadata;
    metadata.setCommand("command");

    QVERIFY(metadata.hasCommand());
}

void
TestMetadata::testHasCommnadFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasCommand());
}

void
TestMetadata::testLocalPath_data() {
    QTest::addColumn<QString>("path");

    QTest::newRow("/home/test") << "/home/test";
    QTest::newRow("second_file") << "second_file";
    QTest::newRow("/tmp/data") << "/tmp/data";
}

void
TestMetadata::testLocalPath() {
    QFETCH(QString, path);

    Metadata metadata;
    metadata[Metadata::LOCAL_PATH_KEY] = path;
    QCOMPARE(path, metadata.localPath());
}

void
TestMetadata::testSetLocalPath_data() {
    QTest::addColumn<QString>("path");

    QTest::newRow("/home/test") << "/home/test";
    QTest::newRow("second_file") << "second_file";
    QTest::newRow("/tmp/data") << "/tmp/data";
}

void
TestMetadata::testSetLocalPath() {
    QFETCH(QString, path);

    Metadata metadata;
    metadata.setLocalPath(path);
    QCOMPARE(metadata[Metadata::LOCAL_PATH_KEY].toString(), path);
}

void
TestMetadata::testHasLocalPathTrue() {
    Metadata metadata;
    metadata.setLocalPath("command");

    QVERIFY(metadata.hasLocalPath());
}

void
TestMetadata::testHashLocalPathFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasLocalPath());
}

void
TestMetadata::testObjectPath_data() {
    QTest::addColumn<QString>("objectPath");

    QTest::newRow("/com/canonica/si") << "/com/canonical/si";
    QTest::newRow("/com/testing") << "/com/testing";
    QTest::newRow("/com/data/download") << "/com/data/download";
}

void
TestMetadata::testObjectPath() {
    QFETCH(QString, objectPath);

    Metadata metadata;
    metadata[Metadata::OBJECT_PATH_KEY] = objectPath;
    QCOMPARE(objectPath, metadata.objectPath());
}

void
TestMetadata::testSetObjectPath_data() {
    QTest::addColumn<QString>("objectPath");

    QTest::newRow("/com/canonica/si") << "/com/canonical/si";
    QTest::newRow("/com/testing") << "/com/testing";
    QTest::newRow("/com/data/download") << "/com/data/download";
}

void
TestMetadata::testSetObjectPath() {
    QFETCH(QString, objectPath);

    Metadata metadata;
    metadata.setObjectPath(objectPath);
    QCOMPARE(metadata[Metadata::OBJECT_PATH_KEY].toString(), objectPath);
}

void
TestMetadata::testHasObjectPathTrue() {
    Metadata metadata;
    metadata.setObjectPath("command");

    QVERIFY(metadata.hasObjectPath());
}

void
TestMetadata::testHasObjectPathFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasObjectPath());
}

void
TestMetadata::testTitle_data() {
    QTest::addColumn<QString>("title");

    QTest::newRow("Profile image") << "Profile image";
    QTest::newRow("Americana.mp3") << "Americana.mp3";
    QTest::newRow("Test title") << "Test title";
}

void
TestMetadata::testTitle() {
    QFETCH(QString, title);

    Metadata metadata;
    metadata[Metadata::TITLE_KEY] = title;
    QCOMPARE(title, metadata.title());
}

void
TestMetadata::testSetTitle_data() {
    QTest::addColumn<QString>("title");

    QTest::newRow("Profile image") << "Profile image";
    QTest::newRow("Americana.mp3") << "Americana.mp3";
    QTest::newRow("Test title") << "Test title";
}

void
TestMetadata::testSetTitle() {
    QFETCH(QString, title);

    Metadata metadata;
    metadata.setTitle(title);
    QCOMPARE(metadata[Metadata::TITLE_KEY].toString(), title);
}

void
TestMetadata::testHasTitleTrue() {
    Metadata metadata;
    metadata.setTitle("tlte");

    QVERIFY(metadata.hasTitle());
}

void
TestMetadata::testHasTitleFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasTitle());
}

void
TestMetadata::testIndicator_data() {
    QTest::addColumn<bool>("show");

    QTest::newRow("True") << true;
    QTest::newRow("False") << false;
}

void
TestMetadata::testIndicator() {
    QFETCH(bool, show);

    Metadata metadata;
    metadata[Metadata::SHOW_IN_INDICATOR_KEY] = show;
    QCOMPARE(show, metadata.showInIndicator());
}

void
TestMetadata::testSetIndicator_data() {
    QTest::addColumn<bool>("show");

    QTest::newRow("True") << true;
    QTest::newRow("False") << false;
}

void
TestMetadata::testSetIndicator() {
    QFETCH(bool, show);

    Metadata metadata;
    metadata.setShowInIndicator(show);
    QCOMPARE(metadata[Metadata::SHOW_IN_INDICATOR_KEY].toBool(), show);
}

void
TestMetadata::testHasIndicatorTrue() {
    Metadata metadata;
    metadata.setShowInIndicator(true);

    QVERIFY(metadata.hasShowInIndicator());
}

void
TestMetadata::testHasIndicatorFasle() {
    Metadata metadata;
    QVERIFY(!metadata.hasShowInIndicator());
}

void
TestMetadata::testClick_data() {
    QTest::addColumn<QString>("click");

    QTest::newRow("My click") << "My click";
    QTest::newRow("Maps") << "Maps";
    QTest::newRow("Test") << "Test";
}

void
TestMetadata::testClick() {
    QFETCH(QString, click);

    Metadata metadata;
    metadata[Metadata::CLICK_PACKAGE_KEY] = click;
    QCOMPARE(click, metadata.clickPackage());
}

void
TestMetadata::testSetClick_data() {
    QTest::addColumn<QString>("click");

    QTest::newRow("My click") << "My click";
    QTest::newRow("Maps") << "Maps";
    QTest::newRow("Test") << "Test";
}

void
TestMetadata::testSetClick() {
    QFETCH(QString, click);

    Metadata metadata;
    metadata.setClickPackage(click);
    QCOMPARE(metadata[Metadata::CLICK_PACKAGE_KEY].toString(), click);
}

void
TestMetadata::testHasClickTrue() {
    Metadata metadata;
    metadata.setClickPackage("test");
    QVERIFY(metadata.hasClickPackage());
}

void
TestMetadata::testHasClickFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasClickPackage());
}

void
TestMetadata::testSetDeflate_data() {
    QTest::addColumn<bool>("deflate");

    QTest::newRow("True") << true;
    QTest::newRow("False") << false;
}

void
TestMetadata::testSetDeflate() {
    QFETCH(bool, deflate);

    Metadata metadata;
    metadata.setDeflate(deflate);
    QCOMPARE(metadata[Metadata::DEFLATE_KEY].toBool(), deflate);
}

void
TestMetadata::testHasDeflateTrue() {
    Metadata metadata;
    metadata.setDeflate(true);

    QVERIFY(metadata.hasDeflate());
}

void
TestMetadata::testHasDeflateFalse() {
    Metadata metadata;
    QVERIFY(!metadata.hasDeflate());
}

QTEST_MAIN(TestMetadata)
#include "moc_test_metadata.cpp"
