//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_APPCONTROLLER_HPP
#define GAMIFY_LIFE_APPCONTROLLER_HPP
#include <memory>

#include "controller/ProfileController.hpp"
#include "controller/TaskController.hpp"


class AppController {
public:
    AppController() {
        task_controller = std::make_shared<TaskController>();
        profile_controller = std::make_shared<ProfileController>();
    }
    std::shared_ptr<TaskController> task_controller;
    std::shared_ptr<ProfileController> profile_controller;
};

#endif //GAMIFY_LIFE_APPCONTROLLER_HPP