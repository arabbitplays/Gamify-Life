//
// Created by oschdi on 04.11.25.
//

#include "persistence/postgres/PostgresTaskRepository.hpp"

PostgresTaskRepository::PostgresTaskRepository() : connection("dbname=gamify-life user=postgres host=/var/run/postgresql")
{
    if (!connection.is_open()) {
        throw std::runtime_error("Can't connect to postgres db");
    }
}

void PostgresTaskRepository::addTask(const TaskHandle &task) {

    pqxx::work work(connection);

    const std::string sql = R"(
        INSERT INTO public.tasks
        ("name", score, streak_name)
        VALUES($1, $2, $3);
    )";

    work.exec(sql, pqxx::params(task->getName(), task->getScore(), task->getStreakName()));
    work.commit();
}

std::vector<TaskHandle> PostgresTaskRepository::getTasks() {
    pqxx::work work(connection);

    pqxx::result result = work.exec("SELECT name, score, streak_name FROM public.tasks;");

    std::vector<TaskHandle> tasks{};
    for (const auto &row : result)
    {
        // Access columns by index or name
        auto [name, score, streak] = row.as<std::string, float, std::string>();
        TaskHandle task = std::make_shared<Task>(name, score, streak);
        tasks.push_back(task);
    }

    work.commit();
    return tasks;
}

TaskHandle PostgresTaskRepository::getTaskByName(const std::string &name) {
    pqxx::work work(connection);

    const std::string sql = R"(
        SELECT name, score, streak_name
        FROM public.tasks
        WHERE name = $1;
    )";

    pqxx::result result = work.exec(sql, pqxx::params(name));
    work.commit();

    if (result.empty()) {
        return nullptr;
    }

    auto [taks_name, score, streak] = result.at(0).as<std::string, float, std::string>();
    TaskHandle task = std::make_shared<Task>(taks_name, score, streak);

    return task;
}
