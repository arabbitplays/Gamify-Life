//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKWINDOW_HPP
#define GAMIFY_LIFE_TASKWINDOW_HPP
#include "controller/ProfileController.hpp"
#include "controller/TaskController.hpp"
#include "view/not_curses/windows/BorderWindow.hpp"

class TaskWindow : public BorderWindow {
    static constexpr std::string TASK_WINDOW_NAME = "Tasks Available";

public:
    TaskWindow(const std::shared_ptr<TaskController> &task_controller,
            const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane)
            : BorderWindow(TASK_WINDOW_NAME, parent_plane, glm::ivec2(10, 10), TOP_RIGHT),
            task_controller(task_controller), profile_controller(profile_controller) {
        setMargin(glm::ivec2(2, 1));
    }
    void draw() override;
    void handleInput(ncinput input) override;

    void handleActiveInput(ncinput input);

private:
    std::shared_ptr<TaskController> task_controller;
    std::shared_ptr<ProfileController> profile_controller;
};


#endif //GAMIFY_LIFE_TASKWINDOW_HPP