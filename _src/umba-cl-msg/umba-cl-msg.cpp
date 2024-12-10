/*! \file
    \brief Утилита umba-cl-msg - форматирование ошибок компилятора C++
 */

/*

Пример сообщения

'_Ret std::_Func_class< _Ret
                      , umba::tokenizer::TokenizerFunctionHandlers< CharType
                                                                  , UserDataType
                                                                  , CharClassTableType
                                                                  , TrieVectorType
                                                                  , StringType
                                                                  , MessagesStringType
                                                                  , InputIteratorType
                                                                  , umba::iterator::TextIteratorTraits< InputIteratorType >
                                                                  > &
                      , bool
                      , umba::tokenizer::payload_type
                      , InputIteratorType &
                      , InputIteratorType &
                      , std::variant< umba::tokenizer::TokenizerBaseImpl< umba::tokenizer::TokenizerFunctionHandlers< CharType
                                                                                                                    , UserDataType
                                                                                                                    , CharClassTableType
                                                                                                                    , TrieVectorType
                                                                                                                    , StringType
                                                                                                                    , MessagesStringType
                                                                                                                    , InputIteratorType
                                                                                                                    , umba::iterator::TextIteratorTraits< InputIteratorType >
                                                                                                                    >
                                                                        , CharType
                                                                        , UserDataType
                                                                        , CharClassTableType
                                                                        , TrieVectorType
                                                                        , StringType
                                                                        , MessagesStringType
                                                                        , InputIteratorType
                                                                        , InputIteratorTraits
                                                                        >::EmptyData
                                    , umba::tokenizer::TokenizerBaseImpl< umba::tokenizer::TokenizerFunctionHandlers< CharType
                                                                                                                    , UserDataType
                                                                                                                    , CharClassTableType
                                                                                                                    , TrieVectorType
                                                                                                                    , StringType
                                                                                                                    , MessagesStringType
                                                                                                                    , InputIteratorType
                                                                                                                    , InputIteratorTraits
                                                                                                                    >
                                                                        , CharType
                                                                        , UserDataType
                                                                        , CharClassTableType
                                                                        , TrieVectorType
                                                                        , StringType
                                                                        , MessagesStringType
                                                                        , InputIteratorType
                                                                        , InputIteratorTraits
                                                                        >::CommentData
                                    ,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IdentifierData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::StringLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IntegerNumericLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::FloatNumericLiteralData> &,std::basic_string<char,std::char_traits<char>,std::allocator<char>> &>::operator ()(umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits> &,bool,umba::tokenizer::payload_type,InputIteratorType &,InputIteratorType &,std::variant<umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::EmptyData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::CommentData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IdentifierData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::StringLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IntegerNumericLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::FloatNumericLiteralData> &,std::basic_string<char,std::char_traits<char>,std::allocator<char>> &) const': cannot convert argument 6 from 'umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,umba::iterator::TextIteratorTraits<InputIteratorType>>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::EmptyData' to 'std::variant<umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,umba::iterator::TextIteratorTraits<InputIteratorType>>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::EmptyData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::CommentData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IdentifierData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::StringLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::IntegerNumericLiteralData,umba::tokenizer::TokenizerBaseImpl<umba::tokenizer::TokenizerFunctionHandlers<CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>,CharType,UserDataType,CharClassTableType,TrieVectorType,StringType,MessagesStringType,InputIteratorType,InputIteratorTraits>::FloatNumericLiteralData> &'	umba-brief-scanner	F:\_github\umba-tools\umba-brief-scanner\_libs\umba_tokenizer\inc\umba\tokenizer\token_filters.h	767	


Это "скобочные" выражения вида

  ПРЕФИКС <[АРГУМЕНТ,[АРГУМЕНТ,...]]> СУФФИКС

где АРГУМЕНТ - также может быть скобочным выражением


*/


// Должна быть первой
#include "umba/umba.h"
//---
#include "umba/app_main.h"
//

