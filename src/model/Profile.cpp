//
// Created by oschdi on 05.10.25.
//

#include "../../include/model/Profile.hpp"

#include <iostream>

Profile::Profile(std::string name) : name(std::move(name)) {
}

void Profile::addDoneTaskToday(const TaskHandle &task) {
    addDoneTask(task, Date::createToday());

}

void Profile::addDoneTask(const TaskHandle &task, const Date &date) {
    if (!done_tasks.contains(date)) {
        done_tasks[date] = {};
    }

    done_tasks[date].push_back(task);
    if (streaks.contains(task->getStreakName())) {
        streaks[task->getStreakName()]->checkStreakForToday();
    }
}

void Profile::addStreak(const StreakHandle &streak) {
    std::string streak_name = streak->getName();
    if (!streaks.contains(streak->getName())) {
        streaks[streak->getName()] = streak;
    }
}

std::vector<TaskHandle> Profile::getDoneTasksToday() {
    Date today = Date::createToday();
    if (done_tasks.contains(today)) {
        return done_tasks[today];
    }
    return {};
}

std::unordered_map<Date, std::vector<TaskHandle>> Profile::getDoneTasks() {
    return done_tasks;
}

std::string Profile::getName() {
    return name;
}
