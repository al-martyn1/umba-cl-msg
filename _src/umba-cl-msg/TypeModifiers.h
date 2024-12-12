#pragma once


#include <string>
#include <unordered_set>
#include <vector>


struct TypeModifiers
{
    std::unordered_set<std::string>              prefixModifiers   ;
    std::unordered_map<std::string, std::size_t> suffixModifiersMap; 
    std::vector<std::string>                     suffixModifiers   ; // Порядок суффиксов имеет значение - так, нельзя проверять & до &&

    bool addPrefixModifier(std::string m)
    {
        if (m.empty())
            return false;

        if (umba::string::is_alpha(m.back())) // Если обычная буква, не символ, то должна отделяться от остального пробелом
            m.append(1, ' ');

        prefixModifiers.insert(m);

        return true;
    }

    bool addSuffixModifier(std::string m)
    {
        // Надо ли модифицировать буквенные суффиксы?

        if (suffixModifiersMap.find(m)!=suffixModifiersMap.end())
            return true; // already exist

        suffixModifiersMap[m] = suffixModifiers.size();
        suffixModifiers.emplace_back(m);

        return true;
    }

};