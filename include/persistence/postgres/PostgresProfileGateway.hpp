//
// Created by oschdi on 30.10.25.
//

#ifndef POSTGRESPROFILEGATEWAY_HPP
#define POSTGRESPROFILEGATEWAY_HPP
#include "controller/IProfileGateway.hpp"
#include <pqxx/pqxx>

#include "controller/ITaskRepository.hpp"

class PostgresProfileGateway : public IProfileGateway {
public:
    explicit PostgresProfileGateway(const std::shared_ptr<ITaskRepository> &task_repository);

    ProfileHandle loadProfile(std::string name) override;
    ProfileHandle createProfile(std::string name) override;
    void addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) override;

public:
    pqxx::connection connection;

    std::shared_ptr<ITaskRepository> task_repository;
};



#endif //POSTGRESPROFILEGATEWAY_HPP
