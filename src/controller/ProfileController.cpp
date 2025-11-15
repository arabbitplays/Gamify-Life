#include "../../include/controller/ProfileController.hpp"

#include "controller/ConfigYamlKeys.hpp"
#include "persistence/StreakFactory.hpp"

ProfileController::ProfileController(YAML::Node config_node, const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_gateway)
        : task_repo(task_repo), profile_gateway(profile_gateway) {

    if (!config_node[PROFILE_NAME_KEY]) {
        throw std::runtime_error("Profile name missing in config");
    }
    loadProfile(config_node[PROFILE_NAME_KEY].as<std::string>());
}

ProfileHandle ProfileController::getProfile() {
    return profile;
}

void ProfileController::loadProfile(const std::string &name) {
    profile = profile_gateway->loadProfile(name);
    if (profile == nullptr) {
        profile = profile_gateway->createProfile(name);
        if (profile == nullptr) {
            throw std::runtime_error("Profile '" + name + "' could not be loaded");
        }
    }
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
    profile_gateway->addDoneTaskToProfile(profile->getName(), Date::createToday(), task);
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