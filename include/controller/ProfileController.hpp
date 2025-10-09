//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_PROFILECONTROLLER_HPP
#define GAMIFY_LIFE_PROFILECONTROLLER_HPP
#include "model/Profile.hpp"


class ProfileController {
public:
    ProfileController();

    void createNewProfile(const std::string& name);
    std::string getName() const;
    void addDoneTaskToday(const TaskHandle &task) const;
    float getTotalScoreToday() const;
    std::vector<TaskHandle> getTasksDoneToday() const;
private:
    ProfileHandle profile;
};


#endif //GAMIFY_LIFE_PROFILECONTROLLER_HPP