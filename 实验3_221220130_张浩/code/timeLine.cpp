/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "timeLine.h"

void Timeline::removeTask(int taskId) {
    for (auto iterator = tasks.begin(); iterator != tasks.end(); iterator++) {
        if ((*iterator)->getID() == taskId) {
            tasks.erase(iterator);
            break;
        }
    }
}

void Timeline::getTasksSortedByDeadline() {
    sort(tasks.begin(), tasks.end(),
                [](Task* a, Task* b) { return a->getDDL() < b->getDDL(); });
}

void Timeline::showTask() {
    getTasksSortedByDeadline();
    for (const auto& task : tasks) {
        task->displayTask();
    }
}
