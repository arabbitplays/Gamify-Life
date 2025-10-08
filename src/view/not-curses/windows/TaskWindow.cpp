//
// Created by oschdi on 08.10.25.
//

#include "TaskWindow.hpp"

#include <cmath>
#include <vector>

#include "Task.hpp"

void TaskWindow::draw() const {
    NotCursesWindow::draw();
    uint32_t first_col_x = 1;
    uint32_t second_col_x = 20;

    plane->writeText(glm::ivec2(first_col_x, 1), "Tasks:");

    plane->writeText(glm::ivec2(first_col_x, 2), "Name:");
    plane->writeText(glm::ivec2(second_col_x, 2), "Points:");

    std::vector<TaskHandle> tasks = task_controller->getAvailableTasks();
    for (uint32_t i = 0; i < tasks.size(); i++) {
        uint32_t displayed_score = std::floor(tasks.at(i)->getScore());
        plane->writeText(glm::ivec2(first_col_x, 3 + i), tasks.at(i)->getName());
        plane->writeText(glm::ivec2(second_col_x, 3 + i), std::to_string(displayed_score));
    }

}
