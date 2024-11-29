/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "./task.h"

void Task::displayTask() const {
    time_t due_time = chrono::system_clock::to_time_t(deadline);
    cout << "TaskID: " << taskId << "\n"
         << "Task: " << title << "\n";
    if (this->description.size() == 0)
        cout << "Description: 无";
    else
        cout << "Description: " << description;
    cout << "\nDeadline: " << ctime(&due_time)
         << "\nPriority: " << levelToString(priority.level)
         << "\nStatus: " << stateToString(status.statusName)
         << "\n";
    for (int i = 0; i < 20; i++)
        cout << "***";
    cout << "\n";
}

void Task::updateDeadline() {
    cout << "请设置DDL：年：";
    tm time_info = {};
    int temp;
    cin >> temp;
    time_info.tm_year = temp - 1900;
    cout << "月份：";
    cin >> temp;
    while (temp < 1 || temp > 12) {
        cout << "格式错误，请重新输入月份：";
        cin >> temp;
    }
    time_info.tm_mon = temp - 1;
    cout << "日期：";
    cin >> temp;
    while (temp < 1 || temp > 31) {
        cout << "格式错误，请重新输入日期：";
        cin >> temp;
    }
    time_info.tm_mday = temp;
    cout << "小时：";
    cin >> temp;
    while (temp < 0 || temp > 23) {
        cout << "格式错误，请重新输入小时：";
        cin >> temp;
    }
    time_info.tm_hour = temp;
    cout << "分钟：";
    cin >> temp;
    while (temp < 0 || temp > 59) {
        cout << "格式错误，请重新输入分钟：";
        cin >> temp;
    }
    time_info.tm_min = temp;
    cout << "秒数：";
    cin >> temp;
    while (temp < 0 || temp > 59) {
        cout << "格式错误，请重新输入秒数：";
        cin >> temp;
    }
    time_info.tm_sec = temp;
    time_t time_since_epoch = mktime(&time_info);
    auto time_point = chrono::system_clock::from_time_t(time_since_epoch);
    this->deadline = time_point;
}

void Task::updateReminderInterval() {
    cout << "请输入提醒间隔(min)：";
    int temp;
    cin >> temp;
    this->reminderInterval = temp;
}

void Task::updateCategory() {
    int temp;
    cout << "请设置任务类别（输入选项前的数字）\n"
         << "0 工作， 1 生活， 2 娱乐， 3 其他\n";
    cin >> temp;
    Type p;
    switch (temp) {
        case 0: p = WORK; break;
        case 1: p = LIFE; break;
        case 2: p = PLAY; break;
        case 3: p = ELSE; break;
    }
    this->category.addType(p);
    cout << "请设置任务标签颜色（输入选项前的数字）\n"
         << "0 红色， 1 黄色， 2 绿色， 3 蓝色， 4 粉色， "
         << "5 黑色， 6 棕色， 7 紫色， 8 白色\n";
    cin >> temp;
    Color c;
    switch (temp) {
        case 0: c = RED; break;
        case 1: c = YELLOW; break;
        case 2: c = GREEN; break;
        case 3: c = BLUE; break;
        case 4: c = PINK; break;
        case 5: c = BLACK; break;
        case 6: c = BROWN; break;
        case 7: c = PURPLE; break;
        case 8: c = WHITE; break;
    }
    this->category.addTagColor(c);
}

void Task::updateStatus() {
    int temp;
    cout << "请设置任务状态（输入选项前的数字）\n"
         << "0 已完成， 1 正在进行， 2 即将到期， 3 未开始\n";
    cin >> temp;
    State l;
    switch (temp) {
        case 0: l = FINISHED; break;
        case 1: l = UNDERWAY; break;
        case 2: l = DUESOON; break;
        case 3: l = UNSTARTED; break;
    }
    this->status.setStatus(l);
}

void Task::updatePriority() {
    int temp;
    cout << "请设置任务优先级（输入选项前的数字）\n" << "0 高， 1 中， 2 低\n";
    cin >> temp;
    Level l;
    switch (temp) {
        case 0: l = HIGH; break;
        case 1: l = MEDIUM; break;
        case 2: l = LOW; break;
    }
    this->priority.setPriority(l);
}

void Task::newTask() {
    cout << "请输入任务标题：";
    string t;
    int temp;
    getchar();
    // cin >> t;
    getline(cin, t);
    while (t.size() == 0 || t[0] == '\n' || t[0] == ' ') {
        cout << "标题不能为空！请再次输入：";
        // cin >> t;
        getline(cin, t);
    }
    this->title = t;
    cout << "请输入任务描述：";
    getline(cin, this->description);
    if (description[0] == '\n' || description[0] == ' ')
        description = "";
    this->updateDeadline();
    this->updateReminderInterval();
    this->updateCategory();
    this->updatePriority();
    this->status.setStatus(UNSTARTED);
}

string Task::levelToString(Level level) const {
    switch (level) {
        case HIGH: return "High";
        case MEDIUM: return "Medium";
        case LOW: return "Low";
        default: return "Unknown";
    }
}

string Task::stateToString(State state) const {
    switch (state) {
        case FINISHED: return "Finished";
        case UNDERWAY: return "Underway";
        case DUESOON: return "Due Soon";
        case UNSTARTED: return "Unstarted";
        default: return "Unknown";
    }
}
