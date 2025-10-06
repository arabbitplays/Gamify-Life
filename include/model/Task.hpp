//
// Created by oschdi on 05.10.25.
//

#ifndef GAMIFY_LIFE_TASK_HPP
#define GAMIFY_LIFE_TASK_HPP
#include <cstdint>
#include <memory>
#include <string>

class Task;
typedef std::shared_ptr<Task> TaskHandle;

class Task {
public:
    Task(std::string name, uint32_t score);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] float getScore() const;
private:
    std::string name;
    uint32_t score;
};


#endif //GAMIFY_LIFE_TASK_HPP