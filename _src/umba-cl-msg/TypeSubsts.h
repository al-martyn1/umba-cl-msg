#pragma once


#include "NameGenerator.h"
#include "Record.h"
// #include "RecordUtils.h"
#include "parseClMessage.h"
//
#include "umba/debug_helpers.h"
//
#include <unordered_map>
#include <utility>
#include <iostream>

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct ReplacePair
{
    std::string    typeString; 
    std::string    replaceWith;
};


//----------------------------------------------------------------------------
struct TypeSubsts
{
    using MapType = std::unordered_map<std::string, Record>;

    MapType  substMap;

    bool add(const std::string &substType, const std::string &orgType)
    {
        Record substTypeRec = parseClMessage(substType);
        Record orgTypeRec   = parseClMessage(orgType);

        std::string orgTypeRecSerialized = orgTypeRec.serialize(); // serializeCleanType()
        substTypeRec.setQuoted(true);

        substMap[orgTypeRecSerialized] = substTypeRec;

        return true;
    }

    MapType::const_iterator findSubst(const Record &r) const
    {
        std::string strt = r.serializeCleanType();

        // if (strt.find("basic_string")!=strt.npos)
        // {
        //     UMBA_DEBUGBREAK();
        // }

        #if defined(DETAILED_TYPESUBSTS)
            std::cout << "TypeSubsts:findSubst: strt: " << strt << "\n";
        #endif
        return substMap.find(strt);
    }

    bool makeSubst(Record &r) const
    {
        if (!r.isQuoted())
            return false;

        auto it = findSubst(r);

        #if defined(DEBUG) || defined(_DEBUG)
            std::string strt = r.serializeCleanType();
        #endif

        if (it==substMap.end())
        {
            #if defined(DETAILED_TYPESUBSTS)
                std::cout << "TypeSubsts:makeSubst: not found\n";
            #endif
            return false;
        }

        r.replaceBase(it->second);
        #if defined(DETAILED_TYPESUBSTS)
            std::cout << "TypeSubsts:makeSubst: replace with: " << r.serializeCleanType() << "\n";
        #endif

        return true;
    }


}; // struct TypeSubsts

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
bool substTypes(Record &r, const TypeSubsts &ts)
{
    #if defined(DETAILED_TYPESUBSTS)
        std::cout << "substTypes: entrance with: " << r.serializeCleanType() << "\n";
    #endif

    if (!ts.makeSubst(r))
    {
        bool res = false;

        #if defined(DETAILED_TYPESUBSTS)
            std::cout << "substTypes: hasNested, try substTypes on args\n";
        #endif
        for(auto &a : r.getArgs())
        {
            if (substTypes(a, ts))
                res = true;
        }

        if (r.hasNested())
        {
            #if defined(DETAILED_TYPESUBSTS)
                std::cout << "substTypes: hasNested, try substTypes on nested\n";
            #endif
            if (substTypes(r.getNested(), ts))
                res = true;
        }

        return res;
    }

    return true;
}

//----------------------------------------------------------------------------
inline
bool substType(Record &r, const std::string &strCleanType, const Record &replaceWith)
{
    std::string curCleanType = r.serializeCleanType();

    #if defined(DETAILED_TYPESUBSTS)
        std::cout << "substType: curCleanType: " << curCleanType << "\n";
    #endif

    if (curCleanType==strCleanType)
    {
        #if defined(DETAILED_TYPESUBSTS)
            std::cout << "substType: replace with: " << replaceWith.serializeCleanType() << "\n";
        #endif
        r.replaceBase(replaceWith);
        return true;
    }

    bool res = false;
    for(auto &a : r.getArgs())
    {
        if (substType(a, strCleanType, replaceWith))
            res = true;
    }

    if (r.hasNested())
    {
        #if defined(DETAILED_TYPESUBSTS)
            std::cout << "substType: process nested\n";
        #endif
        if (substType(r.getNested(), strCleanType, replaceWith))
            res = true;
    }

    return res;
}

//----------------------------------------------------------------------------
/*
    Нам надо самую короткую строку типа проверить на необходимость замены.
    Если ей автозамена не нужна - переходим к следующему типу.
    Поэтому нам нужен отсортированный по длине строки мап - ключ - строковое представление типа, значение - Record. По Record проверяем, нужна ли замена
*/
inline
bool findAutoReplaceCandidate(const Record &r, Record &candidate, std::size_t templateTypesMaxLen=48, std::size_t exactTypesMaxLen=48)
{

    // DETAILED_AUTOREPLACE

    RecordStringMap m;
    findAllTypeStrings(r, m, true /* cleanTypes */ );

    #if 0
    std::cout << "------------\n";
    std::cout << "!!! findAutoReplaceCandidate\n";
    for(const auto &it : m)
    {
        std::cout << it.first << "\n";
    }
    #endif

    RecordStringMap::const_iterator rit = m.begin();
    for(; rit!=m.end(); ++rit)
    {
        if (rit->second.needAutoSubst(templateTypesMaxLen, exactTypesMaxLen))
        {
            candidate = rit->second;
            // std::cout << "\nRound: " << rit->first << "\n";
            // std::cout << "------------\n";
            return true;
        }

    }

    // std::cout << "------------\n";
    return false;
}

//----------------------------------------------------------------------------
inline
void performAutoSubsts(Record &r, std::vector<ReplacePair> &replaces, NameGenerator &nameGen, std::size_t templateTypesMaxLen=48, std::size_t exactTypesMaxLen=48)
{
    Record rReplace;
    while(findAutoReplaceCandidate(r, rReplace, templateTypesMaxLen, exactTypesMaxLen))
    {
        std::string replaceToBaseName = rReplace.getNameForAutoRename();
        std::string replaceToName     = nameGen.generateName(replaceToBaseName);
        std::string strCleanType      = rReplace.serializeCleanType();
        rReplace.replaceBase(replaceToName);

        replaces.emplace_back(ReplacePair{strCleanType, replaceToName});

        // bool 
        substType(r, strCleanType, rReplace);
    }

}

//----------------------------------------------------------------------------



// void replaceBase(const std::string &str)

// void findAllTypeStrings(const std::vector<Record> &vr, RecordStringSet &s, bool cleanTypes=true);



//----------------------------------------------------------------------------
//bool isValidIdentChar( char ch, bool allowNonAsciiIdents, const std::string &forceAllowedChars )
//filterName( const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents = false)


// std::string getNameForAutoRename() const
// bool needAutoSubst(std::size_t templateTypesMaxLen=48, std::size_t exactTypesMaxLen=48) const



    // MapType::const_iterator findSubst(const Record &r) const
    // {
    //     std::string strt = r.serializeCleanType();
    //     return substMap.find(strt);
    // }
    //  
    // bool makeSubst(Record &r) const
    // {
    //     auto it = findSubst(r);
    //     if (it==substMap.end())
    //         return false;
    //  
    //     r.replaceBase(it->second);
    //     return true;
    // }

// void substType(Record &r, const std::string &strCleanType, const Record &replaceWith)




