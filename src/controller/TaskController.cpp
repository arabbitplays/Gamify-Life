//
// Created by oschdi on 08.10.25.
//

#include "controller/TaskController.hpp"

TaskController::TaskController(const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_gateway) : task_repo(task_repo), profile_gateway(profile_gateway) {
    task_repo->loadTasks();
}

std::vector<TaskHandle> TaskController::getAvailableTasks() const {
    ProfileHandle profile = profile_gateway->loadProfile("Oschdi");
    std::vector done_tasks = profile->getDoneTasksAtDate(Date::createToday());
    std::vector<TaskHandle> tasks = task_repo->getTasks();
    std::unordered_map<std::string, TaskHandle> available_task_map{};

    for (const auto& task : tasks) {
        available_task_map[task->getName()] = task;
    }

    for (const auto& done_task : done_tasks) {
        if (available_task_map.contains(done_task->getName())) {
            available_task_map.erase(done_task->getName());
        }
    }

    std::vector<TaskHandle> result;
    result.reserve(available_task_map.size());
    for (const auto& [key, value] : available_task_map)
        result.push_back(value);
    return result;
}
