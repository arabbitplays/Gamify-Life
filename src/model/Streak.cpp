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

std::set<Date> Streak::getCheckedDates() {
    return checked_dates;
}

std::string Streak::getName() {
    return name;
}

