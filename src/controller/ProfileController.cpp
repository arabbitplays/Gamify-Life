//
// Created by oschdi on 09.10.25.
//

#include "../../include/controller/ProfileController.hpp"
#include "persistence/StreakFactory.hpp"

ProfileController::ProfileController(const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_gateway)
        : task_repo(task_repo), profile_gateway(profile_gateway) {
    profile_gateway->loadProfile();
    profile = profile_gateway->getProfile();

    // TODO remove this
    std::vector<TaskHandle> tasks = task_repo->getTasks();
    Date date = Date::createToday();
    profile->addDoneTask(tasks.at(1), date);
    date = date.createPrev();
    profile->addDoneTask(tasks.at(1), date);
    profile->addDoneTask(tasks.at(2), date);
    profile->addDoneTask(tasks.at(0), date); // lang
    date = date.createPrev(5);
    profile->addDoneTask(tasks.at(0), date);
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

std::vector<StreakHandle> ProfileController::getStreaks() const {
    return StreakFactory::createStreaksForProfile(profile); // TODO return the ones in the profile here
}