//#-sort
#include "umba/simple_formatter.h"
#include "umba/char_writers.h"
//#+sort

#include "umba/debug_helpers.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <utility>
#include <exception>
#include <stdexcept>

#include "umba/debug_helpers.h"
#include "umba/string_plus.h"
#include "umba/program_location.h"
#include "umba/scope_exec.h"
#include "umba/macro_helpers.h"
#include "umba/macros.h"
#include "umba/scanners.h"
#include "umba/relops.h"
#include "umba/debug_helpers.h"
#include "umba/rule_of_five.h"

#include "marty_cpp/marty_cpp.h"
#include "marty_cpp/marty_enum.h"
#include "marty_cpp/marty_flags.h"
#include "marty_cpp/sort_includes.h"
#include "marty_cpp/enums.h"
#include "marty_cpp/src_normalization.h"
#include "marty_cpp/marty_ns.h"
#include "marty_cpp/marty_enum_impl_helpers.h"

#include "encoding/encoding.h"
#include "umba/cli_tool_helpers.h"
#include "umba/time_service.h"
#include "umba/shellapi.h"

namespace umba
{
    namespace string = string_plus;
}


inline
char getPair(char ch)
{
    switch(ch)
    {
        case '<': return '>';
        case '>': return '<';
        case '(': return ')';
        case ')': return '(';
        case '{': return '}';
        case '}': return '{';
        case '[': return ']';
        case ']': return '[';
        default : return ch ;
    }
}

inline
bool isOpenChar(char ch)
{
    switch(ch)
    {
        case '<': return true ;
        case '(': return true ;
        case '{': return true ;
        case '[': return true ;
        default : return false;
    }
}

inline
bool isCloseChar(char ch)
{
    switch(ch)
    {
        case '>': return true ;
        case ')': return true ;
        case '}': return true ;
        case ']': return true ;
        default : return false;
    }
}

inline
bool isPairedChar(char ch)
{
    return ch!=getPair(ch);
}



struct Record
{
    std::string           prefix;
    std::string           suffix;
    char                  cBrace = 0; // Открывающая
    std::vector<Record>   args;

    Record()
    : prefix()
    , suffix()
    , cBrace(0)
    , args() 
    {}

