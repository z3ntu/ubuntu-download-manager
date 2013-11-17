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

#ifndef FAKE_H
#define FAKE_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QUuid>
#include <QStringList>
#include <string>


class BoolWrapper : public QObject {
    Q_OBJECT

 public:
    BoolWrapper(bool value, QObject* parent = 0);

    bool value();
    void setValue(bool value);

 private:
    bool _value;
};

class StringWrapper : public QObject {
    Q_OBJECT

 public:
    StringWrapper(const QString& string, QObject* parent = 0);

    QString value();
    void setValue(const QString& value);

 private:
    QString _value;
};


class StringListWrapper : public QObject {
    Q_OBJECT

 public:
    StringListWrapper(const QStringList& list, QObject* parent = 0);

    QStringList value();
    void setValue(const QStringList& value);

 private:
    QStringList _value;
};

class IntWrapper : public QObject {
    Q_OBJECT

 public:
    IntWrapper(int value, QObject* parent = 0);

    int value();
    void setValue(int value);

 private:
    int _value;
};

class UintWrapper : public QObject {
    Q_OBJECT

 public:
    UintWrapper(uint value, QObject* parent = 0);

    uint value();
    void setValue(uint value);

 private:
    uint _value;
};

class UuidWrapper : public QObject {
 public:
    UuidWrapper(QUuid value, QObject* parent = 0);

    QUuid value();
    void setValue(QUuid value);

 private:
    QUuid _value;
};

class MethodParams : public QPair<QList<QObject*>, QList<QObject*> > {
 public:
    explicit MethodParams();
    explicit MethodParams(QList<QObject*> inParams, QList<QObject*> outParams);

    QList<QObject*> inParams();
    void setInParams(QList<QObject*> params);

    QList<QObject*> outParams();
    void setOutParams(QList<QObject*> params);
};

class MethodData : public QPair<QString, MethodParams> {
 public:
    explicit MethodData();
    explicit MethodData(const QString& name, const MethodParams& params);

    QString methodName();
    void setMethodName(const QString& name);

    MethodParams params();
    void setParams(const MethodParams& params);
};

class Fake {
 public:
    explicit Fake();

    void record();
    void stopRecording();
    void clear();
    QList<MethodData> calledMethods();

 protected:
    bool _recording;
    QList<MethodData> _called;
};

#endif  // FAKE_H