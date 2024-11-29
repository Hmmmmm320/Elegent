#ifndef _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____USER_H_
#define _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____USER_H_
/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "./timeLine.h"

class Notification {
 private:
    bool flag;
    int notificationId;
    int taskId;
    string message;
    chrono::system_clock::time_point time;
    int reminderInterval;

 public:
    friend class User;

    Notification(int id, int taskId, const string& msg,
                 chrono::system_clock::time_point t, int interval)
        : notificationId(id), taskId(taskId), message(msg),
          time(t), reminderInterval(interval), flag(1) {}

    void sendNotification() {
        for (int i = 0; i < 20; i++)
            cout << "***";
        cout << "\n";
        cout << "Notification: "<< notificationId
             << "\nTaskId: " << taskId << "\n";
        cout << "Message: " << message << "\n";
        cout << "The task is to due, remind to finish it!\n";
        for (int i = 0; i < 20; i++)
            cout << "***";
        cout << "\n";
    }
};

class User {
 private:
    int userId;  // 用户ID
    string userName;  // 用户昵称
    vector<Task*> tasks;  // 已有任务列表
    vector<Notification*> userNotifications;  // 提醒消息列表
    Timeline Tline;  // 时间线视图

 public:
    int taskCount;  // 任务序号
    int notificationCount;  // 消息序号
    User(int id, const string& name) : userId(id), userName(name),
         taskCount(0), notificationCount(0) {}

    void addTask();  // 新建任务
    void editTask(int taskId);  // 编辑已有任务
    void deleteTask(int taskId);  // 删除任务
    void addNotification(Notification* n);  // 增加提醒消息
    void changeNotification(Task* t);  // 修改提醒消息
    void deleteNotification(int id);  // 删除提醒消息
    void listTasks() const;  // 显示任务界面
    void TimeList();  // 显示任务时间线视图
    void listNotifications();  // 发出提醒消息
};

#endif  // _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____USER_H_
