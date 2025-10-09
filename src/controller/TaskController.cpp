//
// Created by oschdi on 08.10.25.
//

#include "controller/TaskController.hpp"

TaskController::TaskController(const std::shared_ptr<ITaskRepository> &task_repo) : task_repo(task_repo) {
    task_repo->loadTasks();
}

std::vector<TaskHandle> TaskController::getAvailableTasks() const {
    return task_repo->getTasks();
}
