//
// Created by oschdi on 12.10.25.
//

#ifndef GAMIFY_LIFE_HISTOGRAM_HPP
#define GAMIFY_LIFE_HISTOGRAM_HPP
#include "model/Profile.hpp"
#include "view/not_curses/NotCursesPlane.hpp"

class Histogram;
typedef std::shared_ptr<Histogram> HistogramHandle;

class Histogram {
private:
    struct Datapoint {
        std::string key;
        float value;
    };

    static constexpr int32_t X_AXIS_HEIGHT = 1;
    static constexpr int32_t Y_AXIS_WIDTH = 3;

public:
    Histogram() = default;

    void drawToPlane(const PlaneHandle& plane_handle, glm::ivec2 pos, glm::ivec2 size) const;

    static uint32_t getDatapointCount(glm::ivec2 size);
    void addDatapoint(const std::string &key, float value);
    void clear();

private:
    static void drawHistogramBar(const PlaneHandle& plane, glm::ivec2 pos, float bar_height);
    static std::string getResidualSegmentCharacter(double value);

    std::vector<Datapoint> datapoints{};
};


#endif //GAMIFY_LIFE_HISTOGRAM_HPP