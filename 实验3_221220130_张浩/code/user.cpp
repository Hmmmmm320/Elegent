/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "./user.h"

void User::addTask() {
    Task* task = new Task(++taskCount);  // 新建一个任务
    task->newTask();  // 设置任务各种信息
    tasks.push_back(task);  // 将新任务加入任务列表中
    Tline.addTask(task);  // 将新任务加入时间线视图中
    // 新建一个消息提醒
    Notification* n = new Notification(++notificationCount, task->taskId,
        task->description, task->deadline, task->reminderInterval);
    addNotification(n);  // 将新的消息提醒加入消息列表中
}

void User::changeNotification(Task* t) {
    auto iterator = this->userNotifications.begin();
    for (; iterator != userNotifications.end(); iterator++) {
        if ((*iterator)->taskId == t->taskId) {
            break;
        }
    }
    int num = (*iterator)->notificationId;
    free((*iterator));
    (*iterator) = new Notification(num, t->taskId, t->description,
                                   t->deadline, t->reminderInterval);
}

void User::deleteNotification(int id) {
    auto iterator = this->userNotifications.begin();
    for (; iterator != userNotifications.end(); iterator++) {
        if ((*iterator)->taskId == id) {
            break;
        }
    }
    (*iterator)->flag = 0;
    free((*iterator));
}

void User::editTask(int taskId) {
    auto iterator = this->tasks.begin();
    for (; iterator != tasks.end(); iterator++) {
        if ((*iterator)->taskId == taskId) {
            break;
        }
    }
    Task* task = (*iterator);
    int choice;
    cout << "请选择修改的内容（输入选项前的数字）：\n"
         << "0 退出， 1 任务标题， 2 任务详情， 3 截止时间，"
         << "4 提醒间隔， 5 类别， 6 优先级， 7 状态\n";
    cin >> choice;
    int flag = 1;
    while (choice != 0) {
        while (choice < 1 || choice > 7) {
            cout << "请选择正确的数字！\n";
            cin >> choice;
        }
        string s;
        switch (choice) {
            case 1:
                cout << "请输入标题（输入EXIT可以退出）：";
                // cin >> s;
                getchar();
                getline(cin, s);
                if (s == "EXIT")
                    {flag = 0; break;}
                while (s.size() == 0 || s[0] == ' ' || s[0] == '\n') {
                    cout << "标题不能为空！请重新输入：";
                    // cin >> s;
                    getline(cin, s);
                    if (s == "EXIT")
                        {flag = 0; break;}
                }
                if (flag != 0)
                    task->title = s;
                break;
            case 2:
                cout << "请输入任务详情（输入EXIT可以退出）：";
                // cin >> s;
                getchar();
                getline(cin, s);
                if (s == "EXIT")
                    {flag = 0; break;}
                task->description = s;
                break;
            case 3:
                task->updateDeadline();
                break;
            case 4:
                task->updateReminderInterval();
                break;
            case 5:
                task->updateCategory();
                break;
            case 6:
                task->updatePriority();
                break;
            case 7:
                task->updateStatus();
                break;
        }
        cout << "请选择修改的内容（输入选项前的数字）：\n"
             << "0 退出， 1 任务标题， 2 任务详情， 3 截止时间， "
             << "4 提醒间隔， 5 类别， 6 优先级， 7 状态\n";
        cin >> choice;
    }
    if (flag) {
        this->Tline.removeTask(task->taskId);
        this->Tline.addTask(task);
    }
    changeNotification(task);
}

void User::deleteTask(int taskId) {
    int fflag = 0;
    // 查找任务
    for (auto iterator = tasks.begin(); iterator != tasks.end(); iterator++) {
        if ((*iterator)->taskId == taskId) {
            fflag = 1;
            break;
        }
    }
    if (fflag == 0) {
        cout << "没有这个任务哦！重新选择一下吧！\n";
        return;
    }
    // 删除任务
    tasks.erase(remove_if(tasks.begin(), tasks.end(),
                 [taskId](Task* task) { return task->taskId == taskId; }),
                 tasks.end());
    Tline.tasks.erase(remove_if(Tline.tasks.begin(), Tline.tasks.end(),
                 [taskId](Task* task) { return task->taskId == taskId; }),
                 Tline.tasks.end());
    deleteNotification(taskId);
}

void User::addNotification(Notification* n) {
    userNotifications.push_back(n);
}

void User::listTasks() const {
    if (taskCount == 0) {
        cout << "当前还没有任务哦！快来创建任务吧！\n";
        return;
    }
    for (int i = 0; i < 20; i++)
        cout << "***";
    cout << "\n";
    for (const auto& task : tasks) {
        task->displayTask();
    }
}

void User::TimeList() {
    if (taskCount == 0) {
        cout << "当前还没有任务哦！快来创建任务吧！\n";
        return;
    }
    for (int i = 0; i < 20; i++)
        cout << "***";
    cout << "\n";
    this->Tline.showTask();
}

void User::listNotifications() {
    if (this->userNotifications.size() == 0) {
        return;
    }
    // 计算当前时间和DDL的间隔
    chrono::system_clock::time_point current_time = chrono::system_clock::now();
    vector<Notification*>* UN = &userNotifications;
    for (auto iterator = (*UN).begin(); iterator != (*UN).end(); iterator++) {
        chrono::minutes interval = chrono::duration_cast<chrono::minutes>((*iterator)->time.time_since_epoch()) - chrono::duration_cast<chrono::minutes>(current_time.time_since_epoch());
        // 判断是否需要发出消息
        if ((*iterator)->flag && interval.count() <= (*iterator)->reminderInterval) {
            // 发出通知
            (*iterator)->sendNotification();
            deleteNotification((*iterator)->taskId);
        }
    }
}
