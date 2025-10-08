//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKWINDOW_HPP
#define GAMIFY_LIFE_TASKWINDOW_HPP
#include "BorderWindow.hpp"
#include "NotCursesWindow.hpp"
#include "TaskController.hpp"


class TaskWindow : public BorderWindow {
    static constexpr std::string TASK_WINDOW_NAME = "Tasks Available";

public:
    TaskWindow(const std::shared_ptr<TaskController> &task_controller, const PlaneHandle &parent_plane, const WindowAlignment alignment)
        : BorderWindow(TASK_WINDOW_NAME, parent_plane, glm::ivec2(10, 10), alignment), task_controller(task_controller) {}
    void draw() const override;

private:
    std::shared_ptr<TaskController> task_controller;
};


#endif //GAMIFY_LIFE_TASKWINDOW_HPP