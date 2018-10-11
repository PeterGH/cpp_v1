#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <stdarg.h>
#include <string>

using namespace std;

namespace Test
{
class Log
{
  public:
    enum Level
    {
        Error,
        Warning,
        Information,
        Verbose
    };

  private:
    static const size_t MaxLength = 1024;
    ostream &_os;
    Level _level;

#define WRITE(level, format)                      \
    if (_level >= level)                          \
    {                                             \
        char buf[MaxLength];                      \
        va_list args;                             \
        va_start(args, format);                   \
        vsnprintf(buf, MaxLength, format, args);  \
        va_end(args);                             \
        if (level <= Level::Warning)              \
        {                                         \
            _os << #level << ": " << string(buf); \
        }                                         \
        else                                      \
        {                                         \
            _os << string(buf);                   \
        }                                         \
    }

  public:
    Log(ostream &os = cout, Level level = Level::Information)
        : _os(os), _level(level)
    {
    }

    ~Log() {}

    void WriteError(const char *format, ...)
    {
        WRITE(Error, format);
    }

    void WriteWarning(const char *format, ...)
    {
        WRITE(Warning, format);
    }

    void WriteInformation(const char *format, ...)
    {
        WRITE(Information, format);
    }

    void WriteVerbose(const char *format, ...)
    {
        WRITE(Verbose, format);
    }

    template <class T>
    Log &operator<<(const T &v)
    {
        _os << v;
        return *this;
    }

    Log &operator<<(ostream &(*pf)(ostream &))
    {
        _os << (*pf);
        return *this;
    }
};
} // namespace Test

#endif