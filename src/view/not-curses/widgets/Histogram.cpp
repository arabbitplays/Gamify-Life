//
// Created by oschdi on 12.10.25.
//

#include "../../../../include/view/not_curses/widgets/Histogram.hpp"

void Histogram::drawToPlane(const PlaneHandle &plane, glm::ivec2 pos, glm::ivec2 size) const {
    const uint32_t max_bar_height = size.y - X_AXIS_HEIGHT;

    float max_value = 0;
    for (const auto& [key, value] : datapoints) {
        max_value = std::max(value, max_value);
    }

    uint32_t data_point_x_offset = Y_AXIS_WIDTH;
    for (const auto& [key, value] : datapoints) {
        float bar_heigth = value / max_value * static_cast<float>(max_bar_height);
        drawHistogramBar(plane, pos + glm::ivec2(data_point_x_offset, max_bar_height - 1), bar_heigth);

        if ((data_point_x_offset - Y_AXIS_WIDTH) % 8 == 0) {
            plane->writeText(pos + glm::ivec2(data_point_x_offset, max_bar_height), key);
        }
        data_point_x_offset++;
    }

    const uint32_t x_legend_count = std::floor(max_bar_height / 3);
    for (uint32_t i = 0; i < x_legend_count; i++) {
        const uint32_t y_offset = max_bar_height / x_legend_count * i;
        const auto legend_value = static_cast<uint32_t>(std::floor(max_value / static_cast<float>(x_legend_count) * static_cast<float>(x_legend_count - i)));
        plane->writeText(pos + glm::ivec2(0, y_offset), std::to_string(legend_value));
    }
}

// pos is the bottom most bar segment
void Histogram::drawHistogramBar(const PlaneHandle& plane, glm::ivec2 pos, float bar_height) {
    double full_segment_count;
    const double residual_segment_value = std::modf(bar_height, &full_segment_count);

    for (uint32_t i = 0; i < full_segment_count; i++) {
        plane->writeText(pos - glm::ivec2(0, i), "\u28FF", STATS_WINDOW);
    }
    plane->writeText(pos - glm::ivec2(0, full_segment_count), getResidualSegmentCharacter(residual_segment_value), STATS_WINDOW);
}

std::string Histogram::getResidualSegmentCharacter(double value) {
    assert(value >= 0 && value < 1);

    if (value < 1.0 / 8.0) {
        return "\u28C0";
    } else if (value < 1.0f / 4.0f) {
        return "\u28E4";
    } else if (value < 2.0f / 4.0f) {
        return "\u28E4";
    }

    return "\u28F6";
}

uint32_t Histogram::getDatapointCount(const glm::ivec2 size) {
    return size.x - Y_AXIS_WIDTH;
}


void Histogram::addDatapoint(const std::string &key, const float value) {
    datapoints.push_back({key, value});
}

void Histogram::clear() {
    datapoints.clear();
}
