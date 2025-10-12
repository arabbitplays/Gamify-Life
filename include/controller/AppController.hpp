//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_APPCONTROLLER_HPP
#define GAMIFY_LIFE_APPCONTROLLER_HPP
#include <memory>

#include "controller/ProfileController.hpp"
#include "controller/TaskController.hpp"
#include "../persistence/in_memory/InMemoryProfileGateway.hpp"
#include "persistence/yaml/YamlProfileGateway.hpp"
#include "persistence/yaml/YamlTaskRepository.hpp"


class AppController {
public:
    AppController() {
        task_repo = std::make_shared<YamlTaskRepository>("../resources/tasks.yaml");
        task_repo->loadTasks();
        profile_gateway = std::make_shared<YamlProfileGateway>("../resources/profile.yaml", task_repo);

        task_controller = std::make_shared<TaskController>(task_repo, profile_gateway);
        profile_controller = std::make_shared<ProfileController>(task_repo, profile_gateway);
    }
    std::shared_ptr<TaskController> task_controller;
    std::shared_ptr<ProfileController> profile_controller;

    std::shared_ptr<ITaskRepository> task_repo;
    std::shared_ptr<IProfileGateway> profile_gateway;
};

#endif //GAMIFY_LIFE_APPCONTROLLER_HPP