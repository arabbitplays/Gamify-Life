//
// Created by oschdi on 08.10.25.
//

#include "TaskWindow.hpp"

#include <cmath>
#include <vector>

void TaskWindow::draw() const {
    BorderWindow::draw();
    uint32_t col_distance = 20;

    uint32_t header_y = 0;
    content_plane->writeText(glm::ivec2(0, header_y), "Name:", DEFAULT, BOLD);
    content_plane->writeText(glm::ivec2(col_distance, header_y), "Points:", DEFAULT, BOLD);

    std::vector<TaskHandle> tasks = task_controller->getAvailableTasks();
    for (uint32_t i = 0; i < tasks.size(); i++) {
        uint32_t displayed_score = std::floor(tasks.at(i)->getScore());
        content_plane->writeText(glm::ivec2(0, header_y + i + 1), tasks.at(i)->getName());
        content_plane->writeText(glm::ivec2(col_distance, header_y + i + 1), std::to_string(displayed_score));
    }
}
