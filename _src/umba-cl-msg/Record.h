#pragma once

#include "TypeModifiers.h"

#include <sstream>

#include "umba/string_plus.h"
#include "umba/rule_of_five.h"
#include "umba/assert.h"

//
#include "marty_cpp/marty_cpp.h"

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct Record
{

protected:

    std::string               prefix;
    std::string               suffix;

    char                      cBrace = 0; // Открывающая
    std::vector<Record>       args;
    bool                      quoted = false;

    std::shared_ptr<Record>   nestedRecord   ; // для вложенных типов и функций/операторов

    std::vector<std::string>  prefixModifiers;
    std::vector<std::string>  psModifiers    ; // prefix-suffix modifiers
    std::vector<std::string>  suffixModifiers;


public:

    Record() {}
    // : prefix()
    // , suffix()
    // , cBrace(0)
    // , args() 
    // {}

    // explicit Record(char ch)
    // : prefix()
    // , suffix()
    // , cBrace(ch)
    // , args() 
    // {}

    explicit Record(bool q)
    : quoted(q) 
    {}

    explicit Record(const std::vector<Record> &a)
    : prefix()
    , suffix()
    , cBrace()
    , args(a) 
    {}

    UMBA_RULE_OF_FIVE_COPY(Record, default, default);
    UMBA_RULE_OF_FIVE_MOVE(Record, default, default);

    bool hasNested() const
    {
        return !!nestedRecord;
    }

    Record& getNested()
    {
        UMBA_ASSERT(nestedRecord);
        return *nestedRecord;
    }

    const Record& getNested() const
    {
        UMBA_ASSERT(nestedRecord);
        return *nestedRecord;
    }

    void setBrace(char ch)
    {
        if (nestedRecord)
            return nestedRecord->setBrace(ch);

        UMBA_ASSERT(cBrace==0);
        cBrace = ch;
    }

    void clrBrace()
    {
        if (nestedRecord)
            return nestedRecord->clrBrace();

        cBrace = 0;
    }

    bool isTypeList() const
    {
        return cBrace=='<';
    }

    bool isParamList() const
    {
        return cBrace=='(';
    }

    bool isSimpleType() const
    {
        return args.empty() && !nestedRecord;
    }

    bool isQuoted() const
    {
        // if (nestedRecord)
        //     return nestedRecord->isQuoted();
        return quoted;
    }

    void setQuoted(bool q=true)
    {
        if (nestedRecord)
            nestedRecord->setQuoted(q);
        quoted = q;
    }

    std::vector<Record>& getArgs()
    {
        // if (nestedRecord)
        //     return nestedRecord->getArgs();
        return args;
    }

    const std::vector<Record>& getArgs() const
    {
        // if (nestedRecord)
        //     return nestedRecord->getArgs();
        return args;
    }

    void createNestedRecord()
    {
        if (nestedRecord)
        {
            nestedRecord->createNestedRecord();
        }
        else
        {
            nestedRecord = std::make_shared<Record>();
            nestedRecord->quoted = true;
        }
    }

    char getBrace() const
    {
        if (nestedRecord)
            return nestedRecord->getBrace();
        return cBrace;
    }

    void clearBrace()
    {
        if (nestedRecord)
            return nestedRecord->clearBrace();
        cBrace = 0;
    }

    void replaceBase(const Record &r)
    {
        prefix = r.prefix;
        suffix = r.suffix;
    
        cBrace = r.cBrace;
        args   = r.args  ;

        if (nestedRecord && r.nestedRecord)
        {
            nestedRecord->replaceBase(*r.nestedRecord);
        }
        else
        {
            nestedRecord.reset();
        }
    }

    void replaceBase(const std::string &str)
    {
        prefix = str;
        cBrace = 0;
        suffix.clear();
        args.clear();
        nestedRecord.reset();
    }

    bool hasBrace(char braceCh, bool checkSelf=true, bool checkArgs=true, bool checkNested=true) const
    {
        if (isPairedChar(braceCh) && isCloseChar(braceCh))
            braceCh = getPair(braceCh);

        if (checkSelf)
        {
            if (cBrace==braceCh)
                return true;
        }

        if (checkNested)
        {
            if (nestedRecord)
            {
                if (nestedRecord->hasBrace(braceCh, true /* checkSelf */, checkArgs, checkNested))
                    return true;
            }
        }

        if (checkArgs)
        {
            for(auto &&a : args)
            {
                if (a.hasBrace(braceCh, true /* checkSelf */, checkArgs /* de facto - true */, checkNested ))
                    return true;
            }
        }

        return false;
    }

    bool needAutoSubst(std::size_t templateTypesMaxLen=48, std::size_t exactTypesMaxLen=48) const
    {
        UMBA_USED(templateTypesMaxLen);
        UMBA_USED(exactTypesMaxLen);

        if (!quoted)
            return false;

        if (isSimpleType())
            return false;

        if (hasBrace('(', true, true)) // выражения с круглыми скобками не оптимизируем
            return false;

        std::string cleanType = serializeCleanType();

        if (hasBrace('<', true, true)) // шаблон?
        {
            // шаблон
            if (cleanType.size()>templateTypesMaxLen)
                return true;
        }
        else
        {
            // Пока нешаблонные типы не заменяем
            // if (cleanType.size()>exactTypesMaxLen)
            //     return true;
        }

        return false;
    }

    std::string getNameForAutoRenameFromPrefix() const
    {
        auto pos = prefix.rfind(':');
        if (pos==prefix.npos)
            return marty_cpp::filterName(prefix);

        return marty_cpp::filterName(std::string(prefix, pos+1, prefix.npos));
    }

    std::string getNameForAutoRenameFromSuffix() const
    {
        if (nestedRecord)
            return nestedRecord->getNameForAutoRenameFromPrefix();

        auto pos = suffix.rfind(':');
        if (pos==suffix.npos)
            return marty_cpp::filterName(suffix);
         
        return marty_cpp::filterName(std::string(suffix, pos+1, suffix.npos));
    }

    std::string getNameForAutoRename() const
    {
        if (nestedRecord && !nestedRecord->isParamList())
            return getNameForAutoRenameFromSuffix();

        if (prefix.empty())
            return getNameForAutoRenameFromSuffix();

        if (suffix.rfind(':')!=suffix.npos)
            return getNameForAutoRenameFromSuffix();

        return getNameForAutoRenameFromPrefix();
    }

    bool empty() const
    {
        bool nestedEmpty = nestedRecord ? nestedRecord->empty() : true;
        return nestedEmpty && prefixModifiers.empty() && psModifiers.empty() && suffixModifiers.empty() && prefix.empty() && suffix.empty() && args.empty() && cBrace==0;
    }

    void clear(bool q)
    {
        *this = Record();
        quoted = q;
        nestedRecord.reset();
    }

    void clearModifiers()
    {
        prefixModifiers.clear();
        psModifiers    .clear();
        suffixModifiers.clear();
    }

    void append(char ch)
    {
        if (nestedRecord)
            nestedRecord->append(ch);
        else if (cBrace==0)
            prefix.append(1, ch);
        else
            suffix.append(1, ch);
    }

    void appendArg(const Record &r)
    {
        if (nestedRecord)
            nestedRecord->args.emplace_back(r);
        else
            args.emplace_back(r);
    }

    bool isPrefixMode() const
    {
        if (nestedRecord)
           return nestedRecord->isPrefixMode();

        return cBrace==0;
    }

    std::string serializePrefixModifiers() const
    {
        return umba::string::merge<std::string>(prefixModifiers, std::string() /* , [](auto s) { return s; } */ );
    }

    std::string serializePrefixSuffixModifiers() const
    {
        return umba::string::merge<std::string>(psModifiers, std::string() /* , [](auto s) { return s; } */ );
    }

    std::string serializeSuffixModifiers() const
    {
        return umba::string::merge<std::string>(suffixModifiers, std::string() /* , [](auto s) { return s; } */ );
    }


    //void extractModifiers(const std::unordered_set<std::string> &knownPrefixModifiers, const std::vector<std::string> &knownSuffixModifiers)
    // psModifiers
    void extractModifiers(const TypeModifiers &typeModifiers)
    {
        if (nestedRecord)
            nestedRecord->extractModifiers(typeModifiers);

        umba::string::ltrim(prefix);

        for(auto && kpm : typeModifiers.prefixModifiers)
        {
            if (umba::string::starts_with_and_strip(prefix, kpm))
            {
                prefixModifiers.emplace_back(kpm);
                umba::string::ltrim(prefix);
            }
        }


        umba::string::rtrim(prefix);

        for(auto && ksm : typeModifiers.suffixModifiers)
        {
            if (umba::string::ends_with_and_strip(prefix, ksm))
            {
                auto modifier = ksm;
                if (!prefix.empty() && prefix.back()==' ')
                {
                    modifier.insert(0, 1, ' ');    // Добавляем к модифиатору спереди
                    prefix.erase(prefix.size()-1); // Удаляем у префикса сзади
                }
                psModifiers.emplace_back(modifier);
                umba::string::rtrim(prefix);
            }
        }


        umba::string::rtrim(suffix);

        for(auto && ksm : typeModifiers.suffixModifiers)
        {
            if (umba::string::ends_with_and_strip(suffix, ksm))
            {
                auto modifier = ksm;
                if (!suffix.empty() && suffix.back()==' ')
                {
                    modifier.insert(0, 1, ' ');    // Добавляем к модифиатору спереди
                    suffix.erase(suffix.size()-1); // Удаляем у суффикса сзади
                }
                suffixModifiers.emplace_back(modifier);
                umba::string::rtrim(suffix);
            }
        }


        for(auto & a: args)
        {
            a.extractModifiers(typeModifiers);
        }
        
    }


    int compare(const Record &other) const
    {
        std::string s1 =       serialize();
        std::string s2 = other.serialize();

        if (s1.size()<s2.size())
            return -1;

        if (s1.size()>s2.size())
            return  1;

        std::string::const_iterator it1 = s1.begin();
        std::string::const_iterator it2 = s2.begin();

        for(; it1!=s1.end() && it2!=s2.end(); ++it1, ++it2)
        {
            if (*it1==*it2)
                continue;
            if (*it1<*it2)
                return -1;
            return 1;
        }

        if (it1==s1.end())
            return -1;

        if (it2==s2.end())
            return  1;

        return 0;

        /*
        if (prefix<other.prefix)  return -1;
        if (prefix>other.prefix)  return  1;

        if (suffix<other.suffix)  return -1;
        if (suffix>other.suffix)  return  1;

        if (cBrace<other.cBrace)  return -1;
        if (cBrace>other.cBrace)  return  1;

        if (args.size()<other.args.size())  return -1;
        if (args.size()>other.args.size())  return  1;

        std::vector<Record>::const_iterator it      = args.begin();
        std::vector<Record>::const_iterator itOther = other.args.begin();

        for(; it!=args.end() && itOther!=other.args.end(); ++it, ++itOther)
        {
            auto res = it->compare(*itOther);
            if (res!=0)
                return res;
        }

        return 0;
        */
    }

    UMBA_IMPLEMENT_MEMBER_RELOPS(Record)

    void trim()
    {
        umba::string::ltrim(prefix);
        umba::string::rtrim(suffix);

        std::vector<Record> argsCopy;

        for(auto &a : args)
        {
            a.trim();
            if (!a.empty())
            {
                argsCopy.emplace_back(a);
            }
        }

        swap(args, argsCopy);

        auto argsSize = args.size();
        if (prefix.empty() && suffix.empty() && cBrace==0 && argsSize==1)
        {
            Record tmp = args.front();
            *this = tmp;
        }

    }

    Record trimCopy() const
    {
        Record r = *this;
        r.trim();
        return r;
    }

    template<typename StreamType>
    StreamType& serialize(StreamType &oss, bool useModifiers=true) const
    {
        if (useModifiers)
            oss << serializePrefixModifiers();

        oss << prefix;

        if (useModifiers)
            oss << serializePrefixSuffixModifiers();

        if (cBrace!=0)
            oss << std::string(1, cBrace);

        std::size_t cnt=0;
        for(const auto &a : args)
        {
            if (cnt)
                oss << ",";
            a.serialize(oss);
            ++cnt;
        }

        if (cBrace!=0)
            oss << std::string(1, getPair(cBrace));

        oss << suffix;

        if (useModifiers)
            oss << serializeSuffixModifiers();

        if (nestedRecord)
            nestedRecord->serialize(oss, useModifiers);

        return oss;
    }

    std::string serialize(bool useModifiers=true) const
    {
        std::ostringstream oss;
        serialize(oss, useModifiers);
        return oss.str();
    }

    std::string serializeCleanType() const // Только тип без модификаторов
    {
        std::ostringstream oss;
        serialize(oss, false);
        return oss.str();
    }

    template<typename StreamType>
    StreamType& print(StreamType &oss, std::size_t indendBase=0) const
    {
        std::size_t indend = 4; // prefix.size();

        oss << serializePrefixModifiers() << prefix << serializePrefixSuffixModifiers();

        if (cBrace!=0)
        {
            if (args.size()>1)
                oss << "\n" << std::string(indendBase+indend, ' ');
            oss << std::string(1, cBrace) << " ";
        }

        std::vector<Record>::const_iterator it = args.begin();
        if (it!=args.end())
        {
            it->print(oss, indendBase+indend);
            ++it;
        }

        for(; it!=args.end(); ++it)
        {
            
            oss << "\n";
            if (it->quoted)
            {
                oss << std::string(indendBase+indend, ' ') << ", ";
                it->print(oss, indendBase+indend);
            }
            else
            {
                it->print(oss, indendBase);
            }
        }

        if (cBrace!=0)
        {
            if (args.size()>1)
                oss << "\n" << std::string(indendBase+indend, ' ');
            else
                oss << " ";

            oss << std::string(1, getPair(cBrace)) << " ";
        }

        oss << suffix << serializeSuffixModifiers();

        if (nestedRecord)
            nestedRecord->print(oss, indendBase+indend);

        return oss;
    }

}; // struct Record

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename StreamType>
StreamType& print(StreamType &oss, const std::vector<Record> &vr)
{
    // bool prevQuoted = false;
    for(const auto &r : vr)
        r.print(oss, 0) << "\n";
    return oss;
}

//----------------------------------------------------------------------------
template<typename StreamType>
StreamType& serialize(StreamType &oss, const std::vector<Record> &vr)
{
    // bool prevQuoted = false;
    for(const auto &r : vr)
        r.serialize(oss) << "\n";
    return oss;
}

//----------------------------------------------------------------------------
template<typename StreamType>
StreamType& print(StreamType &oss, const Record &r)
{
    return print(oss, r.getArgs());
}

//----------------------------------------------------------------------------
template<typename StreamType>
StreamType& serialize(StreamType &oss, const Record &r)
{
    return serialize(oss, r.getArgs());
}

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------


