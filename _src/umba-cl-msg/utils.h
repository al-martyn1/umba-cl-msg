#pragma once


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
