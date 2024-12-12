#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>



struct NameGenerator
{
    std::unordered_map<std::string, std::size_t>    counters;

    std::string generateName(const std::string &baseName)
    {
        auto cnt = ++counters[baseName];
        return baseName + "_" + std::to_string(cnt);
    }

}; // struct NameGenerator