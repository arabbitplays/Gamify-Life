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
public:
    StreakMatrix() = default;

    void addStreak(const StreakHandle& streak);
    void drawToPlane(const PlaneHandle& plane, glm::ivec2 pos, glm::ivec2 size) const;
    void clear();

private:
    void drawPerfectDay(const PlaneHandle& plane, glm::ivec2 pos, uint32_t streak_count) const;

    std::vector<StreakHandle> streaks;
};


#endif //GAMIFY_LIFE_STREAKMATRIX_HPP