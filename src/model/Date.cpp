//
// Created by oschdi on 05.10.25.
//

#include "model/Date.hpp"

Date::Date(const uint32_t year, const uint32_t month, const uint32_t day) {
    std::chrono::year y{static_cast<int32_t>(year)};
    std::chrono::month m{month};
    std::chrono::day d{day};

    ymd = {y, m, d};
}

Date::Date(std::chrono::year_month_day ymd) : ymd(ymd) {
}

uint32_t Date::getYear() const {
    return static_cast<uint32_t>(int(ymd.year()));
}

uint32_t Date::getMonth() const {
    return static_cast<uint32_t>(ymd.month());
}

uint32_t Date::getDay() const {
    return static_cast<uint32_t>(ymd.day());
}

uint32_t Date::getWeekdayIdx() const {
    using namespace std::chrono;

    sys_days sd = ymd;
    weekday wd{sd};

    return wd.c_encoding();
}

Date Date::createNext(uint32_t delta) const {
    using namespace std::chrono;
    sys_days sd{ymd};
    sd += days{delta};
    year_month_day next_ymd = {sd};
    Date result(next_ymd);
    return result;
}

Date Date::createPrev(uint32_t delta) const {
    using namespace std::chrono;
    sys_days sd{ymd};
    sd -= days{delta};
    year_month_day next_ymd = {sd};
    Date result(next_ymd);
    return result;
}

bool Date::operator==(const Date & d) const {
    return ymd == d.ymd;
}

bool Date::operator<(const Date &other) const {
    return ymd < other.ymd;
}