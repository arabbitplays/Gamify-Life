//
// Created by oschdi on 08.10.25.
//

#include "controller/TaskController.hpp"

#include "persistence/InMemoryTaskRepository.hpp"

TaskController::TaskController() {
    task_repo = std::make_shared<InMemoryTaskRepository>();
    task_repo->loadTasks();
}

std::vector<TaskHandle> TaskController::getAvailableTasks() const {
    return task_repo->getTasks();
}
