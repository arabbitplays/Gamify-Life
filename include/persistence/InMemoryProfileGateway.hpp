//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP
#define GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP
#include "controller/IProfileGateway.hpp"


class InMemoryProfileGateway : public IProfileGateway {
public:
    InMemoryProfileGateway() = default;
    void loadProfile() override;
    ProfileHandle getProfile() override;

private:
    ProfileHandle profile;
};


#endif //GAMIFY_LIFE_INMEMORYPROFILEREPOSITORY_HPP