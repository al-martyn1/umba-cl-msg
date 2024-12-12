#pragma once


#include "Record.h"
#include "parseClMessage.h"
//
#include <unordered_map>


struct TypeSubsts
{
    using MapType = std::unordered_map<std::string, Record>;

    MapType  substMap;

    bool add(const std::string &substType, const std::string &orgType)
    {
        Record substTypeRec = parseClMessage(substType);
        Record orgTypeRec   = parseClMessage(orgType);

        std::string orgTypeRecSerialized = orgTypeRec.serialize(); // serializeCleanType()
        substTypeRec.quoted = true;

        substMap[orgTypeRecSerialized] = substTypeRec;

        return true;
    }

    MapType::const_iterator findSubst(const Record &r) const
    {
        std::string strt = r.serializeCleanType();
        return substMap.find(strt);
    }

    bool makeSubst(Record &r) const
    {
        auto it = findSubst(r);
        if (it==substMap.end())
            return false;

        r.replaceBase(it->second);
        return true;
    }


}; // struct TypeSubsts


inline
void substTypes(Record &r, const TypeSubsts &ts)
{
    if (!ts.makeSubst(r))
    {
        for(auto &a : r.args)
        {
            substTypes(a, ts);
        }
    }
}