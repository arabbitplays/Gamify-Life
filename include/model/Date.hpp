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
    explicit Date(std::chrono::year_month_day ymd);

    [[nodiscard]] uint32_t getYear() const;
    [[nodiscard]] uint32_t getMonth() const;
    [[nodiscard]] uint32_t getDay() const;

    Date createNext(uint32_t delta = 1) const;
    Date createPrev(uint32_t delta = 1) const;

    bool operator==(const Date & d) const;
    bool operator<(const Date& other) const;

    static Date createToday() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto today = floor<days>(now);
        year_month_day ymd = year_month_day{today};

        Date date{ymd};
        return date;
    }

private:
    std::chrono::year_month_day ymd;
};

namespace std {
    template <>
    struct hash<Date> {
        std::size_t operator()(const Date& d) const noexcept {
            return std::hash<uint32_t>()(d.getDay()) ^ (std::hash<uint32_t>()(d.getMonth()) << 1) ^ (std::hash<uint32_t>()(d.getYear()) << 2);
        }
    };
}


#endif //GAMIFY_LIFE_DATE_HPP