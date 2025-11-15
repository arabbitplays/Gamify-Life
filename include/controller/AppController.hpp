//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_APPCONTROLLER_HPP
#define GAMIFY_LIFE_APPCONTROLLER_HPP
#include <memory>

#include "controller/ProfileController.hpp"
#include "controller/TaskController.hpp"
#include "../persistence/in_memory/InMemoryProfileGateway.hpp"
#include "persistence/postgres/PostgresProfileGateway.hpp"
#include "persistence/postgres/PostgresTaskRepository.hpp"
#include "persistence/yaml/YamlProfileGateway.hpp"
#include "persistence/yaml/YamlTaskRepository.hpp"

enum PersistenceType {
    IN_MEMORY,

};

class AppController {
public:
    AppController(std::string config_path) {
        loadConfig(config_path);
        initPersistence();
        initController();
    }

    YAML::Node config_node;

    std::shared_ptr<TaskController> task_controller;
    std::shared_ptr<ProfileController> profile_controller;

    std::shared_ptr<ITaskRepository> task_repo;
    std::shared_ptr<IProfileGateway> profile_gateway;

private:

    void loadConfig(const std::string &path);
    void initPersistence();
    void initController();
};

#endif //GAMIFY_LIFE_APPCONTROLLER_HPP