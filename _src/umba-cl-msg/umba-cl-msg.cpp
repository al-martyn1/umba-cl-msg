/*! \file
    \brief Утилита umba-tabtool - нормализация табов
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
#include <unordered_map>
#include <unordered_set>
#include <tuple>

#include "umba/debug_helpers.h"
#include "umba/string_plus.h"
#include "umba/program_location.h"
#include "umba/scope_exec.h"
#include "umba/macro_helpers.h"
#include "umba/macros.h"
#include "umba/scanners.h"

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



UMBA_APP_MAIN()
{
    // std::cout << "Hello world\n";

    std::string text;

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

    std::cout << text;

    return 0;
}



