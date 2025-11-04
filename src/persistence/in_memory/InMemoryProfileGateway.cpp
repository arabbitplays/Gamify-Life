//
// Created by oschdi on 09.10.25.
//

#include "../../../include/persistence/in_memory/InMemoryProfileGateway.hpp"

ProfileHandle InMemoryProfileGateway::loadProfile(std::string name) {
    if (profile == nullptr) {
        profile = createProfile(name);
    }
    return profile;
}

ProfileHandle InMemoryProfileGateway::createProfile(std::string name) {
    return std::make_shared<Profile>(name);
}

void InMemoryProfileGateway::addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) {
    // intentionally empty
}
