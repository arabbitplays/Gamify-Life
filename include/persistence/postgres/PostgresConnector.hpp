#ifndef GAMIFY_LIFE_POSTGRESCONNECTOR_HPP
#define GAMIFY_LIFE_POSTGRESCONNECTOR_HPP
#include <pqxx/connection.hxx>

#include "controller/ConfigYamlKeys.hpp"

inline std::shared_ptr<pqxx::connection> getPostgresConnection(const YAML::Node& config_node)
{
    static std::shared_ptr<pqxx::connection> connection_ptr;

    if (!connection_ptr)
    {
        std::string con_string =
            "dbname=" + config_node[PERSISTENCE_POSTGRES_DBNAME_KEY].as<std::string>()
        + " user=" + config_node[PERSISTENCE_POSTGRES_USER_KEY].as<std::string>()
        + " host=" + config_node[PERSISTENCE_POSTGRES_HOST_KEY].as<std::string>();
        connection_ptr = std::make_shared<pqxx::connection>(con_string);
    }

    return connection_ptr;
}

#endif //GAMIFY_LIFE_POSTGRESCONNECTOR_HPP
