#pragma once


#include "parseClMessage.h"
#include "Record.h"
#include "RecordStack.h"
#include "RecordUtils.h"
#include "TypeModifiers.h"
#include "TypeSubsts.h"

//
#include "umba/string_plus.h"

//
#include <map>
#include <unordered_map>
#include <unordered_set>


struct AppConfig
{
    TypeSubsts     typeSubsts;
    TypeModifiers  typeModifiers;


    // Приходит в опции ком строки в формате substType=orgType, разедялется по символу '=' и  передаётся сюда
    bool addTypeSubst(const std::string &substType, const std::string &orgType)
    {
        return typeSubsts.add(substType, orgType);
    }

    bool addTypeModifierPrefix(const std::string &m)
    {
        return typeModifiers.addPrefixModifier(m);
    }

    bool addTypeModifierSuffix(const std::string &m)
    {
        return typeModifiers.addSuffixModifier(m);
    }




}; // struct AppConfig



