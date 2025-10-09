//
// Created by oschdi on 06.10.25.
//

#ifndef GAMIFY_LIFE_IFRONTEND_HPP
#define GAMIFY_LIFE_IFRONTEND_HPP
#include <memory>

#include "../controller/AppController.hpp"


class IFrontend;
typedef std::shared_ptr<IFrontend> FrontendHandle;

class IFrontend {
public:
    virtual ~IFrontend() = default;

    virtual void init(const std::shared_ptr<AppController>& app_controller) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
};

#endif //GAMIFY_LIFE_IFRONTEND_HPP