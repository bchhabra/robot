/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

#include <Arduino.h>
#include <unity.h>
#include "ActionList.h"
#include "ToneAction.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {, 
// // clean stuff up here
// }

bool f_executed, f2_executed = false;

void f() {
    f_executed = true;
}
void f2() {
    f2_executed = true;
}

void test_timed_action() {
    f_executed = false;

    actionList.addTimedAction(f, 2000);
    TEST_ASSERT_FALSE_MESSAGE(f_executed, "f() not yet executed");
    actionList.playNextAction();
    TEST_ASSERT_TRUE_MESSAGE(f_executed, "f() was executed");
    delay(1000);
    actionList.playNextAction();
    TEST_ASSERT_FALSE_MESSAGE(actionList.isEmpty(), "action not yet finished");
    delay(1001);
    actionList.playNextAction();
    TEST_ASSERT_TRUE_MESSAGE(actionList.isEmpty(), "action is finished");
}

void test_parallel_action() {
    f_executed = false;
    f2_executed = false;

    actionList.addTimedAction(f, 2000)->parallel = f2;
    TEST_ASSERT_FALSE_MESSAGE(f_executed, "f() not yet executed");
    TEST_ASSERT_FALSE_MESSAGE(f2_executed, "f2() not yet executed");
    actionList.playNextAction();
    TEST_ASSERT_TRUE_MESSAGE(f_executed, "f() was executed");
    TEST_ASSERT_TRUE_MESSAGE(f2_executed, "f2() was executed");
}

void test_tone_action() {
    f_executed = false;

    Action* action = new ToneAction(300, 100);
    actionList2.add(action);
    Action* timedAction = actionList2.addTimedAction(f, 200);
    TEST_ASSERT_FALSE_MESSAGE(f_executed, "f() not yet executed");
    TEST_ASSERT_FALSE_MESSAGE(action->isStarted(), "action not yet started");
    actionList2.playNextAction();
    TEST_ASSERT_TRUE_MESSAGE(action->isStarted() && !action->isFinished(), "action is in progress");
    delay(200);
    TEST_ASSERT_TRUE_MESSAGE(action->isFinished(), "action is finished");
    actionList2.playNextAction();
    TEST_ASSERT_TRUE_MESSAGE(timedAction->isStarted(), "timed action has started");
    delay(201);
    TEST_ASSERT_TRUE_MESSAGE(timedAction->isFinished(), "timed action is finished");
    TEST_ASSERT_TRUE_MESSAGE(f_executed, "f() was executed");
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_timed_action);
    RUN_TEST(test_parallel_action);
    RUN_TEST(test_tone_action);
    UNITY_END();
}

void loop() {
}