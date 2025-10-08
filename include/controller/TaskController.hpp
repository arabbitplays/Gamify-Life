//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKCONTROLLER_HPP
#define GAMIFY_LIFE_TASKCONTROLLER_HPP
#include "ITaskRepository.hpp"


class TaskController {
public:
    TaskController();

    std::vector<TaskHandle> getAvailableTasks() const;
private:
    std::shared_ptr<ITaskRepository> task_repo;
};


#endif //GAMIFY_LIFE_TASKCONTROLLER_HPP