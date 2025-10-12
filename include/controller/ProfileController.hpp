//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_PROFILECONTROLLER_HPP
#define GAMIFY_LIFE_PROFILECONTROLLER_HPP
#include "IProfileGateway.hpp"
#include "ITaskRepository.hpp"
#include "model/Profile.hpp"

class ProfileController {
public:
    ProfileController(const std::shared_ptr<ITaskRepository> &task_repo, const std::shared_ptr<IProfileGateway>& profile_repo);
    void loadProfile(const std::string &name);

    std::string getName() const;
    void addDoneTaskToday(const std::string &task_name) const;

    float getTotalScoreAtDate(const Date& date) const;
    std::vector<TaskHandle> getTasksDoneAtDate(const Date& date) const;

    std::vector<StreakHandle> getStreaks() const;

private:
    ProfileHandle profile;

    std::shared_ptr<ITaskRepository> task_repo;
    std::shared_ptr<IProfileGateway> profile_gateway;
};


#endif //GAMIFY_LIFE_PROFILECONTROLLER_HPP