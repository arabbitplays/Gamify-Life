//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKREPOSITORY_HPP
#define GAMIFY_LIFE_TASKREPOSITORY_HPP
#include <vector>

#include "../model/Task.hpp"
#include "controller/ITaskRepository.hpp"


class InMemoryTaskRepository : public ITaskRepository {
public:
    InMemoryTaskRepository() = default;

    void loadTasks() override;
    void addTask(const TaskHandle& task) override;
    std::vector<TaskHandle> getTasks() override;
    TaskHandle getTaskByName(const std::string &task_name) override;
private:
    std::vector<TaskHandle> tasks;
};


#endif //GAMIFY_LIFE_TASKREPOSITORY_HPP