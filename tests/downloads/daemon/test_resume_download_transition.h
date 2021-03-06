/*
 * Copyright 2013-2014 Canonical Ltd.
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

#ifndef TEST_RESUME_DOWNLOAD_TRANSITION_H
#define TEST_RESUME_DOWNLOAD_TRANSITION_H

#include <QFinalState>
#include <QObject>
#include <QState>
#include <QStateMachine>
#include <ubuntu/downloads/state_machines/download_sm.h>
#include "base_testcase.h"
#include "sm_file_download.h"

using namespace Ubuntu::DownloadManager::Daemon::StateMachines;

class TestResumeDownloadTransition : public BaseTestCase {
    Q_OBJECT
 public:
    explicit TestResumeDownloadTransition(QObject *parent = 0)
        : BaseTestCase("TestResumeDownloadTransition", parent) {}

 private slots:  // NOLINT(whitespace/indent)

    void init() override;
    void cleanup() override;
    void testOnTransition();

 private:
    QStateMachine _stateMachine;
    MockSMFileDownload* _down;
    ResumeDownloadTransition* _transition;
    QState* _s1;
    QFinalState* _s2;
};

#endif // TEST_RESUME_DOWNLOAD_TRANSITION_H
