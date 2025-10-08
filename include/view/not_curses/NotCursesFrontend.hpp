//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#define GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#include "NotCursesInstance.hpp"
#include "view/IFrontend.hpp"


class NotCursesFrontend : public IFrontend {
public:
    NotCursesFrontend() = default;

    void init() override;
    void run() override;

    void handleInput();

    void stop() override;

private:
    std::shared_ptr<NotCursesInstance> instance;
    PlaneHandle main_plane;

    bool stopped = false;
};


#endif //GAMIFY_LIFE_NOTCURSORFRONTEND_HPP