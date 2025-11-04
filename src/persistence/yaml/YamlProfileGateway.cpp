//
// Created by oschdi on 11.10.25.
//

#include "persistence/yaml/YamlProfileGateway.hpp"

#include <fstream>

YamlProfileGateway::YamlProfileGateway(const std::string &profile_dir_path, const std::shared_ptr<ITaskRepository>& task_repo)
        : profile_dir_path(profile_dir_path), task_repository(task_repo) {

}

ProfileHandle YamlProfileGateway::loadProfile(std::string name) {
    std::string file_name = profile_dir_path + "/" + name + "_profile.yaml";
    try {
        YAML::Node profile_node = YAML::LoadFile(file_name);

        if (!profile_node[NAME_KEY] || !profile_node[DONE_TASKS_KEY] || !profile_node[DONE_TASKS_KEY].IsSequence()) {
            throw std::runtime_error("File is not a valid profile!");
        }

        ProfileHandle profile = std::make_shared<Profile>(profile_node[NAME_KEY].as<std::string>());

        for (const auto& date_node : profile_node[DONE_TASKS_KEY]) {
            if (!date_node[DATE_KEY] || !date_node[TASKS_NAMES_KEY] || !date_node[TASKS_NAMES_KEY].IsSequence()) {
                fprintf(stderr, "Date node is not valid!");
                continue;
            }

            auto date = date_node[DATE_KEY].as<Date>();
            for (const auto& name_node : date_node[TASKS_NAMES_KEY]) {
                std::string task_name = name_node.as<std::string>();
                TaskHandle task = task_repository->getTaskByName(task_name);
                if (task == nullptr) {
                    fprintf(stderr, "Task %s doesnt exist!", task_name.c_str());
                    continue;
                }
                profile->addDoneTask(task, date);
            }
        }

        return profile;
    } catch (const YAML::BadFile& e) {
        throw std::runtime_error("Error: Could not open file " + file_name);
    } catch (const YAML::ParserException& e) {
        throw std::runtime_error("Error parsing YAML: " + std::string(e.what()));
    }
}

ProfileHandle YamlProfileGateway::createProfile(std::string name) {
    ProfileHandle profile = std::make_shared<Profile>(name);

    YAML::Node profile_node;
    profile_node[NAME_KEY] = profile->getName();
    profile_node[DONE_TASKS_KEY] = YAML::Node(YAML::NodeType::Sequence);

    std::ofstream fout(profile_dir_path + "/" + profile->getName() + "_profile.yaml");
    fout << profile_node;

    return profile;
}

void YamlProfileGateway::addDoneTaskToProfile(std::string profile_name, Date insert_date, TaskHandle task) {
    std::string file_path = profile_dir_path + "/" + profile_name + "_profile.yaml";
    try {
        YAML::Node profile_node = YAML::LoadFile(file_path);

        if (!profile_node[NAME_KEY] || !profile_node[DONE_TASKS_KEY] || !profile_node[DONE_TASKS_KEY].IsSequence()) {
            throw std::runtime_error("File is not a valid profile!");
        }

        bool found_date = false;

        for (const auto& date_node_iterator : profile_node[DONE_TASKS_KEY]) {
            YAML::Node date_node = date_node_iterator;
            if (!date_node[DATE_KEY] || !date_node[TASKS_NAMES_KEY] || !date_node[TASKS_NAMES_KEY].IsSequence()) {
                fprintf(stderr, "Date node is not valid!");
                continue;
            }

            auto date = date_node[DATE_KEY].as<Date>();
            if (insert_date == date) {
                found_date = true;
                date_node[TASKS_NAMES_KEY].push_back(task->getName());
                break;
            }
        }

        if (!found_date) {
            YAML::Node date_node;
            date_node[DATE_KEY] = insert_date;
            date_node[TASKS_NAMES_KEY] = YAML::Node(YAML::NodeType::Sequence);
            date_node[TASKS_NAMES_KEY].push_back(task->getName());

            profile_node[DONE_TASKS_KEY].push_back(date_node);
        }

        std::ofstream fout(file_path);
        fout << profile_node;
    } catch (const YAML::BadFile& e) {
        throw std::runtime_error("Error: Could not open file " + file_path);
    } catch (const YAML::ParserException& e) {
        throw std::runtime_error("Error parsing YAML: " + std::string(e.what()));
    }
}
