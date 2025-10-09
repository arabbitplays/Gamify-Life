//
// Created by oschdi on 08.10.25.
//


#include "persistence/InMemoryTaskRepository.hpp"

void InMemoryTaskRepository::loadTasks() {
    const auto task1 = std::make_shared<Task>("Stretching", 5);
    const auto task2 = std::make_shared<Task>("Running", 10);
    const auto task3 = std::make_shared<Task>("Being Awesome", 0);
    addTask(task3);
    addTask(task1);
    addTask(task2);
}

void InMemoryTaskRepository::addTask(const TaskHandle &task) {
    tasks.push_back(task);
}

std::vector<TaskHandle> InMemoryTaskRepository::getTasks() {
    return tasks;
}

TaskHandle InMemoryTaskRepository::getTaskByName(const std::string &task_name) {
    for (auto& task : tasks) {
        if (task->getName() == task_name) {
            return task;
        }
    }
    return nullptr;
}

