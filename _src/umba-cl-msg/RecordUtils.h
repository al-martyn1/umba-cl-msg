#pragma once

#include "Record.h"
//
#include <string>
#include <map>

// https://en.cppreference.com/w/cpp/container/map
// https://en.cppreference.com/w/cpp/string/basic_string


struct StringLessPriorBySize
{
    bool operator()(const std::string &s1, const std::string &s2) const
    {
        if (s1.size()<s2.size())
            return true;

        if (s1.size()>s2.size())
            return false;

        int cmp = s1.compare(s2);
        return cmp<0;
    }

}; // struct StringLessPriorBySize


// using RecordStringCountersMap = std::map<std::string, std::size_t>;
using RecordStringCountersMap = std::map<std::string, std::size_t, StringLessPriorBySize>;


inline
void findAllNestedTypesIncHelper(const std::string &r, RecordStringCountersMap &countMap)
{
    ++countMap[r];
}

void findAllNestedTypes(const             Record  &r , RecordStringCountersMap &countMap, bool cleanTypes=true);
void findAllNestedTypes(const std::vector<Record> &vr, RecordStringCountersMap &countMap, bool cleanTypes=true);

inline
void findAllNestedTypes(const Record &r, RecordStringCountersMap &countMap, bool cleanTypes)
{
    if (r.quoted)
        findAllNestedTypesIncHelper(r.serialize(!cleanTypes), countMap);
    for(auto && ar : r.args)
        findAllNestedTypes(ar, countMap, cleanTypes);
}

void findAllNestedTypes(const std::vector<Record> &vr, RecordStringCountersMap &countMap, bool cleanTypes)
{
    for(auto && ar : vr)
    {
        if (ar.quoted)
        {
            findAllNestedTypes(ar, countMap, cleanTypes);
        }
    }
}

