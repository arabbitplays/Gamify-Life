//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_YAMLTASKREPOSITORY_HPP
#define GAMIFY_LIFE_YAMLTASKREPOSITORY_HPP
#include "controller/ITaskRepository.hpp"
#include <yaml-cpp/yaml.h>

class YamlTaskRepository : public ITaskRepository {
private:
    static constexpr std::string TASK_LIST_KEY = "tasks";
    static constexpr std::string NAME_KEY = "name";
    static constexpr std::string SCORE_KEY = "score";
    static constexpr std::string STREAK_KEY = "streak";

public:
    explicit YamlTaskRepository(const std::string &file_path);

    void loadTasks() override;
    void addTask(const TaskHandle& task) override;
    std::vector<TaskHandle> getTasks() override;
    TaskHandle getTaskByName(const std::string &task_name) override;

    std::string file_path;
    YAML::Node main_node;

    std::vector<TaskHandle> tasks;
};


#endif //GAMIFY_LIFE_YAMLTASKREPOSITORY_HPP