//
// Created by oschdi on 08.10.25.
//

#include "TaskWindow.hpp"

#include <cmath>
#include <vector>

#include "Task.hpp"

void TaskWindow::draw() const {
    BorderWindow::draw();
    uint32_t first_col_x = LEFT_MARGIN + 1;
    uint32_t second_col_x = LEFT_MARGIN + 20;

    uint32_t header_y = 2;

    plane->writeText(glm::ivec2(first_col_x, header_y), "Name:", DEFAULT, BOLD | ITALIC);
    plane->writeText(glm::ivec2(second_col_x, header_y), "Points:", DEFAULT, BOLD);

    std::vector<TaskHandle> tasks = task_controller->getAvailableTasks();
    for (uint32_t i = 0; i < tasks.size(); i++) {
        uint32_t displayed_score = std::floor(tasks.at(i)->getScore());
        plane->writeText(glm::ivec2(first_col_x, header_y + i + 1), tasks.at(i)->getName());
        plane->writeText(glm::ivec2(second_col_x, header_y + i + 1), std::to_string(displayed_score));
    }

}
