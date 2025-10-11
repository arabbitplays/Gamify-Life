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
    constexpr uint32_t MIN_NAME_SIZE = 3;
    constexpr float NAME_RATIO = 0.1f;
    constexpr int32_t GAP_SIZE = 2;
    constexpr int32_t MIN_DATA_POINT_COUNT = 2;
    constexpr  int32_t DATA_POINT_SIZE = 2;

    const int32_t max_name_size = std::floor(std::max(NAME_RATIO * static_cast<float>(size.x), static_cast<float>(MIN_NAME_SIZE)));
    const int32_t data_point_count = (size.x - GAP_SIZE - max_name_size) / DATA_POINT_SIZE;
    if (data_point_count < MIN_DATA_POINT_COUNT)
        return;

    Date today = Date::createToday();
    Date start_date = today.createPrev(data_point_count - 1);

    // print names and cache needed data points
    std::vector<std::vector<Date>> streak_cache{};
    streak_cache.reserve(streaks.size());
    for (uint32_t i = 0; i < streaks.size(); i++) {
        const StreakHandle streak = streaks.at(i);
        std::string trimmed_name = ScalingUtil::trimToLength(streak->getName(), max_name_size);
        plane->writeText(pos + glm::ivec2(0, i * 2), trimmed_name);

        streak_cache.push_back(streak->getCheckedDatesSince(start_date));
    }

    Date represented_date = start_date;
    for (int32_t i = 0; i < data_point_count; i++) {
        bool is_perfect_day = true;
        for (uint32_t streak_idx = 0; streak_idx < streaks.size(); streak_idx++) {
            auto& checked_dates = streak_cache.at(streak_idx);
            bool checked = std::find(checked_dates.begin(), checked_dates.end(), represented_date) != checked_dates.end();
            if (checked) {
                plane->writeText(glm::ivec2(pos + glm::ivec2(GAP_SIZE + max_name_size + i * DATA_POINT_SIZE, streak_idx * 2)), "\u25CF", SELECTED);
            } else {
                plane->writeText(glm::ivec2(pos + glm::ivec2(GAP_SIZE + max_name_size + i * DATA_POINT_SIZE, streak_idx * 2)), "\u25CF");
                is_perfect_day = false;
            }
        }

        if (is_perfect_day) {
            drawPerfectDay(plane, pos + glm::ivec2(GAP_SIZE + max_name_size + i * DATA_POINT_SIZE, 0), streaks.size());
        }
        represented_date = represented_date.createNext(1);
    }
}

void StreakMatrix::drawPerfectDay(const PlaneHandle& plane, glm::ivec2 pos, uint32_t streak_count) const {
    for (uint32_t streak_idx = 0; streak_idx < streak_count; streak_idx++) {
        plane->writeText(glm::ivec2(pos + glm::ivec2(0, streak_idx * 2)), "\u25CF", GOLD);
    }
}


