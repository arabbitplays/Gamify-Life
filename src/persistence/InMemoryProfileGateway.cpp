//
// Created by oschdi on 09.10.25.
//

#include "../../include/persistence/InMemoryProfileGateway.hpp"

void InMemoryProfileGateway::loadProfile() {
    profile = std::make_shared<Profile>("Oschdi");
}

ProfileHandle InMemoryProfileGateway::getProfile() {
    return profile;
}
