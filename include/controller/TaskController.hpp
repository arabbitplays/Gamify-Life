//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKCONTROLLER_HPP
#define GAMIFY_LIFE_TASKCONTROLLER_HPP
#include "IProfileGateway.hpp"
#include "ITaskRepository.hpp"


class TaskController {
public:
    explicit TaskController(const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_gateway);

    [[nodiscard]] std::vector<TaskHandle> getAvailableTasks() const;
private:
    std::shared_ptr<ITaskRepository> task_repo;
    std::shared_ptr<IProfileGateway> profile_gateway;
};


#endif //GAMIFY_LIFE_TASKCONTROLLER_HPP