//
// Created by oschdi on 11.10.25.
//

#include "model/Streak.hpp"

Streak::Streak(const std::string &name) : name(name) {

}

void Streak::checkStreakForToday() {
    Date today = Date::createToday();
    checked_dates.insert(today);
}

void Streak::checkForDate(const Date &date) {
    checked_dates.insert(date);
}

std::vector<Date> Streak::getCheckedDatesSince(const Date& date) {
    std::vector<Date> result {};

    auto it = checked_dates.lower_bound(date);
    for (; it != checked_dates.end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::string Streak::getName() {
    return name;
}

