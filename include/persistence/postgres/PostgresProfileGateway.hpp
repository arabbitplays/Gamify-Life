//
// Created by oschdi on 30.10.25.
//

#ifndef POSTGRESPROFILEGATEWAY_HPP
#define POSTGRESPROFILEGATEWAY_HPP
#include "controller/IProfileGateway.hpp"
#include <pqxx/pqxx>

class PostgresProfileGateway : public IProfileGateway {
public:
    PostgresProfileGateway() = default;

    ProfileHandle loadProfile(std::string name) override;
    bool storeProfile(ProfileHandle) override;
};



#endif //POSTGRESPROFILEGATEWAY_HPP
