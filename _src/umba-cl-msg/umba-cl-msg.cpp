/*! \file
    \brief Утилита umba-cl-msg - форматирование ошибок компилятора C++
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

//
#include "utils.h"
//
#include "Record.h"
//
#include "RecordStack.h"
#include "RecordUtils.h"
#include "TypeSubsts.h"
//
#include "parseClMessage.h"

//
#include "AppConfig.h"



AppConfig appConfig;


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

    UMBA_USED(argc);
    UMBA_USED(argv);

    std::string text;

    if (umba::isDebuggerPresent())
    {
        text = 
        #include "msg1.h"
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

    //------------------------------
    // Пока захардкоживаем заполнение.
    // Не раньше, чем распарсили главный текст
    appConfig.addTypeModifierPrefix("const");
    appConfig.addTypeModifierSuffix("&");
    appConfig.addTypeModifierSuffix("&&");
     
    // MSVC
    appConfig.addTypeSubst("std::string" , "std::basic_string<char,std::char_traits<char>,std::allocator<char>>");
    appConfig.addTypeSubst("std::wstring", "std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>>");
    // GCC
    appConfig.addTypeSubst("std::string" , "std::__cxx11::basic_string<char>");
    
    //------------------------------

    r.extractModifiers(appConfig.typeModifiers);
    substTypes(r, appConfig.typeSubsts);

    // r.print(std::cout);
    // print(std::cout, r.args);
    // serialize(std::cout, r.args);
    // serialize(std::cout, r);

    RecordStringCountersMap countMap;
    findAllTypeStrings(r.getArgs(), countMap);

    std::vector<ReplacePair> replaces;
    NameGenerator nameGen;
    performAutoSubsts(r, replaces, nameGen);

    //r.print(std::cout);
    print(std::cout, r);

    std::cout << "---\n\nWith:\n\n";
    for(auto &&rpls : replaces)
    {
        std::cout << rpls.replaceWith << " - " << rpls.typeString << "\n\n";
    }

    return 0;

}


