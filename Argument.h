#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_

#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace Test
{
template <class T>
class Argument
{
private:
    vector<basic_string<T>> _indexedArg;
    map<basic_string<T>, basic_string<T>> _namedArg;

    void Parse(int argc, const T *argv[])
    {
        if (argc <= 0 || argv == nullptr)
            return;
        int i = 0;
        while (i < argc)
        {
            if (argv[i][0] == T('-'))
            {
                basic_string<T> key = basic_string<T>(&argv[i][1]);
                ToLower(key);
                if (i + 1 < argc && argv[i + 1][0] != T('-'))
                {
                    // case: -key value
                    basic_string<T> value = basic_string<T>(argv[i + 1]);
                    _namedArg.insert(make_pair(key, value));
                    i += 2;
                }
                else
                {
                    // case 1: -key
                    // case 2: -key1 -key2
                    _namedArg.insert(make_pair(key, basic_string<T>()));
                    i++;
                }
            }
            else
                _indexedArg.push_back(basic_string<T>(argv[i++]));
        }
    }

    static void ToLower(string &input)
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);
    }

    static void ToLower(wstring &input)
    {
        transform(input.begin(), input.end(), input.begin(), ::towlower);
    }

    static basic_string<T> ToLower(const basic_string<T> &input)
    {
        basic_string<T> output(input);
        ToLower(output);
        return output;
    }

    static string ToString(const basic_string<T> &input)
    {
        string output(input.begin(), input.end());
        return output;
    }

public:
    Argument(int argc, const T *argv[]) { Parse(argc, argv); }

    Argument(const Argument &a)
        : _indexedArg(a._indexedArg), _namedArg(a._namedArg)
    {
    }
    ~Argument(void) {}

    size_t NamedArgCount(void) const { return _namedArg.size(); }

    size_t IndexedArgCount(void) const { return _indexedArg.size(); }

    size_t Count(void) const { return _namedArg.size() + _indexedArg.size(); }

    bool Has(const basic_string<T> &name) const
    {
        basic_string<T> namel = ToLower(name);
        return _namedArg.find(namel) != _namedArg.end();
    }

    bool Has(size_t index) const { return index < _indexedArg.size(); }

    const basic_string<T> &operator[](const basic_string<T> &name) const
    {
        basic_string<T> namel = ToLower(name);
        typename map<basic_string<T>, basic_string<T>>::const_iterator it =
            _namedArg.find(namel);
        if (it != _namedArg.end())
            return it->second;
        ostringstream ss;
        ss << "Invalid argument name '" << ToString(name) << "'";
        throw invalid_argument(ss.str());
    }

    const basic_string<T> &operator[](size_t index) const
    {
        if (index < _indexedArg.size())
            return _indexedArg[index];
        ostringstream ss;
        ss << "Invalid argument index '" << index << "'";
        throw invalid_argument(ss.str());
    }

    const set<basic_string<T>> Names(void) const
    {
        set<basic_string<T>> names;
        for (typename map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArg.cbegin();
             it != _namedArg.cend(); it++)
        {
            names.insert(it->first);
        }
        return names;
    }

    const basic_string<T> ToString(void) const
    {
        basic_stringstream<T> ss;
        size_t i = 0;
        for (typename map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArg.cbegin();
             it != _namedArg.cend(); it++)
        {
            ss << T('-') << it->first << T(' ') << it->second;
            if ((i++) < _namedArg.size() - 1)
                ss << T(' ');
        }
        if (_namedArg.size() > 0 && _indexedArg.size() > 0)
            ss << T(' ');
        for (i = 0; i < _indexedArg.size(); i++)
        {
            ss << _indexedArg[i];
            if (i != _indexedArg.size() - 1)
                ss << T(' ');
        }
        return ss.str();
    }

    // Get the names of all named arguments
    const set<basic_string<T>> Keys(void) const
    {
        set<basic_string<T>> keys;
        for (typename map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArg.cbegin();
             it != _namedArg.cend();
             it++)
        {
            keys.insert(it->first);
        }
        return keys;
    }
};
} // namespace Test
#endif