//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_IPROFILEGATEWAY_HPP
#define GAMIFY_LIFE_IPROFILEGATEWAY_HPP
#include "model/Profile.hpp"

class IProfileGateway {
public:
    virtual ~IProfileGateway() = default;

    virtual ProfileHandle loadProfile(std::string name) = 0;
    virtual ProfileHandle createProfile(std::string name) = 0;
    virtual void addDoneTaskToProfile(std::string profile_name, Date date, TaskHandle task_handle) = 0;
};


#endif //GAMIFY_LIFE_IPROFILEGATEWAY_HPP
