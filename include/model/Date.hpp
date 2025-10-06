//
// Created by oschdi on 05.10.25.
//

#ifndef GAMIFY_LIFE_DATE_HPP
#define GAMIFY_LIFE_DATE_HPP
#include <chrono>
#include <cstdint>
#include <functional>

struct Date {
    Date(uint32_t year, uint32_t month, uint32_t day);

    bool operator==(const Date & d) const;

    uint32_t year, month, day;

    static Date createToday() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto today = floor<days>(now);
        year_month_day ymd = year_month_day{today};

        Date date{ static_cast<uint32_t>(static_cast<int>(ymd.year())), static_cast<uint32_t>(ymd.month()), static_cast<uint32_t>(ymd.day()) };
        return date;
    }
};

namespace std {
    template <>
    struct hash<Date> {
        std::size_t operator()(const Date& d) const noexcept {
            return std::hash<uint32_t>()(d.day) ^ (std::hash<uint32_t>()(d.month) << 1) ^ (std::hash<uint32_t>()(d.year) << 2);
        }
    };
}


#endif //GAMIFY_LIFE_DATE_HPP