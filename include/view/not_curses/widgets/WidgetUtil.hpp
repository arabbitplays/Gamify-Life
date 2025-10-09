//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_WIDGETUTIL_HPP
#define GAMIFY_LIFE_WIDGETUTIL_HPP
#include <memory>

#include "Table.hpp"
#include "model/Task.hpp"

class WidgetUtil {
public:
    WidgetUtil() = delete;

    static std::shared_ptr<Table> convertTaskListToTable(const std::vector<TaskHandle> &tasks) {
        std::shared_ptr<Table> table = std::make_shared<Table>(2);
        table->addHeader({"Task:", "Points:"});
        for (const auto& task : tasks) {
            uint32_t displayed_score = std::floor(task->getScore());
            table->addRow({task->getName(), std::to_string(displayed_score)});
        }
        return table;
    }
};

#endif //GAMIFY_LIFE_WIDGETUTIL_HPP