//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_ITASKREPOSITORY_HPP
#define GAMIFY_LIFE_ITASKREPOSITORY_HPP
#include <vector>

#include "Task.hpp"

class ITaskRepository {
public:
    virtual ~ITaskRepository() = default;

    virtual void loadTasks() = 0;
    virtual void addTask(const TaskHandle& task) = 0;
    virtual std::vector<TaskHandle> getTasks() = 0;
};

#endif //GAMIFY_LIFE_ITASKREPOSITORY_HPP