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
    virtual bool storeProfile(ProfileHandle) = 0;
};


#endif //GAMIFY_LIFE_IPROFILEGATEWAY_HPP