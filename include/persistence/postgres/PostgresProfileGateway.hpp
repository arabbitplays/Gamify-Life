//
// Created by oschdi on 30.10.25.
//

#ifndef POSTGRESPROFILEGATEWAY_HPP
#define POSTGRESPROFILEGATEWAY_HPP
#include "controller/IProfileGateway.hpp"
#include <pqxx/pqxx>

class PostgresProfileGateway : public IProfileGateway {
public:
    PostgresProfileGateway();

    ProfileHandle loadProfile(std::string name) override;
    ProfileHandle createProfile(std::string name) override;
    void addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) override;

public:
    pqxx::connection connection;
};



#endif //POSTGRESPROFILEGATEWAY_HPP
