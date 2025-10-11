//
// Created by oschdi on 09.10.25.
//

#include "../../../include/persistence/in_memory/InMemoryProfileGateway.hpp"

ProfileHandle InMemoryProfileGateway::loadProfile(std::string name) {
    if (profile == nullptr) {
        profile = std::make_shared<Profile>(name);
    }
    return profile;
}

bool InMemoryProfileGateway::storeProfile(ProfileHandle) {
    // Intentional empty
    return true;
}
