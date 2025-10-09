//
// Created by oschdi on 05.10.25.
//

#include "../../include/model/Profile.hpp"

#include <iostream>

Profile::Profile(std::string name) : name(std::move(name)) {
}

void Profile::addDoneTaskToday(const TaskHandle &task) {
    Date today = Date::createToday();
    if (!done_tasks.contains(today)) {
        done_tasks[today] = {};
    }

    done_tasks[today].push_back(task);
}

std::vector<TaskHandle> Profile::getDoneTasksToday() {
    Date today = Date::createToday();
    if (done_tasks.contains(today)) {
        return done_tasks[today];
    }
    return {};
}

std::string Profile::getName() {
    return name;
}
