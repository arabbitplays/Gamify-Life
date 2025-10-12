//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_STREAKMATRIX_HPP
#define GAMIFY_LIFE_STREAKMATRIX_HPP
#include <glm/vec2.hpp>

#include "model/Streak.hpp"
#include "view/not_curses/NotCursesPlane.hpp"

class StreakMatrix;
typedef std::shared_ptr<StreakMatrix> StreakMatrixHandle;

class StreakMatrix {
private:
    static constexpr uint32_t MIN_NAME_SIZE = 3;
    static constexpr float NAME_RATIO = 0.1f;
    static constexpr int32_t GAP_SIZE = 2;
    static constexpr int32_t MIN_DATA_POINT_COUNT = 2;
    static constexpr  int32_t DATA_POINT_SIZE = 2;
    static constexpr int32_t FIRST_ROW_Y_OFFSET = 1;
    static constexpr int32_t WEEKDAY_MARKER_ROW = 0;
public:
    StreakMatrix() = default;

    void addStreak(const StreakHandle& streak);
    void drawToPlane(const PlaneHandle& plane, glm::ivec2 pos, glm::ivec2 size) const;
    void clear();

private:
    void printName(const PlaneHandle& plane, glm::ivec2 base_pos, std::string name, uint32_t max_name_size, uint32_t streak_idx, Color color) const;
    void drawCirleOfMatrix(const PlaneHandle& plane, glm::ivec2 base_pos, uint32_t streak_idx, uint32_t day_idx, Color color, uint32_t name_size) const;
    void drawPerfectDay(const PlaneHandle& plane, glm::ivec2 pos, uint32_t streak_count, uint32_t day_idx, uint32_t name_size) const;
    void drawWeekdayMarker(const PlaneHandle& plane, glm::ivec2 base_pos, uint32_t day_idx, uint32_t name_size) const;

    std::vector<StreakHandle> streaks;
};


#endif //GAMIFY_LIFE_STREAKMATRIX_HPP