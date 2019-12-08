#ifndef _TEST_H_
#define _TEST_H_

#include "Log.h"
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <typeinfo>

using namespace std;

namespace Test {
class AssertError : public domain_error {
  public:
    AssertError(const string &message) : domain_error(message) {}
};

#define ASSERT1(statement) Assert(statement, #statement, "", __FILE__, __LINE__)

#define ASSERT2(statement, message)                                            \
    Assert(statement, #statement, message, __FILE__, __LINE__)

#define ASSERTERROR(statement, error)                                          \
    try {                                                                      \
        statement;                                                             \
    } catch (error &) {                                                        \
        ASSERT1(true);                                                         \
    }

class TestClass {
  private:
    size_t _passCount;
    size_t _failCount;
    Log &_log;
    map<string, function<void(void)>> _testMethod;

    bool Has(const string &name) const {
        return _testMethod.find(name) != _testMethod.end();
    }

    void Run(map<string, function<void(void)>>::const_iterator &it) {
        try {
            _log << "  === " << it->first << " ===" << endl;
            it->second();
            _passCount++;
        } catch (AssertError &e) {
            _failCount++;
            _log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(),
                            e.what());
        } catch (exception &e) {
            _failCount++;
            _log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(),
                            e.what());
        } catch (...) {
            _failCount++;
            _log.WriteError("%s\n", it->first.c_str());
        }
    }

  public:
    TestClass(Log &log) : _passCount(0), _failCount(0), _log(log) {}

    virtual ~TestClass(void) {}

    static void Assert(bool result, const string &statement,
                       const string &message, const string &file, size_t line) {
        if (!result) {
            ostringstream error;
            error << message << "\n"
                  << file << ", " << line << ": " << statement;
            throw AssertError(error.str());
        }
    }

    virtual void Init(void) = 0;

    const string Name(void) const {
        string name = typeid(*this).name();
        return name;
    }

    Log &Logger(void) const { return _log; }
    size_t PassCount(void) const { return _passCount; }
    size_t FailCount(void) const { return _failCount; }

    void Add(const string &name, const function<void(void)> &test) {
        if (Has(name)) {
            ostringstream error;
            error << "Test method '" << name << "' already exists.";
            throw invalid_argument(error.str());
        }
        _testMethod.insert(make_pair(name, test));
    }

    void List(void) const {
        for (map<string, function<void(void)>>::const_iterator it =
                 _testMethod.cbegin();
             it != _testMethod.cend(); it++) {
            _log << "\t" << it->first << endl;
        }
    }

    void Run(void) {
        for (map<string, function<void(void)>>::const_iterator it =
                 _testMethod.cbegin();
             it != _testMethod.cend(); it++) {
            Run(it);
        }
    }

    void Run(const string &name) {
        for (map<string, function<void(void)>>::const_iterator it =
                 _testMethod.cbegin();
             it != _testMethod.cend(); it++) {
            if (0 == it->first.compare(0, name.size(), name))
                Run(it);
        }
    }

    void Report(void) const {
        _log << _passCount << " passed, " << _failCount << " failed." << endl;
    }
};

class TestSuite final {
  private:
    size_t _passCount;
    size_t _failCount;
    Log &_log;
    map<string, TestClass *> _test;

    bool Has(const string &name) const {
        return _test.find(name) != _test.end();
    }

    void Run(map<string, TestClass *>::const_iterator &it) {
        _log << " ==== " << it->first << " ====" << endl;
        it->second->Run();
        it->second->Report();
        _passCount += it->second->PassCount();
        _failCount += it->second->FailCount();
    }

    void Run(map<string, TestClass *>::const_iterator &it,
             const string &method) {
        _log << " ==== " << it->first << " ====" << endl;
        it->second->Run(method);
        it->second->Report();
        _passCount += it->second->PassCount();
        _failCount += it->second->FailCount();
    }

  public:
    TestSuite(Log &log) : _passCount(0), _failCount(0), _log(log) {}
    ~TestSuite(void) {}

    void Add(TestClass *test) {
        string name = test->Name();
        if (Has(name)) {
            ostringstream error;
            error << "Test class '" << name << "' already exists.";
            throw invalid_argument(error.str());
        }
        test->Init();
        _test.insert(make_pair(name, test));
    }

    void List(void) const {
        for (map<string, TestClass *>::const_iterator it = _test.cbegin();
             it != _test.cend(); it++) {
            _log << "\t" << it->first << endl;
        }
    }

    void List(const string &test) const {
        for (map<string, TestClass *>::const_iterator it = _test.cbegin();
             it != _test.cend(); it++) {
            if (0 == it->first.compare(0, test.size(), test)) {
                _log << "Available test methods of " << it->first
                     << " are:" << endl;
                it->second->List();
            }
        }
    }

    void Run(void) {
        for (map<string, TestClass *>::const_iterator it = _test.cbegin();
             it != _test.cend(); it++) {
            Run(it);
        }
    }

    void Run(const string &test) {
        for (map<string, TestClass *>::const_iterator it = _test.cbegin();
             it != _test.cend(); it++) {
            if (0 == it->first.compare(0, test.size(), test)) {
                Run(it);
            }
        }
    }

    void Run(const string &test, const string &method) {
        for (map<string, TestClass *>::const_iterator it = _test.cbegin();
             it != _test.cend(); it++) {
            if (0 == it->first.compare(0, test.size(), test)) {
                Run(it, method);
            }
        }
    }

    void Report(void) const {
        _log << " ==== Summary ====" << endl;
        _log << _passCount << " passed, " << _failCount << " failed." << endl;
    }
};
} // namespace Test
#endif