    // explicit Record(char ch)
    // : prefix()
    // , suffix()
    // , cBrace(ch)
    // , args() 
    // {}

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

    }

    UMBA_IMPLEMENT_MEMBER_RELOPS(Record)

    void trim()
    {
        umba::string::trim(prefix);
        umba::string::trim(suffix);
        for(auto &a : args)
            a.trim();
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

    #if 0
    template<typename StreamType>
    StreamType& print(StreamType &oss, std::size_t indendBase=0) const
    {
        std::size_t indend = prefix.size();
        oss << prefix;

        if (cBrace!=0)
            oss <<std::string(1, cBrace);

        std::vector<Record>::const_iterator it = args.begin();
        if (it!=args.end())
        {
            oss << " ";
            it->print(oss, indendBase+indend);
            ++it;
        }

        for(; it!=args.end(); ++it)
        {
            oss << "\n" << std::string(indendBase+indend+1, ' ') << ", ";
            it->print(oss, indendBase+indend+2);
        }

        // if (cBrace!=0)
        //     oss << std::string(indendBase+indend, ' ') << " " << std::string(1, getPair(cBrace));

        return oss;
    }
    #endif

    #if 0
    template<typename StreamType>
    StreamType& print(StreamType &oss, std::size_t indendBase=0) const
    {
        std::size_t indend = 4; // prefix.size();
        oss << prefix;

        if (cBrace!=0)
        {
            oss << "\n" << std::string(indendBase+indend+1, ' ') << std::string(1, cBrace) << " ";
        }

        std::vector<Record>::const_iterator it = args.begin();
        if (it!=args.end())
        {
            it->print(oss, indendBase+indend);
            ++it;
        }

        for(; it!=args.end(); ++it)
        {
            // if (cBrace==0)
            // {
            //     oss << "\n" << std::string(indendBase+indend+1, ' ');
            //     it->print(oss, indendBase+indend);
            // }
            // else
            {
                oss << "\n" << std::string(indendBase+indend+1, ' ') << ", ";
                it->print(oss, indendBase+indend);
            }
        }

        // if (cBrace!=0)
        //     oss << std::string(indendBase+indend, ' ') << " " << std::string(1, getPair(cBrace));

        return oss;
    }
    #endif

    template<typename StreamType>
    StreamType& print(StreamType &oss, std::size_t indendBase=0) const
    {
        std::size_t indend = 4; // prefix.size();
        oss 
            << "[" 
            << prefix
            << "]"
            ;

        if (cBrace!=0)
        {
            oss << "\n" << std::string(indendBase+indend, ' ') 
                << "[" 
                << std::string(1, cBrace) 
                << "]" 
                << " "
                ;
        }

        std::vector<Record>::const_iterator it = args.begin();
        if (it!=args.end())
        {
            it->print(oss, indendBase+indend);
            ++it;
        }

        for(; it!=args.end(); ++it)
        {
            // if (cBrace==0)
            // {
            //     oss << "\n" << std::string(indendBase+indend+1, ' ');
            //     it->print(oss, indendBase+indend);
            // }
            // else
            {
                oss << "\n" << std::string(indendBase+indend, ' ') << ", ";
                it->print(oss, indendBase+indend);
            }
        }


        if (cBrace!=0)
        {
            if (args.size()>1)
            {
                oss << "\n" << std::string(indendBase+indend, ' ');
            }
            else
            {
                oss << " ";
            }

            oss 
                << "[" 
                << std::string(1, getPair(cBrace)) 
                << "]" 
                << " "
                ;
        }

        oss 
            << "[" 
            << suffix 
            << "]"
            ;

        // if (cBrace!=0)
        //     oss << std::string(indendBase+indend, ' ') << " " << std::string(1, getPair(cBrace));

        return oss;
    }



}; // struct Record






//template <typename StringType, typename TrimPred> inline StringType trim_copy(StringType s, const TrimPred &pred)

#define RECORD_STACK_USE_VECTOR

struct RecordStack
{
#if defined(RECORD_STACK_USE_VECTOR)
    using Container = std::vector<Record>;
#else
    using Container = std::stack<Record>;
#endif

    using container_type   = Container                          ;
    using value_type       = typename Container::value_type     ;
    using size_type        = typename Container::size_type      ;
    using reference        = typename Container::reference      ;
    using const_reference  = typename Container::const_reference;

#if defined(RECORD_STACK_USE_VECTOR)

    reference top()                      { return m_stack.back(); }
    const_reference top() const          { return m_stack.back(); }
    bool empty() const                   { return m_stack.empty();}
    size_type size() const               { return m_stack.size(); }
	
    void push( const value_type& value ) { m_stack.emplace_back(value); }
    void push( value_type&& value )      { m_stack.emplace_back(std::forward<value_type>(value)); }
    void pop()                           { m_stack.pop_back(); }

    void clear()                         { m_stack.clear(); }

#else

    reference top()                      { return m_stack.top();  }
    const_reference top() const          { return m_stack.top();  }
    bool empty() const                   { return m_stack.empty();}
    size_type size() const               { return m_stack.size(); }
	
    void push( const value_type& value ) { m_stack.push(value); }
    void push( value_type&& value )      { m_stack.push(std::forward<value_type>(value)); }
    void pop()                           { m_stack.pop(); }

    void clear()                         { while(!empty()) pop(); }

#endif

	

protected:

    Container m_stack;

}; // struct RecordStack


// Сначала кладём в префикс
// Если мы после закрывающей скобки, то кладём в суффикс

