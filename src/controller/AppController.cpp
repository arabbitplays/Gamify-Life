#include "controller/AppController.hpp"

#include "controller/ConfigYamlKeys.hpp"
#include "persistence/in_memory/InMemoryTaskRepository.hpp"


void AppController::loadConfig(const std::string &path) {
    try {
        config_node = YAML::LoadFile(path);
    } catch (std::exception& e) {
        const std::string msg = e.what();
        throw std::runtime_error("Error while loading config: " + msg);
    }
}

void AppController::initPersistence() {
    if (!config_node[PERSISTENCE_KEY] || !config_node[PERSISTENCE_KEY][PERSISTENCE_TYPE_KEY]) {
        throw std::runtime_error("Invalid config");
    }

    const auto type = config_node[PERSISTENCE_KEY][PERSISTENCE_TYPE_KEY].as<std::string>();
    if (type == "in_memory") {
        task_repo = std::make_shared<InMemoryTaskRepository>();
        profile_gateway = std::make_shared<InMemoryProfileGateway>();
    } else if (type == "yaml") {
        task_repo = std::make_shared<YamlTaskRepository>(config_node[PERSISTENCE_KEY]);
        profile_gateway = std::make_shared<YamlProfileGateway>(config_node[PERSISTENCE_KEY], task_repo);
    } else if (type == "postgres") {
        task_repo = std::make_shared<PostgresTaskRepository>(config_node[PERSISTENCE_KEY]);
        profile_gateway = std::make_shared<PostgresProfileGateway>(config_node[PERSISTENCE_KEY], task_repo);
    } else {
        throw std::runtime_error("Not a valid persistence type");
    }
}

void AppController::initController() {
    task_controller = std::make_shared<TaskController>(config_node, task_repo, profile_gateway);
    profile_controller = std::make_shared<ProfileController>(config_node, task_repo, profile_gateway);
}
