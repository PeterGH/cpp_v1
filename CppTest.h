#ifndef _CPPTEST_H_
#define _CPPTEST_H_

#include "Test.h"

using namespace std;
using namespace Test;

class CppTest : public TestClass {
  public:
    CppTest(Log &log) : TestClass(log) {}
    ~CppTest(void) {}
    void Init(void);
};

class BaseObject {
  public:
    BaseObject(void) { cout << "BaseObject Constructor" << endl; }

    // Has to make the destructor virtual
    // Otherwise, the destructor of derived object will
    // not be called if delete a pointer of base type.
    virtual ~BaseObject(void) { cout << "BaseObject Destructor" << endl; }

    virtual void VirtualMethod(void) = 0;
};

class DerivedObject1 : public BaseObject {
  public:
    DerivedObject1(void) { cout << "DerivedObject1 Constructor" << endl; }

    ~DerivedObject1(void) { cout << "DerivedObject1 Destructor" << endl; }

    void VirtualMethod(void) { cout << "DerivedObject1 VirtualMethod" << endl; }
};

class DerivedObject2 : public BaseObject {
  public:
    DerivedObject2(void) { cout << "DerivedObject2 Constructor" << endl; }

    ~DerivedObject2(void) { cout << "DerivedObject2 Destructor" << endl; }

    void VirtualMethod(void) { cout << "DerivedObject2 VirtualMethod" << endl; }
};

class AnObject {
  public:
    AnObject(void) { cout << "AnObject Constructor" << endl; }

    ~AnObject(void) { cout << "AnObject Destructor" << endl; }

    void Method(void) { cout << "AnObject Method" << endl; }

    static void ReferObject(AnObject &o) {
        cout << "AnObject ReferObject ";
        o.Method();
    }
};

class AnotherObject {
  private:
    unique_ptr<AnObject> anObject;

  public:
    AnotherObject(void) {
        anObject = unique_ptr<AnObject>(new AnObject());
        cout << "AnotherObject Constructor" << endl;
    }

    ~AnotherObject(void) { cout << "AnotherObject Destructor" << endl; }
};

template <class T> T Test_VarArg(int count, T arg1, ...) {
    va_list ptr;

    va_start(ptr, count);

    cout << count;

    T next;

    for (int i = 0; i < count; i++) {
        next = va_arg(ptr, T);
        cout << " " << next;
    }

    next = va_arg(ptr, T);
    if (typeid(T) == typeid(int)) {
        cout << " int " << next << endl;
        // WIN_ASSERT_EQUAL(next, 0);
    } else {
        cout << " " << next << endl;
        // WIN_ASSERT_EQUAL(next, NULL);
    }

    va_end(ptr);

    return next;
}

class Node {
  public:
    int data;
    Node *next;

    Node(int d) {
        data = d;
        next = nullptr;
    }

    // This will be called recursively.
    ~Node(void) {
        if (next != nullptr) {
            delete next;
            next = nullptr;
        }

        cout << "Deleting " << data << endl;
    }
};

