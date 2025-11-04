//
// Created by oschdi on 04.11.25.
//

#ifndef POSTGRESTASKREPOSITORY_HPP
#define POSTGRESTASKREPOSITORY_HPP
#include <pqxx/pqxx>

#include "controller/ITaskRepository.hpp"


class PostgresTaskRepository final : public ITaskRepository {
public:
    PostgresTaskRepository();

    void addTask(const TaskHandle &task) override;
    std::vector<TaskHandle> getTasks() override;
    TaskHandle getTaskByName(const std::string &string) override;

private:
    pqxx::connection connection;
};



#endif //POSTGRESTASKREPOSITORY_HPP
