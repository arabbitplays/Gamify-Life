//
// Created by oschdi on 05.10.25.
//

#ifndef GAMIFY_LIFE_TASK_HPP
#define GAMIFY_LIFE_TASK_HPP
#include <cstdint>
#include <memory>
#include <string>
#include <bits/unordered_map.h>

class Task;
typedef std::shared_ptr<Task> TaskHandle;

class Task {
public:
    Task(std::string name, uint32_t score, std::string streak_name = "");

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] float getScore() const;

    std::string getStreakName();

private:
    std::string name;
    std::string streak_name;
    uint32_t score;
};


#endif //GAMIFY_LIFE_TASK_HPP