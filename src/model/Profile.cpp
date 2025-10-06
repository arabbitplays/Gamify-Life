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

void Profile::printDoneTasks() {
    const Date today = Date::createToday();
    std::cout << std::left  << std::setw(15) << "Name"
              << std::right << std::setw(10) << "Score" << "\n";

    for (const auto& task : done_tasks[today]) {
        std::cout << std::left  << std::setw(15) << task->getName()
                << std::right << std::setw(10) << task->getScore() << "\n";
    }
}