// Если встречаем открывающую скобку, то - устанавливаем её для текущего элемента (на вершине),
// и вставляем на вершину пустой элемент (с нулевой скобкой).

// Если встречаем запятую, снимаем элемент со стека, и кладём в список аргументов элемента на вершине, 
// и сразу добавляем пустой элемент.

// Если встречаем закрывающую скобку, то снимаем элемент со стека и кладём в список аргументов элемента на вершине,
// не помещая на стек пустой элемент

template<typename IterType>
Record parseClMessage(IterType b, IterType e)
{
    std::vector<Record> records;

    RecordStack stack;
    stack.push(Record());

    auto checkStack = [&]()
    {
        if (stack.empty())
            throw std::runtime_error("Something goes wrong (1)");
    };

    auto checkStackSize1 = [&]()
    {
        if (stack.size()>1)
            throw std::runtime_error("Something goes wrong (2)");
    };

    auto finalizeCurrentStack = [&]()
    {
        while(stack.size()>1)
        {
            auto r = stack.top().trimCopy();
            stack.pop();
            if (!r.empty())
                stack.top().args.emplace_back(r);
        }
         
        if (!stack.empty())
        {
            auto r = stack.top().trimCopy();
            if (!r.empty())
                records.emplace_back(r);
            //stack.pop();
            stack.clear();
        }
    };


    for(; b!=e; ++b)
    {
        const char *pRest = &*b; // Для отладки, содержимое итераторов VSCode уродски показывает

        auto ch = *b;

        if (isOpenChar(ch))
        {
            checkStack();

            auto &stackTop = stack.top(); // Для отладки, небезопасно

            if (stack.top().isSuffixMode())
            {
                checkStackSize1();
                records.emplace_back(stack.top());
                stack.pop();
                stack.push(Record());
                stack.top().cBrace = ch;
                stack.push(Record());
            }
            else
            {
                stack.top().cBrace = ch;
                stack.push(Record());
            }

            continue;
        }

        if (ch==',')
        {
            checkStack();

            auto t = stack.top();
            stack.pop();

            if (stack.empty())
                records.emplace_back(t);
            else
                stack.top().args.emplace_back(t);

            stack.push(Record());

            continue;
        }

        checkStack();
        char stackTopCbrace = stack.top().cBrace;
        if (getPair(ch)==stackTopCbrace) // Закрываем
        {
            checkStack();

            auto t = stack.top();
            stack.pop();

            if (stack.empty())
                records.emplace_back(t);
            else
                stack.top().args.emplace_back(t);

            // Как и с запятой, только ничего нового на стек не кладём

            continue;
        }

        if (ch=='>')
        {
            UMBA_DEBUGBREAK();
            continue;
        }

        if (ch=='\'')
        {
            finalizeCurrentStack();
            stack.push(Record());
            continue;
        }

        checkStack();

        stack.top().append(ch);

    }

    finalizeCurrentStack();

    return Record(records).trimCopy();
}


inline
Record parseClMessage(const std::string &str)
{
    return parseClMessage(str.begin(), str.end());
}


int unsafeMain(int argc, char* argv[]);


UMBA_APP_MAIN()
{
    // std::cout << "Hello world\n";
    try
    {
        return unsafeMain(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }
    catch(...)
    {
        std::cout << "Unknown error\n";
        return 2;
    }

}



int unsafeMain(int argc, char* argv[])
{

    std::string text;

    if (umba::isDebuggerPresent())
    {
        text = 
        #include "msg4.h"
    }
    else
    {
        std::string line;
        while (std::getline(std::cin, line))
        {
            // std::cout << line << std::endl;
            if (!text.empty())
            {
                text.append(1, '\n');
            }
    
            text.append(line);
        }
    
        text.append(1, '\n');
    }


    Record r = parseClMessage(text);

    r.print(std::cout);

    return 0;

}


