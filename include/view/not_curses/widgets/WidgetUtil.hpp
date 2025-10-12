//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_WIDGETUTIL_HPP
#define GAMIFY_LIFE_WIDGETUTIL_HPP
#include <memory>

#include "DateUtil.hpp"
#include "Histogram.hpp"
#include "SelectionTable.hpp"
#include "controller/ProfileController.hpp"
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

    static void fillHistogramWithProfile(const HistogramHandle& histogram, const std::shared_ptr<ProfileController>& profile_controller, glm::ivec2 size) {
        const uint32_t datapoint_count = histogram->getDatapointCount(size);

        Date today = Date::createToday();
        Date curr_date = today.createPrev(datapoint_count - 1);
        for (uint32_t i = 0; i < datapoint_count; i++) {
            histogram->addDatapoint(DateUtil::getDateAsStringWithoutYear(curr_date), profile_controller->getTotalScoreAtDate(curr_date));
            curr_date = curr_date.createNext();
        }
    }
};

#endif //GAMIFY_LIFE_WIDGETUTIL_HPP