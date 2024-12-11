#pragma once

#include "Record.h"
//
#include <string>
#include <map>

// https://en.cppreference.com/w/cpp/container/map
// https://en.cppreference.com/w/cpp/string/basic_string


inline
void findAllNestedTypesIncHelper(const std::string &r, std::map<std::string, std::size_t> &countMap)
{
    ++countMap[r];
}

void findAllNestedTypes(const             Record  &r , std::map<std::string, std::size_t> &countMap);
void findAllNestedTypes(const std::vector<Record> &vr, std::map<std::string, std::size_t> &countMap);

inline
void findAllNestedTypes(const Record &r, std::map<std::string, std::size_t> &countMap)
{
    if (r.quoted)
        findAllNestedTypesIncHelper(r.serialize(), countMap);
    for(auto && ar : r.args)
        findAllNestedTypes(ar, countMap);
}

void findAllNestedTypes(const std::vector<Record> &vr, std::map<std::string, std::size_t> &countMap)
{
    for(auto && ar : vr)
    {
        if (ar.quoted)
        {
            findAllNestedTypes(ar, countMap);
        }
    }
}

