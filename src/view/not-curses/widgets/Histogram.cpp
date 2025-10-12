//
// Created by oschdi on 12.10.25.
//

#include "../../../../include/view/not_curses/widgets/Histogram.hpp"

void Histogram::drawToPlane(const PlaneHandle &plane, glm::ivec2 size) const {
    uint32_t curr_row = 0;
    for (const auto& [key, value] : datapoints) {
        if (value == 0) {
            plane->writeText(glm::ivec2(0, curr_row++), key);
        }
    }
}

uint32_t Histogram::getDatapointCount(const glm::ivec2 size) {
    return size.y - Y_AXIS_WIDTH;
}


void Histogram::addDatapoint(const std::string &key, const float value) {
    datapoints.push_back({key, value});
}

void Histogram::clear() {
    datapoints.clear();
}
