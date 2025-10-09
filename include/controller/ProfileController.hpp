//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_PROFILECONTROLLER_HPP
#define GAMIFY_LIFE_PROFILECONTROLLER_HPP
#include "ITaskRepository.hpp"
#include "model/Profile.hpp"


class ProfileController {
public:
    explicit ProfileController(const std::shared_ptr<ITaskRepository> &task_repo);

    void createNewProfile(const std::string& name);
    std::string getName() const;
    void addDoneTaskToday(const std::string &task_name) const;
    float getTotalScoreToday() const;
    std::vector<TaskHandle> getTasksDoneToday() const;
private:
    ProfileHandle profile;

    std::shared_ptr<ITaskRepository> task_repo;
};


#endif //GAMIFY_LIFE_PROFILECONTROLLER_HPP