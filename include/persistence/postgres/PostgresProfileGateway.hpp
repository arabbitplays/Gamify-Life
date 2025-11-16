//
// Created by oschdi on 30.10.25.
//

#ifndef POSTGRESPROFILEGATEWAY_HPP
#define POSTGRESPROFILEGATEWAY_HPP
#include "controller/IProfileGateway.hpp"
#include <pqxx/pqxx>
#include "yaml-cpp/yaml.h"

#include "controller/ITaskRepository.hpp"

class PostgresProfileGateway : public IProfileGateway {
public:
    PostgresProfileGateway(const YAML::Node &config_node, const std::shared_ptr<ITaskRepository> &task_repository);

    ProfileHandle loadProfile(std::string name) override;
    ProfileHandle createProfile(std::string name) override;
    void addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) override;

public:
    std::shared_ptr<pqxx::connection> connection;

    std::shared_ptr<ITaskRepository> task_repository;
};



#endif //POSTGRESPROFILEGATEWAY_HPP
