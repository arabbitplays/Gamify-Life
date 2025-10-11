//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_STREAKFACTORY_HPP
#define GAMIFY_LIFE_STREAKFACTORY_HPP
#include <ranges>

#include "model/Profile.hpp"
#include "model/Streak.hpp"

class StreakFactory {
public:
    StreakFactory() = delete;

    static std::vector<StreakHandle> createStreakForProfile(const ProfileHandle& profile) {
        std::unordered_map<Date, std::vector<TaskHandle>> done_tasks = profile->getDoneTasks();
        std::unordered_map<std::string, StreakHandle> streak_map{};

        for (const auto& [date, task_list] : done_tasks) {
            for (const auto& task : task_list) {
                std::string streak_name = task->getStreakName();
                if (streak_name.empty())
                    continue;

                if (!streak_map.contains(streak_name)) {
                    const auto new_streak = std::make_shared<Streak>(streak_name);
                    streak_map[streak_name] = new_streak;
                }

                streak_map[streak_name]->checkForDate(date);
            }
        }

        std::vector<StreakHandle> result{};
        result.reserve(streak_map.size());
        for (const auto &streak: streak_map | std::views::values) {
            result.push_back(streak);
        }

        return result;
    }
};

#endif //GAMIFY_LIFE_STREAKFACTORY_HPP