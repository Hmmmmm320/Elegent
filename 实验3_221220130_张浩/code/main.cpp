/*
# Copyright (c) 2024 Hmmmm All rights reserved.
*/
#include "./user.h"

int main() {
    cout << "欢迎使用ToDoList，给自己起个名字吧！\nYour Name:";
    string name;
    getline(cin, name);
    // cin >> name;
    while (name.size() == 0 || name[0] == '\n' || name[0] == ' ') {
        cout << "空名字吗？重新起一个吧！\nYour Name:";
        getline(cin, name);
        // cin >> name;
    }

    // 创建用户
    User user(1, name);
    int flag = 1;
    int choice;
    cout << "\n你想做什么呢？（输入选项前的数字我就可以帮你完成喔！)\n"
         << "0 退出程序， 1 查看任务单， 2 查看任务时间线页面， "
         << "3 新建任务， 4 修改任务， 5 删除任务\n";
    cin >> choice;
    cout << endl;
    if (choice == 0)
        flag = 0;
    // 不断判断用户做出的选择
    while (flag) {
        while (choice != 0 && (choice < 1 || choice > 5)) {
            cout << "没有这个选项哦！重新选择一下吧！\n";
            cout << "0 退出程序， 1 查看任务单， 2 查看任务时间线页面， "
                 << "3 新建任务， 4 修改任务， 5 删除任务\n";
            cin >> choice;
            cout << endl;
        }
        if (choice == 0) {
            flag = 0;
            break;
        }
        int Tid;
        switch (choice) {
            // 查看任务单
            case 1:
                user.listTasks();
                break;
            // 查看任务时间线页面
            case 2:
                user.TimeList();
                break;
            // 新建任务
            case 3:
                user.addTask();
                break;
            // 修改任务
            case 4:
                cout << "告诉我你想修改哪个任务呢？(输入0可以退出）\n";
                cin >> Tid;
                cout << endl;
                while (Tid != 0 && (Tid < 1 || Tid > user.taskCount)) {
                    cout << "没有这个任务哦！再仔细看一下然后告诉我吧！"
                         << "(输入0可以退出）\n";
                    cin >> Tid;
                    cout << endl;
                    if (Tid == 0)
                        break;
                }
                if (Tid != 0)
                    user.editTask(Tid);
                break;
            // 删除任务
            case 5:
                cout << "告诉我你想删除哪个任务呢？(输入0可以退出）\n";
                cin >> Tid;
                cout << endl;
                while (Tid != 0 && (Tid < 1 || Tid > user.taskCount)) {
                    cout << "没有这个任务哦！再仔细看一下然后告诉我吧！"
                         << "(输入0可以退出）\n";
                    cin >> Tid;
                    cout << endl;
                    if (Tid == 0)
                        break;
                }
                if (Tid != 0)
                    user.deleteTask(Tid);
                break;
        }
        user.listNotifications();
        cout << "接下来还想让我帮你做什么呢？\n"
             << "0 退出程序， 1 查看任务单， 2 查看任务时间线页面， "
             << "3 新建任务， 4 修改任务， 5 删除任务\n";
        cin >> choice;
        cout << endl;
    }
    if (flag == 0) {
        cout << "要离开了吗？期待下次见面咯！\n";
    }
    return 0;
}
