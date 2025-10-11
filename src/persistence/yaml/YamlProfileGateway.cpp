//
// Created by oschdi on 11.10.25.
//

#include "persistence/yaml/YamlProfileGateway.hpp"

#include <fstream>

YamlProfileGateway::YamlProfileGateway(const std::string &file_path) : file_path(file_path) {

}

ProfileHandle YamlProfileGateway::loadProfile(std::string name) {
    try {
        YAML::Node profile_node = YAML::LoadFile(file_path);

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
            for (const auto& task_name : profile_node[TASKS_NAMES_KEY]) {
                // TODO
            }
        }

        return profile;
    } catch (const YAML::BadFile& e) {
        throw std::runtime_error("Error: Could not open file" + file_path);
    } catch (const YAML::ParserException& e) {
        throw std::runtime_error("Error parsing YAML: " + std::string(e.what()));
    }
}

bool YamlProfileGateway::storeProfile(ProfileHandle profile) {
    YAML::Node profile_node;
    profile_node[NAME_KEY] = profile->getName();
    profile_node[DONE_TASKS_KEY] = YAML::Node(YAML::NodeType::Sequence);

    std::unordered_map<Date, std::vector<TaskHandle>> done_tasks = profile->getDoneTasks();
    for (const auto& [date, task_list] : done_tasks) {
        YAML::Node date_node;
        date_node[DATE_KEY] = date;
        date_node[TASKS_NAMES_KEY] = YAML::Node(YAML::NodeType::Sequence);

        for (const auto& task : task_list) {
            date_node[TASKS_NAMES_KEY].push_back(task->getName());
        }

        profile_node[DONE_TASKS_KEY].push_back(date_node);
    }

    std::ofstream fout(file_path);
    fout << profile_node;

    return true;
}
