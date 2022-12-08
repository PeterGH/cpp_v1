#ifndef _CPPTEST_H_
#define _CPPTEST_H_

#include "Test.h"
#include "Util.h"
#include <limits.h>
#include <set>
#include <string.h>
#include <utility>

using namespace std;
using namespace Test;

class CppTest : public TestClass {
  public:
    CppTest(Log &log) : TestClass(log) {}
    ~CppTest(void) {}
    void Init(void);

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

void CppTest::Init(void) {
    Add("Raw Pointer", [&]() {
        AnObject *anObject = new AnObject();
        anObject->Method();
        delete anObject;
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

    Add("set insert vector", [&]() {
        set<vector<int>> s;
        pair<set<vector<int>>::iterator, bool> p;
        p = s.insert(vector<int>{});
        Logger() << s;
        ASSERT1(p.second == true);
        p = s.insert(vector<int>{});
        Logger() << s;
        ASSERT1(p.second == false);
        p = s.insert(vector<int>{1});
        Logger() << s;
        ASSERT1(p.second == true);
        p = s.insert(vector<int>{1});
        Logger() << s;
        ASSERT1(p.second == false);
        p = s.insert(vector<int>{2});
        Logger() << s;
        ASSERT1(p.second == true);
        p = s.insert(vector<int>{2});
        Logger() << s;
        ASSERT1(p.second == false);
        p = s.insert(vector<int>{1, 2});
        Logger() << s;
        ASSERT1(p.second == true);
        p = s.insert(vector<int>{1, 2});
        Logger() << s;
        ASSERT1(p.second == false);
        p = s.insert(vector<int>{2, 1});
        Logger() << s;
        ASSERT1(p.second == true);
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

    Add("String substr", [&]() {
        string s = "abc";
        Logger() << s << ", " << s.substr(0, 0) << endl;
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

    Add("CompareStrings", [&]() {
        auto check = [&](const string &l, const string &r, int e) {
            int c = l.compare(r);
            Logger() << "compare(" << l << ", " << r << ") = " << c << endl;
            ASSERT1(c == e);
        };
        check("a", "b", -1);
        check("b", "a", 1);
        check("ab", "cd", -2);
        check("c", "ab", 2);
        check("", "ab", -2);
        check("", "c", -1);
        check("", "def", -3);
        check("f", "", 1);
        check("gh", "", 2);
        check("fasdf", "", 5);
        check("", "", 0);
    });

    Add("SortStrings", [&]() {
        auto check = [&](vector<string> &v) {
            Logger() << v;
            sort(v.begin(), v.end(),
                 [&](const string &l, const string &r) -> bool {
                     return l.compare(r) < 0;
                 });
            Logger() << v;
            for (size_t i = 0; i + 1 < v.size(); i++)
                ASSERT1(v[i].compare(v[i + 1]) < 0);
        };
        {
            vector<string> v = {"eat", "tea", "ate"};
            check(v);
        }
    });

    Add("Sort vector<vector<int>>", [&]() {
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

    Add("Sort vector<vector<string>>", [&]() {
        auto check = [&](vector<vector<string>> &g) {
            Logger() << "Before sort" << endl << g;
            sort(g.begin(), g.begin());
            Logger() << "After sort" << endl << g;
        };
        {
            vector<vector<string>> g = {{"abc", "def", "hij"},
                                        {"xyz", "uvw", "rst"},
                                        {"l"},
                                        {"n", "m"}};
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
        printf("The set is %ssorted\n", s ? "" : "not ");

        for (set<int>::iterator i = sorted.begin(); i != sorted.end(); i++) {
            printf("\t%d", *i);
        }

        printf("\n");
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

    Add("Next_Permutation", [&]() {
        auto check = [&](const vector<int> &w) {
            vector<int> v(w);
            Logger() << v;
            while (std::next_permutation(v.begin(), v.end()))
                Logger() << v;
            Logger() << endl;
        };
        check({1, 1, 2});
        check({2, 1, 1});
        check({2, 1, 2});
        check({3, 3, 3});
    });

    Add("Vector size after insert at begin", [&]() {
        vector<int> v;
        ASSERT1(v.size() == 0);
        v.insert(v.begin(), 3);
        ASSERT1(v.size() == 1);
        vector<vector<int>> g;
        ASSERT1(g.size() == 0);
        // {} will be treated as an initializer list,
        // which effectly insert nothing at the begin,
        // so the size is still zero.
        g.insert(g.begin(), {});
        Logger() << g;
        Logger() << "g.size() = " << g.size() << endl;
        ASSERT1(g.size() == 0);
        // Explicitly insert an empty vector at begin,
        // and increase size by 1.
        g.insert(g.begin(), vector<int>());
        Logger() << g;
        Logger() << "g.size() = " << g.size() << endl;
        ASSERT1(g.size() == 1);
    });

    Add("SetOfVectors", [&](){
        set<vector<int>> s;
        s.insert({1, 1, 1});
        s.insert({2, 2, 2});
        s.insert({1, 1, 1});
        s.insert({1, 2, 1});
        s.insert({2, 2, 2});
        s.insert({1, 1});
        s.insert({2, 1});
        s.insert({2, 2});
        Logger() << s;
    });

    Add("Reference", [&]() {
        map<int, vector<int>> m;
        for (int i = 0; i < 5; i++)
            m[i] = {};
        Logger() << m;
        function<vector<int>&(int)> getVector = [&](int i)->vector<int>&{
            if (m.find(i) != m.end())
                return m[i];
            else
                return m[0];
        };
        function<void(int, vector<int>&)> getVector2 = [&](int i, vector<int>& v){
            if (m.find(i) != m.end())
                v = m[i];
            else
                v = vector<int>();
        };
        vector<int>& v = getVector(0);
        v.push_back(0);
        v.push_back(1);
        v = getVector(1);
        v.push_back(2);
        v.push_back(3);
        vector<int>& v2 = v;
        getVector2(2, v2);
        v2.push_back(4);
        v2.push_back(5);
        getVector2(3, v2);
        v2.push_back(6);
        v2.push_back(7);
        Logger() << m;
    });

    Add("Erase Iterator", [&](){
        vector<int> v = { 0, 1, 2, 3 };
        vector<int>::iterator it = v.begin();
        ++it;
        ++it;
        Logger() << "it (at index 2): " << *it << endl;
        vector<int>::iterator it2 = v.begin();
        ++it2;
        ++it2;
        Logger() << "it2: " << *it2 << endl;
        Logger() << "it (at index 2): " << *it << endl;
        ASSERT1(it2 == it);
        ++it2;
        Logger() << "it2: " << *it2 << endl;
        Logger() << "it (at index 2): " << *it << endl;
        ASSERT1(it2 != it);
        vector<int>::iterator it3 = v.begin();
        ++it3;
        Logger() << "it3: " << *it3 << endl;
        Logger() << "it (at index 2): " << *it << endl;
        ASSERT1(it3 != it);
        // Errase makes v shorter. it still at index 2 but now points to a different element.
        it3 = v.erase(it3);
        Logger() << "it3: " << *it3 << endl;
        Logger() << "it (at index 2): " << *it << endl;
        ASSERT1(*it3 != *it);
        ASSERT1(it3 != it);
        ++it3;
        Logger() << "it3: " << *it3 << endl;
        Logger() << "it (at index 2): " << *it << endl;
        ASSERT1(*it3 == *it);
        ASSERT1(it3 == it);
    });

    Add("LeastSignificantBitValue1", [&]() {
        auto check = [&](int b, int e) {
            int c = ~b + 1;
            Logger() << std::hex << "~" << b << " + 1 = " << c << endl;
            int d = b & c;
            Logger() << std::hex << b << " & (~" << b << " + 1) = " << d << ", expect " << e << endl;
            ASSERT1(d == e);
        };
        check(1, 1);
        check(2, 2);
        check(3, 1);
        check(4, 4);
        check(5, 1);
        check(6, 2);
        check(7, 1);
        check(8, 8);
        check(9, 1);
        check(10, 2);
        check(0x10100000, 0x00100000);
    });

    Add("LeastSignificantBitValue2", [&]() {
        auto check = [&](int b, int e) {
            int c = -b;
            Logger() << std::hex << "-" << b << " = " << c << endl;
            int d = b & c;
            Logger() << std::hex << b << " & (-" << b << ") = " << d << ", expect " << e << endl;
            ASSERT1(d == e);
        };
        check(1, 1);
        check(2, 2);
        check(3, 1);
        check(4, 4);
        check(5, 1);
        check(6, 2);
        check(7, 1);
        check(8, 8);
        check(9, 1);
        check(10, 2);
        check(0x10100000, 0x00100000);
    });

    Add("MultiplyBy2", [&]() {
        auto check = [&](int n, int e) {
            int v = n << 1;
            Logger() << n << " << 1 = " << v << ", " << e << endl;
            ASSERT1(v == e);
        };
        check(1, 2);
        check(-1, -2);
        check(3, 6);
        check(-3, -6);
        check(INT_MAX >> 1, INT_MAX - 1);
        check(INT_MIN >> 1, INT_MIN);
    });
}

#endif
