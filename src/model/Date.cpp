//
// Created by oschdi on 05.10.25.
//

#include "../../include/model/Date.hpp"

Date::Date(uint32_t year, uint32_t month, uint32_t day) : year(year), month(month), day(day) {

}

bool Date::operator==(const Date & d) const {
    return year == d.year && month == d.month && day == d.day;
}
