//
// Created by oschdi on 11.10.25.
//

#ifndef GAMIFY_LIFE_SCALINGUTIL_HPP
#define GAMIFY_LIFE_SCALINGUTIL_HPP
#include <string>

class ScalingUtil {
public:
    ScalingUtil() = delete;

    static std::string trimToLength(const std::string& input, const std::size_t maxLen) {
        if (input.size() <= maxLen)
            return input;
        return input.substr(0, maxLen);
    }
};

#endif //GAMIFY_LIFE_SCALINGUTIL_HPP