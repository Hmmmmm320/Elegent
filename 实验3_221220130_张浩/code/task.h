#ifndef _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TASK_H_
#define _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TASK_H_
/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>
using namespace std;

enum Level { HIGH, MEDIUM, LOW };
enum State { FINISHED, UNDERWAY, DUESOON, UNSTARTED };
enum Type { WORK, LIFE, PLAY, ELSE };
enum Color { RED, YELLOW, GREEN, BLUE, PINK, BLACK, BROWN, PURPLE, WHITE };

class Category {  // 类别
 public:
    Type categoryType;
    Color tagColor;

    void addType(Type t) {categoryType = t;}
    void addTagColor(Color color) { tagColor = color; }
    void removeTagColor() { tagColor = WHITE; }  // Default to white if removed
};

class Priority {  // 优先级
 public:
    Level level;
    void setPriority(Level newLevel) { level = newLevel; }
};

class Status {  // 任务状态
 public:
    State statusName;

    void setStatus(State newState) { statusName = newState; }
};

class Task {
 private:
    int taskId;  // 任务ID
    string title;  // 任务标题
    string description;  // 任务详情
    chrono::system_clock::time_point deadline;  // 截止时间
    int reminderInterval;  // 提醒间隔
    Category category;  // 任务类别
    Priority priority;  // 任务优先级
    Status status;  // 任务状态

 public:
    friend class User;

    friend class Timeline;

    explicit Task(int id):taskId(id), title(""),
                          description(""), reminderInterval(0) {}

    Task(int id, const string& title, const string& description)
        : taskId(id), title(title), description(description),
          reminderInterval(0) {}

    int getID() {
        return this->taskId;
    }

    chrono::system_clock::time_point getDDL() {
        return this->deadline;
    }

    void newTask();

    void updateDeadline();

    void updateReminderInterval();

    void updateStatus();

    void updatePriority();

    void updateCategory();

    void displayTask() const;

 private:
    string levelToString(Level level) const;

    string stateToString(State state) const;
};

#endif  // _MNT_D__MYCOLLEGE_JUNIOR_1_SOFTWAREPROJUCT_____TASK_H_
