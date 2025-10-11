//
// Created by oschdi on 05.10.25.
//

#include <utility>

#include "../../include/model/Task.hpp"

Task::Task(std::string name, const uint32_t score) : name(std::move(name)), score(score) {

}

std::string Task::getName() const {
    return name;
}

float Task::getScore() const {
    return static_cast<float>(score);
}

std::string Task::getStreakName() {
    return streak_name;
}
