#ifndef _LEETCODETEST2_H_
#define _LEETCODETEST2_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init2(void)
{
    Add("200. Number of Islands", [&]()
        {
            auto check = [&](vector<vector<char>> &grid)
            {
                Logger() << grid;
                vector<vector<char>> grid2(grid);
                vector<vector<char>> grid3(grid);
                int c = numIslands(grid);
                int c2 = numIslands2(grid2);
                int c3 = numIslands3(grid3);
                Logger() << "#Islands: " << c << ", " << c2 << ", " << c3 << endl;
                ASSERT1(c == c2);
                ASSERT1(c == c3);
            };
            {
                vector<vector<char>> g = {
                    {'1', '1', '1', '1', '0'},
                    {'1', '1', '0', '1', '0'},
                    {'1', '1', '0', '0', '0'},
                    {'0', '0', '0', '0', '0'}};
                check(g);
            }
            {
                vector<vector<char>> g = {
                    {'1', '1', '0', '0', '0'},
                    {'1', '1', '0', '0', '0'},
                    {'0', '0', '1', '0', '0'},
                    {'0', '0', '0', '1', '1'}};
                check(g);
            }
            for (int i = 0; i < 10; i++)
            {
                int m = Random::Int(100, 1);
                int n = Random::Int(100, 1);
                vector<vector<char>> v = Random::Grid(m, n, '1', '0');
                check(v);
            }
        });

    Add("201. Bitwise AND of Numbers Range", [&]()
        {
            auto check = [&](int m, int n)
            {
                Logger() << "BitwiseAddRange [" << m << ", " << n << "] = ";
                int r = rangeBitwiseAnd(m, n);
                int r2 = rangeBitwiseAnd2(m, n);
                int r3 = rangeBitwiseAnd3(m, n);
                Logger() << r << ", " << r2 << ", " << r3 << endl;
                ASSERT1(r == r2);
                ASSERT1(r == r3);
            };
            for (int i = 0; i < 100; i++)
            {
                int m = Random::Int(INT_MAX, 0);
                int n = Random::Int(INT_MAX, m);
                check(m, n);
            }
        });

    Add("202. Happy Number", [&]()
        {
            auto check = [&](int n)
            {
                bool r = isHappy(n);
                Logger() << "isHappy(" << n << ") = " << r << endl;
            };
            check(2);
            for (int n = 3; n <= 100; n++)
                check(n);
        });

    Add("204. Count Primes", [&]()
        {
            auto check = [&](int n)
            {
                Logger() << "Count of primes less than " << n << ": ";
                int c = countPrimes(n);
                int c2 = countPrimes2(n);
                Logger() << c << ", " << c2 << endl;
                ASSERT1(c == c2);
            };
            for (int n = 2; n < 100; n++)
            {
                check(n);
                check(Random::Int(1000000, 0));
            }
        });

    Add("205. Isomorphic Strings", [&]()
        {
            auto check = [&](const string &s, const string &t)
            {
                Logger() << s << std::endl;
                Logger() << t << std::endl;
                bool r = isIsomorphic(s, t);
                bool r2 = isIsomorphic2(s, t);
                Logger() << "isIsomorphic = " << r << ", " << r2 << std::endl;
                ASSERT1(r == r2);
            };
            check("egg", "add");
            check("paper", "title");
        });

    Add("207. Course Schedule", [&]()
        {
            auto check = [&](int n, const vector<vector<int>> &p)
            {
                Logger() << n << "courses" << std::endl;
                Logger() << p;
                bool r = canFinish(n, p);
                bool r2 = canFinish2(n, p);
                Logger() << "canFinish = " << r << ", " << r2 << std::endl;
                ASSERT1(r == r2);
            };
            check(3, {{0, 1},
                      {0, 2},
                      {1, 2}});
        });

    Add("208. Implement Trie (Prefix Tree)", [&]()
        {
            auto check = [&](Trie *t, Trie *t2, const string &w)
            {
                bool r = t->search(w);
                bool r2 = t2->search(w);
                Logger() << "search(" << w << ") = " << r << ", " << r2 << endl;
                ASSERT1(r == r2);
                r = t->startsWith(w);
                r2 = t2->startsWith(w);
                Logger() << "startsWith(" << w << ") = " << r << ", " << r2 << endl;
                ASSERT1(r == r2);
                Logger() << "insert(" << w << ")" << endl;
                t->insert(w);
                t2->insert(w);
                r = t->search(w);
                r2 = t2->search(w);
                Logger() << "search(" << w << ") = " << r << ", " << r2 << endl;
                ASSERT1(r == r2);
                r = t->startsWith(w);
                r2 = t2->startsWith(w);
                Logger() << "startsWith(" << w << ") = " << r << ", " << r2 << endl;
                ASSERT1(r == r2);
            };
            vector<string> v = {"Trie", "insert", "search", "search",
                                "startsWith", "insert", "search", "",
                                "apple", "apple", "app", "app",
                                "app", "app"};
            Trie t;
            Trie t2;
            for (size_t i = 0; i < v.size(); i++)
                check(&t, &t2, v[i]);
            for (int i = 0; i < 100; i++)
            {
                string w = Random::String<char>(100, "abcdefghijklmnopqrstuvwxyz");
                check(&t, &t2, w);
            }
        });

    Add("214. Shortest Palindrome", [&]()
        {
            auto check = [&](const string &s)
            {
                Logger() << "ShortestPalindrome(" << s << ") = " << endl;
                string r = shortestPalindrome(s);
                string r2 = shortestPalindrome2(s);
                string r3 = shortestPalindrome3(s);
                string r4 = shortestPalindrome4(s);
                Logger() << r << endl
                         << r2 << endl
                         << r3 << endl
                         << r4 << endl;
                ASSERT1(r.compare(r2) == 0);
                ASSERT1(r.compare(r3) == 0);
                ASSERT1(r.compare(r4) == 0);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(30);
                string s = Random::String<char>(n, "abcd");
                check(s);
            }
        });

    Add("215. Kth Largest Element in an Array", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                for (int k = 1; k <= (int)v.size(); k++)
                {
                    vector<int> v1(v);
                    vector<int> v2(v);
                    Logger() << v1;
                    int r = findKthLargest(v1, k);
                    int r2 = findKthLargest2(v2, k);
                    int r3 = findKthLargest3(v, k);
                    Logger() << "FindKthLargest(" << k << ") = " << r << ", " << r2
                             << ", " << r3 << endl;
                    ASSERT1(r == r2);
                    ASSERT1(r == r3);
                }
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(50, 1);
                vector<int> v = Random::Vector(n, 20);
                check(v);
            }
        });

    Add("367. Valid Perfect Square", [&]()
        {
            auto check = [&](int n)
            {
                bool r = isPerfectSquare(n);
                bool r2 = isPerfectSquare2(n);
                bool r3 = isPerfectSquare3(n);
                int q = sqrt(n);
                bool r4 = (q * q == n);
                Logger() << "isPerfectSquare(" << n << ") = " << r << ", " << r2
                         << ", " << r3 << ", " << r4 << " ~= " << q << "^2" << endl;
                ASSERT1(r == r2);
                ASSERT1(r == r3);
                ASSERT1(r == r4);
            };
            for (int i = 1; i <= 100; i++)
            {
                check(i);
                check(rand());
            }
        });

    Add("Serialize and Deserialize Binary Tree", [&]()
        {
            auto checkTree = [&](TreeNode *t)
            {
                Print(t);
                string d = Codec::serialize(t);
                string d2 = Codec2::serialize(t);
                Logger() << d << endl;
                Logger() << d2 << endl;
                TreeNode *o = Codec::deserialize(d);
                TreeNode *o2 = Codec2::deserialize(d2);
                Print(o);
                Print(o2);
                bool r = isSameTree(t, o);
                bool r2 = isSameTree(t, o2);
                DeleteTree(o);
                DeleteTree(o2);
                DeleteTree(t);
                ASSERT1(r == true);
                ASSERT1(r2 == true);
            };
            auto check = [&](const vector<int> &v)
            {
                Logger() << "Input: " << v;
                TreeNode *t = RandomTree(v);
                checkTree(t);
            };
            {
                TreeNode *n = new TreeNode(1);
                n->left = new TreeNode(2);
                n->right = new TreeNode(3);
                n->right->left = new TreeNode(4);
                n->right->right = new TreeNode(5);
                checkTree(n);
            }
            check({});
            check({1});
            check({1, 2});
            check({1, 2, 3});
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100);
                vector<int> v = Util::IncreasingVector(n);
                check(v);
            }
        });

    Add("Delete Node in a BST", [&]()
        {
            auto check = [&](vector<int> &v)
            {
                Logger() << v;
                TreeNode *t = RandomTreeFromInOrder(v);
                Print(t);
                random_device rd;
                mt19937 g(rd());
                shuffle(v.begin(), v.end(), g);
                for (int i : v)
                {
                    Logger() << "Delete " << i << endl;
                    t = deleteNode(t, i);
                    Print(t);
                }
            };
            for (int i = 0; i < 20; i++)
            {
                vector<int> v = Util::IncreasingVector(i + 1);
                check(v);
            }
        });

    Add("Odd Even Linked List", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                Logger() << v;
                ListNode *l = ToList(v);
                Print(l);
                l = oddEvenList(l);
                Print(l);
                vector<int> w = ToVector(l);
                DeleteList(l);
                ListNode *l2 = ToList(v);
                l2 = oddEvenList2(l2);
                Print(l2);
                vector<int> w2 = ToVector(l2);
                DeleteList(l2);
                ASSERT1(0 == Util::Compare(w, w2));
            };
            for (int i = 0; i < 20; i++)
            {
                vector<int> v = Util::IncreasingVector(i + 1);
                check(v);
            }
        });

    Add("GetNode", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                Logger() << v;
                ListNode *h = ToList(v);
                Print(h);
                vector<int> w;
                vector<int> w2;
                for (int i = 0; i < (int)v.size(); i++)
                {
                    ListNode *n = GetNode(h, i);
                    ListNode *n2 = GetNode2(h, i);
                    w.push_back(n->val);
                    w2.push_back(n2->val);
                }
                ListNode *a = GetNode(h, -1);
                ListNode *a2 = GetNode2(h, -1);
                ListNode *b = GetNode(h, (int)v.size());
                ListNode *b2 = GetNode2(h, (int)v.size());
                DeleteList(h);
                h = nullptr;
                Logger() << w;
                ASSERT1(a == nullptr);
                ASSERT1(a2 == nullptr);
                ASSERT1(b == nullptr);
                ASSERT1(b2 == nullptr);
                ASSERT1(0 == Util::Compare(v, w));
                ASSERT1(0 == Util::Compare(v, w2));
                ASSERT1(nullptr == GetNode(nullptr, 0));
                ASSERT1(nullptr == GetNode2(nullptr, 0));
            };
            for (int i = 0; i < 10; i++)
            {
                int n = Random::Int(100);
                vector<int> v = Random::Vector(n, 100);
                check(v);
            }
        });

    Add("GetMedian", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                int lowerMedian = -1;
                int lowerMedianPrev = -1;
                int higherMedian = -1;
                int higherMedianPrev = -1;
                Logger() << v;
                ListNode *h = ToList(v);
                Print(h);
                ListNode *p = GetLowerMedian(h);
                if (p != nullptr)
                    lowerMedian = p->val;
                p = GetLowerMedianPrev(h);
                if (p != nullptr)
                    lowerMedianPrev = p->val;
                p = GetHigherMedian(h);
                if (p != nullptr)
                    higherMedian = p->val;
                p = GetHigherMedianPrev(h);
                if (p != nullptr)
                    higherMedianPrev = p->val;
                DeleteList(h);
                h = nullptr;
                int n = (int)v.size();
                Logger() << lowerMedianPrev << ", " << lowerMedian << ", " << higherMedianPrev << ", " << higherMedian << ", " << n << endl;
                ASSERT1(lowerMedianPrev == (n >= 3 ? ((n - 1) >> 1) - 1 : -1));
                ASSERT1(lowerMedian == ((n + 1) >> 1) - 1);
                ASSERT1(higherMedianPrev == (n >= 2 ? (n >> 1) - 1 : -1));
                ASSERT1(higherMedian == (n >> 1));
            };
            vector<int> v;
            for (int i = 0; i <= 50; i++)
            {
                v.push_back(i);
                check(v);
            }
        });

    Add("Find Duplicate Subtrees", [&]()
        {
            auto check = [&](TreeNode *t)
            {
                Print(t);
                vector<TreeNode *> d = findDuplicateSubtrees(t);
                vector<TreeNode *> d2 = findDuplicateSubtrees2(t);
                Logger() << d << d2;
                bool sameSize = (d.size() == d2.size());
                bool sameTree = true;
                for (TreeNode *n : d)
                {
                    bool found = false;
                    for (TreeNode *n2 : d2)
                    {
                        if (isSameTree(n, n2))
                        {
                            found = true;
                            break;
                        }
                    }
                    sameTree &= found;
                }
                DeleteTree(t);
                ASSERT1(sameSize);
                ASSERT1(sameTree);
            };
            {
                TreeNode *n1 = new TreeNode(1);
                n1->left = new TreeNode(2);
                n1->left->left = new TreeNode(4);
                n1->right = new TreeNode(3);
                n1->right->left = new TreeNode(2);
                n1->right->left->left = new TreeNode(4);
                n1->right->right = new TreeNode(4);
                check(n1);
            }
        });

    Add("4Sum II", [&]()
        {
            auto check = [&](vector<int> a, vector<int> b, vector<int> c, vector<int> d)
            {
                Logger() << a << b << c << d;
                int n = fourSumCount(a, b, c, d);
                int n2 = fourSumCount2(a, b, c, d);
                int n3 = fourSumCount3(a, b, c, d);
                Logger() << "fourSumCount: " << n << ", " << n2 << ", " << n3 << endl;
                ASSERT1(n == n2);
                ASSERT1(n == n3);
            };
            check({1, 2}, {-2, -1}, {-1, 2}, {0, 2});
            check({-1, -1}, {-1, 1}, {-1, 1}, {1, -1});
        });

    Add("Add and Search Word - Data structure design", [&]()
        {
            {
                WordDictionary2 dict;
                dict.addWord("ran");
                dict.addWord("rune");
                dict.addWord("runner");
                dict.addWord("runs");
                dict.addWord("add");
                dict.addWord("adds");
                dict.addWord("adder");
                dict.addWord("addee");
                ASSERT1(dict.search("r.n") == dict.search2("r.n"));
            }
            {
                WordDictionary2 dict;
                dict.addWord("at");
                dict.addWord("and");
                dict.addWord("an");
                dict.addWord("add");
                ASSERT1(dict.search("a") == dict.search2("a"));
                ASSERT1(dict.search(".at") == dict.search2(".at"));
                dict.addWord("bat");
                ASSERT1(dict.search(".at") == dict.search2(".at"));
                ASSERT1(dict.search("an.") == dict.search2("an."));
                ASSERT1(dict.search("a.d.") == dict.search2("a.d."));
                ASSERT1(dict.search("b.") == dict.search2("b."));
                ASSERT1(dict.search("a.d") == dict.search2("a.d"));
                ASSERT1(dict.search(".") == dict.search2("."));
            }
        });

    Add("Map Sum Pairs", [&]()
        {
            auto check = [&](const map<string, int> &m)
            {
                MapSum ms;
                MapSum2 ms2;
                for (const auto &p : m)
                {
                    ms.insert(p.first, p.second);
                    ms2.insert(p.first, p.second);
                    for (size_t i = 0; i <= p.first.size(); i++)
                    {
                        string t = p.first.substr(0, i);
                        int s = ms.sum(t);
                        int s2 = ms2.sum(t);
                        Logger() << t << ": " << s << ", " << s2 << endl;
                        ASSERT1(s == s2);
                    }
                }
            };
            {
                map<string, int> m = {
                    {"abc", 1},
                    {"ab", 2},
                    {"a", 3},
                };
                check(m);
            }
            {
                map<string, int> m;
                for (int i = 0; i < 100; i++)
                {
                    size_t n = Random::Int(1, 10);
                    string key = Random::String<char>(n, "abcde");
                    m[key] = n;
                    check(m);
                }
            }
        });

    Add("287. Find the Duplicate Number", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                Logger() << v;
                int d = findDuplicate(v);
                Logger() << d;
                vector<int> v2(v);
                int d2 = findDuplicate2(v2);
                Logger() << ", " << d2;
                vector<int> v3(v);
                int d3 = findDuplicate3(v3);
                Logger() << ", " << d3;
                int d4 = findDuplicate4(v);
                Logger() << ", " << d4;
                int d5 = findDuplicate5(v);
                Logger() << ", " << d5 << endl;
                ASSERT1(d == d2);
                ASSERT1(d == d3);
                ASSERT1(d == d4);
                ASSERT1(d == d5);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 2);
                vector<int> v = Util::IncreasingVector(n, 1);
                int d = Random::Int(n, 1);
                v.push_back(d);
                random_device rd;
                mt19937 g(rd());
                shuffle(v.begin(), v.end(), g);
                check(v);
            }
        });

    Add("Daily Temperatures", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                Logger() << v;
                vector<int> o = dailyTemperatures(v);
                Logger() << o;
                vector<int> o2 = dailyTemperatures2(v);
                Logger() << o2;
                ASSERT1(Util::Compare(o, o2) == 0);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 1);
                vector<int> v = Random::Vector(n, 100, 0);
                check(v);
            }
        });

    Add("Skyline Problem", [&]()
        {
            auto check = [&](const vector<vector<int>> &v)
            {
                Logger() << v;
                vector<vector<int>> s = getSkyline(v);
                Logger() << s;
                vector<vector<int>> s2 = getSkyline2(v);
                Logger() << s2;
                ASSERT1(Util::Compare(s, s2) == 0);
            };
            check({{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
        });

    Add("241. Different Ways to Add Parentheses", [&]()
        {
            auto check = [&](const string &s)
            {
                Logger() << s << endl;
                vector<int> r = diffWaysToCompute(s);
                vector<int> r2 = diffWaysToCompute2(s);
                Logger() << r << r2;
                sort(r.begin(), r.end());
                sort(r2.begin(), r2.end());
                ASSERT1(Util::Compare(r, r2) == 0);
            };
            check("2-1-1");
            check("1-2+3*4-5*6-7+8*9");
            check("2*3-4*5");
        });

    Add("264. Ugly Number II", [&]()
        {
            auto check = [&](int n)
            {
                int x = nthUglyNumber(n);
                int y = nthUglyNumber2(n);
                int z = nthUglyNumber3(n);
                Logger() << n << "-th ugly number: " << x << ", " << y << ", " << z << endl;
                ASSERT1(x == z);
            };
            for (int i = 1; i < 21; i++)
                check(i);
        });

    Add("282. Expression Add Operators", [&]()
        {
            auto check = [&](const string &num, int target)
            {
                vector<string> v = addOperators(num, target);
                Logger() << v;
            };
            check("123", 6);
            check("105", 5);
            check("2147483648", -2147483648);
        });

    Add("290. Word Pattern", [&]()
        {
            auto check = [&](const string &pattern, const string &s, bool e)
            {
                bool r = wordPattern(pattern, s);
                ASSERT1(r == e);
            };
            check("abba", "dog cat cat dog", true);
            check("abba", "dog dog dog dog", false);
        });
}
#endif