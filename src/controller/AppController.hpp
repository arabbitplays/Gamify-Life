//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_APPCONTROLLER_HPP
#define GAMIFY_LIFE_APPCONTROLLER_HPP
#include <memory>

#include "TaskController.hpp"

struct AppController {
public:
    std::shared_ptr<TaskController> task_controller;
};

#endif //GAMIFY_LIFE_APPCONTROLLER_HPP