//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#define GAMIFY_LIFE_NOTCURSORFRONTEND_HPP
#include "NotCursorInstance.hpp"
#include "view/IFrontend.hpp"


class NotCursorFrontend : public IFrontend {
public:
    NotCursorFrontend() = default;

    void init() override;
    void render() override;
    void stop() override;

private:
    std::shared_ptr<NotCursorInstance> instance;
    std::shared_ptr<NotCursorPlane> main_plane;
};


#endif //GAMIFY_LIFE_NOTCURSORFRONTEND_HPP