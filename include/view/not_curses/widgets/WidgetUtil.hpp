//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_WIDGETUTIL_HPP
#define GAMIFY_LIFE_WIDGETUTIL_HPP
#include <memory>

#include "SelectionTable.hpp"
#include "model/Task.hpp"

class WidgetUtil {
public:
    WidgetUtil() = delete;

    static void fillTableWithTaskList(const TableHandle& table, const std::vector<TaskHandle> &tasks) {
        table->addHeader({"Task:", "Points:"});
        for (const auto& task : tasks) {
            uint32_t displayed_score = std::floor(task->getScore());
            table->addRow({task->getName(), std::to_string(displayed_score)});
        }
    }
};

#endif //GAMIFY_LIFE_WIDGETUTIL_HPP