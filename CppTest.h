#ifndef _CPPTEST_H_
#define _CPPTEST_H_

#include "Test.h"

using namespace std;
using namespace Test;

class CppTest : public TestClass
{
public:
    CppTest(Log &log) : TestClass(log) {}
    ~CppTest(void) {}
    void Init(void);
};

class BaseObject
{
public:
    BaseObject(void)
    {
        cout << "BaseObject Constructor" << endl;
    }

    // Has to make the destructor virtual
    // Otherwise, the destructor of derived object will
    // not be called if delete a pointer of base type.
    virtual ~BaseObject(void)
    {
        cout << "BaseObject Destructor" << endl;
    }

    virtual void VirtualMethod(void) = 0;
};

class DerivedObject1 : public BaseObject
{
public:
    DerivedObject1(void)
    {
        cout << "DerivedObject1 Constructor" << endl;
    }

    ~DerivedObject1(void)
    {
        cout << "DerivedObject1 Destructor" << endl;
    }

    void VirtualMethod(void)
    {
        cout << "DerivedObject1 VirtualMethod" << endl;
    }
};

class DerivedObject2 : public BaseObject
{
public:
    DerivedObject2(void)
    {
        cout << "DerivedObject2 Constructor" << endl;
    }

    ~DerivedObject2(void)
    {
        cout << "DerivedObject2 Destructor" << endl;
    }

    void VirtualMethod(void)
    {
        cout << "DerivedObject2 VirtualMethod" << endl;
    }
};

class AnObject
{
public:
    AnObject(void)
    {
        cout << "AnObject Constructor" << endl;
    }

    ~AnObject(void)
    {
        cout << "AnObject Destructor" << endl;
    }

    void Method(void)
    {
        cout << "AnObject Method" << endl;
    }

    static void ReferObject(AnObject &o)
    {
        cout << "AnObject ReferObject ";
        o.Method();
    }
};

class AnotherObject
{
private:
    unique_ptr<AnObject> anObject;

public:
    AnotherObject(void)
    {
        anObject = unique_ptr<AnObject>(new AnObject());
        cout << "AnotherObject Constructor" << endl;
    }

    ~AnotherObject(void)
    {
        cout << "AnotherObject Destructor" << endl;
    }
};

