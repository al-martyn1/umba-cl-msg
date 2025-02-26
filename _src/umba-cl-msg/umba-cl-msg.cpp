/*! \file
    \brief Утилита umba-cl-msg - форматирование ошибок компилятора C++
 */


// Должна быть первой
#include "umba/umba.h"
//---
#include "umba/app_main.h"
//
#include "umba/debug_helpers.h"
#include "umba/shellapi.h"
#include "umba/program_location.h"
#include "umba/cli_tool_helpers.h"
#include "umba/cmd_line.h"
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


umba::StdStreamCharWriter coutWriter(std::cout);
umba::StdStreamCharWriter cerrWriter(std::cerr);
umba::NulCharWriter       nulWriter;

umba::SimpleFormatter umbaLogStreamErr(&cerrWriter);
umba::SimpleFormatter umbaLogStreamMsg(&coutWriter);
umba::SimpleFormatter umbaLogStreamNul(&nulWriter);

bool umbaLogGccFormat   = false; // true;
bool umbaLogSourceInfo  = false;

bool bOverwrite         = false;

//
#include "log.h"
//
#include "AppConfig.h"

AppConfig appConfig;

#include "ArgParser.h"



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

    auto argsParser = umba::command_line::makeArgsParser( ArgParser<std::string>()
                                                        , CommandLineOptionCollector()
                                                        , argc, argv
                                                        , umba::program_location::getProgramLocation
                                                            ( argc, argv
                                                            , false // useUserFolder = false
                                                            //, "" // overrideExeName
                                                            )
                                                        );

    // Force set CLI arguments while running under debugger
    if (umba::isDebuggerPresent())
    {
        // argsParser.args.clear();
        // argsParser.args.push_back("--overwrite");

        std::string cwd;
        std::string rootPath = umba::shellapi::getDebugAppRootFolder(&cwd);
        std::cout << "App Root Path: " << rootPath << "\n";
        std::cout << "Working Dir  : " << cwd << "\n";

    } // if (umba::isDebuggerPresent())


    // try
    // {
        // Job completed - may be, --where option found
        if (argsParser.mustExit)
            return 0;

        // if (!argsParser.quet)
        // {
        //     printNameVersion();
        // }

        // LOG_INFO("config") << "-----------------------------------------" << "\n";
        // LOG_INFO("config") << "Processing builtin option files\n";
        if (!argsParser.parseStdBuiltins())
        {
            // LOG_INFO("config") << "Error found in builtin option files\n";
            return 1;
        }
        // LOG_INFO("config") << "-----------------------------------------" << "\n";

        if (argsParser.mustExit)
            return 0;

        // LOG_INFO("config") << "-----------------------------------------" << "\n";
        // LOG_INFO("config") << "Processing command line arguments\n";
        if (!argsParser.parse())
        {
            // LOG_INFO("config") << "Error found while parsing command line arguments\n";
            return 1;
        }
        // LOG_INFO("config") << "-----------------------------------------" << "\n";

        if (argsParser.mustExit)
            return 0;
    // }
    // catch(const std::exception &e)
    // {
    //     LOG_ERR << e.what() << "\n";
    //     return -1;
    // }
    // catch(const std::exception &e)
    // {
    //     LOG_ERR << "command line arguments parsing error" << "\n";
    //     return -1;
    // }

    if (!argsParser.quet  /* && !hasHelpOption */ )
    {
        //printNameVersion();
        //LOG_MSG<<"\n";
        umba::cli_tool_helpers::printNameVersion(umbaLogStreamMsg);
    }




    std::string text;

    if (umba::isDebuggerPresent())
    {
        std::string cwd;
        std::string rootPath = umba::shellapi::getDebugAppRootFolder(&cwd);
        std::cout << "App Root Path: " << rootPath << "\n";
        std::cout << "Working Dir  : " << cwd << "\n";

        // std::string inputFilename = rootPath + "/tests/msg2_4.txt";
        // std::cout << "Processing   : '" << inputFilename << "'\n";
        // if (!umba::filesys::readFile(inputFilename, text))
        // {
        //     std::cout << "Failed to read input file\n";
        //     return 1;
        // }

        // text = 
        // #include "msg1.h"

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
    // appConfig.addTypeModifierPrefix("const");
    // appConfig.addTypeModifierSuffix("&");
    // appConfig.addTypeModifierSuffix("&&");
     
    // // MSVC
    // appConfig.addTypeSubst("std::string" , "std::basic_string<char,std::char_traits<char>,std::allocator<char>>");
    // appConfig.addTypeSubst("std::wstring", "std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>>");
    // // GCC
    // appConfig.addTypeSubst("std::string" , "std::__cxx11::basic_string<char>");
    
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


