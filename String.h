#ifndef _STRING_H_
#define _STRING_H_

#include <bitset>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace Test
{
namespace String
{
static const size_t MaxLength = 1024;

template <class T>
static basic_string<T> Empty()
{
    basic_string<T> empty;
    return empty;
}

// Convert an input string into an output string of different encoding.
// Template arguments I and O can be char or wchar_t.
template <class O, class I>
static basic_string<O> ToString(const basic_string<I> &input)
{
    basic_string<O> output(input.begin(), input.end());
    return output;
}

template <class T>
static string ToString(const basic_string<T> &input)
{
    string output(input.begin(), input.end());
    return output;
}

template <class T>
static wstring ToWString(const basic_string<T> &input)
{
    wstring output(input.begin(), input.end());
    return output;
}

static string ToString(const wchar_t *input)
{
    wstring s(input);
    return ToString(s);
}

static wstring ToWString(const char *input)
{
    string s(input);
    return ToWString(s);
}

template <class T>
static string ToString(const T &v)
{
    ostringstream ss;
    ss << v;
    return ss.str();
}

template <class T>
static wstring ToWString(const T &v)
{
    wostringstream ss;
    ss << v;
    return ss.str();
}

template <class T>
static basic_string<T> ToLower(const basic_string<T> &input)
{
    basic_string<T> output;
    for (size_t i = 0; i < input.length(); i++)
    {
        output.append(1, tolower(input[i]));
    }

    return output;
}

// Check if string input1 starts with string input2
template <class T>
static bool StartsWith(const basic_string<T> &input1, const basic_string<T> &input2)
{
    return 0 == ToLower(input1).compare(0, input2.size(), ToLower(input2));
}

// Check if string input1 ends with string input2
template <class T>
static bool EndsWith(const basic_string<T> &input1, const basic_string<T> &input2)
{
    return (input1.size() - input2.size()) == ToLower(input1).rfind(ToLower(input2), input1.size());
}

// Check if string input1 contains string input2
template <class T>
static bool Contains(const basic_string<T> &input1, const basic_string<T> &input2)
{
    return basic_string<T>::npos != ToLower(input1).find(ToLower(input2));
}

static string Format(const char *format, ...)
{
    char buffer[MaxLength];
    va_list args;
    va_start(args, format);
    // vsprintf_s(buffer, format, args);
    vsnprintf(buffer, MaxLength, format, args);
    va_end(args);
    return string(buffer);
}

static wstring Format(const wchar_t *format, ...)
{
    wchar_t buffer[MaxLength];
    va_list args;
    va_start(args, format);
    // vswprintf_s(buffer, format, args);
    vswprintf(buffer, MaxLength, format, args);
    va_end(args);
    return wstring(buffer);
}

template <class T>
static basic_string<T> TrimStart(const basic_string<T> &input, const T *characters)
{
    if (input.length() == 0)
        return input;
    size_t index = input.find_first_not_of(characters);
    if (index == basic_string<T>::npos)
        return Empty<T>();
    return input.substr(index);
}

template <class T>
static basic_string<T> TrimEnd(const basic_string<T> &input, const T *characters)
{
    if (input.length() == 0)
        return input;
    size_t index = input.find_last_not_of(characters);
    if (index == basic_string<T>::npos)
        return Empty<T>();
    return input.substr(0, index + 1);
}

template <class T>
static basic_string<T> Trim(const basic_string<T> &input, const T *characters)
{
    if (input.length() == 0)
        return input;
    size_t f = input.find_first_not_of(characters);
    size_t l = input.find_last_not_of(characters);
    if (f == basic_string<T>::npos)
        return Empty<T>();
    return input.substr(f, l - f + 1);
}

template <class T, class C>
static basic_string<C> Join(const T *input, int length, const C *separator)
{
    basic_stringstream<C> ss;
    if (length > 0)
    {
        ss << input[0];
        for (int i = 1; i < length; i++)
        {
            ss << separator << input[i];
        }
    }
    return ss.str();
}

template <class T, class C>
static basic_string<C> Join(const vector<T> &input, const C *separator)
{
    basic_stringstream<C> ss;
    if (input.size() > 0)
    {
        ss << input[0];
        for (size_t i = 1; i < input.size(); i++)
        {
            ss << separator << input[i];
        }
    }
    return ss.str();
}

template <class T>
static set<T> UniqueChars(const basic_string<T> &input)
{
    set<T> output;
    for (size_t i = 0; i < input.length(); i++)
        output.insert(input[i]);
    return output;
}

static bool ContainsUniqueChars(const string &input)
{
    if (input.length() > 256)
        return false;
    bitset<256> mask;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (mask.test(input[i]))
            return false;
        mask.set(input[i]);
    }
    return true;
}
} // namespace String
} // namespace Test

#endif