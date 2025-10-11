//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_STREAK_HPP
#define GAMIFY_LIFE_STREAK_HPP
#include <set>
#include <string>
#include <vector>

#include "Date.hpp"
#include "Task.hpp"

class Streak;
typedef std::shared_ptr<Streak> StreakHandle;

class Streak {
public:
    explicit Streak(const std::string &name);

    void checkStreakForToday();
    void checkForDate(const Date& date);
    std::set<Date> getCheckedDates();

    std::string getName();

private:
    std::string name;

    std::set<Date> checked_dates{};
};


#endif //GAMIFY_LIFE_STREAK_HPP