void CppTest::Init(void)
{
    Add("string", [&]() {
        {
            string s = "Test";
            s[1] = 'E';
            bool eq = (s == "TEst");
            Logger().WriteInformation("%s\n", s.c_str());
            ASSERT2(eq, String::Format("%s %s TEst\n", s.c_str(), eq ? "==" : "!="));
        }
        {
            string s = "Test";
            s[2] = '\0';
            bool eq1 = (s == "Te");
            int eq2 = strcmp(s.c_str(), "Te");
            cout << s << endl;
            Logger().WriteInformation("%s\n", s.c_str());
            ASSERT2(eq1 == false, String::Format("%s %s Te\n", s.c_str(), eq1 ? "==" : "!="));
            ASSERT2(eq2 == 0, String::Format("%s %s Te\n", s.c_str(), eq2 ? "==" : "!="));
        }
    });

    Add("ComparePair", [&]() {
        auto check = [&](pair<int, int> p0, pair<int, int> p1, char expect) {
            char e;
            if (p0 < p1)
                e = '<';
            else if (p0 == p1)
                e = '=';
            else
                e = '>';
            Logger().WriteInformation("<%d,%d> %c <%d,%d>\n", p0.first, p0.second, e, p1.first, p1.second);
            ASSERT1(e == expect);
        };
        check(make_pair(-1, -1), make_pair(-1, -1), '=');
        check(make_pair(-1, -2), make_pair(-1, -3), '>');
        check(make_pair(-1, -4), make_pair(-1, -2), '<');
        check(make_pair(-2, -1), make_pair(-1, -1), '<');
        check(make_pair(-1, -1), make_pair(-2, -1), '>');
        check(make_pair(0, 0), make_pair(0, 0), '=');
        check(make_pair(0, -1), make_pair(0, 1), '<');
        check(make_pair(0, 1), make_pair(0, -1), '>');
        check(make_pair(1, 0), make_pair(-1, 0), '>');
        check(make_pair(-1, 0), make_pair(1, 0), '<');
    });

    Add("SortPairs", [&]() {
        vector<int> v;
        for (int i = 0; i < 20; i++)
        {
            v.push_back(rand());
        }
        auto print = [&](vector<pair<int, int>> i) {
            Logger().WriteInformation("[");
            for (size_t j = 0; j < i.size(); j++)
            {
                if (j > 0)
                    Logger().WriteInformation(", ");
                Logger().WriteInformation("<%d,%d>", i[j].first, i[j].second);
            }
            Logger().WriteInformation("]\n");
        };
        vector<pair<int, int>> p;
        for (int i = 0; i < (int)v.size(); i++)
        {
            p.push_back(make_pair(i, v[i]));
        }
        print(p);
        random_shuffle(p.begin(), p.end());
        print(p);
        sort(p.begin(), p.end());
        print(p);
    });

    Add("unique_ptr", [&]() {
        {
            AnObject *anObject = new AnObject();
            anObject->Method();
            delete anObject;
        }
        {
            cout << endl;
            unique_ptr<AnObject> anObject(new AnObject());
            anObject->Method();
            AnObject::ReferObject(*anObject);
        }
        {
            cout << endl;
            BaseObject *anObject = new DerivedObject1();
            anObject->VirtualMethod();
            // Both DerivedObject1 destructor and BaseObject
            // destructor get called because the destructor
            // of BaseObject is virtual
            delete anObject;
        }
        {
            cout << endl;
            unique_ptr<BaseObject> anObject(new DerivedObject1());
            anObject->VirtualMethod();
            // Both DerivedObject1 destructor and BaseObject
            // destructor get called because the destructor
            // of BaseObject is virtual
        }
        {
            cout << endl;
            unique_ptr<DerivedObject1> anObject(new DerivedObject1());
            anObject->VirtualMethod();
            // Both DerivedObject1 destructor and BaseObject
            // destructor get called
        }
        {
            cout << endl;
            vector<BaseObject *> v;
            BaseObject *object1 = new DerivedObject1();
            BaseObject *object2 = new DerivedObject2();
            v.push_back(object1);
            v.push_back(object2);
            for_each(v.begin(), v.end(), [&](BaseObject *it) {
                it->VirtualMethod();
                // Both DerivedObject1 destructor and BaseObject
                // destructor get called because the destructor
                // of BaseObject is virtual
                delete it;
            });
        }
        {
            cout << endl;
            vector<BaseObject *> v;
            DerivedObject1 *object1 = new DerivedObject1();
            DerivedObject2 *object2 = new DerivedObject2();
            v.push_back(object1);
            v.push_back(object2);
            for_each(v.begin(), v.end(), [&](BaseObject *it) {
                it->VirtualMethod();
                // Both DerivedObject1 destructor and BaseObject
                // destructor get called because the destructor
                // of BaseObject is virtual
                delete it;
            });
        }
        {
            cout << endl;
            vector<unique_ptr<AnObject>> v;
            v.push_back(unique_ptr<AnObject>(new AnObject()));
            for_each(v.begin(), v.end(), [&](unique_ptr<AnObject> &it) {
                it->Method();
            });
        }
        {
            cout << endl;
            vector<unique_ptr<BaseObject>> v;
            v.push_back(unique_ptr<BaseObject>(new DerivedObject1()));
            v.push_back(unique_ptr<BaseObject>(new DerivedObject2()));
            for_each(v.begin(), v.end(), [&](unique_ptr<BaseObject> &it) {
                it->VirtualMethod();
            });
        }
        {
            cout << endl;
            unique_ptr<AnotherObject> anotherObject(new AnotherObject());
        }
    });
}

#endif
