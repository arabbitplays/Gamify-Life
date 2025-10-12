//
// Created by oschdi on 08.10.25.
//

#ifndef GAMIFY_LIFE_TASKWINDOW_HPP
#define GAMIFY_LIFE_TASKWINDOW_HPP
#include "controller/ProfileController.hpp"
#include "controller/TaskController.hpp"
#include "view/not_curses/widgets/SelectionTable.hpp"
#include "view/not_curses/windows/BorderWindow.hpp"

class TaskWindow : public BorderWindow {
    static constexpr std::string TASK_WINDOW_NAME = "Tasks Available";
    static constexpr std::string TASK_WINDOW_SHORT_NAME = "Tasks";

public:
    TaskWindow(const std::shared_ptr<TaskController> &task_controller,
            const std::shared_ptr<ProfileController> &profile_controller, const PlaneHandle &parent_plane);
    void draw() override;
    void handleInput(ncinput input) override;

    void handleActiveInput(ncinput input);

private:
    std::shared_ptr<TaskController> task_controller;
    std::shared_ptr<ProfileController> profile_controller;

    SelectionTableHandle tasks_table;
};


#endif //GAMIFY_LIFE_TASKWINDOW_HPP