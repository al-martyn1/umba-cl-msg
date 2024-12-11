#pragma once

#include <sstream>

struct Record
{
    std::string           prefix;
    std::string           suffix;
    char                  cBrace = 0; // Открывающая
    std::vector<Record>   args;
    bool                  quoted = false;

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

    bool empty() const
    {
        return prefix.empty() && suffix.empty() && args.empty() && cBrace==0;
    }

    void clear(bool q)
    {
        *this = Record();
        quoted = q;
    }

    void append(char ch)
    {
        if (cBrace==0)
            prefix.append(1, ch);
        else
            suffix.append(1, ch);
    }

    bool isSuffixMode() const
    {
        return cBrace!=0;
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
        umba::string::trim(prefix);
        umba::string::trim(suffix);

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

    // std::string           prefix;
    // std::string           suffix;
    // char                  cBrace = 0; // Открывающая
    // std::vector<Record>   args;

    template<typename StreamType>
    StreamType& serialize(StreamType &oss) const
    {
        oss << prefix;
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

        return oss;
    }

    std::string serialize() const
    {
        std::ostringstream oss;
        serialize(oss);
        return oss.str();
    }

        // std::ostringstream oss1;
        // std::string s1 = serialize(oss1);


    template<typename StreamType>
    StreamType& print(StreamType &oss, std::size_t indendBase=0) const
    {
        std::size_t indend = 4; // prefix.size();

        oss << prefix;

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

        oss << suffix ;

        return oss;
    }


}; // struct Record


template<typename StreamType>
StreamType& print(StreamType &oss, const std::vector<Record> &vr)
{
    bool prevQuoted = false;
    for(const auto r : vr)
        r.print(oss, 0) << "\n";
    return oss;
}

template<typename StreamType>
StreamType& serialize(StreamType &oss, const std::vector<Record> &vr)
{
    bool prevQuoted = false;
    for(const auto r : vr)
        r.serialize(oss) << "\n";
    return oss;
}

