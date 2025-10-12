//
// Created by oschdi on 05.10.25.
//

#include "../../include/model/Profile.hpp"

#include <iostream>
#include <ranges>

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

void Profile::addStreaks(const std::vector<StreakHandle> &new_streaks) {
    for (const auto& streak : new_streaks) {
        std::string streak_name = streak->getName();
        if (!streaks.contains(streak->getName())) {
            streaks[streak->getName()] = streak;
        }
    }
}

std::vector<StreakHandle> Profile::getStreaks() const {
    std::vector<StreakHandle> result;
    for (const auto &streak: streaks | std::views::values) {
        result.push_back(streak);
    }
    return result;
}

std::vector<TaskHandle> Profile::getDoneTasksAtDate(const Date& date) {
    if (done_tasks.contains(date)) {
        return done_tasks[date];
    }
    return {};
}

std::unordered_map<Date, std::vector<TaskHandle>> Profile::getDoneTasks() {
    return done_tasks;
}

std::string Profile::getName() {
    return name;
}
