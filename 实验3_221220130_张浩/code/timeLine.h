#ifndef _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TIMELINE_H_
#define _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TIMELINE_H_
/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "./task.h"

class Timeline {
 private:
    vector<Task*> tasks;

 public:
    friend class User;

    void addTask(Task* task) {
        tasks.push_back(task);
    }

    void removeTask(int taskId);

    void getTasksSortedByDeadline();

    void showTask();
};

#endif  // _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TIMELINE_H_
