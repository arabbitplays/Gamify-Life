//
// Created by oschdi on 09.10.25.
//

#include "../../include/controller/ProfileController.hpp"
#include "persistence/StreakFactory.hpp"

ProfileController::ProfileController(const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_gateway)
        : task_repo(task_repo), profile_gateway(profile_gateway) {

    loadProfile("Oschdi");
}

void ProfileController::loadProfile(const std::string &name) {
    profile = profile_gateway->loadProfile(name);
    profile->addStreaks(StreakFactory::createStreaksForProfile(profile));
}


std::string ProfileController::getName() const {
    return profile->getName();
}

void ProfileController::addDoneTaskToday(const std::string& task_name) const {
    TaskHandle task = task_repo->getTaskByName(task_name);
    if (task == nullptr) {
        fprintf(stderr, "Task %s not found!\n", task_name.c_str());
        return;
    }

    profile->addDoneTaskToday(task);
    profile_gateway->storeProfile(profile);
}

float ProfileController::getTotalScoreAtDate(const Date &date) const {
    const std::vector<TaskHandle> done_tasks = profile->getDoneTasksAtDate(date);
    float result = 0;
    for (const auto& task : done_tasks) {
        result += task->getScore();
    }
    return result;
}

std::vector<TaskHandle> ProfileController::getTasksDoneAtDate(const Date& date) const {
    return profile->getDoneTasksAtDate(date);
}

std::vector<StreakHandle> ProfileController::getStreaks() const {
    return profile->getStreaks();
}