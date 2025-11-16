//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP
#define GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP
#include "controller/IProfileGateway.hpp"


class InMemoryProfileGateway : public IProfileGateway {
public:
    InMemoryProfileGateway() = default;

    ProfileHandle loadProfile(std::string name) override;
    ProfileHandle createProfile(std::string name) override;
    void addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) override;


private:
    ProfileHandle profile;
};


#endif //GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP