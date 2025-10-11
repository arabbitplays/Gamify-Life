//
// Created by oschdi on 11.10.25.
//

#include "../../../include/persistence/yaml/YamlTaskRepository.hpp"

#include <fstream>

YamlTaskRepository::YamlTaskRepository(const std::string &file_path) : file_path(file_path) {

}

void YamlTaskRepository::loadTasks() {
    try {
        main_node = YAML::LoadFile(file_path);

        if (main_node[TASK_LIST_KEY] && main_node[TASK_LIST_KEY].IsSequence()) {
            YAML::Node task_list_node = main_node[TASK_LIST_KEY];

            for (const auto& task_node : task_list_node) {
                if (!task_node[NAME_KEY] || !task_node[SCORE_KEY]) {
                    fprintf(stderr, "Task node is not valid!");
                    continue;
                }

                auto task_name = task_node[NAME_KEY].as<std::string>();
                auto score = task_node[SCORE_KEY].as<uint32_t>();
                std::string streak_name = task_node[STREAK_KEY] ? task_node[STREAK_KEY].as<std::string>() : "";
                auto new_task = std::make_shared<Task>(task_name, score, streak_name);

                tasks.push_back(new_task);
            }
        } else {
            throw std::runtime_error("Task list does not exist or is not a list!");
        }
    } catch (const YAML::BadFile& e) {
        throw std::runtime_error("Error: Could not open file" + file_path);
    } catch (const YAML::ParserException& e) {
        throw std::runtime_error("Error parsing YAML: " + std::string(e.what()));
    }

}

void YamlTaskRepository::addTask(const TaskHandle &task) {
    tasks.push_back(task);

    YAML::Node new_task_node;
    new_task_node[NAME_KEY] = task->getName();
    new_task_node[SCORE_KEY] = task->getScore();
    new_task_node[STREAK_KEY] = task->getStreakName();

    main_node[TASK_LIST_KEY].push_back(new_task_node);

    std::ofstream fout(file_path);
    fout << main_node;
}

std::vector<TaskHandle> YamlTaskRepository::getTasks() {
    return tasks;
}

TaskHandle YamlTaskRepository::getTaskByName(const std::string &task_name) {
    for (auto& task : tasks) {
        if (task->getName() == task_name) {
            return task;
        }
    }
    return nullptr;
}


