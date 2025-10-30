//
// Created by oschdi on 30.10.25.
//

#include "persistence/postgres/PostgresProfileGateway.hpp"


ProfileHandle PostgresProfileGateway::loadProfile(std::string name) {
    try {
        pqxx::connection C("dbname=gamify-life user=postgres host=/var/run/postgresql");

        if (!C.is_open()) {
            throw std::runtime_error("Can't connect to postgres db");
        }

        pqxx::work W(C);

        const std::string sql = R"(
            CREATE TABLE IF NOT EXISTS profiles (
                id SERIAL PRIMARY KEY,
                data JSONB NOT NULL
            );
        )";

        W.exec(sql);
        W.commit();

        W.commit();  // commit transaction
    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
        return nullptr;
    }

    return nullptr;
}

bool PostgresProfileGateway::storeProfile(ProfileHandle) {
    return false;
}

