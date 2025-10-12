//
// Created by oschdi on 12.10.25.
//

#ifndef GAMIFY_LIFE_WORKDAYUTIL_HPP
#define GAMIFY_LIFE_WORKDAYUTIL_HPP
#include "model/Date.hpp"

class DateUtil {
public:
    DateUtil() = delete;

    static std::string getWeekdayAsString(const Date& date) {
        switch (date.getWeekdayIdx()) {
            case 0:
                return "Su";
            case 1:
                return "Mo";
            case 2:
                return "Tu";
            case 3:
                return "We";
            case 4:
                return "Th";
            case 5:
                return "Fr";
            case 6:
                return "Sa";
            default:
                return "";
        }
    }

    static std::string getDateAsString(const Date& date) {
        std::string result = "";
        if (date.getDay() < 10)
            result += "0";
        result += std::to_string(date.getDay()) + ".";

        if (date.getMonth() < 10)
            result += "0";
        result += std::to_string(date.getMonth()) + ".";

        result += std::to_string(date.getYear());

        return result;
    }
};

#endif //GAMIFY_LIFE_WORKDAYUTIL_HPP