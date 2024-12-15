#pragma once

#include <memory>

// Сначала кладём в префикс
// Если мы после закрывающей скобки, то кладём в суффикс

// Если встречаем открывающую скобку, то - устанавливаем её для текущего элемента (на вершине),
// и вставляем на вершину пустой элемент (с нулевой скобкой).

// Если встречаем запятую, снимаем элемент со стека, и кладём в список аргументов элемента на вершине, 
// и сразу добавляем пустой элемент.

// Если встречаем закрывающую скобку, то снимаем элемент со стека и кладём в список аргументов элемента на вершине,
// не помещая на стек пустой элемент

// Новая проблемка - суффикс может быть не только const или символом ccылки, но и вложенным типом или функцией/оператором.



template<typename IterType>
Record parseClMessage(IterType b, IterType e)
{
    std::vector<Record> records;
    Record              curRecord;
    RecordStack         stack;
    std::size_t         quoteCount = 0;


    auto isQuoted = [&]()
    {
        return (quoteCount&1) ? true : false;
    };


    // auto checkStack = [&]()
    // {
    //     if (stack.empty())
    //         throw std::runtime_error("Something goes wrong (1)");
    // };
    //  
    // auto checkStackSize1 = [&]()
    // {
    //     if (stack.size()>1)
    //         throw std::runtime_error("Something goes wrong (2)");
    // };

    auto finalizeCurrentStack = [&]()
    {
        while(stack.size()>1)
        {
            auto r = stack.top().trimCopy();
            stack.pop();
            // if (quoteCount&1)
            //     r.quoted = true;
            if (!r.empty())
                stack.top().appendArg(r);
        }


        if (!curRecord.empty())
            records.emplace_back(curRecord);
        curRecord.clear(isQuoted());
         
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
        // const char *pRest = &*b; // Для отладки, содержимое итераторов VSCode уродски показывает

        auto ch = *b;

        if (ch=='\'')
        {
            ++quoteCount;
            finalizeCurrentStack();
            continue;
        }


        if (!isQuoted())
        {
            curRecord.append(ch);
            continue;
        }


        if (isOpenChar(ch))
        {
            // у нас всё клалось в "текущую" Record

            if (curRecord.isPrefixMode()) // скобок ещё не было (в самой curRecord или в nestedRecord, если она есть)
            {
                curRecord.setBrace(ch); // помечаем открывающей скобкой
                stack.push(curRecord); // на стек
                curRecord.clear(isQuoted()); // текущую запись очищаем
            }
            else
            {
                // скобки уже были
                // закидываем её либо как аргумент в вершине стека, либо в список records
                if (stack.empty())
                    records.emplace_back(curRecord);
                else
                    stack.top().appendArg(curRecord);

                curRecord.clear(isQuoted());
            }

            continue;

        } // if (isOpenChar(ch))


        if (ch==',')
        {
            if (stack.empty())
                records.emplace_back(curRecord);
            else
                stack.top().appendArg(curRecord);

            curRecord.clear(isQuoted());

            continue;

        } // if (ch==',')


        if (!stack.empty() && getPair(ch)==stack.top().getBrace()) // Если закрывающая скобка была без открывающей - не обрабатываем как спец символ
        {
            // Парная закрывающая скобка
            if (ch==')' && !stack.empty() && curRecord.empty()) // тест на спец случай, когда две круглые скобки идут одна за другой
            {
                curRecord = stack.top();
                stack.pop();
                curRecord.clearBrace(); // Очищаем признак скобки
                curRecord.append('(');
                curRecord.append(')');
            }
            else
            {
                if (!curRecord.empty())
                    stack.top().appendArg(curRecord);
                // curRecord.clear();
                curRecord = stack.top();
                stack.pop();
            }

                // // скобки уже были
                // // закидываем её либо как аргумент в вершине стека, либо в список records
                // if (stack.empty())
                //     records.emplace_back(curRecord);
                // else
                //     stack.top().args.emplace_back(curRecord);
                //  
                // curRecord.clear(isQuoted());

            continue;

        } // if (!stack.empty() && getPair(ch)==stack.top().cBrace)


        if (ch==':') // пришло двоеточие
        {
            if (!curRecord.isPrefixMode()) // кладём в суффикс?
            {
                curRecord.createNestedRecord();
                curRecord.append(ch);
                continue;
            }
        }

        curRecord.append(ch);

    } // for(; b!=e; ++b)


    finalizeCurrentStack();

    return Record(records).trimCopy();
}


inline
Record parseClMessage(const std::string &str)
{
    return parseClMessage(str.begin(), str.end());
}


