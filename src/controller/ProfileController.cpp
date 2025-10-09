//
// Created by oschdi on 09.10.25.
//

#include "../../include/controller/ProfileController.hpp"

ProfileController::ProfileController() {
    createNewProfile("Oschdi");
}

void ProfileController::createNewProfile(const std::string& name) {
    profile = std::make_shared<Profile>(name);
}

std::string ProfileController::getName() const {
    return profile->getName();
}

void ProfileController::addDoneTaskToday(const TaskHandle &task) const {
    profile->addDoneTaskToday(task);
}

float ProfileController::getTotalScoreToday() const {
    const std::vector<TaskHandle> done_tasks = profile->getDoneTasksToday();
    float result = 0;
    for (const auto& task : done_tasks) {
        result += task->getScore();
    }
    return result;
}

std::vector<TaskHandle> ProfileController::getTasksDoneToday() const {
    return profile->getDoneTasksToday();
}
