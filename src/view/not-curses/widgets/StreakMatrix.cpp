//
// Created by oschdi on 11.10.25.
//

#include "view/not_curses/widgets/StreakMatrix.hpp"

#include "view/not_curses/widgets/ScalingUtil.hpp"
#include "view/not_curses/windows/BorderWindow.hpp"
#include "view/not_curses/windows/BorderWindow.hpp"

void StreakMatrix::addStreak(const StreakHandle &streak) {
    streaks.push_back(streak);
}

void StreakMatrix::clear() {
    streaks.clear();
}

void StreakMatrix::drawToPlane(const PlaneHandle &plane, const glm::ivec2 pos, const glm::ivec2 size) const {
    const int32_t max_name_size = std::floor(std::max(NAME_RATIO * static_cast<float>(size.x), static_cast<float>(MIN_NAME_SIZE)));
    const int32_t data_point_count = (size.x - GAP_SIZE - max_name_size) / DATA_POINT_SIZE;
    if (data_point_count < MIN_DATA_POINT_COUNT)
        return;

    Date today = Date::createToday();
    Date start_date = today.createPrev(data_point_count - 1);

    // cache needed data points
    std::vector<std::vector<Date>> streak_cache{};
    streak_cache.reserve(streaks.size());
    for (uint32_t i = 0; i < streaks.size(); i++) {
        const StreakHandle streak = streaks.at(i);
        streak_cache.push_back(streak->getCheckedDatesSince(start_date));
    }

    Date represented_date = start_date;
    for (int32_t day_idx = 0; day_idx < data_point_count; day_idx++) {
        if (represented_date.getWeekdayIdx() == 1) {
            drawWeekdayMarker(plane, pos, day_idx, max_name_size);
        }

        bool is_perfect_day = true;
        for (uint32_t streak_idx = 0; streak_idx < streaks.size(); streak_idx++) {
            auto& checked_dates = streak_cache.at(streak_idx);
            const bool checked = std::find(checked_dates.begin(), checked_dates.end(), represented_date) != checked_dates.end();

            Color circle_color = DEFAULT;
            if (checked)
                circle_color = SELECTED;
            else
                is_perfect_day = false;
            drawCirleOfMatrix(plane, pos, streak_idx, day_idx, circle_color, max_name_size);

            // print names
            if (represented_date == today) {
                Color name_color = DEFAULT;
                if (is_perfect_day)
                    name_color = GOLD;
                else if (checked)
                    name_color = SELECTED;
                printName(plane, pos, streaks.at(streak_idx)->getName(), max_name_size,  streak_idx, name_color);
            }
        }

        if (is_perfect_day) {
            drawPerfectDay(plane, pos, streaks.size(), day_idx, max_name_size);
        }

        represented_date = represented_date.createNext();
    }
}

void StreakMatrix::printName(const PlaneHandle& plane, glm::ivec2 base_pos, std::string name, uint32_t max_name_size, uint32_t streak_idx, Color color) const {
    std::string trimmed_name = ScalingUtil::trimToLength(name, max_name_size);
    plane->writeText(base_pos + glm::ivec2(0, FIRST_ROW_Y_OFFSET + streak_idx * 2), trimmed_name, color);
}

void StreakMatrix::drawWeekdayMarker(const PlaneHandle& plane, glm::ivec2 base_pos, uint32_t day_idx, uint32_t name_size) const {
    plane->writeText(base_pos + glm::ivec2(GAP_SIZE + name_size + day_idx * DATA_POINT_SIZE, WEEKDAY_MARKER_ROW), "Mo");
}

void StreakMatrix::drawCirleOfMatrix(const PlaneHandle& plane, glm::ivec2 base_pos, uint32_t streak_idx, uint32_t day_idx, Color color, uint32_t name_size) const {
    plane->writeText(glm::ivec2(base_pos + glm::ivec2(GAP_SIZE + name_size + day_idx * DATA_POINT_SIZE, FIRST_ROW_Y_OFFSET + streak_idx * 2)), "\u25CF", color);
}

void StreakMatrix::drawPerfectDay(const PlaneHandle& plane, glm::ivec2 pos, uint32_t streak_count, uint32_t day_idx, uint32_t name_size) const {
    for (uint32_t streak_idx = 0; streak_idx < streak_count; streak_idx++) {
        drawCirleOfMatrix(plane, pos, streak_idx, day_idx, GOLD, name_size);
    }
}


