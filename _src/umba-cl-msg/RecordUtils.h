#pragma once

#include "Record.h"
//
#include <string>
#include <map>

// https://en.cppreference.com/w/cpp/container/map
// https://en.cppreference.com/w/cpp/string/basic_string

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// using RecordStringCountersMap = std::map<std::string, std::size_t>;
using RecordStringCountersMap = std::map<std::string, std::size_t, StringLessPriorBySize>;
using RecordStringSet         = std::set<std::string, StringLessPriorBySize>;
using RecordStringMap         = std::map<std::string, Record, StringLessPriorBySize>;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// template<typename THandler> void findAllTypeStringsImpl(const             Record  &r , std::size_t lvl, THandler &handler, bool cleanTypes=true);
// template<typename THandler> void findAllTypeStringsImpl(const std::vector<Record> &vr, THandler &handler, bool cleanTypes=true);

template<typename THandler>
void traverseRecordsRecursive(const Record &r,  std::size_t lvl, THandler &handler, bool cleanTypes=true)
{
    #ifndef NDEBUG
    auto ser = r.serialize(!cleanTypes);
    #endif

    bool isQuoted = r.isQuoted();
    if (lvl>0)
        isQuoted = true;

    if (isQuoted && !r.isParamList())
        handler(r);

    if (r.hasNested())
        traverseRecordsRecursive(r.getNested(), lvl+1, handler, cleanTypes);

    for(auto && ar : r.getArgs())
        traverseRecordsRecursive(ar, lvl+1, handler, cleanTypes);
}

template<typename THandler>
void traverseRecordsRecursive(const std::vector<Record> &vr, THandler &handler, bool cleanTypes=true)
{
    for(auto && ar : vr)
    {
        if (ar.isQuoted())
        {
            traverseRecordsRecursive(ar, 0, handler, cleanTypes);
        }
    }
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
void findAllTypeStrings(const Record &r, RecordStringCountersMap &countMap, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        countMap[str]++;
    };

    traverseRecordsRecursive(r, 0, handler, cleanTypes);
}

void findAllTypeStrings(const std::vector<Record> &vr, RecordStringCountersMap &countMap, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        countMap[str]++;
    };

    traverseRecordsRecursive(vr, handler, cleanTypes);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
void findAllTypeStrings(const Record &r, RecordStringSet &s, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        s.insert(str);
    };

    traverseRecordsRecursive(r, 0, handler, cleanTypes);
}

void findAllTypeStrings(const std::vector<Record> &vr, RecordStringSet &s, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        s.insert(str);
    };

    traverseRecordsRecursive(vr, handler, cleanTypes);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
void findAllTypeStrings(const Record &r, RecordStringMap &m, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        m[str] = r_;
    };

    traverseRecordsRecursive(r, 0, handler, cleanTypes);
}

void findAllTypeStrings(const std::vector<Record> &vr, RecordStringMap &m, bool cleanTypes=true)
{
    auto handler = [&](const Record &r_)
    {
        auto str = r_.serialize(!cleanTypes);
        m[str] = r_;
    };

    traverseRecordsRecursive(vr, handler, cleanTypes);
}

//----------------------------------------------------------------------------






