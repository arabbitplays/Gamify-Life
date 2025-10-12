//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_YAMLPROFILEGATEWAY_HPP
#define GAMIFY_LIFE_YAMLPROFILEGATEWAY_HPP
#include <yaml-cpp/yaml.h>

#include "controller/IProfileGateway.hpp"
#include "controller/ITaskRepository.hpp"

namespace YAML {
    template<>
    struct convert<Date> {
        static Node encode(const Date& date) {
            Node node;
            node["day"] = date.getDay();
            node["month"] = date.getMonth();
            node["year"] = date.getYear();
            return node;
        }

        static bool decode(const Node& node, Date& date) {
            if(!node.IsMap() || node.size() != 3) {
                return false;
            }
            date = Date(
                node["year"].as<uint32_t>(),
                node["month"].as<uint32_t>(),
                node["day"].as<uint32_t>()
            );
            return true;
        }
    };
} // namespace YAML

class YamlProfileGateway : public IProfileGateway {
private:
    static constexpr std::string NAME_KEY = "name";
    static constexpr std::string DONE_TASKS_KEY = "done";
    static constexpr std::string DATE_KEY = "date";
    static constexpr std::string TASKS_NAMES_KEY = "tasks";

public:
    YamlProfileGateway(const std::string &file_path, const std::shared_ptr<ITaskRepository>& task_repo);

    ProfileHandle loadProfile(std::string name) override;
    bool storeProfile(ProfileHandle) override;

private:
    std::string file_path;
    std::shared_ptr<ITaskRepository> task_repository;
};


#endif //GAMIFY_LIFE_YAMLPROFILEGATEWAY_HPP