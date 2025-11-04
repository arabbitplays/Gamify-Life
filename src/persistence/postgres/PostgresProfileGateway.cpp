//
// Created by oschdi on 30.10.25.
//

#include "persistence/postgres/PostgresProfileGateway.hpp"


PostgresProfileGateway::PostgresProfileGateway() : connection("dbname=gamify-life user=postgres host=/var/run/postgresql")
{
    if (!connection.is_open()) {
        throw std::runtime_error("Can't connect to postgres db");
    }
}

ProfileHandle PostgresProfileGateway::loadProfile(std::string name) {
    try {
        pqxx::work work(connection);

        const std::string sql = R"(

        )";

        work.commit();

    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
        return nullptr;
    }

    return nullptr;
}

ProfileHandle PostgresProfileGateway::createProfile(std::string name) {
    return nullptr;
}

void PostgresProfileGateway::addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) {
}

