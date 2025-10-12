//
// Created by oschdi on 05.10.25.
//

#ifndef GAMIFY_LIFE_PROFILE_HPP
#define GAMIFY_LIFE_PROFILE_HPP
#include <unordered_map>
#include <vector>

#include "Date.hpp"
#include "Streak.hpp"
#include "Task.hpp"

class Profile;
typedef std::shared_ptr<Profile> ProfileHandle;

class Profile {
public:
    explicit Profile(std::string name);

    void addDoneTaskToday(const TaskHandle &task);
    void addDoneTask(const TaskHandle& task, const Date& date);

    void addStreaks(const std::vector<StreakHandle> & new_streaks);
    std::vector<StreakHandle> getStreaks() const;

    std::vector<TaskHandle> getDoneTasksAtDate(const Date& date);
    std::unordered_map<Date, std::vector<TaskHandle>> getDoneTasks();

    std::string getName();


private:
    std::string name;
    std::unordered_map<Date, std::vector<TaskHandle>> done_tasks{};
    std::unordered_map<std::string, StreakHandle> streaks{};
};


#endif //GAMIFY_LIFE_PROFILE_HPP