void CppTest::Init(void) {
    Add("Raw Pointer", [&]() {
        AnObject *anObject = new AnObject();
        anObject->Method();
        delete anObject;
    });

    Add("unique_ptr", [&]() {
        unique_ptr<AnObject> anObject(new AnObject());
        anObject->Method();
        AnObject::ReferObject(*anObject);
    });

    Add("inheritance", [&]() {
        BaseObject *anObject = new DerivedObject1();
        anObject->VirtualMethod();
        // Both DerivedObject1 destructor and BaseObject destructor get called
        // because the destructor of BaseObject is virtual
        delete anObject;
    });

    Add("unique_ptr inheritance", [&]() {
        unique_ptr<BaseObject> anObject(new DerivedObject1());
        anObject->VirtualMethod();
        // Both DerivedObject1 destructor and BaseObject destructor get called
        // because the destructor of BaseObject is virtual
    });

    Add("unique_ptr inheritance2", [&]() {
        unique_ptr<DerivedObject1> anObject(new DerivedObject1());
        anObject->VirtualMethod();
        // Both DerivedObject1 destructor and BaseObject destructor get called
    });

    Add("vector raw pointer base type", [&]() {
        vector<BaseObject *> v;
        BaseObject *object1 = new DerivedObject1();
        BaseObject *object2 = new DerivedObject2();
        v.push_back(object1);
        v.push_back(object2);
        for_each(v.begin(), v.end(), [&](BaseObject *it) {
            it->VirtualMethod();
            // Both DerivedObject1 destructor and BaseObject destructor get
            // called because the destructor of BaseObject is virtual
            delete it;
        });
    });

    Add("vector raw pointer derived type", [&]() {
        vector<BaseObject *> v;
        DerivedObject1 *object1 = new DerivedObject1();
        DerivedObject2 *object2 = new DerivedObject2();
        v.push_back(object1);
        v.push_back(object2);
        for_each(v.begin(), v.end(), [&](BaseObject *it) {
            it->VirtualMethod();
            // Both DerivedObject1 destructor and BaseObject destructor get
            // called because the destructor of BaseObject is virtual
            delete it;
        });
    });

    Add("vector unique_ptr", [&]() {
        vector<unique_ptr<AnObject>> v;
        v.push_back(unique_ptr<AnObject>(new AnObject()));
        for_each(v.begin(), v.end(),
                 [&](unique_ptr<AnObject> &it) { it->Method(); });
    });

    Add("vector unique_ptr base type", [&]() {
        vector<unique_ptr<BaseObject>> v;
        v.push_back(unique_ptr<BaseObject>(new DerivedObject1()));
        v.push_back(unique_ptr<BaseObject>(new DerivedObject2()));
        for_each(v.begin(), v.end(),
                 [&](unique_ptr<BaseObject> &it) { it->VirtualMethod(); });
    });

#if NULL
    Add("vector unique_ptr", [&]() {
        vector<AnObject &> v;
        unique_ptr<AnObject> anObject(new AnObject());
        v.push_back(*anObject);
        for_each(v.begin(), v.end(), [&](AnObject &it) { it.Method(); });
    });
    Add("vector unique_ptr2", [&]() {
        vector<unique_ptr<AnObject>> v;
        unique_ptr<AnObject> anObject(new AnObject());
        v.push_back(anObject);
        for_each(v.begin(), v.end(),
                 [&](unique_ptr<AnObject> &it) { it.Method(); });
    });
    Add("vector unique_ptr base type", [&]() {
        vector<unique_ptr<BaseObject>> v;
        unique_ptr<BaseObject> object1(new DerivedObject1());
        unique_ptr<BaseObject> object2(new DerivedObject2());
        v.push_back(object1);
        v.push_back(object2);
        for_each(v.begin(), v.end(),
                 [&](unique_ptr<BaseObject> &it) { it->VirtualMethod(); });
    });
#endif
    Add("Subtraction of two size_t", [&]() {
        size_t a = 123;
        size_t b = 456;
        auto c = a - b;
        Logger() << "(size_t)" << a << " - (size_t)" << b << " = ("
                 << typeid(a - b).name() << ")" << a - b << "\n";
        ASSERT1(a - b > 0);
    });

    Add("Map by pair", [&]() {
        map<pair<int, int>, int> m;
        m[make_pair(0, 1)] = 1;
        m[make_pair(2, 3)] = 5;
        ASSERT1(m.find(make_pair(2, 3)) != m.end());
        ASSERT1(m.find(make_pair(0, 1)) != m.end());
        ASSERT1(m.find(make_pair(0, 3)) == m.end());
    });

    Add("string", [&]() {
        {
            string s = "Test";
            s[1] = 'E';
            bool eq = (s == "TEst");
            Logger().WriteInformation("%s\n", s.c_str());
            ASSERT2(eq, String::Format("%s %s TEst\n", s.c_str(),
                                       eq ? "==" : "!="));
        }
        {
            string s = "Test";
            s[2] = '\0';
            bool eq1 = (s == "Te");
            int eq2 = strcmp(s.c_str(), "Te");
            cout << s << endl;
            Logger().WriteInformation("%s\n", s.c_str());
            ASSERT2(eq1 == false,
                    String::Format("%s %s Te\n", s.c_str(), eq1 ? "==" : "!="));
            ASSERT2(eq2 == 0,
                    String::Format("%s %s Te\n", s.c_str(), eq2 ? "==" : "!="));
        }
    });

    Add("Change string", [&]() {
        string s = "a string";
        Logger() << s << "\n";
        s[0] = 'b';
        Logger() << s << endl;
        s[5] = '\0';
        Logger() << s << endl;
    });

    Add("String character", [&]() {
        string s = "ab";
        ASSERT1(s[0] == 'a');
        ASSERT1(s[1] == 'a' + 1);
    });

    Add("String resize", [&]() {
        auto print = [&](string s) {
            Logger() << "\"" << s << "\".length = " << s.length() << endl;
            Logger() << "\"" << s << "\".size = " << s.size() << endl;
        };
        string str = "0123456789";
        print(str);
        for (int i = 9; i >= 0; i--) {
            str.resize(i);
            print(str);
        }
    });

    Add("atoi", [&]() {
        auto test = [&](string s, int expect) {
            int n = atoi(s.c_str());
            ASSERT1(n == expect);
        };
        test("01", 1);
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
            Logger().WriteInformation("<%d,%d> %c <%d,%d>\n", p0.first,
                                      p0.second, e, p1.first, p1.second);
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
        for (int i = 0; i < 20; i++) {
            v.push_back(rand());
        }
        auto print = [&](vector<pair<int, int>> i) {
            Logger().WriteInformation("[");
            for (size_t j = 0; j < i.size(); j++) {
                if (j > 0)
                    Logger().WriteInformation(", ");
                Logger().WriteInformation("<%d,%d>", i[j].first, i[j].second);
            }
            Logger().WriteInformation("]\n");
        };
        vector<pair<int, int>> p;
        for (int i = 0; i < (int)v.size(); i++) {
            p.push_back(make_pair(i, v[i]));
        }
        print(p);
        random_shuffle(p.begin(), p.end());
        print(p);
        sort(p.begin(), p.end());
        print(p);
    });

    Add("Sort vector<vector>", [&]() {
        auto check = [&](vector<vector<int>> &g) {
            Logger() << "Before sort" << endl << g;
            sort(g.begin(), g.begin());
            Logger() << "After sort" << endl << g;
        };
        {
            vector<vector<int>> g = {{3, 2, 1}, {2, 1}, {3, 1},
                                     {3, 2},    {2},    {1}};
            check(g);
        }
        {
            vector<vector<int>> g = {{1, 2, 3}, {1, 2}, {1, 3},
                                     {2, 3},    {2},    {1}};
            check(g);
        }
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
            for_each(v.begin(), v.end(),
                     [&](unique_ptr<AnObject> &it) { it->Method(); });
        }
        {
            cout << endl;
            vector<unique_ptr<BaseObject>> v;
            v.push_back(unique_ptr<BaseObject>(new DerivedObject1()));
            v.push_back(unique_ptr<BaseObject>(new DerivedObject2()));
            for_each(v.begin(), v.end(),
                     [&](unique_ptr<BaseObject> &it) { it->VirtualMethod(); });
        }
        {
            cout << endl;
            unique_ptr<AnotherObject> anotherObject(new AnotherObject());
        }
    });

    Add("Link", [&]() {
        Node n(0);
        n.next = new Node(1);
        n.next->next = new Node(2);
    });

    Add("PriorityQueue", [&]() {
        vector<int> v(20);
        generate(v.begin(), v.end(), rand);

        cout << "Vector v is ( ";
        for_each(v.begin(), v.end(), [&](int x) { cout << x << " "; });
        cout << ")." << endl;

        priority_queue<int> maxQueue(v.begin(), v.end());
        cout << "Max Priority Queue:" << endl;
        while (!maxQueue.empty()) {
            int i = maxQueue.top();
            cout << i << " ";
            maxQueue.pop();
        }
        cout << endl;

        priority_queue<int, vector<int>, greater<int>> minQueue(v.begin(),
                                                                v.end());
        cout << "Min Priority Queue:" << endl;
        while (!minQueue.empty()) {
            int i = minQueue.top();
            cout << i << " ";
            minQueue.pop();
        }
        cout << endl;
    });

    Add("Set", [&]() {
        srand((unsigned int)time(NULL));
        int n = 100;
        set<int> sorted;
        for (int i = 0; i < n; i++) {
            sorted.insert(rand());
        }

        bool s = is_sorted(sorted.begin(), sorted.end());
        printf_s("The set is %ssorted\n", s ? "" : "not ");

        for (set<int>::iterator i = sorted.begin(); i != sorted.end(); i++) {
            printf_s("\t%d", *i);
        }

        printf_s("\n");
    });

    Add("Jagged Array", [&]() {
        vector<vector<int>> jagged;

        for (int i = 1; i < 10; i++) {
            vector<int> v;
            for (int j = 0; j < i; j++) {
                v.push_back(j);
            }

            jagged.push_back(v);
        }

        for_each(jagged.begin(), jagged.end(),
                 [&](const vector<int> &v) -> void {
                     for_each(v.begin(), v.end(),
                              [&](int i) -> void { cout << "\t" << i; });

                     cout << endl;
                 });
    });

    Add("Array[i]", [&]() {
        vector<vector<int>> jagged;

        for (int i = 1; i < 10; i++) {
            vector<int> v;
            for (int j = 0; j < i; j++) {
                v.push_back(j);
            }

            jagged.push_back(v);
        }

        for (size_t j = 0; j < jagged.size(); j++) {
            for (size_t i = 0; i < jagged[j].size(); i++) {
                cout << "\t" << jagged[j][i];
            }

            cout << endl;
        }
    });
}

#endif
