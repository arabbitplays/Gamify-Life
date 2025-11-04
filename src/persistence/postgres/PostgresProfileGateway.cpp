//
// Created by oschdi on 30.10.25.
//

#include "persistence/postgres/PostgresProfileGateway.hpp"

#include <utility>


PostgresProfileGateway::PostgresProfileGateway(const std::shared_ptr<ITaskRepository> &task_repository)
    : connection("dbname=gamify-life user=postgres host=/var/run/postgresql"),
    task_repository(task_repository)
{
    if (!connection.is_open()) {
        throw std::runtime_error("Can't connect to postgres db");
    }
}

Date convertSqlDateToDate(const std::string& sqlDate) {
    if (sqlDate.size() != 10 || sqlDate[4] != '-' || sqlDate[7] != '-') {
        throw std::invalid_argument("Invalid SQL date format, expected YYYY-MM-DD");
    }

    int year = std::stoi(sqlDate.substr(0, 4));
    int month = std::stoi(sqlDate.substr(5, 2));
    int day = std::stoi(sqlDate.substr(8, 2));

    return Date(year, month, day);
}

std::string convertDateToSqlDate(const Date date) {
    return std::to_string(date.getYear()) + "-" + std::to_string(date.getMonth()) + "-" + std::to_string(date.getDay());
}

ProfileHandle PostgresProfileGateway::loadProfile(std::string name) {
    try {
        pqxx::work work(connection);

        std::string sql = R"(
            SELECT id, "name"
            FROM public.profiles
            WHERE name = $1;
        )";
        pqxx::result result = work.exec(sql, pqxx::params(name));
        work.commit();
        if (result.empty()) {
            return nullptr;
        }
        auto [profile_id, profile_name] = result.at(0).as<int32_t, std::string>();

        ProfileHandle profile = std::make_shared<Profile>(profile_name);

        sql = R"(
            SELECT "date", task_id
            FROM public.done_tasks
            WHERE profile_id = $1;
        )";
        result = work.exec(sql, pqxx::params(profile_id));
        work.commit();

        for (const auto& row : result) {
            auto [date_string, task_id] = row.as<std::string, uint32_t>();

            sql = R"(
                SELECT name
                FROM public.tasks
                WHERE id = $1;
            )";
            pqxx::result task_result = work.exec(sql, pqxx::params(task_id));
            work.commit();
            if (result.empty()) {
                fprintf(stderr, "Task with id %d not found", task_id);
                continue;
            }
            auto [task_name] = task_result.at(0).as<std::string>();

            Date date = convertSqlDateToDate(date_string);
            TaskHandle task = task_repository->getTaskByName(task_name);

            profile->addDoneTask(task, date);
        }

        return profile;
    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
        return nullptr;
    }
}

ProfileHandle PostgresProfileGateway::createProfile(std::string name) {
    try {
        pqxx::work work(connection);

        const std::string sql = R"(
            INSERT INTO public.profiles
            ("name")
            VALUES($1);
        )";

        work.exec(sql, pqxx::params(name));
        work.commit();

        return std::make_shared<Profile>(name);
    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
        return nullptr;
    }

    return nullptr;
}

void PostgresProfileGateway::addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) {
    try {
        pqxx::work work(connection);

        std::string sql = R"(
            SELECT id
            FROM public.profiles
            WHERE name = $1;
        )";
        pqxx::result result = work.exec(sql, pqxx::params(profile_name));
        if (result.empty()) {
            fprintf(stderr, "Profile '%s' not found", profile_name.c_str());
            return;
        }
        auto [profile_id] = result.at(0).as<int32_t>();

        sql = R"(
            SELECT id
            FROM public.tasks
            WHERE name = $1;
        )";
        result = work.exec(sql, pqxx::params(task_handle->getName()));
        if (result.empty()) {
            fprintf(stderr, "Task '%s' not found", task_handle->getName().c_str());
            return;
        }
        auto [task_id] = result.at(0).as<int32_t>();


        sql = R"(
            INSERT INTO public.done_tasks
            ("date", profile_id, task_id)
            VALUES($1, $2, $3);
        )";
        work.exec(sql, pqxx::params(convertDateToSqlDate(date), profile_id, task_id));
        work.commit();
    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
    }
}

