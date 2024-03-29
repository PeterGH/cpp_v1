#ifndef _LEETCODE2_H_
#define _LEETCODE2_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 200. Number of Islands
        // Given a 2d grid map of '1's (land) and '0's (water), count the number of
        // islands. An island is surrounded by water and is formed by connecting
        // adjacent lands horizontally or vertically. You may assume all four edges of
        // the grid are all surrounded by water. Example 1: Input:
        // 11110
        // 11010
        // 11000
        // 00000
        // Output: 1
        // Example 2: Input:
        // 11000
        // 11000
        // 00100
        // 00011
        // Output: 3
        int numIslands(vector<vector<char>> &grid)
        {
            if (grid.empty() || grid[0].empty())
                return 0;
            int m = grid.size();
            int n = grid[0].size();
            function<void(int, int)> mark = [&](int i, int j)
            {
                if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1')
                    return;
                grid[i][j] = '2';
                mark(i - 1, j);
                mark(i + 1, j);
                mark(i, j - 1);
                mark(i, j + 1);
            };
            int c = 0;
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j] == '1')
                    {
                        c++;
                        mark(i, j);
                    }
                }
            }
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j] == '2')
                        grid[i][j] = '1';
                }
            }
            return c;
        }
        int numIslands2(vector<vector<char>> &grid)
        {
            if (grid.empty() || grid[0].empty())
                return 0;
            function<void(int, int)> visit = [&](int i, int j)
            {
                queue<pair<int, int>> q;
                pair<int, int> p = make_pair(i, j);
                q.push(p);
                while (!q.empty())
                {
                    p = q.front();
                    q.pop();
                    grid[p.first][p.second] = 'x';
                    if (p.first > 0 && grid[p.first - 1][p.second] == '1')
                        q.push(make_pair(p.first - 1, p.second));
                    if (p.second + 1 < (int)grid[p.first].size() && grid[p.first][p.second + 1] == '1')
                        q.push(make_pair(p.first, p.second + 1));
                    if (p.first + 1 < (int)grid.size() && grid[p.first + 1][p.second] == '1')
                        q.push(make_pair(p.first + 1, p.second));
                    if (p.second > 0 && grid[p.first][p.second - 1] == '1')
                        q.push(make_pair(p.first, p.second - 1));
                }
            };
            int c = 0;
            for (int i = 0; i < (int)grid.size(); i++)
            {
                for (int j = 0; j < (int)grid[i].size(); j++)
                {
                    if (grid[i][j] == '1')
                    {
                        c++;
                        visit(i, j);
                    }
                }
            }
            for (int i = 0; i < (int)grid.size(); i++)
            {
                for (int j = 0; j < (int)grid[i].size(); j++)
                {
                    if (grid[i][j] == 'x')
                        grid[i][j] = '1';
                }
            }
            return c;
        }
        int numIslands3(vector<vector<char>> &grid)
        {
            int m = grid.size();
            int n = grid[0].size();
            set<pair<int, int>> visited;
            int c = 0;
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    pair<int, int> p = make_pair(i, j);
                    if (grid[i][j] != '1' || visited.find(p) != visited.end())
                        continue;
                    c++;
                    stack<pair<int, int>> s;
                    while (true)
                    {
                        if (0 <= p.first && p.first < m && 0 <= p.second && p.second < n && grid[p.first][p.second] == '1' && visited.find(p) == visited.end())
                        {
                            visited.insert(p);
                            s.push(p);
                            p.second--;
                        }
                        else
                        {
                            while (!s.empty() && p.first == s.top().first + 1 && p.second == s.top().second)
                            {
                                p = s.top();
                                s.pop();
                            }
                            if (s.empty())
                                break;
                            auto &t = s.top();
                            if (p.first == t.first && p.second + 1 == t.second)
                            {
                                p.first--;
                                p.second++;
                            }
                            else if (p.first + 1 == t.first && p.second == t.second)
                            {
                                p.first++;
                                p.second++;
                            }
                            else if (p.first == t.first && p.second == t.second + 1)
                            {
                                p.first++;
                                p.second--;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
            return c;
        }

        // 201. Bitwise AND of Numbers Range
        // Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND
        // of all numbers in this range, inclusive.
        // Example 1:
        // Input: [5,7]
        // Output: 4
        // Example 2:
        // Input: [0,1]
        // Output: 0
        int rangeBitwiseAnd(int m, int n)
        {
            int b = 0x40000000;
            int r = 0;
            while (b > 0)
            {
                if ((b & n) == 0)
                {
                    // n < b
                    // r & b == 0
                    b = b >> 1;
                    continue;
                }
                // b <= n
                if (b <= m)
                {
                    // b <= m <= n
                    // r & b == 1
                    r |= b;
                    m -= b;
                    n -= b;
                    b = b >> 1;
                }
                else
                {
                    // m < b <= n
                    // 1. r & b == 0, and
                    // 2. bitwiseAND range [m,n] must be 0 because lower bits of b are zeros
                    break;
                }
            }
            return r;
        }
        int rangeBitwiseAnd2(int m, int n)
        {
            // m = 0xC0X
            // n = 0xC1Y
            // where C are common bits same between m and n,
            // X and Y are lower bits.
            // bitwiseAND range [m,n] must be 0xC because
            // 1. the bit after 0xC is 0 or 1 in the range
            // 2. the range must contain 0xC10, where bits after 0xC1 are all zeros
            int x = 0;
            while (m != n)
            {
                m >>= 1;
                n >>= 1;
                x++;
            }
            return m << x;
        }
        int rangeBitwiseAnd3(int m, int n)
        {
            int r = m;
            for (int i = m + 1; i <= n; i++)
                r &= i;
            return r;
        }

        // 202. Happy Number
        // Write an algorithm to determine if a number is "happy". A happy number is a
        // number defined by the following process: Starting with any positive integer,
        // replace the number by the sum of the squares of its digits, and repeat the
        // process until the number equals 1 (where it will stay), or it loops endlessly
        // in a cycle which does not include 1. Those numbers for which this process
        // ends in 1 are happy numbers. Example: Input: 19 Output: true Explanation: 12
        // + 92 = 82 82 + 22 = 68 62 + 82 = 100 12 + 02 + 02 = 1
        bool isHappy(int n)
        {
            if (n <= 0)
                return false;
            set<int> s;
            while (n != 1 && s.find(n) == s.end())
            {
                // if (!s.empty())
                //     cout << ", ";
                // cout << n;
                s.insert(n);
                int t = 0;
                while (n > 0)
                {
                    int d = n % 10;
                    n /= 10;
                    t += d * d;
                }
                n = t;
            }
            // cout << (s.empty() ? "" : ", ") << n << endl;
            return n == 1;
        }
        // This is wrong. The input n may not be in the cycle, e.g.,
        // 2, 4, 16, 37, 58, 89, 145, 42, 20, 4
        bool isHappy2(int n)
        {
            int x = n;
            cout << n;
            do
            {
                int y = 0;
                while (x > 0)
                {
                    int r = x % 10;
                    y += (r * r);
                    x /= 10;
                }
                x = y;
                cout << ", " << x;
            } while (x != n && x != 1);
            cout << endl;
            return x == 1;
        }

        // 203. Remove Linked List Elements
        // Remove all elements from a linked list of integers that have value val.
        // Example:
        // Input:  1->2->6->3->4->5->6, val = 6
        // Output: 1->2->3->4->5
        ListNode *removeElements(ListNode *head, int val)
        {
            ListNode *p;
            while (head != nullptr && head->val == val)
            {
                p = head->next;
                delete head;
                head = p;
            }
            if (head == nullptr)
                return head;
            p = head;
            while (p->next != nullptr)
            {
                if (p->next->val == val)
                {
                    ListNode *t = p->next;
                    p->next = t->next;
                    delete t;
                }
                else
                {
                    p = p->next;
                }
            }
            return head;
        }
        ListNode *removeElements2(ListNode *head, int val)
        {
            ListNode *p = nullptr;
            ListNode *q = head;
            while (q != nullptr)
            {
                if (q->val == val)
                {
                    if (p == nullptr)
                    {
                        head = q->next;
                        q->next = nullptr;
                        delete q;
                        q = head;
                    }
                    else
                    {
                        p->next = q->next;
                        q->next = nullptr;
                        delete q;
                        q = p->next;
                    }
                }
                else
                {
                    p = q;
                    q = p->next;
                }
            }
            return head;
        }

        // 204. Count Primes
        // Count the number of prime numbers less than a non-negative number, n.
        // Example:
        // Input: 10
        // Output: 4
        // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
        int countPrimes(int n)
        {
            if (n <= 2)
                return 0;
            vector<int> v;
            v.push_back(2);
            for (int i = 3; i < n; i++)
            {
                bool isPrime = true;
                for (size_t j = 0; (j < v.size()) && (v[j] * v[j] <= i); j++)
                {
                    if ((i % v[j]) == 0)
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                    v.push_back(i);
            }
            return (int)v.size();
        }
        int countPrimes2(int n)
        {
            if (n <= 2)
                return 0;
            const int NumBitsInt = sizeof(int) * 8;
            const int NumInts = (n / NumBitsInt) + 1;
            unique_ptr<int[]> bits(new int[NumInts]);
            memset(bits.get(), 0, NumInts * sizeof(int));
            function<void(int, int)> setbit = [&](int i, int b)
            {
                int j = i / NumBitsInt;
                int k = i % NumBitsInt;
                if (b == 1)
                    bits[j] |= (0x1 << k);
                else if (b == 0)
                    bits[j] &= ~(0x1 << k);
            };
            function<int(int)> getbit = [&](int i) -> int
            {
                int j = i / NumBitsInt;
                int k = i % NumBitsInt;
                return (bits[j] & (0x1 << k)) >> k;
            };
            int c = 0;
            for (int i = 2; i < n; i++)
            {
                if (getbit(i) == 0)
                {
                    c++;
                    for (int j = i + i; j < n; j += i)
                        setbit(j, 1);
                }
            }
            return c;
        }

        // 205. Isomorphic Strings
        // Given two strings s and t, determine if they are isomorphic. Two strings are
        // isomorphic if the characters in s can be replaced to get t. All occurrences
        // of a character must be replaced with another character while preserving the
        // order of characters. No two characters may map to the same character but a
        // character may map to itself. Example 1: Input: s = "egg", t = "add" Output:
        // true Example 2: Input: s = "foo", t = "bar" Output: false Example 3: Input: s
        // = "paper", t = "title" Output: true Note: You may assume both s and t have
        // the same length.
        bool isIsomorphic(const string &s, const string &t)
        {
            if (s.size() != t.size())
                return false;
            map<char, char> st;
            map<char, char> ts;
            for (size_t i = 0; i < s.size(); i++)
            {
                if ((st.find(s[i]) != st.end() && ts.find(t[i]) == ts.end()) ||
                    (st.find(s[i]) == st.end() && ts.find(t[i]) != ts.end()))
                    return false;
                if (st.find(s[i]) == st.end())
                {
                    st[s[i]] = t[i];
                    ts[t[i]] = s[i];
                }
                else if (st[s[i]] != t[i])
                    return false;
            }
            return true;
        }
        bool isIsomorphic2(const string &s, const string &t)
        {
            if (s.size() != s.size())
                return false;
            map<char, char> ms;
            map<char, char> mt;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (ms.find(s[i]) == ms.end())
                    ms[s[i]] = t[i];
                else if (ms[s[i]] != t[i])
                    return false;
                if (mt.find(t[i]) == mt.end())
                    mt[t[i]] = s[i];
                else if (mt[t[i]] != s[i])
                    return false;
            }
            return true;
        }
        // This is wrong. Cannot use one map for both s and t, because
        // characters in s and t are in different domain.
        // e.g., "paper" and "title" and the mapping indicates:
        // "e" -> "l"
        // "r" -> "e"
        bool isIsomorphic3(const string &s, const string &t)
        {
            if (s.size() != t.size())
                return false;
            map<char, char> m;
            for (size_t i = 0; i < s.size(); i++)
            {
                // if (i > 0)
                //     cout << ", ";
                // cout << "(" << i << ", " << s[i] << ", " << t[i] << ")" << std::endl;
                if ((m.find(s[i]) == m.end() && m.find(t[i]) != m.end()) || (m.find(s[i]) != m.end() && m.find(t[i]) == m.end()))
                {
                    // cout << "only one of s[i] and t[i] in map" << std::endl;
                    return false;
                }
                if (m.find(s[i]) == m.end())
                {
                    m[s[i]] = t[i];
                    m[t[i]] = s[i];
                }
                else
                {
                    if (m[s[i]] != t[i])
                    {
                        // cout << "m[s[i]] != t[i]" << std::endl;
                        return false;
                    }
                    if (m[t[i]] != s[i])
                    {
                        // cout << "m[t[i]] != s[i]" << std::endl;
                        return false;
                    }
                }
                // cout << "m = {" << std::endl;
                // for (auto it : m)
                // {
                //     cout << "  " << it.first << ": " << it.second << std::endl;
                // }
                // cout << "}" << std::endl;
            }
            return true;
        }

        // 206. Reverse Linked List
        // Reverse a singly linked list.
        // Example:
        // Input: 1->2->3->4->5->NULL
        // Output: 5->4->3->2->1->NULL
        // Follow up: A linked list can be reversed either iteratively or recursively.
        // Could you implement both?
        ListNode *reverseList(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return head;
            ListNode *p = nullptr;
            ListNode *m = head;
            while (m != nullptr)
            {
                ListNode *n = m->next;
                m->next = p;
                p = m;
                m = n;
            }
            return p;
        }
        ListNode *reverseList2(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *t = head;
            while (t->next != nullptr)
            {
                ListNode *n = t->next;
                t->next = n->next;
                n->next = head;
                head = n;
            }
            return head;
        }
        ListNode *reverseList3(ListNode *head)
        {
            function<ListNode *(ListNode *)> reverse = [&](ListNode *t) -> ListNode *
            {
                if (t == nullptr || t->next == nullptr)
                    return t;
                ListNode *h = reverse(t->next);
                t->next->next = t;
                t->next = nullptr;
                return h;
            };
            return reverse(head);
        }
        ListNode *reverseList4(ListNode *head)
        {
            function<void(ListNode *, ListNode **, ListNode **)> reverse =
                [&](ListNode *node, ListNode **h, ListNode **t)
            {
                if (node == nullptr || node->next == nullptr)
                {
                    *h = node;
                    *t = node;
                    return;
                }
                reverse(node->next, h, t);
                (*t)->next = node;
                node->next = nullptr;
                *t = node;
            };
            ListNode *tail = nullptr;
            reverse(head, &head, &tail);
            return head;
        }

        // 207. Course Schedule
        // There are a total of n courses you have to take, labeled from 0 to n-1.
        // Some courses may have prerequisites, for example to take course 0 you have
        // to first take course 1, which is expressed as a pair: [0,1]. Given the
        // total number of courses and a list of prerequisite pairs, is it possible
        // for you to finish all courses?
        // Example 1:
        // Input: 2, [[1,0]]
        // Output: true
        // Explanation: There are a total of 2 courses to take. To take course 1 you
        // should have finished course 0. So it is possible.
        // Example 2:
        // Input: 2, [[1,0],[0,1]]
        // Output: false
        // Explanation: There are a total of 2 courses to take. To take course 1 you
        // should have finished course 0, and to take course 0 you should also have
        // finished course 1. So it is impossible.
        // Note: The input prerequisites is a graph represented by a list of edges,
        // not adjacency matrices. Read more about how a graph is represented.
        // You may assume that there are no duplicate edges in the input prerequisites.
        bool canFinish(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e)
                     {
                         if (g.find(e[1]) == g.end())
                             g[e[1]] = vector<int>(1, e[0]);
                         else
                             g[e[1]].push_back(e[0]);
                     });
            set<int> trees;
            function<bool(int, set<int> &)> hasCircle = [&](int i, set<int> &visited) -> bool
            {
                if (g.find(i) == g.end())
                    return false;
                if (trees.find(i) != trees.end())
                    return false;
                visited.insert(i);
                for (size_t j = 0; j < g[i].size(); j++)
                {
                    if (visited.find(g[i][j]) != visited.end())
                        return true;
                    if (hasCircle(g[i][j], visited))
                        return true;
                }
                visited.erase(i);
                trees.insert(i);
                return false;
            };
            for (auto it = g.begin(); it != g.end(); it++)
            {
                set<int> v;
                if (hasCircle(it->first, v))
                    return false;
            }
            return true;
        }
        bool canFinish2(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, int> indegree;
            map<int, vector<int>> graph;
            for (int i = 0; i < numCourses; i++)
            {
                indegree[i] = 0;
            }
            for (const auto &e : prerequisites)
            {
                indegree[e[0]]++;
                if (graph.find(e[1]) == graph.end())
                {
                    graph[e[1]] = vector<int>{};
                }
                graph[e[1]].push_back(e[0]);
            }
            queue<int> q;
            size_t c = 0;
            // start with nodes whose indegree is 0
            for (int i = 0; i < numCourses; i++)
            {
                if (indegree[i] == 0)
                {
                    q.push(i);
                }
            }
            while (!q.empty())
            {
                int t = q.front();
                q.pop();
                c++;
                for (int n : graph[t])
                {
                    // reduce indegree of the neighbor
                    // add it to the queue if the result is 0
                    indegree[n]--;
                    if (indegree[n] == 0)
                    {
                        q.push(n);
                    }
                }
            }
            // If there is a cycle, the node where the cycle begins will not
            // be added to the queue becaue its indegree will never be reduced
            // to 0.
            return c == graph.size();
        }
        // This BFS is wrong, e.g., for inputs 3 and [[0,1],[0,2],[1,2]]
        //    0
        //   ^ ^
        //  /   \
        // 1 <-- 2
        bool canFinish3(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e)
                     {
                         if (g.find(e[1]) == g.end())
                             g[e[1]] = vector<int>(1, e[0]);
                         else
                             g[e[1]].push_back(e[0]);
                     });
            for (auto it = g.begin(); it != g.end(); it++)
            {
                cout << "Tree at " << it->first << std::endl;
                set<int> visited;
                queue<int> q;
                q.push(it->first);
                visited.insert(it->first);
                while (!q.empty())
                {
                    int t = q.front();
                    q.pop();
                    cout << "  " << t << std::endl;
                    if (g.find(t) == g.end())
                        continue;
                    for (size_t i = 0; i < g[t].size(); i++)
                    {
                        if (i > 0)
                            cout << ", ";
                        cout << g[t][i];
                        if (visited.find(g[t][i]) != visited.end())
                            return false;
                        q.push(g[t][i]);
                        visited.insert(g[t][i]);
                    }
                    cout << std::endl;
                }
            }
            return true;
        }

        // 208. Implement Trie (Prefix Tree)
        // Implement a trie with insert, search, and startsWith methods.
        // Example:
        // Trie trie = new Trie();
        // trie.insert("apple");
        // trie.search("apple");   // returns true
        // trie.search("app");     // returns false
        // trie.startsWith("app"); // returns true
        // trie.insert("app");
        // trie.search("app");     // returns true
        // Note: You may assume that all inputs are consist of lowercase letters a-z.
        // All inputs are guaranteed to be non-empty strings.
        // Your Trie object will be instantiated and called as such:
        // Trie* obj = new Trie();
        // obj->insert(word);
        // bool param_2 = obj->search(word);
        // bool param_3 = obj->startsWith(prefix);
        class Trie
        {
        private:
            class Node
            {
            public:
                vector<Node *> children;
                string val;
                bool complete;
                Node(const string &w, bool c) : val(w), complete(c) {}
                Node() : Node(string(), true) {}
                // Try to match word[i..] partially or entirely
                bool Match(const string &word, size_t i, size_t &j)
                {
                    j = 0; // matched characters count
                    for (j = 0; j < val.size() && i < word.size(); j++, i++)
                    {
                        if (word[i] != val[j])
                            break;
                    }
                    return j > 0;
                }
            };

            Node *root;

            void Delete(Node *node)
            {
                if (node == nullptr)
                    return;
                for_each(node->children.begin(), node->children.end(),
                         [&](Node *n)
                         { Delete(n); });
                node->children.clear();
            }

            // Return the deepest node matching the word partially or entirely
            // Case 1: Return the root
            //   word is empty
            //   word not match any of the children of the root
            // Case 2: Return a non-root node
            //   word matches the node entirely (i == word.size(), j is the length of
            //   the node->val) word matches the node partially (j < the length of the
            //   node->val, i <= word.size())
            Node *Search(const string &word, size_t &i, size_t &j)
            {
                i = 0; // count the prefix characters of word that are matched
                j = 0; // count the characters of the node that are matched
                if (word.empty())
                    return root;
                Node *node = root;
                bool stop = false;
                while (i < word.size() && !stop)
                {
                    stop = true;
                    for (size_t k = 0; k < node->children.size(); k++)
                    {
                        size_t l = 0;
                        if (node->children[k]->Match(word, i, l))
                        {
                            j = l;
                            i += j;
                            node = node->children[k];
                            stop = (j < node->val.size());
                            break;
                        }
                    }
                }
                return node;
            }

        public:
            Trie() { root = new Node(); }

            ~Trie()
            {
                Delete(root);
                root = nullptr;
            }

            void insert(string word)
            {
                if (word.empty())
                    return;
                size_t i = 0;
                size_t j = 0;
                Node *node = Search(word, i, j);
                if (j < node->val.size())
                {
                    // split between val[0..(j-1)] and val[j..]
                    Node *c = new Node(node->val.substr(j), node->complete);
                    c->children.insert(c->children.end(), node->children.begin(),
                                       node->children.end());
                    node->val.resize(j);
                    node->children.clear();
                    node->children.push_back(c);
                    node->complete = (i == word.size());
                }
                if (i == word.size())
                {
                    if (!node->complete)
                        node->complete = true;
                }
                else
                {
                    Node *c = new Node(word.substr(i), true);
                    node->children.push_back(c);
                }
            }

            bool search(string word)
            {
                if (word.empty())
                    return true;
                size_t i = 0;
                size_t j = 0;
                Node *node = Search(word, i, j);
                return i == word.size() && j == node->val.size() && node->complete;
            }

            // Returns if there is any word in the trie that starts with the given
            // prefix.
            bool startsWith(string prefix)
            {
                if (prefix.empty())
                    return true;
                size_t i = 0;
                size_t j = 0;
                Search(prefix, i, j);
                return i == prefix.size();
            }
        };
        class Trie2
        {
        private:
            struct Node
            {
                vector<Node *> children;
                char val;
                bool complete;

                Node(char v, bool c) : val(v), complete(c) {}

                Node() : Node((char)0, true) {}
            };

            Node *root;

            void Delete(Node *node)
            {
                if (node == nullptr)
                    return;
                for_each(node->children.begin(), node->children.end(),
                         [&](Node *n)
                         { Delete(n); });
                node->children.clear();
            }

            Node *Search(const string &word, size_t &i)
            {
                i = 0;
                if (word.empty())
                    return root;
                Node *node = root;
                bool stop = false;
                while (i < word.size() && !stop)
                {
                    stop = true;
                    for (size_t k = 0; k < node->children.size(); k++)
                    {
                        if (word[i] == node->children[k]->val)
                        {
                            i++;
                            node = node->children[k];
                            stop = false;
                            break;
                        }
                    }
                }
                return node;
            }

        public:
            Trie2() { root = new Node(); }

            ~Trie2()
            {
                Delete(root);
                root = nullptr;
            }

            void insert(string word)
            {
                if (word.empty())
                    return;
                size_t i = 0;
                Node *node = Search(word, i);
                while (i < word.size())
                {
                    Node *c = new Node(word[i], false);
                    node->children.push_back(c);
                    node = c;
                    i++;
                }
                node->complete = true;
            }

            bool search(string word)
            {
                if (word.empty())
                    return true;
                size_t i = 0;
                Node *node = Search(word, i);
                return i == word.size() && node->complete;
            }

            // Returns if there is any word in the trie that starts with the given
            // prefix.
            bool startsWith(string prefix)
            {
                if (prefix.empty())
                    return true;
                size_t i = 0;
                Search(prefix, i);
                return i == prefix.size();
            }
        };
        class Trie3
        {
        private:
            struct Node
            {
                char val;
                map<char, Node *> children;
                bool complete;
                Node(char v)
                {
                    val = v;
                    complete = false;
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = children.begin(); it != children.end(); it++)
                        delete it->second;
                    children.clear();
                }
            } * root;

        public:
            /** Initialize your data structure here. */
            Trie3()
                : root(new Node('\0'))
            {
            }

            ~Trie3()
            {
                delete root;
                root = nullptr;
            }

            /** Inserts a word into the trie. */
            void insert(string word)
            {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->children.find(word[i]) == node->children.end())
                        break;
                    node = node->children[word[i++]];
                }
                while (i < word.size())
                {
                    node->children[word[i]] = new Node(word[i]);
                    node = node->children[word[i++]];
                }
                node->complete = true;
            }

            /** Returns if the word is in the trie. */
            bool search(string word)
            {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->children.find(word[i]) == node->children.end())
                        return false;
                    node = node->children[word[i++]];
                }
                return node->complete;
            }

            /** Returns if there is any word in the trie that starts with the given prefix. */
            bool startsWith(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                while (i < prefix.size())
                {
                    if (node->children.find(prefix[i]) == node->children.end())
                        return false;
                    node = node->children[prefix[i++]];
                }
                return true;
            }
        };

        // Map Sum Pairs
        // Implement a MapSum class with insert, and sum methods.
        // For the method insert, you'll be given a pair of (string, integer).
        // The string represents the key and the integer represents the value.
        // If the key already existed, then the original key-value pair will
        // be overridden to the new one. For the method sum, you'll be given a
        // string representing the prefix, and you need to return the sum of all
        // the pairs' value whose key starts with the prefix.
        // Example 1:
        // Input: insert("apple", 3), Output: Null
        // Input: sum("ap"), Output: 3
        // Input: insert("app", 2), Output: Null
        // Input: sum("ap"), Output: 5
        class MapSum
        {
        private:
            struct Node
            {
                char key;
                int val;
                bool complete;
                map<char, Node *> next;
                Node(char k, int v, bool c)
                    : key(k), val(v), complete(c)
                {
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;
            void search(string key, Node *&node, size_t &i)
            {
                while (i < key.size())
                {
                    if (node->next.find(key[i]) == node->next.end())
                        break;
                    node = node->next[key[i++]];
                }
            }

        public:
            MapSum()
                : root(new Node('\0', 0, true))
            {
            }
            ~MapSum()
            {
                delete root;
                root = nullptr;
            }
            void insert(string key, int val)
            {
                Node *node = root;
                size_t i = 0;
                search(key, node, i);
                while (i < key.size())
                {
                    node->next[key[i]] = new Node(key[i], 0, false);
                    node = node->next[key[i++]];
                }
                node->val = val;
                node->complete = true;
            }
            int sum(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                search(prefix, node, i);
                if (i < prefix.size())
                    return 0;
                stack<Node *> s;
                int a = 0;
                s.push(node);
                while (!s.empty())
                {
                    node = s.top();
                    s.pop();
                    if (node->complete)
                        a += node->val;
                    for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        s.push(it->second);
                }
                return a;
            }
        };
        class MapSum2
        {
        private:
            struct Node
            {
                char key;
                int val;
                bool complete;
                map<char, Node *> next;
                Node(char k, int v, bool c)
                    : key(k), val(v), complete(c)
                {
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;
            void search(const string &key, int val, Node *&node, size_t &i, bool insert)
            {
                while (i < key.size())
                {
                    if (insert)
                        node->val += val;
                    if (node->next.find(key[i]) == node->next.end())
                        return;
                    node = node->next[key[i++]];
                }
                if (insert)
                    node->val += val;
            }

        public:
            MapSum2()
                : root(new Node('\0', 0, true))
            {
            }
            ~MapSum2()
            {
                delete root;
                root = nullptr;
            }
            void insert(const string &key, int val)
            {
                Node *node = root;
                size_t i = 0;
                search(key, val, node, i, true);
                while (i < key.size())
                {
                    node->next[key[i]] = new Node(key[i], val, false);
                    node = node->next[key[i++]];
                }
                node->complete = true;
            }
            int sum(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                search(prefix, 0, node, i, false);
                if (i < prefix.size())
                    return 0;
                return node->val;
            }
        };

        // Replace Words
        // In English, we have a concept called root, which can be followed by some
        // other words to form another longer word - let's call this word successor.
        // For example, the root an, followed by other, which can form another word another.
        // Now, given a dictionary consisting of many roots and a sentence. You need
        // to replace all the successor in the sentence with the root forming it. If
        // a successor has many roots can form it, replace it with the root with the
        // shortest length. You need to output the sentence after the replacement.
        // Example 1:
        // Input: dict = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
        // Output: "the cat was rat by the bat"
        // Constraints:
        // The input will only have lower-case letters.
        // 1 <= dict.length <= 1000
        // 1 <= dict[i].length <= 100
        // 1 <= sentence words number <= 1000
        // 1 <= sentence words length <= 1000
        string replaceWords(const vector<string> &dict, string sentence)
        {
            struct Node
            {
                char val;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } *root = new Node('\0', true);
            function<void(const string &)> insert = [&](const string &word)
            {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->next.find(word[i]) == node->next.end())
                        break;
                    node = node->next[word[i++]];
                }
                while (i < word.size())
                {
                    node->next[word[i]] = new Node(word[i], false);
                    node = node->next[word[i++]];
                }
                node->complete = true;
            };
            function<size_t(size_t)> match = [&](size_t i) -> size_t
            {
                Node *node = root;
                size_t j = i;
                while (j < sentence.size())
                {
                    if (node->next.find(sentence[j]) == node->next.end())
                        break;
                    node = node->next[sentence[j++]];
                    if (node->complete)
                        break;
                }
                return node->complete ? j : i;
            };
            for (const string &r : dict)
                insert(r);
            size_t i = 0;
            size_t j = 0;
            while (j < sentence.size())
            {
                if (sentence[j] == ' ')
                {
                    if (i++ < j++)
                        sentence[i - 1] = sentence[j - 1];
                }
                else
                {
                    size_t k = match(j);
                    if (j < k)
                    {
                        if (i < j)
                        {
                            while (j < k)
                                sentence[i++] = sentence[j++];
                        }
                        else
                        {
                            j = k;
                            i = j;
                        }
                        while (j < sentence.size() && sentence[j] != ' ')
                            j++;
                    }
                    else
                    {
                        while (j < sentence.size() && sentence[j] != ' ')
                        {
                            if (i++ < j++)
                                sentence[i - 1] = sentence[j - 1];
                        }
                    }
                }
            }
            delete root;
            return sentence.substr(0, i);
        }

        // 209. Minimum Size Subarray Sum
        // Given an array of n positive integers and a positive integer s, find the
        // minimal length of a contiguous subarray of which the sum >= s. If there
        // isn't one, return 0 instead.
        // Example:
        // Input: s = 7, nums = [2,3,1,2,4,3]
        // Output: 2
        // Explanation: the subarray [4,3] has the minimal length under the problem
        // constraint. Follow up: If you have figured out the O(n) solution, try coding
        // another solution of which the time complexity is O(n log n).
        int minSubArrayLen(int s, const vector<int> &nums)
        {
            int a = 0;
            size_t i = 0;
            int m = 0;
            for (size_t j = 0; j < nums.size(); j++)
            {
                a += nums[j];
                while (a >= s)
                {
                    m = min((m == 0 ? nums.size() : m), j - i + 1);
                    a -= nums[i];
                    i++;
                }
            }
            return m;
        }
        int minSubArrayLen2(int s, const vector<int> &nums)
        {
            int l = 0;
            int c = 0;
            int i = 0;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                c += nums[j];
                while (c >= s)
                {
                    l = (l == 0 ? j - i + 1 : min(l, j - i + 1));
                    c -= nums[i++];
                }
            }
            return l;
        }

        // 210. Course Schedule II
        // There are a total of n courses you have to take, labeled from 0 to n-1. Some
        // courses may have prerequisites, for example to take course 0 you have to
        // first take course 1, which is expressed as a pair: [0,1]. Given the total
        // number of courses and a list of prerequisite pairs, return the ordering of
        // courses you should take to finish all courses. There may be multiple correct
        // orders, you just need to return one of them. If it is impossible to finish
        // all courses, return an empty array. Example 1: Input: 2, [[1,0]] Output:
        // [0,1] Explanation: There are a total of 2 courses to take. To take course 1
        // you should have finished course 0. So the correct course order is [0,1] .
        // Example 2:
        // Input: 4, [[1,0],[2,0],[3,1],[3,2]]
        // Output: [0,1,2,3] or [0,2,1,3]
        // Explanation: There are a total of 4 courses to take. To take course 3 you
        // should have finished both courses 1 and 2. Both courses 1 and 2 should be
        // taken after you finished course 0. So one correct course order is [0,1,2,3].
        // Another correct ordering is [0,2,1,3] . Note: The input prerequisites is a
        // graph represented by a list of edges, not adjacency matrices. Read more about
        // how a graph is represented. You may assume that there are no duplicate edges
        // in the input prerequisites.
        // DFS Topological Sort
        vector<int> findOrder(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e)
                     {
                         if (g.find(e[0]) == g.end())
                             g[e[0]] = vector<int>();
                         g[e[0]].push_back(e[1]);
                     });
            vector<pair<int, int>> rankNodeVector;
            set<int> visited;
            set<int> path;
            bool solvable = true;
            int rank = 0;
            function<bool(int)> solve = [&](int i) -> bool
            {
                if (visited.find(i) != visited.end())
                    return true;
                if (g.find(i) != g.end())
                {
                    path.insert(i);
                    for (size_t j = 0; j < g[i].size(); j++)
                    {
                        if (path.find(g[i][j]) != path.end())
                        {
                            solvable = false;
                            return false;
                        }
                        solve(g[i][j]);
                    }
                    path.erase(i);
                }
                visited.insert(i);
                rankNodeVector.push_back(make_pair(rank++, i));
                return true;
            };
            for (int i = 0; i < numCourses && solvable; i++)
                solve(i);
            vector<int> result;
            if (solvable)
            {
                // sort(rankNodeVector.begin(), rankNodeVector.end());
                for_each(rankNodeVector.cbegin(), rankNodeVector.cend(),
                         [&](const pair<int, int> &p)
                         { result.push_back(p.second); });
            }
            return result;
        }
        // BFS Topological Sort using indegree counting
        vector<int> findOrder2(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            vector<int> indegree(numCourses, 0);
            for (const auto &e : prerequisites)
            {
                if (g.find(e[1]) == g.end())
                    g[e[1]] = vector<int>();
                g[e[1]].push_back(e[0]);
                indegree[e[0]]++;
            }
            queue<int> q;
            for (int i = 0; i < numCourses; i++)
            {
                if (indegree[i] == 0)
                {
                    q.push(i);
                }
            }
            vector<int> output;
            int c = 0;
            while (!q.empty())
            {
                int t = q.front();
                q.pop();
                output.push_back(t);
                c++;
                for (int n : g[t])
                {
                    indegree[n]--;
                    if (indegree[n] == 0)
                    {
                        q.push(n);
                    }
                }
            }
            if (c < numCourses)
                output.clear();
            return output;
        }
        // BFS Topological Sort using ancestor tracking, not efficient
        vector<int> findOrder3(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for (const auto &e : prerequisites)
            {
                if (g.find(e[1]) == g.end())
                    g[e[1]] = vector<int>();
                g[e[1]].push_back(e[0]);
            }
            vector<int> output;
            vector<int> rank(numCourses, 0);
            bool solvable = true;
            for (int i = 0; i < numCourses && solvable; i++)
            {
                queue<int> q;
                map<int, set<int>> ancestors;
                q.push(i);
                ancestors[i] = set<int>();
                while (!q.empty() && solvable)
                {
                    int t = q.front();
                    q.pop();
                    for (int j : g[t])
                    {
                        if (ancestors[t].find(j) != ancestors[t].end())
                        {
                            solvable = false;
                            break;
                        }
                        rank[j] = max(rank[j], rank[t] + 1);
                        if (ancestors.find(j) == ancestors.end())
                            ancestors[j] = set<int>();
                        ancestors[j].insert(ancestors[t].begin(), ancestors[t].end());
                        ancestors[j].insert(t);
                        q.push(j);
                    }
                }
            }
            if (solvable)
            {
                int j = 0;
                output.resize(numCourses, 0);
                generate(output.begin(), output.end(), [&]()
                         { return j++; });
                sort(output.begin(), output.end(), [&](int x, int y) -> bool
                     { return rank[x] < rank[y]; });
            }
            return output;
        }

        // 211. Add and Search Word - Data structure design
        // Design a data structure that supports the following two operations:
        // void addWord(word)
        // bool search(word)
        // search(word) can search a literal word or a regular expression string
        // containing only letters a-z or .. A . means it can represent any one letter.
        // Example:
        // addWord("bad")
        // addWord("dad")
        // addWord("mad")
        // search("pad") -> false
        // search("bad") -> true
        // search(".ad") -> true
        // search("b..") -> true
        // Note: You may assume that all words are consist of lowercase letters a-z.
        // Your WordDictionary object will be instantiated and called as such:
        // WordDictionary* obj = new WordDictionary();
        // obj->addWord(word);
        // bool param_2 = obj->search(word);
        class WordDictionary
        {
        private:
            struct Node
            {
                char val;
                vector<Node *> children;
                bool valid;
                Node(char v, bool b) : val(v), valid(b) {}
                Node() : Node(0, true) {}
            };
            Node *root;
            void Delete(Node *n)
            {
                if (n != nullptr)
                {
                    for_each(n->children.begin(), n->children.end(),
                             [&](Node *c)
                             { Delete(c); });
                    n->children.clear();
                }
            }

        public:
            WordDictionary() { root = new Node(); }
            ~WordDictionary()
            {
                Delete(root);
                root = nullptr;
            }
            void addWord(const string &word)
            {
                size_t i = 0;
                function<Node *(Node *, size_t &)>
                    match = [&](Node *node, size_t &i) -> Node *
                {
                    if (i == word.size())
                        return node;
                    for (size_t j = 0; j < node->children.size(); j++)
                    {
                        Node *c = node->children[j];
                        if (c->val == word[i])
                        {
                            i++;
                            return match(c, i);
                        }
                    }
                    return node;
                };
                Node *node = match(root, i);
                for (; i < word.size(); i++)
                {
                    Node *c = new Node(word[i], i + 1 == word.size());
                    node->children.push_back(c);
                    node = c;
                }
            }
            bool search(const string &word)
            {
                function<bool(Node *, size_t)>
                    match = [&](Node *node, size_t i) -> bool
                {
                    if (i == word.size())
                        return node->valid;
                    for (size_t j = 0; j < node->children.size(); j++)
                    {
                        Node *c = node->children[j];
                        if (word[i] == '.' || word[i] == c->val)
                        {
                            if (match(c, i + 1))
                                return true;
                        }
                    }
                    return false;
                };
                return match(root, 0);
            }
        };
        class WordDictionary2
        {
        private:
            struct Node
            {
                char val;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;

        public:
            WordDictionary2()
            {
                root = new Node('\0', true);
            }

            ~WordDictionary2()
            {
                if (root != nullptr)
                    delete root;
            }

            void Print()
            {
                function<void(int, Node *)> print = [&](int i, Node *node)
                {
                    cout << string(i, ' ') << node->val << (node->complete ? "/" : " ") << endl;
                    for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        print(i + 2, it->second);
                };
                print(0, root);
            }

            void addWord(const string &word)
            {
                // cout << "addWord(" << word << ")" << endl;
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->next.find(word[i]) == node->next.end())
                        break;
                    node = node->next[word[i++]];
                }
                while (i < word.size())
                {
                    node->next[word[i]] = new Node(word[i], false);
                    node = node->next[word[i++]];
                }
                node->complete = true;
                // Print();
            }

            bool search(const string &word)
            {
                function<bool(Node *, size_t)> find = [&](Node *node, size_t i) -> bool
                {
                    if (i >= word.size())
                        return node->complete;
                    if (node->next.find(word[i]) == node->next.end())
                    {
                        if (word[i] != '.')
                            return false;
                        for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        {
                            if (find(it->second, i + 1))
                                return true;
                        }
                    }
                    else if (find(node->next[word[i]], i + 1))
                    {
                        return true;
                    }
                    return false;
                };
                bool f = find(root, 0);
                // cout << "search(" << word << ") = " << f << endl;
                return f;
            }

            bool search2(const string &word)
            {
                stack<pair<Node *, size_t>> s;
                s.push(make_pair(root, 0));
                bool found = false;
                while (!s.empty())
                {
                    pair<Node *, size_t> t = s.top();
                    s.pop();
                    Node *node = t.first;
                    size_t i = t.second;
                    // cout << "<'" << node->val << "', " << i << ">" << endl;
                    if (i == word.size())
                    {
                        found = node->complete;
                        if (found)
                            break;
                        else
                            continue;
                    }
                    if (node->next.empty())
                        continue;
                    if (node->next.find(word[i]) == node->next.end())
                    {
                        if (word[i] != '.')
                            continue;
                        for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        {
                            s.push(make_pair(it->second, i + 1));
                        }
                    }
                    else
                    {
                        s.push(make_pair(node->next[word[i]], i + 1));
                    }
                }
                // cout << "search2(" << word << ") = " << found << endl;
                return found;
            }
        };

        // 212. Word Search II
        // Given a 2D board and a list of words from the dictionary, find all words in
        // the board. Each word must be constructed from letters of sequentially
        // adjacent cell, where "adjacent" cells are those horizontally or vertically
        // neighboring. The same letter cell may not be used more than once in a word.
        // Example:
        // Input:
        // board = [
        //   ['o','a','a','n'],
        //   ['e','t','a','e'],
        //   ['i','h','k','r'],
        //   ['i','f','l','v']
        // ]
        // words = ["oath","pea","eat","rain"]
        // Output: ["eat","oath"]
        // Note: All inputs are consist of lowercase letters a-z. The values of words
        // are distinct.
        vector<string> findWords(const vector<vector<char>> &board,
                                 const vector<string> &words)
        {
            vector<string> result;
            if (board.empty() || board[0].empty())
                return result;
            int m = board.size();
            int n = board[0].size();
            set<pair<int, int>> path;
            function<bool(int, int, const string &, int)> find =
                [&](int i, int j, const string &word, size_t k) -> bool
            {
                if (k == word.size())
                    return true;
                if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k])
                    return false;
                pair<int, int> p = make_pair(i, j);
                if (path.find(p) != path.end())
                    return false;
                path.insert(p);
                bool found = find(i - 1, j, word, k + 1) ||
                             find(i + 1, j, word, k + 1) ||
                             find(i, j - 1, word, k + 1) || find(i, j + 1, word, k + 1);
                path.erase(p);
                return found;
            };
            for_each(words.cbegin(), words.cend(), [&](const string &w)
                     {
                         bool found = false;
                         for (int i = 0; i < m && !found; i++)
                         {
                             for (int j = 0; j < n && !found; j++)
                             {
                                 if (find(i, j, w, 0))
                                     found = true;
                             }
                         }
                         if (found)
                             result.push_back(w); });
            return result;
        }
        vector<string> findWords2(const vector<vector<char>> &board, const vector<string> &words)
        {
            struct Node
            {
                char val;
                int index;
                map<char, Node *> next;
                Node(char v, int i = -1) : val(v), index(i) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> root(new Node('\0'));
            function<void(int)> add = [&](int i)
            {
                const string &w = words[i];
                Node *node = root.get();
                size_t j = 0;
                while (j < w.size() && node->next.find(w[j]) != node->next.end())
                    node = node->next[w[j++]];
                while (j < w.size())
                {
                    node->next[w[j]] = new Node(w[j]);
                    node = node->next[w[j++]];
                }
                node->index = i;
            };
            for (int i = 0; i < (int)words.size(); i++)
                add(i);
            set<string> found; // use set because a word may appear more than once in the board
            function<void(int, int, Node *, set<pair<int, int>> &)> find =
                [&](int i, int j, Node *node, set<pair<int, int>> &visited)
            {
                if (i < 0 || i >= (int)board.size() || j < 0 || j >= (int)board[i].size() || node == nullptr)
                    return;
                if (node->next.find(board[i][j]) == node->next.end())
                    return;
                pair<int, int> p = make_pair(i, j);
                if (visited.find(p) != visited.end())
                    return;
                node = node->next[board[i][j]];
                if (node->index >= 0)
                    found.insert(words[node->index]);
                visited.insert(p);
                find(i - 1, j, node, visited);
                find(i, j + 1, node, visited);
                find(i + 1, j, node, visited);
                find(i, j - 1, node, visited);
                visited.erase(p);
            };
            set<pair<int, int>> visited;
            for (int i = 0; i < (int)board.size(); i++)
            {
                for (int j = 0; j < (int)board[i].size(); j++)
                {
                    find(i, j, root.get(), visited);
                }
            }
            vector<string> result(found.cbegin(), found.cend());
            return result;
        }

        // 213. House Robber II
        // You are a professional robber planning to rob houses along a street. Each
        // house has a certain amount of money stashed. All houses at this place are
        // arranged in a circle. That means the first house is the neighbor of the last
        // one. Meanwhile, adjacent houses have security system connected and it will
        // automatically contact the police if two adjacent houses were broken into on
        // the same night. Given a list of non-negative integers representing the amount
        // of money of each house, determine the maximum amount of money you can rob
        // tonight without alerting the police.
        // Example 1:
        // Input: [2,3,2]
        // Output: 3
        // Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money =
        // 2), because they are adjacent houses. Example 2: Input: [1,2,3,1] Output: 4
        // Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
        // Total amount you can rob = 1 + 3 = 4.
        int robII(const vector<int> &nums)
        {
            int a1 = 0;
            int b1 = 0;
            int a2 = 0;
            int b2 = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (i == 0)
                    b1 = nums[i]; // track when starting at house 1
                if (i == 1)
                    b2 = nums[i]; // track when starting at house 2
                if (i > 0 && i + 1 < nums.size())
                { // ignore the last house
                    int c1 = max(a1 + nums[i], b1);
                    a1 = b1;
                    b1 = c1;
                }
                if (i > 1)
                {
                    int c2 = max(a2 + nums[i], b2);
                    a2 = b2;
                    b2 = c2;
                }
            }
            return max(b1, b2);
        }

        // 214. Shortest Palindrome
        // Given a string s, you are allowed to convert it to a palindrome by adding
        // characters in front of it. Find and return the shortest palindrome you can
        // find by performing this transformation.
        // Example 1:
        // Input: "aacecaaa"
        // Output: "aaacecaaa"
        // Example 2:
        // Input: "abcd"
        // Output: "dcbabcd"
        string shortestPalindrome(const string &s)
        {
            string r(s);
            reverse(r.begin(), r.end());
            // Find the prefix of s which is also a suffix of r
            // s[0]...s[c-1]s[c]...#...s[c]s[c-1]...s[0]
            // s[0]...s[c-1] is a palindrome if it matches s[c-1]...s[0]
            string w = s + "#" + r;
            // Using KMP
            vector<int> p(w.size(), 0);
            int c = 0; // prefix length is 0 at w[0]
            for (int i = 1; i < (int)w.size(); i++)
            {
                // prefix of w[0..(i-1)] is w[0..(c-1)]
                // check w[c] and w[i]
                while (c > 0 && w[c] != w[i])
                    c = p[c - 1];
                if (w[c] == w[i])
                    c++;
                p[i] = c;
            }
            int n = p[w.size() - 1];
            string t = s.substr(n);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome2(const string &s)
        {
            if (s.empty())
                return s;
            string r(s);
            reverse(r.begin(), r.end());
            string w = s + r; // eliminate the extra '#'
            vector<int> p(w.size(), 0);
            int c = 0;
            for (int i = 1; i < (int)w.size(); i++)
            {
                // Need an extra check if c exceeds the length of s
                while (c > 0 && (w[c] != w[i] || c >= (int)s.size()))
                    c = p[c - 1];
                if (w[c] == w[i])
                    c++;
                p[i] = c;
            }
            int n = p[w.size() - 1];
            string t = s.substr(n);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome3(const string &s)
        {
            if (s.empty())
                return s;
            int n = s.size();
            int m = n << 1; // eliminate the extra string w
            vector<int> p(m, 0);
            int c = 0;
            for (int i = 1; i < m; i++)
            {
                // map w[i] back to s[j]
                int j = i < n ? i : m - i - 1;
                while (c > 0 && (s[c] != s[j] || c >= n))
                    c = p[c - 1];
                if (s[c] == s[j])
                    c++;
                p[i] = c;
            }
            string t = s.substr(p[m - 1]);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome4(const string &s)
        {
            int i = (int)s.size() - 1;
            while (i >= 0)
            {
                int j = 0;
                int k = i;
                while (j <= k)
                {
                    if (s[j] != s[k])
                        break;
                    j++;
                    k--;
                }
                if (j > k)
                {
                    // s[0..i] is a palindrome
                    break;
                }
                else
                {
                    i--;
                }
            }
            string t = s.substr(i + 1);
            reverse(t.begin(), t.end());
            return t + s;
        }

        // 215. Kth Largest Element in an Array
        // Find the kth largest element in an unsorted array. Note that it is the kth
        // largest element in the sorted order, not the kth distinct element.
        // Example 1:
        // Input: [3,2,1,5,6,4] and k = 2
        // Output: 5
        // Example 2:
        // Input: [3,2,3,1,2,4,5,5,6] and k = 4
        // Output: 4
        // Note: You may assume k is always valid, 1 <= k <= array's length.
        int findKthLargest(vector<int> &nums, int k)
        {
            int b = 0;
            int e = (int)nums.size() - 1;
            while (b <= e)
            {
                int i = b;
                int j = e - 1;
                while (i <= j)
                {
                    if (nums[i] < nums[e])
                    {
                        swap(nums[i], nums[j]);
                        j--;
                    }
                    else
                    {
                        i++;
                    }
                }
                // i > j and nums[i] < nums[e]
                swap(nums[i], nums[e]);
                if (i - b + 1 < k)
                {
                    k -= (i - b + 1);
                    b = i + 1;
                }
                else if (i - b + 1 > k)
                {
                    e = i - 1;
                }
                else
                {
                    return nums[i];
                }
            }
            return nums[b];
        }
        int findKthLargest2(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end(), [&](int a, int b) -> bool
                 { return a > b; });
            return nums[k - 1];
        }
        int findKthLargest3(const vector<int> &nums, int k)
        {
            priority_queue<int> q;
            for (int n : nums)
                q.push(n);
            for (int i = 0; i < k - 1; i++)
                q.pop();
            return q.top();
        }

        // 216. Combination Sum III
        // Find all possible combinations of k numbers that add up to a number n, given
        // that only numbers from 1 to 9 can be used and each combination should be a
        // unique set of numbers. Note: All numbers will be positive integers. The
        // solution set must not contain duplicate combinations.
        // Example 1:
        // Input: k = 3, n = 7
        // Output: [[1,2,4]]
        // Example 2:
        // Input: k = 3, n = 9
        // Output: [[1,2,6], [1,3,5], [2,3,4]]
        vector<vector<int>> combinationSum3(int k, int n)
        {
            vector<vector<int>> result;
            vector<int> s;
            function<void(int, int, int)> solve = [&](int i, int c, int t)
            {
                if (c == 0 && t == 0)
                {
                    result.push_back(s);
                    return;
                }
                for (int j = i; j <= 9 && j <= t; j++)
                {
                    s.push_back(j);
                    solve(j + 1, c - 1, t - j);
                    s.pop_back();
                }
            };
            solve(1, k, n);
            return result;
        }
        vector<vector<int>> combinationSum32(int k, int n)
        {
            vector<pair<vector<int>, int>> s;
            vector<vector<int>> output;
            s.push_back(make_pair(vector<int>(), 0));
            for (int i = 1; i <= 9; i++)
            {
                int l = s.size();
                for (int j = 0; j < l; j++)
                {
                    auto p = s[j];
                    p.first.push_back(i);
                    p.second += i;
                    if ((int)p.first.size() == k && p.second == n)
                        output.push_back(p.first);
                    if ((int)p.first.size() < k)
                        s.push_back(p);
                }
            }
            return output;
        }

        // 217. Contains Duplicate
        // Given an array of integers, find if the array contains any duplicates.
        // Your function should return true if any value appears at least twice
        // in the array, and it should return false if every element is distinct.
        // Example 1:
        // Input: [1,2,3,1]
        // Output: true
        // Example 2:
        // Input: [1,2,3,4]
        // Output: false
        // Example 3:
        // Input: [1,1,1,3,3,4,3,2,4,2]
        // Output: true
        bool containsDuplicate(const vector<int> &nums)
        {
            set<int> s;
            for (int n : nums)
            {
                if (s.find(n) != s.end())
                    return true;
                s.insert(n);
            }
            return false;
        }

        // 218. The Skyline Problem
        // A city's skyline is the outer contour of the silhouette formed by all the
        // buildings in that city when viewed from a distance. Now suppose you are
        // given the locations and height of all the buildings as shown on a cityscape
        // photo (Figure A), write a program to output the skyline formed by these
        // buildings collectively (Figure B). The geometric information of each building
        // is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the
        // x coordinates of the left and right edge of the ith building, respectively,
        // and Hi is its height. It is guaranteed that 0 <= Li, Ri <= INT_MAX, 0 < Hi <= INT_MAX,
        // and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded
        // on an absolutely flat surface at height 0. For instance, the dimensions of
        // all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12],
        // [15 20 10], [19 24 8] ]. The output is a list of "key points" (red dots in
        // Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely
        // defines a skyline. A key point is the left endpoint of a horizontal line
        // segment. Note that the last key point, where the rightmost building ends,
        // is merely used to mark the termination of the skyline, and always has zero
        // height. Also, the ground in between any two adjacent buildings should be
        // considered part of the skyline contour. For instance, the skyline in Figure
        // B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].
        // Notes: he number of buildings in any input list is guaranteed to be in the
        // range [0, 10000]. The input list is already sorted in ascending order by the
        // left x position Li. The output list must be sorted by the x position. There
        // must be no consecutive horizontal lines of equal height in the output skyline.
        // For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
        // the three lines of height 5 should be merged into one in the final output as
        // such: [...[2 3], [4 5], [12 7], ...]
        vector<vector<int>> getSkyline(const vector<vector<int>> &buildings)
        {
            // First compute up boundaries
            vector<vector<int>> up;
            vector<vector<int>> begins(buildings); // already sorted by up boundaries
            vector<vector<int>>::iterator it = begins.begin();
            while (it != begins.end())
            {
                // For all the ranges with the same up boundary,
                // compute the max height at the boundary.
                int b = it->operator[](0);
                int h = it->operator[](2);
                while (it + 1 != begins.end() && (it + 1)->operator[](0) == b)
                {
                    ++it;
                    h = max(h, it->operator[](2));
                }
                // Current up boundary is valid if it is higher than all the previous heights
                bool valid = true;
                it = begins.begin();
                while (it != begins.end() && it->operator[](0) <= b)
                {
                    if (it->operator[](1) < b)
                    {
                        // The range is not covering b
                        it = begins.erase(it);
                    }
                    else
                    {
                        // The range cover b
                        if (it->operator[](2) > h || (it->operator[](0) < b && it->operator[](2) == h))
                        {
                            // Current up boundary not valid since a previous range
                            // is higher
                            valid = false;
                        }
                        ++it;
                    }
                }
                if (valid)
                {
                    up.push_back({b, h});
                }
            }
            // Compute the down boundaries
            vector<vector<int>> down;
            vector<vector<int>> ends(buildings);
            // Sort down boundaries in reverse order so that we can apply similar logic
            // of computing up boundaries
            sort(ends.begin(), ends.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 {
                     if (x[1] > y[1])
                         return true;
                     if (x[1] == y[1] && x[0] > y[0])
                         return true;
                     if (x[1] == y[1] && x[0] == y[0] && x[2] > y[2])
                         return true;
                     return false; });
            it = ends.begin();
            while (it != ends.end())
            {
                // For all the ranges with the same down boundary,
                // compute the max height at the down boundary.
                int e = it->operator[](1);
                int h = it->operator[](2);
                while ((it + 1) != ends.end() && (it + 1)->operator[](1) == e)
                {
                    ++it;
                    h = max(h, it->operator[](2));
                }
                // Compute the max height among all the ranges before e
                it = ends.begin();
                int m = 0;
                while (it != ends.end() && it->operator[](1) >= e)
                {
                    if (it->operator[](0) > e)
                    {
                        // The range is not covering e
                        it = ends.erase(it);
                    }
                    else
                    {
                        // The range cover e
                        if (it->operator[](1) > e)
                            m = max(m, it->operator[](2));
                        ++it;
                    }
                }
                if (m < h)
                {
                    down.insert(down.begin(), {e, m});
                }
            }
            vector<vector<int>> skyline;
            size_t i = 0;
            size_t j = 0;
            while (i < up.size() || j < down.size())
            {
                if (i < up.size() && j < down.size())
                {
                    if (up[i][0] < down[j][0])
                    {
                        skyline.push_back(up[i++]);
                    }
                    else // must be up[i][0] > down[j][0] because a boundary cannot be both up and down
                    {
                        skyline.push_back(down[j++]);
                    }
                }
                else if (i < up.size())
                {
                    skyline.push_back(up[i++]);
                }
                else
                {
                    skyline.push_back(down[j++]);
                }
            }
            return skyline;
        }
        vector<vector<int>> getSkyline2(const vector<vector<int>> &buildings)
        {
            function<vector<vector<int>>(const vector<vector<int>> &, const vector<vector<int>> &)>
                merge = [&](const vector<vector<int>> &a, const vector<vector<int>> &b) -> vector<vector<int>>
            {
                if (a.empty())
                    return b;
                if (b.empty())
                    return a;
                vector<vector<int>> c;
                int ha = 0;
                int hb = 0;
                size_t i = 0;
                size_t j = 0;
                int h;
                while (i < a.size() || j < b.size())
                {
                    if (i < a.size() && j < b.size())
                    {
                        if (a[i][0] < b[j][0])
                        {
                            h = max(a[i][1], hb);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{a[i][0], h});
                            ha = a[i++][1];
                        }
                        else if (a[i][0] > b[j][0])
                        {
                            h = max(ha, b[j][1]);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{b[j][0], h});
                            hb = b[j++][1];
                        }
                        else
                        {
                            h = max(a[i][1], b[j][1]);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{a[i][0], h});
                            ha = a[i++][1];
                            hb = b[j++][1];
                        }
                    }
                    else if (i < a.size())
                    {
                        c.push_back(a[i++]);
                    }
                    else
                    {
                        c.push_back(b[j++]);
                    }
                };
                return c;
            };
            function<vector<vector<int>>(int, int)> solve =
                [&](int b, int e) -> vector<vector<int>>
            {
                if (b > e)
                    return {};
                if (b == e)
                    return vector<vector<int>>{
                        {buildings[b][0], buildings[b][2]},
                        {buildings[b][1], 0}};
                int m = b + ((e - b) >> 1);
                vector<vector<int>> v1 = solve(b, m);
                vector<vector<int>> v2 = solve(m + 1, e);
                vector<vector<int>> v = merge(v1, v2);
                return v;
            };
            return solve(0, (int)buildings.size() - 1);
        }

        // 219. Contains Duplicate II
        // Given an array of integers and an integer k, find out whether there are two
        // distinct indices i and j in the array such that nums[i] = nums[j] and the
        // absolute difference between i and j is at most k.
        // Example 1:
        // Input: nums = [1,2,3,1], k = 3
        // Output: true
        // Example 2:
        // Input: nums = [1,0,1,1], k = 1
        // Output: true
        // Example 3:
        // Input: nums = [1,2,3,1,2,3], k = 2
        // Output: false
        bool containsNearbyDuplicate(const vector<int> &nums, int k)
        {
            set<int> s;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (s.find(nums[i]) == s.end())
                    s.insert(nums[i]);
                else
                    return true;
                if (i >= k)
                    s.erase(nums[i - k]);
            }
            return false;
        }

        // 220. Contains Duplicate III
        // Given an array of integers, find out whether there are two distinct indices i
        // and j in the array such that the absolute difference between nums[i] and nums[j]
        // is at most t and the absolute difference between i and j is at most k.
        // Example 1:
        // Input: nums = [1,2,3,1], k = 3, t = 0
        // Output: true
        // Example 2:
        // Input: nums = [1,0,1,1], k = 1, t = 2
        // Output: true
        // Example 3:
        // Input: nums = [1,5,9,1,5,9], k = 2, t = 3
        // Output: false
        // Hint #1
        // Time complexity O(n logk) - This will give an indication that sorting is involved
        // for k elements.
        // Hide Hint #2
        // Use already existing state to evaluate next state - Like, a set of k sorted
        // numbers are only needed to be tracked. When we are processing the next number
        // in array, then we can utilize the existing sorted state and it is not necessary
        // to sort next overlapping set of k numbers again.
        class ContainsDuplicateIII
        {
        private:
            struct Node
            {
                int val;
                set<int> indices;
                Node *left;
                Node *right;
                Node(int v, int i)
                    : val(v), indices({i}), left(nullptr), right(nullptr)
                {
                }
            };

            Node *root;

            bool insert(int v, int i, int k, int t)
            {
                bool result = false;
                Node *parent = nullptr;
                Node *node = root;
                while (node != nullptr)
                {
                    parent = node;
                    if (abs((long long)node->val - (long long)v) <= (long long)t)
                    {
                        for (int j : node->indices)
                        {
                            if (abs(i - j) <= k)
                            {
                                result = true;
                                break;
                            }
                        }
                    }
                    if (node->val > v)
                    {
                        node = node->left;
                    }
                    else if (node->val < v)
                    {
                        node = node->right;
                    }
                    else
                    {
                        node->indices.insert(i);
                        return result;
                    }
                }
                node = new Node(v, i);
                if (parent == nullptr)
                    root = node;
                else if (parent->val > v)
                    parent->left = node;
                else
                    parent->right = node;
                return result;
            }

            void deleteNode(int v, int i)
            {
                Node *parent = nullptr;
                Node *node = root;
                while (node != nullptr && node->val != v)
                {
                    parent = node;
                    if (node->val > v)
                        node = node->left;
                    else
                        node = node->right;
                }
                if (node == nullptr)
                    return;
                node->indices.erase(i);
                if (!node->indices.empty())
                    return;
                if (node->right == nullptr)
                {
                    if (parent == nullptr)
                        root = node->left;
                    else if (parent->left == node)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                    node->left = nullptr;
                    delete node;
                    node = nullptr;
                    return;
                }
                Node *nextParent = node;
                Node *next = node->right;
                while (next->left != nullptr)
                {
                    nextParent = next;
                    next = next->left;
                }
                if (nextParent->right == next)
                    nextParent->right = next->right;
                else
                    nextParent->left = next->right;
                next->left = node->left;
                next->right = node->right;
                if (parent == nullptr)
                    root = next;
                else if (parent->left == node)
                    parent->left = next;
                else
                    parent->right = next;
                node->left = nullptr;
                node->right = nullptr;
                delete node;
                node = nullptr;
            }

            void deleteTree(Node *node)
            {
                if (node == nullptr)
                    return;
                deleteTree(node->left);
                node->left = nullptr;
                deleteTree(node->right);
                node->right = nullptr;
                delete node;
            }

        public:
            bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
            {
                bool result = false;
                root = nullptr;
                for (int i = 0; i < (int)nums.size(); i++)
                {
                    if (i > k)
                        deleteNode(nums[i - k - 1], i - k - 1);
                    if (insert(nums[i], i, k, t))
                    {
                        result = true;
                        break;
                    }
                }
                deleteTree(root);
                return result;
            }

            bool containsNearbyAlmostDuplicate2(vector<int> &nums, int k, int t)
            {
                map<int, int> m;
                for (int i = 0; i < (int)nums.size(); i++)
                {
                    if (m.find(nums[i]) == m.end())
                        m[nums[i]] = 1;
                    else
                        m[nums[i]]++;
                    if (i > k)
                    {
                        if (m[nums[i - k - 1]] == 1)
                            m.erase(nums[i - k - 1]);
                        else
                            m[nums[i - k - 1]]--;
                    }
                    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
                    {
                        if (it->second > 1 && t >= 0)
                            return true; // there are two identical numbers whose difference is zero
                        map<int, int>::iterator it2 = it;
                        it2++;
                        if (it2 == m.end())
                            break;
                        // No need to increase it2 if difference between *it and *it2 is greater than t
                        // because all numbers after it2 will be greater than t for sure since
                        // map is an ordered structure.
                        if ((long long)it2->first - (long long)it->first <= (long long)t)
                            return true;
                    }
                }
                return false;
            }
        };

        // 221. Maximal Square
        // Given an m x n binary matrix filled with 0's and 1's, find the largest square
        // containing only 1's and return its area.
        // Example 1:
        // Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
        // Output: 4
        // Example 2:
        // Input: matrix = [["0","1"],["1","0"]]
        // Output: 1
        // Example 3:
        // Input: matrix = [["0"]]
        // Output: 0
        // Constraints:
        // m == matrix.length
        // n == matrix[i].length
        // 1 <= m, n <= 300
        // matrix[i][j] is '0' or '1'.
        int maximalSquare(vector<vector<char>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            int m = 0;
            vector<int> c(matrix[0].size(), 0); // Height of 1s at current row
            for (size_t j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[0][j] == '1')
                {
                    c[j] = 1;
                    m = 1;
                }
                else
                {
                    c[j] = 0;
                }
            }
            for (int i = 1; i < (int)matrix.size(); i++)
            {
                vector<pair<int, int>> v;
                int x = 0;
                int h = 0;
                if (matrix[i][0] == '0')
                {
                    c[0] = 0;
                }
                else
                {
                    c[0]++;
                    x = 0;
                    h = c[0];
                    v.push_back(make_pair(x, h));
                    m = max(m, 1);
                }
                for (int j = 1; j < (int)matrix[i].size(); j++)
                {
                    if (matrix[i][j] == '0')
                    {
                        c[j] = 0;
                        v.clear();
                    }
                    else
                    {
                        c[j]++;
                        x = j;
                        h = c[j];
                        while (!v.empty() && v.back().second >= h)
                        {
                            x = v.back().first;
                            v.pop_back();
                        }
                        v.push_back(make_pair(x, h));
                        for (const auto &p : v)
                        {
                            int n = min(j - p.first + 1, p.second);
                            m = max(m, n * n);
                        }
                    }
                }
            }
            return m;
        }
        // Let s[i][j] be the side length of the maximum square whose bottom right corner is matrix[i][j]
        // For every 1 found in the original matrix, we update the value of the current element as
        // s[i][j] = min(s[i-1][j], s[i-1][j-1], s[i][j-1]) + 1
        int maximalSquare2(const vector<vector<char>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            int m = 0;
            vector<int> s(matrix[0].size(), 0);
            for (int j = 0; j < (int)matrix[0].size(); j++)
            {
                s[j] = (matrix[0][j] == '1' ? 1 : 0);
                m = max(m, s[j]);
            }
            for (int i = 1; i < (int)matrix.size(); i++)
            {
                int left = (matrix[i][0] == '1' ? 1 : 0);
                int j;
                for (j = 1; j < (int)matrix[i].size(); j++)
                {
                    int current = (matrix[i][j] == '1' ? min(left, min(s[j - 1], s[j])) + 1 : 0);
                    s[j - 1] = left;
                    m = max(m, s[j - 1]);
                    left = current;
                }
                s[j - 1] = left;
                m = max(m, s[j - 1]);
            }
            return m * m;
        }

        // 222. Count Complete Tree Nodes
        // Given the root of a complete binary tree, return the number of the nodes in the tree.
        // According to Wikipedia, every level, except possibly the last, is completely filled in
        // a complete binary tree, and all nodes in the last level are as far left as possible.
        // It can have between 1 and 2^h nodes inclusive at the last level h.
        // Example 1:
        //    1
        //  2   3
        // 4 5 6
        // Input: root = [1,2,3,4,5,6]
        // Output: 6
        // Example 2:
        // Input: root = []
        // Output: 0
        // Example 3:
        // Input: root = [1]
        // Output: 1
        // Constraints:
        // The number of nodes in the tree is in the range [0, 5 * 104].
        // 0 <= Node.val <= 5 * 104
        // The tree is guaranteed to be complete.
        // Follow up: Traversing the tree to count the number of nodes in the tree is an easy
        // solution but with O(n) complexity. Could you find a faster algorithm?
        int countNodes(TreeNode *root)
        {
            int c = 0;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int h = 0;
            int lastLevelHeight = -1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (n->left != nullptr && lastLevelHeight == -1)
                    {
                        // n is not at the last level
                        c += (1 << h);
                    }
                    s.push(make_pair(n, h));
                    n = n->left;
                    h++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    if (p.first->right == nullptr)
                    {
                        if (lastLevelHeight == -1)
                        {
                            lastLevelHeight = p.second;
                            c++;
                        }
                        else if (p.second == lastLevelHeight)
                        {
                            c++;
                        }
                        else
                        {
                            // at lastLevelHeight - 1
                            break;
                        }
                    }
                    else
                    {
                        n = p.first->right;
                        h = p.second + 1;
                    }
                }
            }
            return c;
        }
        int countNodes2(TreeNode *root)
        {
            int c = 0;
            stack<TreeNode *> s;
            TreeNode *n = root;
            int h = 0;
            int lastLevelHeight = -1;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (n->left != nullptr && lastLevelHeight == -1)
                    {
                        c += (1 << h);
                    }
                    s.push(n);
                    n = n->left;
                    h++;
                }
                else
                {
                    TreeNode *p = s.top();
                    h--;
                    if (p->right == nullptr)
                    {
                        if (lastLevelHeight == -1)
                        {
                            lastLevelHeight = h;
                            c++;
                        }
                        else if (h == lastLevelHeight)
                        {
                            c++;
                        }
                        else
                        {
                            // at lastLevelHeight - 1
                            break;
                        }
                        s.pop();
                    }
                    else if (p->right == last)
                    {
                        s.pop();
                    }
                    else
                    {
                        n = p->right;
                        h++;
                    }
                    last = p;
                }
            }
            return c;
        }
        int countNodes3(TreeNode *root)
        {
            function<int(TreeNode *)> count = [&](TreeNode *n) -> int
            {
                if (n == nullptr)
                    return 0;
                return 1 + count(n->left) + count(n->right);
            };
            return count(root);
        }
        // Encode left edge 0 and right edge 1
        //        ( )
        //      0     1
        //    0   1 0   1
        // and represent the indices of the leaf nodes at the last level as
        // 0, 1, 2, 3, ......, (2^h - 1)
        // then the path to a leaf node has the bits of the index of the leaf node.
        int countNodes4(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            int lh = 0;
            TreeNode *n = root;
            while (n != nullptr)
            {
                lh++;
                n = n->left;
            }
            int rh = 0;
            n = root;
            while (n != nullptr)
            {
                rh++;
                n = n->right;
            }
            // at root rh is 1
            // current total count is 2^rh - 1
            int c = (1 << rh) - 1;
            if (lh > rh)
            {
                // need to count the last level
                int b = 0;
                int e = (1 << (lh - 1)) - 1;
                while (b <= e)
                {
                    int m = b + ((e - b) >> 1);
                    int x = (0x1 << (lh - 2));
                    n = root;
                    while (x > 0)
                    {
                        if (m & x)
                        {
                            n = n->right;
                        }
                        else
                        {
                            n = n->left;
                        }
                        x >>= 1;
                    }
                    if (n != nullptr)
                    {
                        if (m == e)
                        {
                            c += m + 1;
                            break;
                        }
                        b = m + 1;
                    }
                    else
                    {
                        if (b == m)
                        {
                            c += m;
                            break;
                        }
                        e = m - 1;
                    }
                }
            }
            return c;
        }

        // 223. Rectangle Area
        // Find the total area covered by two rectilinear rectangles in a 2D plane.
        // Each rectangle is defined by its bottom left corner and top right corner
        // as shown in the figure.
        // Rectangle Area
        // Example:
        // Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
        // Output: 45
        // Note:
        // Assume that the total area is never beyond the maximum possible value of int.
        int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
        {
            long long lA = A;
            long long lB = B;
            long long lC = C;
            long long lD = D;
            long long lE = E;
            long long lF = F;
            long long lG = G;
            long long lH = H;
            long long a = (lC - lA) * (lD - lB) + (lG - lE) * (lH - lF);
            if (lA < lG && lE < lC && lB < lH && lF < lD)
            {
                // minus overlapping area
                long long b = (min(lC, lG) - max(lA, lE)) * (min(lH, lD) - max(lF, lB));
                a -= b;
            }
            return a;
        }

        // 224. Basic Calculator
        // Given a string s representing an expression, implement a basic calculator to evaluate it.
        // Example 1:
        // Input: s = "1 + 1"
        // Output: 2
        // Example 2:
        // Input: s = " 2-1 + 2 "
        // Output: 3
        // Example 3:
        // Input: s = "(1+(4+5+2)-3)+(6+8)"
        // Output: 23
        // Constraints:
        // 1 <= s.length <= 3 * 105
        // s consists of digits, '+', '-', '(', ')', and ' '.
        // s represents a valid expression.
        int calculate(string s)
        {
            stack<pair<char, long long>> e;
            long long a = 0;
            function<long long(long long)> op = [&](long long v) -> int
            {
                if (!e.empty() && e.top().first != '(')
                {
                    char o = e.top().first;
                    e.pop();
                    long long t = 0;
                    if (!e.empty())
                    {
                        t = e.top().second;
                        e.pop();
                    }
                    if (o == '+')
                    {
                        v = t + v;
                    }
                    else
                    {
                        v = t - v;
                    }
                }
                return v;
            };
            for (const char &c : s)
            {
                if ('0' <= c && c <= '9')
                {
                    a = 10 * a + c - '0';
                }
                else if (c == '(')
                {
                    e.push(make_pair(c, 0));
                }
                else if (c == '+' || c == '-' || c == ')')
                {
                    a = op(a);
                    if (c == ')')
                    {
                        e.pop(); // pop '('
                    }
                    else
                    {
                        e.push(make_pair('0', a));
                        e.push(make_pair(c, 0));
                        a = 0; // reset to start scanning next number
                    }
                }
            }
            a = op(a);
            return a;
        }
        int calculate2(string s)
        {
            stack<pair<char, long long>> e;
            long long a = 0;
            function<long long(long long)> op = [&](long long v) -> int
            {
                if (!e.empty() && e.top().first != '(')
                {
                    char o = e.top().first;
                    long long t = e.top().second;
                    e.pop();
                    if (o == '+')
                    {
                        v = t + v;
                    }
                    else
                    {
                        v = t - v;
                    }
                }
                return v;
            };
            for (const char &c : s)
            {
                if ('0' <= c && c <= '9')
                {
                    a = 10 * a + c - '0';
                }
                else if (c == '(')
                {
                    e.push(make_pair(c, 0));
                }
                else if (c == '+' || c == '-' || c == ')')
                {
                    a = op(a);
                    if (c == ')')
                    {
                        e.pop();
                    }
                    else
                    {
                        e.push(make_pair(c, a));
                        a = 0;
                    }
                }
            }
            a = op(a);
            return a;
        }

        // 225. Implement Stack using Queues
        // Implement the following operations of a stack using queues.
        // push(x) -- Push element x onto stack.
        // pop() -- Removes the element on top of the stack.
        // top() -- Get the top element.
        // empty() -- Return whether the stack is empty.
        // Example:
        // MyStack stack = new MyStack();
        // stack.push(1);
        // stack.push(2);
        // stack.top();   // returns 2
        // stack.pop();   // returns 2
        // stack.empty(); // returns false
        class MyStack
        {
        private:
            queue<int> q0;
            queue<int> q1;
            void flush(queue<int> &from, queue<int> &to)
            {
                while (from.size() > 1)
                {
                    to.push(from.front());
                    from.pop();
                }
            }

        public:
            /** Initialize your data structure here. */
            MyStack()
            {
            }

            /** Push element x onto stack. */
            void push(int x)
            {
                if (q1.empty())
                    q0.push(x);
                else
                    q1.push(x);
            }

            /** Removes the element on top of the stack and returns that element. */
            int pop()
            {
                int v;
                if (q1.empty())
                {
                    flush(q0, q1);
                    v = q0.front();
                    q0.pop();
                }
                else
                {
                    flush(q1, q0);
                    v = q1.front();
                    q1.pop();
                }
                return v;
            }

            /** Get the top element. */
            int top()
            {
                int v;
                if (q1.empty())
                {
                    flush(q0, q1);
                    v = q0.front();
                    q1.push(v);
                    q0.pop();
                }
                else
                {
                    flush(q1, q0);
                    v = q1.front();
                    q0.push(v);
                    q1.pop();
                }
                return v;
            }

            /** Returns whether the stack is empty. */
            bool empty()
            {
                return q0.empty() && q1.empty();
            }
        };

        // 226. Invert Binary Tree
        // Invert a binary tree.
        // Example:
        // Input:
        //      4
        //    /   \
        //   2     7
        //  / \   / \
        // 1   3 6   9
        // Output:
        //      4
        //    /   \
        //   7     2
        //  / \   / \
        // 9   6 3   1
        // Trivia:
        // This problem was inspired by this original tweet by Max Howell:
        // Google: 90% of our engineers use the software you wrote (Homebrew),
        // but you can’t invert a binary tree on a whiteboard so f*** off.
        TreeNode *invertTree(TreeNode *root)
        {
            function<void(TreeNode *)> invert = [&](TreeNode *node)
            {
                if (node == nullptr)
                    return;
                invert(node->left);
                invert(node->right);
                swap(node->left, node->right);
            };
            invert(root);
            return root;
        }
        TreeNode *invertTree2(TreeNode *root)
        {
            stack<TreeNode *> s;
            TreeNode *last = nullptr;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->right != nullptr && t->right != last)
                    {
                        n = t->right;
                    }
                    else
                    {
                        swap(t->left, t->right);
                        s.pop();
                    }
                    last = t;
                }
            }
            return root;
        }

        // 227. Basic Calculator II
        // Given a string s which represents an expression, evaluate this expression and return its value.
        // The integer division should truncate toward zero.
        // Example 1:
        // Input: s = "3+2*2"
        // Output: 7
        // Example 2:
        // Input: s = " 3/2 "
        // Output: 1
        // Example 3:
        // Input: s = " 3+5 / 2 "
        // Output: 5
        // Constraints:
        // 1 <= s.length <= 3 * 105
        // s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
        // s represents a valid expression.
        // All the integers in the expression are non-negative integers in the range [0, 231 - 1].
        // The answer is guaranteed to fit in a 32-bit integer.
        int calculateII(string s)
        {
            stack<pair<char, long long>> e;
            long long a = 0;
            function<long long(long long, bool)> op =
                [&](long long v, bool doAddSub) -> long long
            {
                char o;
                long long t;
                if (!e.empty() && (e.top().first == '*' || e.top().first == '/'))
                {
                    o = e.top().first;
                    e.pop();
                    t = e.top().second;
                    e.pop();
                    if (o == '*')
                    {
                        v = t * v;
                    }
                    else
                    {
                        v = t / v;
                    }
                }
                if (doAddSub)
                {
                    if (!e.empty())
                    {
                        o = e.top().first;
                        e.pop();
                        t = 0;
                        if (!e.empty())
                        {
                            t = e.top().second;
                            e.pop();
                        }
                        if (o == '+')
                        {
                            v = t + v;
                        }
                        else
                        {
                            v = t - v;
                        }
                    }
                }
                return v;
            };
            for (const char &c : s)
            {
                if ('0' <= c && c <= '9')
                {
                    a = 10 * a + c - '0';
                }
                else if (c == '*' || c == '/' || c == '+' || c == '-')
                {
                    a = op(a, (c == '+' || c == '-'));
                    e.push(make_pair('0', a));
                    e.push(make_pair(c, 0));
                    a = 0;
                }
            }
            a = op(a, true);
            return a;
        }
        int calculateII2(string s)
        {
            stack<pair<char, long long>> e;
            long long a = 0;
            function<long long(long long, bool)> op =
                [&](long long v, bool doAddSub) -> long long
            {
                char o;
                long long t;
                if (!e.empty() && (e.top().first == '*' || e.top().first == '/'))
                {
                    o = e.top().first;
                    t = e.top().second;
                    e.pop();
                    if (o == '*')
                    {
                        v = t * v;
                    }
                    else
                    {
                        v = t / v;
                    }
                }
                if (doAddSub)
                {
                    if (!e.empty())
                    {
                        o = e.top().first;
                        t = e.top().second;
                        e.pop();
                        if (o == '+')
                        {
                            v = t + v;
                        }
                        else
                        {
                            v = t - v;
                        }
                    }
                }
                return v;
            };
            for (const char &c : s)
            {
                if ('0' <= c && c <= '9')
                {
                    a = 10 * a + c - '0';
                }
                else if (c == '*' || c == '/' || c == '+' || c == '-')
                {
                    a = op(a, (c == '+' || c == '-'));
                    e.push(make_pair(c, a));
                    a = 0;
                }
            }
            a = op(a, true);
            return a;
        }

        // 228. Summary Ranges
        // You are given a sorted unique integer array nums.
        // Return the smallest sorted list of ranges that cover all the numbers
        // in the array exactly. That is, each element of nums is covered by
        // exactly one of the ranges, and there is no integer x such that x is
        // in one of the ranges but not in nums.
        // Each range [a,b] in the list should be output as:
        // "a->b" if a != b
        // "a" if a == b
        // Example 1:
        // Input: nums = [0,1,2,4,5,7]
        // Output: ["0->2","4->5","7"]
        // Explanation: The ranges are:
        // [0,2] --> "0->2"
        // [4,5] --> "4->5"
        // [7,7] --> "7"
        // Example 2:
        // Input: nums = [0,2,3,4,6,8,9]
        // Output: ["0","2->4","6","8->9"]
        // Explanation: The ranges are:
        // [0,0] --> "0"
        // [2,4] --> "2->4"
        // [6,6] --> "6"
        // [8,9] --> "8->9"
        // Example 3:
        // Input: nums = []
        // Output: []
        // Example 4:
        // Input: nums = [-1]
        // Output: ["-1"]
        // Example 5:
        // Input: nums = [0]
        // Output: ["0"]
        // Constraints:
        // 0 <= nums.length <= 20
        // -231 <= nums[i] <= 231 - 1
        // All the values of nums are unique.
        // nums is sorted in ascending order.
        vector<string> summaryRanges(vector<int> &nums)
        {
            vector<string> ranges;
            if (nums.empty())
                return ranges;
            function<void(int, int)> output =
                [&](int x, int y)
            {
                ostringstream r;
                r << x;
                if (x < y)
                    r << "->" << y;
                ranges.push_back(r.str());
            };
            int b = nums[0];
            int e = b;
            for (size_t i = 1; i < nums.size(); i++)
            {
                if (nums[i] == e + 1)
                {
                    e++;
                }
                else
                {
                    output(b, e);
                    b = nums[i];
                    e = b;
                }
            }
            output(b, e);
            return ranges;
        }

        // 229. Majority Element II
        // Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
        // Follow-up: Could you solve the problem in linear time and in O(1) space?
        // Example 1:
        // Input: nums = [3,2,3]
        // Output: [3]
        // Example 2:
        // Input: nums = [1]
        // Output: [1]
        // Example 3:
        // Input: nums = [1,2]
        // Output: [1,2]
        // Constraints:
        // 1 <= nums.length <= 5 * 104
        // -109 <= nums[i] <= 109
        // Generalised Boyer Moore Voting.
        // Majority Element Problem. Floor(N/k) < Frequency(Majority Element)
        vector<int> majorityElement(vector<int> &nums)
        {
            vector<int> r;
            int n1 = 0;
            int c1 = 0;
            int n2 = 0;
            int c2 = 0;
            int t = nums.size() / 3;
            for (const int &n : nums)
            {
                if (c1 == 0 && c2 == 0)
                {
                    n1 = n;
                    c1 = 1;
                }
                else if (c1 == 0)
                {
                    if (n == n2)
                    {
                        c2++;
                    }
                    else
                    {
                        n1 = n;
                        c1 = 1;
                    }
                }
                else if (c2 == 0)
                {
                    if (n == n1)
                    {
                        c1++;
                    }
                    else
                    {
                        n2 = n;
                        c2 = 1;
                    }
                }
                else if (n == n1)
                {
                    c1++;
                }
                else if (n == n2)
                {
                    c2++;
                }
                else
                {
                    c1--;
                    c2--;
                }
                if (c1 > t && c2 > t)
                {
                    break;
                }
            }
            if (c1 <= t || c2 <= t)
            {
                c1 = 0;
                c2 = 0;
                for (const int &n : nums)
                {
                    if (n == n1)
                        c1++;
                    else if (n == n2)
                        c2++;
                }
            }
            if (c1 > t)
                r.push_back(n1);
            if (c2 > t)
                r.push_back(n2);
            return r;
        }

        // 230. Kth Smallest Element in a BST
        // Given a binary search tree, write a function kthSmallest to find
        // the kth smallest element in it.
        // Example 1:
        // Input: root = [3,1,4,null,2], k = 1
        //    3
        //   / \
        //  1   4
        //   \
        //    2
        // Output: 1
        // Example 2:
        // Input: root = [5,3,6,2,4,null,null,1], k = 3
        //        5
        //       / \
        //      3   6
        //     / \
        //    2   4
        //   /
        //  1
        // Output: 3
        // Follow up:
        // What if the BST is modified (insert/delete operations) often and
        // you need to find the kth smallest frequently? How would you optimize
        // the kthSmallest routine?
        // Constraints:
        // The number of elements of the BST is between 1 to 10^4.
        // You may assume k is always valid, 1 <= k <= BST's total elements.
        int kthSmallest(TreeNode *root, int k)
        {
            stack<TreeNode *> s;
            int i = 0;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    s.pop();
                    i++;
                    if (i == k)
                        return t->val;
                    n = t->right;
                }
            }
            throw invalid_argument("k");
        }

        // 231. Power of Two
        // Given an integer n, return true if it is a power of two. Otherwise, return false.
        // An integer n is a power of two, if there exists an integer x such that n == 2^x.
        // Example 1:
        // Input: n = 1
        // Output: true
        // Explanation: 20 = 1
        // Example 2:
        // Input: n = 16
        // Output: true
        // Explanation: 24 = 16
        // Example 3:
        // Input: n = 3
        // Output: false
        // Example 4:
        // Input: n = 4
        // Output: true
        // Example 5:
        // Input: n = 5
        // Output: false
        // Constraints:
        // -2^31 <= n <= 2^31 - 1
        bool isPowerOfTwo(int n)
        {
            return n > 0 && (n & (n - 1)) == 0;
        }

        // 232. Implement Queue using Stacks
        // Implement the following operations of a queue using stacks.
        // push(x) -- Push element x to the back of queue.
        // pop() -- Removes the element from in front of queue.
        // peek() -- Get the front element.
        // empty() -- Return whether the queue is empty.
        // Example:
        // MyQueue queue = new MyQueue();
        // queue.push(1);
        // queue.push(2);
        // queue.peek();  // returns 1
        // queue.pop();   // returns 1
        // queue.empty(); // returns false
        class MyQueue
        {
        private:
            stack<int> back;
            stack<int> front;
            void flush()
            {
                if (front.empty())
                {
                    while (!back.empty())
                    {
                        front.push(back.top());
                        back.pop();
                    }
                }
            }

        public:
            /** Initialize your data structure here. */
            MyQueue()
            {
            }

            /** Push element x to the back of queue. */
            void push(int x)
            {
                back.push(x);
            }

            /** Removes the element from in front of queue and returns that element. */
            int pop()
            {
                flush();
                int v = front.top();
                front.pop();
                return v;
            }

            /** Get the front element. */
            int peek()
            {
                flush();
                return front.top();
            }

            /** Returns whether the queue is empty. */
            bool empty()
            {
                return front.empty() && back.empty();
            }
        };

        // 233. Number of Digit One
        // Given an integer n, count the total number of digit 1 appearing in
        // all non-negative integers less than or equal to n.
        // Example 1:
        // Input: n = 13
        // Output: 6
        // Example 2:
        // Input: n = 0
        // Output: 0
        // Constraints:
        // 0 <= n <= 2 * 10^9
        // Given a number CBA:
        // F(CBA) = F(C00 - 1) + F(BA) + (C == 1 ? (BA + 1) : 0)
        // i.e., the total count is count over range [0, C00) + count over range [C00, CBA]
        int countDigitOne(int n)
        {
            map<int, int> m;
            function<int(int)> count = [&](int x) -> int
            {
                if (x <= 0)
                    return 0;
                if (x < 10)
                    return 1;
                if (m.find(x) != m.end())
                    return m[x];
                int y = 1;
                int h = x;
                while (h >= 10)
                {
                    h /= 10;
                    y *= 10;
                }
                // h is the highest digit
                y *= h;
                int z = x - y;
                int c = count(y - 1);
                c += count(z);
                if (h == 1)
                    c += (z + 1);
                m[x] = c;
                return c;
            };
            return count(n);
        }

        // 234. Palindrome Linked List
        // Given a singly linked list, determine if it is a palindrome.
        // Example 1:
        // Input: 1->2
        // Output: false
        // Example 2:
        // Input: 1->2->2->1
        // Output: true
        // Follow up: Could you do it in O(n) time and O(1) space?
        bool isPalindrome(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return true;
            function<ListNode *(ListNode *)> reverse = [&](ListNode *h) -> ListNode *
            {
                if (h == nullptr)
                    return nullptr;
                ListNode *t = h;
                while (t->next != nullptr)
                {
                    ListNode *p = t->next;
                    t->next = p->next;
                    p->next = h;
                    h = p;
                }
                return h;
            };
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
            }
            bool oddCount = (q->next == nullptr);
            ListNode *h2 = p->next;
            p->next = nullptr;
            head = reverse(head);
            p = oddCount ? head->next : head;
            q = h2;
            bool result = true;
            while (p != nullptr && q != nullptr)
            {
                if (p->val != q->val)
                {
                    result = false;
                    break;
                }
                p = p->next;
                q = q->next;
            }
            if (result && !(p == nullptr && q == nullptr))
                result = false;
            p = head;
            head = reverse(head);
            p->next = h2;
            return result;
        }

        // 235. Lowest Common Ancestor of a Binary Search Tree
        // Given a binary search tree (BST), find the lowest common ancestor (LCA) of
        // two given nodes in the BST. According to the definition of LCA on Wikipedia:
        // "The lowest common ancestor is defined between two nodes p and q as the lowest
        // node in T that has both p and q as descendants (where we allow a node to be
        // a descendant of itself)."
        // Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]
        // Example 1:
        // Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
        // Output: 6
        // Explanation: The LCA of nodes 2 and 8 is 6.
        // Example 2:
        // Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
        // Output: 2
        // Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant
        // of itself according to the LCA definition.
        TreeNode *lowestCommonAncestorBST(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            TreeNode *node = root;
            while (node != nullptr)
            {
                if (node->val > p->val && node->val > q->val)
                    node = node->left;
                else if (node->val < p->val && node->val < q->val)
                    node = node->right;
                else
                    break;
            }
            return node;
        }

        // 236. Lowest Common Ancestor of a Binary Tree
        // Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
        // in the tree. According to the definition of LCA on Wikipedia: “The lowest
        // common ancestor is defined between two nodes p and q as the lowest node in T
        // that has both p and q as descendants (where we allow a node to be a
        // descendant of itself).” Given the following binary tree:  root =
        // [3,5,1,6,2,0,8,null,null,7,4] Example 1: Input: root =
        // [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1 Output: 3 Explanation: The LCA of
        // nodes 5 and 1 is 3. Example 2: Input: root = [3,5,1,6,2,0,8,null,null,7,4], p
        // = 5, q = 4 Output: 5 Explanation: The LCA of nodes 5 and 4 is 5, since a node
        // can be a descendant of itself according to the LCA definition. Note: All of
        // the nodes' values will be unique. p and q are different and both values will
        // exist in the binary tree.
        TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            if (root == nullptr || p == nullptr || q == nullptr)
                return nullptr;
            TreeNode *left = lowestCommonAncestor(root->left, p, q);
            TreeNode *right = lowestCommonAncestor(root->right, p, q);
            if (left != nullptr && right != nullptr)
                return root;
            if (left != nullptr)
            {
                if (root == p || root == q)
                    return root;
                else
                    return left;
            }
            if (right != nullptr)
            {
                if (root == p || root == q)
                    return root;
                else
                    return right;
            }
            return (root == p || root == q) ? root : nullptr;
        }
        TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    // If found one then mark it
                    s.push(make_pair(n, (n == p || n == q) ? 1 : 0));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    if (p.first->right != nullptr && p.first->right != last)
                    {
                        n = p.first->right;
                    }
                    else
                    {
                        s.pop();
                        if (p.second == 1)
                        {
                            if (s.top().second == 1)
                            {
                                // Two nodes are found
                                return s.top().first;
                            }
                            else
                            {
                                // Only one found
                                s.top().second = 1;
                            }
                        }
                        last = p.first;
                    }
                }
            }
            return nullptr;
        }

        // 237. Delete Node in a Linked List
        // Write a function to delete a node in a singly-linked list.
        // You will not be given access to the head of the list, instead
        // you will be given access to the node to be deleted directly.
        // It is guaranteed that the node to be deleted is not a tail node in the list.
        // Example 1:
        // Input: head = [4,5,1,9], node = 5
        // Output: [4,1,9]
        // Explanation: You are given the second node with value 5, the linked
        // list should become 4 -> 1 -> 9 after calling your function.
        // Example 2:
        // Input: head = [4,5,1,9], node = 1
        // Output: [4,5,9]
        // Explanation: You are given the third node with value 1, the linked
        // list should become 4 -> 5 -> 9 after calling your function.
        // Example 3:
        // Input: head = [1,2,3,4], node = 3
        // Output: [1,2,4]
        // Example 4:
        // Input: head = [0,1], node = 0
        // Output: [1]
        // Example 5:
        // Input: head = [-3,5,-99], node = -3
        // Output: [5,-99]
        // Constraints:
        // The number of the nodes in the given list is in the range [2, 1000].
        // -1000 <= Node.val <= 1000
        // The value of each node in the list is unique.
        // The node to be deleted is in the list and is not a tail node
        void deleteNode(ListNode *node)
        {
            if (node == nullptr || node->next == nullptr)
                return;
            node->val = node->next->val;
            ListNode *n = node->next;
            node->next = n->next;
            delete n;
        }
        void deleteNode2(ListNode *node)
        {
            if (node == nullptr)
                return;
            while (node->next != nullptr)
            {
                node->val = node->next->val;
                if (node->next->next == nullptr)
                {
                    delete node->next;
                    node->next = nullptr;
                }
                else
                {
                    node = node->next;
                }
            }
        }

        // 238. Product of Array Except Self
        // Given an array nums of n integers where n > 1,  return an array output such
        // that output[i] is equal to the product of all the elements of nums except nums[i].
        // Example:
        // Input:  [1,2,3,4]
        // Output: [24,12,8,6]
        // Constraint: It is guaranteed that the product of the elements of any prefix
        // or suffix of the array (including the whole array) fits in a 32 bit integer.
        // Note: Please solve it without division and in O(n).
        // Follow up:
        // Could you solve it with constant space complexity?
        // (The output array does not count as extra space for the purpose of space complexity analysis.)
        vector<int> productExceptSelf(vector<int> &nums)
        {
            vector<int> output(nums);

            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (i == 0)
                    output[0] = 1;
                else
                    output[i] = output[i - 1] * nums[i - 1];
            }
            int a = 1;
            for (int i = (int)nums.size() - 2; i >= 0; i--)
            {
                a *= nums[i + 1];
                output[i] *= a;
            }
            return output;
        }
        // Let M[i..j] = I[i] * I[i+1] * ... * I[j]
        // I[i]  I[0]      I[1]      I[2]      ...... I[i]        ...... I[n-1]
        // L[i]  1         M[0..0]   M[0..1]   ...... M[0..i-1]   ...... M[0..n-2]
        // R[i]  M[1..n-1] M[2..n-1] M[3..n-1] ...... M[i+1..n-1] ...... 1
        // O[i] = L[i] * R[i]
        vector<int> productExceptSelf2(vector<int> &nums)
        {
            vector<int> output(nums.size(), 1);
            int l = 1;
            int r = 1;
            int n = nums.size();
            for (int i = 0; i < n; i++)
            {
                // At loop i, output[i] *= left (= multiplication of input[0..i-1])
                // At loop length - 1 - i, output[i] *= right (= multiplication of
                // input[i+1..length-1])
                output[i] *= l;
                output[n - 1 - i] *= r;
                l *= nums[i];
                r *= nums[n - 1 - i];
            }
            return output;
        }

        // 239. Sliding Window Maximum
        // You are given an array of integers nums, there is a sliding window of size k
        // which is moving from the very left of the array to the very right. You can
        // only see the k numbers in the window. Each time the sliding window moves right
        // by one position. Return the max sliding window.
        // Example 1:
        // Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
        // Output: [3,3,5,5,6,7]
        // Explanation:
        // Window position                Max
        // ---------------               -----
        // [1  3  -1] -3  5  3  6  7       3
        //  1 [3  -1  -3] 5  3  6  7       3
        //  1  3 [-1  -3  5] 3  6  7       5
        //  1  3  -1 [-3  5  3] 6  7       5
        //  1  3  -1  -3 [5  3  6] 7       6
        //  1  3  -1  -3  5 [3  6  7]      7
        // Example 2:
        // Input: nums = [1], k = 1
        // Output: [1]
        // Example 3:
        // Input: nums = [1,-1], k = 1
        // Output: [1,-1]
        // Example 4:
        // Input: nums = [9,11], k = 2
        // Output: [11]
        // Example 5:
        // Input: nums = [4,-2], k = 2
        // Output: [4]
        // Constraints:
        // 1 <= nums.length <= 10^5
        // -10^4 <= nums[i] <= 10^4
        // 1 <= k <= nums.length
        vector<int> maxSlidingWindow(vector<int> &nums, int k)
        {
            vector<int> output;
            deque<int> q;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (!q.empty() && nums[q.back()] <= nums[i])
                    q.pop_back();
                q.push_back(i);
                while (q.front() + k <= i)
                    q.pop_front();
                if (k - 1 <= (int)i)
                    output.push_back(nums[q.front()]);
            }
            return output;
        }
        vector<int> maxSlidingWindow2(vector<int> &nums, int k)
        {
            vector<int> output;
            class compless
            {
            private:
                const vector<int> &n;

            public:
                compless(const vector<int> &v) : n(v) {}
                bool operator()(const int &i, const int &j) const
                {
                    return n[i] < n[j];
                }
            };
            typedef std::priority_queue<int, std::vector<int>, compless> q_type;
            q_type q = q_type(compless(nums));
            for (int i = 0; i < (int)nums.size(); i++)
            {
                q.push(i);
                if (i >= k - 1)
                {
                    while (q.top() < i - k + 1)
                        q.pop();
                    output.push_back(nums[q.top()]);
                }
            }
            return output;
        }
        vector<int> maxSlidingWindow3(vector<int> &nums, int k)
        {
            vector<int> output;
            int m = 0;
            // Start from 0 so it covers the input with only one element
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (k <= i && m + k <= i)
                {
                    m = i - k + 1;
                    for (int j = i - k + 2; j <= i; j++)
                    {
                        if (nums[m] <= nums[j])
                            m = j;
                    }
                }
                else if (nums[m] <= nums[i])
                {
                    m = i;
                }
                if (k - 1 <= i)
                    output.push_back(nums[m]);
            }
            return output;
        }
        vector<int> maxSlidingWindow4(vector<int> &nums, int k)
        {
            struct Node
            {
                int val;
                struct Node *left;
                struct Node *right;
                Node(int v) : val(v), left(nullptr), right(nullptr) {}
            } *root = nullptr;
            function<void(int)> insert = [&](int v)
            {
                struct Node *parent = nullptr;
                struct Node *node = root;
                while (node != nullptr)
                {
                    parent = node;
                    if (v < node->val)
                        node = node->left;
                    else
                        node = node->right;
                }
                node = new Node(v);
                if (parent == nullptr)
                    root = node;
                else if (v < parent->val)
                    parent->left = node;
                else
                    parent->right = node;
            };
            function<int()> get_max = [&]() -> int
            {
                struct Node *node = root;
                if (node == nullptr)
                    return INT_MIN;
                while (node->right != nullptr)
                    node = node->right;
                return node->val;
            };
            function<void(int)> delete_val = [&](int v)
            {
                struct Node *parent = nullptr;
                struct Node *node = root;
                while (node != nullptr && node->val != v)
                {
                    parent = node;
                    if (v < node->val)
                        node = node->left;
                    else
                        node = node->right;
                }
                if (node == nullptr)
                    return;
                if (node->right == nullptr)
                {
                    if (parent == nullptr)
                        root = node->left;
                    else if (parent->left == node)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                    node->left = nullptr;
                    delete node;
                    return;
                }
                struct Node *next = node->right;
                if (next->left == nullptr)
                {
                    next->left = node->left;
                    if (parent == nullptr)
                        root = next;
                    else if (parent->left == node)
                        parent->left = next;
                    else
                        parent->right = next;
                    node->left = nullptr;
                    node->right = nullptr;
                    delete node;
                    return;
                }
                struct Node *next_parent = nullptr;
                while (next->left != nullptr)
                {
                    next_parent = next;
                    next = next->left;
                }
                next_parent->left = next->right;
                next->left = node->left;
                next->right = node->right;
                if (parent == nullptr)
                    root = next;
                else if (parent->left == node)
                    parent->left = next;
                else
                    parent->right = next;
                node->left = nullptr;
                node->right = nullptr;
                delete node;
            };
            vector<int> output;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (k <= i)
                    delete_val(nums[i - k]);
                insert(nums[i]);
                if (k - 1 <= i)
                    output.push_back(get_max());
            }
            return output;
        }

        // 240. Search a 2D Matrix II
        // Write an efficient algorithm that searches for a value in an m x n matrix.
        // This matrix has the following properties:
        // Integers in each row are sorted in ascending from left to right.
        // Integers in each column are sorted in ascending from top to bottom.
        // Example:
        // Consider the following matrix:
        // [
        //   [1,   4,  7, 11, 15],
        //   [2,   5,  8, 12, 19],
        //   [3,   6,  9, 16, 22],
        //   [10, 13, 14, 17, 24],
        //   [18, 21, 23, 26, 30]
        // ]
        // Given target = 5, return true.
        // Given target = 20, return false.
        bool searchMatrixII(vector<vector<int>> &matrix, int target)
        {
            if (matrix.empty() || matrix[0].empty())
                return false;
            int m = matrix.size();
            int n = matrix[0].size();
            int i = 0;
            int j = n - 1;
            while (i < m && j >= 0)
            {
                if (matrix[i][j] < target)
                    i++;
                else if (matrix[i][j] > target)
                    j--;
                else
                    return true;
            }
            return false;
        }
        bool searchMatrixII2(vector<vector<int>> &matrix, int target)
        {
            if (matrix.empty() || matrix[0].empty())
                return false;
            function<bool(int, int, int, int)> search =
                [&](int r0, int r1, int c0, int c1) -> bool
            {
                if (r0 > r1 || c0 > c1)
                    return false;
                if (r1 - r0 <= 1 && c1 - c0 <= 1)
                {
                    for (int i = r0; i <= r1; i++)
                    {
                        for (int j = c0; j <= c1; j++)
                        {
                            if (matrix[i][j] == target)
                                return true;
                        }
                    }
                    return false;
                }
                int i = r0 + ((r1 - r0) >> 1);
                int j = c0 + ((c1 - c0) >> 1);
                if (matrix[i][j] < target)
                {
                    if (search(i + 1, r1, j + 1, c1))
                        return true;
                }
                else if (matrix[i][j] > target)
                {
                    if (search(r0, i - 1, c0, j - 1))
                        return true;
                }
                else
                {
                    return true;
                }
                if (search(r0, i, j, c1))
                    return true;
                if (search(i, r1, c0, j))
                    return true;
                return false;
            };
            int m = matrix.size();
            int n = matrix[0].size();
            return search(0, m - 1, 0, n - 1);
        }

        // 241. Different Ways to Add Parentheses
        // Given a string of numbers and operators, return all possible results
        // from computing all the different possible ways to group numbers and
        // operators. The valid operators are +, - and *.
        // Example 1:
        // Input: "2-1-1"
        // Output: [0, 2]
        // Explanation:
        // ((2-1)-1) = 0
        // (2-(1-1)) = 2
        // Example 2:
        // Input: "2*3-4*5"
        // Output: [-34, -14, -10, -10, 10]
        // Explanation:
        // (2*(3-(4*5))) = -34
        // ((2*3)-(4*5)) = -14
        // ((2*(3-4))*5) = -10
        // (2*((3-4)*5)) = -10
        // (((2*3)-4)*5) = 10
        // Adding parentheses is equivalent to building an AST.
        // (2-1)-1
        //      -
        //     / \
        //    -   1
        //   / \
        //  2   1
        // 2-(1-1)
        //   -
        //  / \
        // 2   -
        //    / \
        //   1   1
        vector<int> diffWaysToCompute(string input)
        {
            vector<int> output;
            map<pair<int, int>, vector<int>> m;
            function<void(int, int)> compute = [&](int i, int j)
            {
                if (i > j)
                    return;
                pair<int, int> p = make_pair(i, j);
                if (m.find(p) != m.end())
                    return;
                int a = 0;
                bool isNum = true;
                vector<int> o;
                for (int k = i; k <= j; k++)
                {
                    if ('0' <= input[k] && input[k] <= '9')
                    {
                        a = 10 * a + input[k] - '0';
                    }
                    else
                    {
                        isNum = false;
                        compute(i, k - 1);
                        compute(k + 1, j);
                        pair<int, int> p1 = make_pair(i, k - 1);
                        pair<int, int> p2 = make_pair(k + 1, j);
                        if (m.find(p1) != m.end() && m.find(p2) != m.end())
                        {
                            for (int x : m[p1])
                            {
                                for (int y : m[p2])
                                {
                                    switch (input[k])
                                    {
                                    case '+':
                                        o.push_back(x + y);
                                        break;
                                    case '-':
                                        o.push_back(x - y);
                                        break;
                                    case '*':
                                        o.push_back(x * y);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                if (isNum)
                    m[p].push_back(a);
                else
                    m[p] = o;
            };
            int n = (int)input.size();
            compute(0, n - 1);
            return m[make_pair(0, n - 1)];
        }
        vector<int> diffWaysToCompute2(string input)
        {
            function<void(const string &, const vector<pair<char, int>> &)> print =
                [&](const string &message, const vector<pair<char, int>> &tokens)
            {
                cout << message << endl;
                for (const auto &p : tokens)
                {
                    if (p.first == '0')
                        cout << p.second;
                    else
                        cout << p.first;
                }
                cout << endl;
            };
            function<int(vector<pair<char, int>> &)> scan =
                [&](vector<pair<char, int>> &tokens) -> int
            {
                int a = 0;
                int countNums = 0;
                for (const char &c : input)
                {
                    if ('0' <= c && c <= '9')
                    {
                        a = 10 * a + c - '0';
                    }
                    else if (c == '+' || c == '-' || c == '*')
                    {
                        countNums++;
                        tokens.push_back(make_pair('0', a));
                        tokens.push_back(make_pair(c, 0));
                        a = 0;
                    }
                }
                countNums++;
                tokens.push_back(make_pair('0', a));
                return countNums;
            };
            vector<pair<char, int>> inputTokens;
            int maxParenthesesCount = scan(inputTokens) - 1;
            print("inputTokens:", inputTokens);
            function<int(stack<pair<char, int>> &, int, bool)> check =
                [&](stack<pair<char, int>> &s, int n, bool doAddSub) -> int
            {
                while (!s.empty() && s.top().first == '*')
                {
                    s.pop();
                    n *= s.top().second;
                    s.pop();
                }
                if (doAddSub)
                {
                    while (!s.empty() && s.top().first != '(')
                    {
                        char op = s.top().first;
                        s.pop();
                        if (op == '+')
                            n = s.top().second + n;
                        else
                            n = s.top().second - n;
                        s.pop();
                    }
                }
                return n;
            };
            function<int(const vector<pair<char, int>> &)> compute =
                [&](const vector<pair<char, int>> &tokens) -> int
            {
                stack<pair<char, int>> s;
                int currentNum = 0;
                for (const auto &p : tokens)
                {
                    if (p.first == '(')
                    {
                        s.push(p);
                    }
                    else if (p.first == '0')
                    {
                        currentNum = p.second;
                    }
                    else
                    {
                        currentNum = check(s, currentNum, (p.first == '+' || p.first == '-' || p.first == ')'));
                        if (p.first == ')')
                        {
                            s.pop();
                        }
                        else
                        {
                            s.push(make_pair('0', currentNum));
                            s.push(p);
                        }
                    }
                }
                currentNum = check(s, currentNum, true);
                return currentNum;
            };
            function<bool(const vector<pair<char, int>> &)> validate =
                [&](const vector<pair<char, int>> &tokens) -> bool
            {
                stack<int> s;
                int n = (int)tokens.size();
                int i = 0;
                int j;
                while (i < n)
                {
                    if (tokens[i].first == '(')
                    {
                        j = i;
                        while (j + 1 < n && tokens[j + 1].first == '(')
                            j++;
                        s.push(j - i + 1);
                        i = j + 1;
                    }
                    else if (tokens[i].first == ')')
                    {
                        j = i;
                        while (j + 1 < n && tokens[j + 1].first == ')')
                            j++;
                        int c = j - i + 1;
                        while (!s.empty() && s.top() == 1)
                        {
                            s.pop();
                            c--;
                        }
                        if ((s.empty() && c > 0) || (!s.empty() && s.top() > 1 && c > 1) || (!s.empty() && s.top() < c))
                            return false;
                        if (!s.empty())
                        {
                            s.top() -= c;
                            if (s.top() == 0)
                                s.pop();
                        }
                        i = j + 1;
                    }
                    else
                    {
                        i++;
                    }
                }
                return true;
            };
            vector<int> output;
            function<void(size_t, int, int, const vector<pair<char, int>> &)> add =
                [&](size_t i, int l, int r, const vector<pair<char, int>> &ctokens)
            {
                if (i == inputTokens.size())
                {
                    if (l == maxParenthesesCount && r == maxParenthesesCount && validate(ctokens))
                    {
                        print("", ctokens);
                        output.push_back(compute(ctokens));
                    }
                    return;
                }
                if (inputTokens[i].first == '0')
                {
                    vector<pair<char, int>> tokens1(ctokens);
                    tokens1.push_back(inputTokens[i]);
                    add(i + 1, l, r, tokens1);
                    if (i + 1 < inputTokens.size() && l < maxParenthesesCount)
                    {
                        vector<pair<char, int>> tokens2(ctokens);
                        for (int k = 1; l + k <= maxParenthesesCount; k++)
                        {
                            tokens2.push_back(make_pair('(', 0));
                            tokens2.push_back(inputTokens[i]);
                            add(i + 1, l + k, r, tokens2);
                            tokens2.pop_back();
                        }
                    }
                    if (0 < i)
                    {
                        vector<pair<char, int>> tokens3(ctokens);
                        tokens3.push_back(inputTokens[i]);
                        for (int k = 1; r + k <= l; k++)
                        {
                            tokens3.push_back(make_pair(')', 0));
                            add(i + 1, l, r + k, tokens3);
                        }
                    }
                }
                else
                {
                    vector<pair<char, int>> tokens(ctokens);
                    tokens.push_back(inputTokens[i]);
                    add(i + 1, l, r, tokens);
                }
            };
            vector<pair<char, int>> t;
            add(0, 0, 0, t);
            return output;
        }

        // 242. Valid Anagram
        // Given two strings s and t , write a function to determine
        // if t is an anagram of s.
        // Example 1:
        // Input: s = "anagram", t = "nagaram"
        // Output: true
        // Example 2:
        // Input: s = "rat", t = "car"
        // Output: false
        // Note:
        // You may assume the string contains only lowercase alphabets.
        // Follow up:
        // What if the inputs contain unicode characters?
        // How would you adapt your solution to such case?
        bool isAnagram(string s, string t)
        {
            if (s.size() != t.size())
                return false;
            function<void(const string &, map<char, int> &)> count =
                [&](const string &w, map<char, int> &m)
            {
                for (const char &c : w)
                {
                    if (m.find(c) == m.end())
                        m[c] = 1;
                    else
                        m[c]++;
                }
            };
            map<char, int> a;
            map<char, int> b;
            count(s, a);
            count(t, b);
            if (a.size() != b.size())
                return false;
            for (const auto &p : a)
            {
                if (b.find(p.first) == b.end())
                    return false;
                if (b[p.first] != p.second)
                    return false;
            }
            return true;
        }
        bool isAnagram2(string s, string t)
        {
            if (s.size() != t.size())
                return false;
            string s1 = s;
            string t1 = t;
            sort(s1.begin(), s1.end());
            sort(t1.begin(), t1.end());
            for (size_t i = 0; i < s1.size(); i++)
            {
                if (s1[i] != t1[i])
                    return false;
            }
            return true;
        }

        // 257. Binary Tree Paths
        // Given a binary tree, return all root-to-leaf paths.
        // Note: A leaf is a node with no children.
        // Example:
        // Input:
        //    1
        //  /   \
        // 2     3
        //  \
        //   5
        // Output: ["1->2->5", "1->3"]
        // Explanation: All root-to-leaf paths are: 1->2->5, 1->3
        vector<string> binaryTreePaths(TreeNode *root)
        {
            vector<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            vector<string> paths;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push_back(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.back();
                    if (t->left == nullptr && t->right == nullptr)
                    {
                        ostringstream ss;
                        for (size_t i = 0; i < s.size(); i++)
                        {
                            if (i > 0)
                                ss << "->";
                            ss << s[i]->val;
                        }
                        paths.push_back(ss.str());
                    }
                    if (t->right == nullptr || t->right == last)
                    {
                        s.pop_back();
                    }
                    else
                    {
                        n = t->right;
                    }
                    last = t;
                }
            }
            return paths;
        }

        // 258. Add Digits
        // Given a non-negative integer num, repeatedly add all its digits
        // until the result has only one digit.
        // Example:
        // Input: 38
        // Output: 2
        // Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
        // Since 2 has only one digit, return it.
        // Follow up:
        // Could you do it without any loop/recursion in O(1) runtime?
        // Digital Root
        int addDigits(int num)
        {
            while (num >= 10)
            {
                int s = 0;
                while (num > 0)
                {
                    s += num % 10;
                    num /= 10;
                }
                num = s;
            }
            return num;
        }

        // 260. Single Number III
        // Given an integer array nums, in which exactly two elements appear only once and
        // all the other elements appear exactly twice. Find the two elements that appear only
        // once. You can return the answer in any order.
        // Follow up: Your algorithm should run in linear runtime complexity.
        // Could you implement it using only constant space complexity?
        // Example 1:
        // Input: nums = [1,2,1,3,2,5]
        // Output: [3,5]
        // Explanation:  [5, 3] is also a valid answer.
        // Example 2:
        // Input: nums = [-1,0]
        // Output: [-1,0]
        // Example 3:
        // Input: nums = [0,1]
        // Output: [1,0]
        // Constraints:
        // 2 <= nums.length <= 3 * 10^4
        // -2^31 <= nums[i] <= 2^31 - 1
        // Each integer in nums will appear twice, only two integers will appear once.
        vector<int> singleNumberIII(vector<int> &nums)
        {
            long long x = 0; // long long to avoid overflow of -x
            for (const int &n : nums)
            {
                x ^= n;
            }
            int n1 = 0;
            int n2 = 0;
            // Two's complement
            // This is to get the right most bit 1
            //  12: 00001100
            // -12: 11110100
            x = x & (-x);
            for (const int &n : nums)
            {
                if (x & n)
                    n1 ^= n; // xor all the numbers setting the bit
                else
                    n2 ^= n; // xor all the numbers not setting the bit
            }
            return vector<int>{n1, n2};
        }
        vector<int> singleNumberIII2(vector<int> &nums)
        {
            set<int> s;
            for (const int n : nums)
            {
                if (s.find(n) == s.end())
                    s.insert(n);
                else
                    s.erase(n);
            }
            return vector<int>(s.cbegin(), s.cend());
        }

        // 262. Trips and Users
        // Table: Trips
        // +-------------+----------+
        // | Column Name | Type     |
        // +-------------+----------+
        // | Id          | int      |
        // | Client_Id   | int      |
        // | Driver_Id   | int      |
        // | City_Id     | int      |
        // | Status      | enum     |
        // | Request_at  | date     |
        // +-------------+----------+
        // Id is the primary key for this table. The table holds all taxi trips. Each trip has a unique Id,
        // while Client_Id and Driver_Id are foreign keys to the Users_Id at the Users table.
        // Status is an ENUM type of (‘completed’, ‘cancelled_by_driver’, ‘cancelled_by_client’).
        // Table: Users
        // +-------------+----------+
        // | Column Name | Type     |
        // +-------------+----------+
        // | Users_Id    | int      |
        // | Banned      | enum     |
        // | Role        | enum     |
        // +-------------+----------+
        // Users_Id is the primary key for this table. The table holds all users. Each user has a unique Users_Id,
        // and Role is an ENUM type of (‘client’, ‘driver’, ‘partner’).
        // Status is an ENUM type of (‘Yes’, ‘No’).
        // Write a SQL query to find the cancellation rate of requests with unbanned users (both client and
        // driver must not be banned) each day between "2013-10-01" and "2013-10-03".
        // The cancellation rate is computed by dividing the number of canceled (by client or driver) requests
        // with unbanned users by the total number of requests with unbanned users on that day.
        // Return the result table in any order. Round Cancellation Rate to two decimal points.
        // The query result format is in the following example:
        // Trips table:
        // +----+-----------+-----------+---------+---------------------+------------+
        // | Id | Client_Id | Driver_Id | City_Id | Status              | Request_at |
        // +----+-----------+-----------+---------+---------------------+------------+
        // | 1  | 1         | 10        | 1       | completed           | 2013-10-01 |
        // | 2  | 2         | 11        | 1       | cancelled_by_driver | 2013-10-01 |
        // | 3  | 3         | 12        | 6       | completed           | 2013-10-01 |
        // | 4  | 4         | 13        | 6       | cancelled_by_client | 2013-10-01 |
        // | 5  | 1         | 10        | 1       | completed           | 2013-10-02 |
        // | 6  | 2         | 11        | 6       | completed           | 2013-10-02 |
        // | 7  | 3         | 12        | 6       | completed           | 2013-10-02 |
        // | 8  | 2         | 12        | 12      | completed           | 2013-10-03 |
        // | 9  | 3         | 10        | 12      | completed           | 2013-10-03 |
        // | 10 | 4         | 13        | 12      | cancelled_by_driver | 2013-10-03 |
        // +----+-----------+-----------+---------+---------------------+------------+
        // Users table:
        // +----------+--------+--------+
        // | Users_Id | Banned | Role   |
        // +----------+--------+--------+
        // | 1        | No     | client |
        // | 2        | Yes    | client |
        // | 3        | No     | client |
        // | 4        | No     | client |
        // | 10       | No     | driver |
        // | 11       | No     | driver |
        // | 12       | No     | driver |
        // | 13       | No     | driver |
        // +----------+--------+--------+
        // Result table:
        // +------------+-------------------+
        // | Day        | Cancellation Rate |
        // +------------+-------------------+
        // | 2013-10-01 | 0.33              |
        // | 2013-10-02 | 0.00              |
        // | 2013-10-03 | 0.50              |
        // +------------+-------------------+
        // On 2013-10-01:
        //   - There were 4 requests in total, 2 of which were canceled.
        //   - However, the request with Id=2 was made by a banned client (User_Id=2), so it is ignored in the calculation.
        //   - Hence there are 3 unbanned requests in total, 1 of which was canceled.
        //   - The Cancellation Rate is (1 / 3) = 0.33
        // On 2013-10-02:
        //   - There were 3 requests in total, 0 of which were canceled.
        //   - The request with Id=6 was made by a banned client, so it is ignored.
        //   - Hence there are 2 unbanned requests in total, 0 of which were canceled.
        //   - The Cancellation Rate is (0 / 2) = 0.00
        // On 2013-10-03:
        //   - There were 3 requests in total, 1 of which was canceled.
        //   - The request with Id=8 was made by a banned client, so it is ignored.
        //   - Hence there are 2 unbanned request in total, 1 of which were canceled.
        //   - The Cancellation Rate is (1 / 2) = 0.50
        // create table if not exists trips (
        // Id int auto_increment primary key,
        // Client_Id int,
        // Driver_Id int,
        // City_Id int,
        // Status enum ('completed', 'cancelled_by_driver', 'cancelled_by_client'),
        // Request_at date
        // ) engine = innodb;
        // create table if not exists users (
        // Users_Id int auto_increment primary key,
        // Banned enum ('Yes', 'No'),
        // Role enum('client', 'driver', 'partner')
        // ) engine = innodb;
        // insert into trips (Client_Id, Driver_Id, City_Id, Status, Request_at)
        // values
        // (1, 10, 1, 'completed', '2013-10-01'),
        // (2, 11, 1, 'cancelled_by_driver', '2013-10-01'),
        // (3, 12, 6, 'completed', '2013-10-01'),
        // (4, 13, 6, 'cancelled_by_client', '2013-10-01'),
        // (1, 10, 1, 'completed', '2013-10-02'),
        // (2, 11, 6, 'completed', '2013-10-02'),
        // (3, 12, 6, 'completed', '2013-10-02'),
        // (2, 12, 12, 'completed', '2013-10-03'),
        // (3, 10, 12, 'completed', '2013-10-03'),
        // (4, 13, 12, 'cancelled_by_driver', '2013-10-03');
        // insert into users (Banned, Role)
        // values
        // ('No', 'client'),
        // ('Yes', 'client'),
        // ('No', 'client'),
        // ('No', 'client'),
        // ('No', 'driver'),
        // ('No', 'driver'),
        // ('No', 'driver'),
        // ('No', 'driver');
        // with banned (id) as (select users_id from users where banned = 'yes'),
        // dailystatus (Day, status) as(
        // select request_at, status from trips
        // where client_id not in (select id from banned) and driver_id not in (select id from banned)
        // )
        // select Day,
        // truncate(sum(case when status <> 'completed' then 1 else 0 end) / count(status), 2) as 'Cancellation Rate'
        // from dailystatus
        // group by Day;

        // 263. Ugly Number
        // Write a program to check whether a given number is an ugly number.
        // Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
        // Example 1:
        // Input: 6
        // Output: true
        // Explanation: 6 = 2 x 3
        // Example 2:
        // Input: 8
        // Output: true
        // Explanation: 8 = 2 x 2 x 2
        // Example 3:
        // Input: 14
        // Output: false
        // Explanation: 14 is not ugly since it includes another prime factor 7.
        // Note:
        // 1 is typically treated as an ugly number.
        // Input is within the 32-bit signed integer range: [−2^31,  2^31 − 1].
        bool isUgly(int num)
        {
            if (num <= 0)
                return false;
            function<int(int, int)> divide = [&](int n, int d) -> int
            {
                while (true)
                {
                    int r = n / d;
                    if (n == r * d)
                        n = r;
                    else
                        break;
                }
                return n;
            };
            num = divide(num, 2);
            num = divide(num, 3);
            num = divide(num, 5);
            return num == 1;
        }
        bool isUgly2(int num)
        {
            if (num <= 0)
                return false;
            while (num % 2 == 0)
                num /= 2;
            while (num % 3 == 0)
                num /= 3;
            while (num % 5 == 0)
                num /= 5;
            return num == 1;
        }

        // 264. Ugly Number II
        // Write a program to find the n-th ugly number.
        // Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
        // Example:
        // Input: n = 10
        // Output: 12
        // Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
        // Note:
        // 1 is typically treated as an ugly number.
        // n does not exceed 1690.
        int nthUglyNumber(int n)
        {
            vector<int> a(1, 1);
            while ((int)a.size() < n)
            {
                int u = a.back();
                // long long m = INT_MAX;
                int m = INT_MAX;
                for (int i = (int)a.size() - 1; i >= 0; i--)
                {
                    // long long x = a[i] * (long long)5;
                    int x = a[i] * 5;
                    if (x <= u)
                        break;
                    if (x > u)
                        m = min(m, x);
                    // x = a[i] * (long long)3;
                    x = a[i] * 3;
                    if (x > u)
                        m = min(m, x);
                    // x = a[i] * (long long)2;
                    x = a[i] * 2;
                    if (x > u)
                        m = min(m, x);
                }
                a.push_back(m);
            }
            return a.back();
        }
        // This is wrong
        int nthUglyNumber2(int n)
        {
            // cout << "nthUglyNumber(" << n << ")" << endl;
            vector<int> f = {2, 3, 5};
            vector<int> a(3, 1);
            int u = 1;
            for (; n > 1; n--)
            {
                // cout << a[0] << "\t" << a[1] << "\t" << a[2] << endl;
                size_t I = 0;
                int m = INT_MAX;
                for (size_t i = 0; i < a.size(); i++)
                {
                    for (size_t j = 0; j < f.size(); j++)
                    {
                        int c = a[i] * f[j];
                        if (c > u && c < m)
                        {
                            m = c;
                            I = i;
                        }
                    }
                }
                // cout << "I = " << I << ", m = " << m << endl;
                a[I] = m;
                u = m;
            }
            return u;
        }
        int nthUglyNumber3(int n)
        {
            set<int> ugly;
            set<int> pretty;
            int a = 0;
            vector<int> factor = {2, 3, 5};
            while ((int)ugly.size() < n)
            {
                a++;
                int b = a;
                bool isUgly = false;
                bool isPretty = false;
                for (size_t i = 0; i < factor.size(); i++)
                {
                    while (b % factor[i] == 0)
                    {
                        b /= factor[i];
                        if (ugly.find(b) != ugly.end() || b == 1)
                        {
                            isUgly = true;
                            break;
                        }
                        if (pretty.find(b) != pretty.end())
                        {
                            isPretty = true;
                            break;
                        }
                    }
                    if (isUgly || isPretty)
                        break;
                }
                if (isUgly || b == 1)
                    ugly.insert(a);
                if (isPretty)
                    pretty.insert(a);
            }
            return *ugly.rbegin(); // set is sorted
        }

        // 268. Missing Number
        // Given an array nums containing n distinct numbers in the range [0, n],
        // return the only number in the range that is missing from the array.
        // Follow up: Could you implement a solution using only O(1) extra space
        // complexity and O(n) runtime complexity?
        // Example 1:
        // Input: nums = [3,0,1]
        // Output: 2
        // Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3].
        // 2 is the missing number in the range since it does not appear in nums.
        // Example 2:
        // Input: nums = [0,1]
        // Output: 2
        // Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2].
        // 2 is the missing number in the range since it does not appear in nums.
        // Example 3:
        // Input: nums = [9,6,4,2,3,5,7,0,1]
        // Output: 8
        // Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9].
        // 8 is the missing number in the range since it does not appear in nums.
        // Example 4:
        // Input: nums = [0]
        // Output: 1
        // Explanation: n = 1 since there is 1 number, so all numbers are in the range [0,1].
        // 1 is the missing number in the range since it does not appear in nums.
        // Constraints:
        // n == nums.length
        // 1 <= n <= 10^4
        // 0 <= nums[i] <= n
        // All the numbers of nums are unique.
        int missingNumber(vector<int> &nums)
        {
            int i = 0;
            while (i < (int)nums.size())
            {
                while (nums[i] != i && nums[i] < (int)nums.size())
                {
                    swap(nums[i], nums[nums[i]]);
                }
                i++;
            }
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (nums[i] != i)
                    return i;
            }
            return nums.size();
        }
        int missingNumber2(vector<int> &nums)
        {
            int x = 0;
            int i = 0;
            for (; i < (int)nums.size(); i++)
            {
                x ^= i;
                x ^= nums[i];
            }
            return x ^ i;
        }

        // 273. Integer to English Words
        // Convert a non-negative integer num to its English words representation.
        // Example 1:
        // Input: num = 123
        // Output: "One Hundred Twenty Three"
        // Example 2:
        // Input: num = 12345
        // Output: "Twelve Thousand Three Hundred Forty Five"
        // Example 3:
        // Input: num = 1234567
        // Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
        // Example 4:
        // Input: num = 1234567891
        // Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
        // Constraints:
        // 0 <= num <= 2^31 - 1
        string numberToWords(int num)
        {
            if (num == 0)
                return "Zero";
            int n1 = num % 1000;
            num /= 1000;
            int n2 = num % 1000;
            num /= 1000;
            int n3 = num % 1000;
            num /= 1000;
            int n4 = num % 1000;
            ostringstream oss;
            vector<string> lt20 = {
                "One",
                "Two",
                "Three",
                "Four",
                "Five",
                "Six",
                "Seven",
                "Eight",
                "Nine",
                "Ten",
                "Eleven",
                "Twelve",
                "Thirteen",
                "Fourteen",
                "Fifteen",
                "Sixteen",
                "Seventeen",
                "Eighteen",
                "Nineteen"};
            vector<string> tens = {
                "Twenty",
                "Thirty",
                "Forty",
                "Fifty",
                "Sixty",
                "Seventy",
                "Eighty",
                "Ninety"};
            function<void(int)> convert = [&](int n)
            {
                int h = n / 100;
                if (h > 0)
                    oss << lt20[h - 1] << " Hundred";
                n %= 100;
                if (n == 0)
                    return;
                if (h > 0)
                    oss << " ";
                if (n < 20)
                {
                    oss << lt20[n - 1];
                }
                else
                {
                    oss << tens[n / 10 - 2];
                    n %= 10;
                    if (n > 0)
                        oss << " " << lt20[n - 1];
                }
            };
            if (n4 > 0)
            {
                convert(n4);
                oss << " Billion";
            }
            if (n3 > 0)
            {
                if (n4 > 0)
                    oss << " ";
                convert(n3);
                oss << " Million";
            }
            if (n2 > 0)
            {
                if (n4 > 0 || n3 > 0)
                    oss << " ";
                convert(n2);
                oss << " Thousand";
            }
            if (n1 > 0)
            {
                if (n4 > 0 || n3 > 0 || n2 > 0)
                    oss << " ";
                convert(n1);
            }
            return oss.str();
        }

        // 274. H-Index
        // Given an array of citations (each citation is a non-negative integer)
        // of a researcher, write a function to compute the researcher's h-index.
        // According to the definition of h-index on Wikipedia: "A scientist has
        // index h if h of his/her N papers have at least h citations each, and
        // the other N − h papers have no more than h citations each."
        // Example:
        // Input: citations = [3,0,6,1,5]
        // Output: 3
        // Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and
        // each of them had received 3, 0, 6, 1, 5 citations respectively. Since the
        // researcher has 3 papers with at least 3 citations each and the remaining
        // two with no more than 3 citations each, her h-index is 3.
        // Note: If there are several possible values for h, the maximum one is taken
        // as the h-index.
        int hIndex(vector<int> &citations)
        {
            sort(citations.begin(), citations.end(), [&](int x, int y) -> bool
                 { return x > y; });
            int h = 0;
            for (; h < (int)citations.size(); h++)
            {
                if (citations[h] < (h + 1))
                    break;
            }
            return h;
        }
        int hIndex2(vector<int> &citations)
        {
            int m = 0;
            for (int c : citations)
            {
                if (c > m)
                    m = c;
            }
            vector<int> count(m + 1, 0);
            for (int c : citations)
            {
                count[c]++;
            }
            int h = 0;
            for (int i = m - 1; i >= 0; i--)
            {
                // count[i] is the number of papers having at least i citations
                count[i] += count[i + 1];
            }
            m = min(m, (int)citations.size());
            for (int i = 0; i <= m; i++)
            {
                if (count[i] >= i)
                    h = i;
            }
            return h;
        }

        // 275. H-Index II
        // Given an array of citations sorted in ascending order (each citation is a
        // non-negative integer) of a researcher, write a function to compute the
        // researcher's h-index.
        // According to the definition of h-index on Wikipedia: "A scientist has index
        // h if h of his/her N papers have at least h citations each, and the other
        // N − h papers have no more than h citations each."
        // Example:
        // Input: citations = [0,1,3,5,6]
        // Output: 3
        // Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each
        // of them had received 0, 1, 3, 5, 6 citations respectively. Since the researcher
        // has 3 papers with at least 3 citations each and the remaining two with no more
        // than 3 citations each, her h-index is 3.
        // Note:
        // If there are several possible values for h, the maximum one is taken as the h-index.
        // Follow up:
        // This is a follow up problem to H-Index, where citations is now guaranteed to
        // be sorted in ascending order.
        // Could you solve it in logarithmic time complexity?
        int hIndexII(vector<int> &citations)
        {
            if (citations.empty())
                return 0;
            int n = citations.size();
            int l = 0;
            int h = n - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (citations[m] < (n - m))
                    l = m + 1;
                else
                    h = m;
            }
            if (citations[h] >= (n - h))
                return n - h;
            return n - h - 1;
        }

        // 278. First Bad Version
        // You are a product manager and currently leading a team to develop a new
        // product. Unfortunately, the latest version of your product fails the quality
        // check. Since each version is developed based on the previous version, all the
        // versions after a bad version are also bad. Suppose you have n versions [1, 2,
        // ..., n] and you want to find out the first bad one, which causes all the
        // following ones to be bad. You are given an API bool isBadVersion(version)
        // which will return whether version is bad. Implement a function to find the
        // first bad version. You should minimize the number of calls to the API.
        // Example:
        // Given n = 5, and version = 4 is the first bad version.
        // call isBadVersion(3) -> false
        // call isBadVersion(5) -> true
        // call isBadVersion(4) -> true
        // Then 4 is the first bad version.
        bool isBadVersion(int v) { return v >= 0; }
        int firstBadVersion(int n)
        {
            int b = 1;
            int e = n;
            while (b <= e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                {
                    if (b == e)
                        return m;
                    e = m;
                }
                else
                {
                    b = m + 1;
                }
            }
            throw runtime_error("not found");
        }
        int firstBadVersion2(int n)
        {
            int b = 1;
            int e = n;
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                    e = m;
                else
                    b = m + 1;
            }
            // Assume there must be a bad version
            // e.g., when the bad version is n.
            return b;
        }
        int firstBadVersion3(int n)
        {
            int b = 1;
            int e = n;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                    e = m;
                else
                    b = m;
            }
            if (isBadVersion(b))
                return b;
            if (isBadVersion(e))
                return e;
            throw runtime_error("not found");
        }

        // 279. Perfect Squares
        // Given a positive integer n, find the least number of perfect square numbers
        // (for example, 1, 4, 9, 16, ...) which sum to n.
        // Example 1:
        // Input: n = 12
        // Output: 3
        // Explanation: 12 = 4 + 4 + 4.
        // Example 2:
        // Input: n = 13
        // Output: 2
        // Explanation: 13 = 4 + 9.
        int numSquares(int n)
        {
            set<int> visited;
            queue<int> current;
            current.push(n);
            visited.insert(n);
            queue<int> next;
            int c = 0;
            while (!current.empty())
            {
                while (!current.empty())
                {
                    n = current.front();
                    current.pop();
                    int s = (int)sqrt(n);
                    for (int i = 1; i <= s; i++)
                    {
                        int i2 = i * i;
                        if (i2 == n)
                            return c + 1;
                        i2 = n - i2;
                        if (visited.find(i2) == visited.end())
                        {
                            next.push(i2);
                            visited.insert(i2);
                        }
                    }
                }
                c++;
                current.swap(next);
            }
            throw runtime_error("not found");
        }

        // 282. Expression Add Operators
        // Given a string that contains only digits 0-9 and a target value,
        // return all possibilities to add binary operators (not unary) +, -,
        // or * between the digits so they evaluate to the target value.
        // Example 1:
        // Input: num = "123", target = 6
        // Output: ["1+2+3", "1*2*3"]
        // Example 2:
        // Input: num = "232", target = 8
        // Output: ["2*3+2", "2+3*2"]
        // Example 3:
        // Input: num = "105", target = 5
        // Output: ["1*0+5","10-5"]
        // Example 4:
        // Input: num = "00", target = 0
        // Output: ["0+0", "0-0", "0*0"]
        // Example 5:
        // Input: num = "3456237490", target = 9191
        // Output: []
        // Constraints:
        // 0 <= num.length <= 10
        // num only contain digits.
        // Think carefully about the multiply operator. It has a higher precedence
        // than the addition and subtraction operators.
        // 1 + 2 = 3
        // 1 + 2 - 4 --> 3 - 4 --> -1
        // 1 + 2 - 4 * 12 --> -1 * 12 --> -12 (WRONG!)
        // 1 + 2 - 4 * 12 --> -1 - (-4) + (-4 * 12) --> 3 + (-48) --> -45 (CORRECT!)
        vector<string> addOperators(string num, int target)
        {
            vector<string> output;
            // use long long instead of int to handle case 2147483648
            // (long long)2147483648 = (int)-2147483648
            function<void(int, const string &, long long, long long)> solve =
                [&](int i, const string &expression, long long total, long long prev)
            {
                cout << string(i, ' ') << "solve(" << i << ", " << expression << ", " << total << ", " << prev << ")" << endl;
                if (i >= (int)num.size())
                {
                    if (total == target)
                    {
                        cout << string(i, ' ') << "output '" << expression << "'" << endl;
                        output.push_back(expression);
                    }
                    return;
                }
                long long c = 0;
                for (int j = i; j < (int)num.size(); j++)
                {
                    cout << string(i, ' ') << i << ".." << j << endl;
                    c = 10 * c + num[j] - '0';
                    string s = to_string(c);
                    if (i == 0)
                    {
                        solve(j + 1, s, c, c);
                    }
                    else
                    {
                        solve(j + 1, expression + "+" + s, total + c, c);
                        solve(j + 1, expression + "-" + s, total - c, -c);
                        long long c1 = prev * c;
                        solve(j + 1, expression + "*" + s, total - prev + c1, c1);
                    }
                    if (num[i] == '0')
                        break;
                }
            };
            solve(0, "", 0, 0);
            return output;
        }

        // 283. Move Zeroes
        // Given an array nums, write a function to move all 0's to the end of it while
        // maintaining the relative order of the non-zero elements. Example:
        // Input: [0,1,0,3,12]
        // Output: [1,3,12,0,0]
        // Note: You must do this in-place without making a copy of the array.
        // Minimize the total number of operations.
        void moveZeroes(vector<int> &nums)
        {
            int i = -1;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                if (nums[j] != 0)
                {
                    if (++i < j)
                        swap(nums[i], nums[j]);
                }
            }
        }
        void moveZeroes2(vector<int> &nums)
        {
            int i = -1;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                if (nums[j] != 0)
                {
                    i++;
                    if (i < j)
                        nums[i] = nums[j];
                }
            }
            for (i++; i < (int)nums.size(); i++)
                nums[i] = 0;
        }

        namespace Problem284
        {
            // 284. Peeking Iterator
            // Design an iterator that supports the peek operation on a list in addition
            // to the hasNext and the next operations.
            // Implement the PeekingIterator class:
            // PeekingIterator(int[] nums) Initializes the object with the given integer array nums.
            // int next() Returns the next element in the array and moves the pointer to thenext element.
            // bool hasNext() Returns true if there are still elements in the array.
            // int peek() Returns the next element in the array without moving the pointer.
            // Example 1:
            // Input
            // ["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
            // [[[1, 2, 3]], [], [], [], [], []]
            // Output
            // [null, 1, 2, 2, 3, false]
            // Explanation
            // PeekingIterator peekingIterator = new PeekingIterator([1, 2, 3]); // [1,2,3]
            // peekingIterator.next();    // return 1, the pointer moves to the next element [1,2,3].
            // peekingIterator.peek();    // return 2, the pointer does not move [1,2,3].
            // peekingIterator.next();    // return 2, the pointer moves to the next element [1,2,3]
            // peekingIterator.next();    // return 3, the pointer moves to the next element [1,2,3]
            // peekingIterator.hasNext(); // return False
            // Constraints:
            // 1 <= nums.length <= 1000
            // 1 <= nums[i] <= 1000
            // All the calls to next and peek are valid.
            // At most 1000 calls will be made to next, hasNext, and peek.
            // Follow up: How would you extend your design to be generic and work with all types,
            // not just integer?
            // Below is the interface for Iterator, which is already defined for you.
            // **DO NOT** modify the interface for Iterator.
            class Iterator
            {
                struct Data;
                Data *data;

            public:
                Iterator(const vector<int> &nums);
                Iterator(const Iterator &iter);
                // Returns the next element in the iteration.
                int next();
                // Returns true if the iteration has more elements.
                bool hasNext() const;
            };
            class PeekingIterator : public Iterator
            {
            private:
                bool peeked;
                int pnext;

            public:
                PeekingIterator(const vector<int> &nums) : Iterator(nums)
                {
                    // Initialize any member here.
                    // **DO NOT** save a copy of nums and manipulate it directly.
                    // You should only use the Iterator interface methods.
                    peeked = false;
                }
                // Returns the next element in the iteration without advancing the iterator.
                int peek()
                {
                    if (!peeked)
                    {
                        pnext = Iterator::next();
                        peeked = true;
                    }
                    return pnext;
                }
                // hasNext() and next() should behave the same as in the Iterator interface.
                // Override them if needed.
                int next()
                {
                    if (!peeked)
                    {
                        return Iterator::next();
                    }
                    else
                    {
                        peeked = false;
                        return pnext;
                    }
                }
                bool hasNext() const
                {
                    return peeked || Iterator::hasNext();
                }
            };
        } // Problem284

        // 287. Find the Duplicate Number
        // Given an array nums containing n + 1 integers where each integer is between 1
        // and n (inclusive), prove that at least one duplicate number must exist.
        // Assume that there is only one duplicate number, find the duplicate one.
        // Example 1:
        // Input: [1,3,4,2,2]
        // Output: 2
        // Example 2:
        // Input: [3,1,3,4,2]
        // Output: 3
        // Note:
        // You must not modify the array (assume the array is read only).
        // You must use only constant, O(1) extra space.
        // Your runtime complexity should be less than O(n2).
        // There is only one duplicate number in the array, but it could be repeated
        // more than once. The first two approaches mentioned do not satisfy the
        // constraints given in the prompt, but they are solutions that you might be
        // likely to come up with during a technical interview. As an interviewer, I
        // personally would not expect someone to come up with the cycle detection
        // solution unless they have heard it before. Proof Proving that at least one
        // duplicate must exist in nums is simple application of the pigeonhole
        // principle. Here, each number in nums is a "pigeon" and each distinct number
        // that can appear in nums is a "pigeonhole". Because there are n+1 numbers are
        // nnn distinct possible numbers, the pigeonhole principle implies that at least
        // one of the numbers is duplicated. Approach #3 Floyd's Tortoise and Hare
        // (Cycle Detection) [Accepted] Intuition If we interpret nums such that for
        // each pair of index i and value v_i, the "next" value v_j​ is at index
        // v_i​, we can reduce this problem to cycle detection. See the solution to
        // Linked List Cycle II for more details. Algorithm First off, we can easily
        // show that the constraints of the problem imply that a cycle must exist.
        // Because each number in nums is between 1 and n, it will necessarily point to
        // an index that exists. Therefore, the list can be traversed infinitely, which
        // implies that there is a cycle. Additionally, because 0 cannot appear as a
        // value in nums, nums[0] cannot be part of the cycle. Therefore, traversing the
        // array in this manner from nums[0] is equivalent to traversing a cyclic linked
        // list. Given this, the problem can be solved just like Linked List Cycle II.
        int findDuplicate(const vector<int> &nums)
        {
            int i = nums[0];
            int j = nums[0];
            do
            {
                i = nums[i];
                j = nums[nums[j]];
            } while (i != j);
            i = nums[0];
            while (i != j)
            {
                i = nums[i];
                j = nums[j];
            }
            return i;
        }
        int findDuplicate2(vector<int> &nums)
        {
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (nums[i] != i + 1)
                {
                    int j = nums[i] - 1;
                    if (nums[i] == nums[j])
                        return nums[i];
                    swap(nums[i], nums[j]);
                }
            }
            throw runtime_error("Duplicate not found");
        }
        int findDuplicate3(vector<int> &nums)
        {
            while (nums[0] != nums[nums[0]])
                swap(nums[0], nums[nums[0]]);
            return nums[0];
        }
        int findDuplicate4(const vector<int> &nums)
        {
            set<int> s;
            int i = 0;
            while (s.find(nums[i]) == s.end())
            {
                s.insert(nums[i]);
                i = nums[i];
            }
            return nums[i];
        }
        int findDuplicate5(const vector<int> &nums)
        {
            set<int> s;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (s.find(nums[i]) == s.end())
                    s.insert(nums[i]);
                else
                    return nums[i];
            }
            throw runtime_error("Duplicate not found");
        }

        // 289. Game of Life
        // According to Wikipedia's article: "The Game of Life, also known simply as Life,
        // is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
        // The board is made up of an m x n grid of cells, where each cell has an initial
        // state: live (represented by a 1) or dead (represented by a 0). Each cell interacts
        // with its eight neighbors (horizontal, vertical, diagonal) using the following four
        // rules (taken from the above Wikipedia article):
        // Any live cell with fewer than two live neighbors dies as if caused by under-population.
        // Any live cell with two or three live neighbors lives on to the next generation.
        // Any live cell with more than three live neighbors dies, as if by over-population.
        // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
        // The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the m x n grid board, return the next state.
        // Example 1:
        // Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
        // Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
        // Example 2:
        // Input: board = [[1,1],[1,0]]
        // Output: [[1,1],[1,1]]
        // Constraints:
        // m == board.length
        // n == board[i].length
        // 1 <= m, n <= 25
        // board[i][j] is 0 or 1.
        // Follow up:
        // Could you solve it in-place? Remember that the board needs to be updated simultaneously:
        // You cannot update some cells first and then use their updated values to update other cells.
        // In this question, we represent the board using a 2D array. In principle, the board is
        // infinite, which would cause problems when the active area encroaches upon the border of
        // the array (i.e., live cells reach the border). How would you address these problems?
        void gameOfLife(vector<vector<int>> &board)
        {
            if (board.empty() || board[0].empty())
                return;
            int m = board.size();
            int n = board[0].size();
            set<pair<int, int>> updated;
            function<int(int, int)> isLive = [&](int i, int j) -> int
            {
                if (0 <= i && i < m && 0 <= j && j < n)
                {
                    auto p = make_pair(i, j);
                    if (updated.find(p) == updated.end())
                        return board[i][j];
                    else
                        return 1 - board[i][j];
                }
                return 0;
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    int c = 0;
                    c += isLive(i - 1, j - 1);
                    c += isLive(i - 1, j);
                    c += isLive(i - 1, j + 1);
                    c += isLive(i, j - 1);
                    c += isLive(i, j + 1);
                    c += isLive(i + 1, j - 1);
                    c += isLive(i + 1, j);
                    c += isLive(i + 1, j + 1);
                    if (board[i][j] == 1)
                    {
                        if (c < 2 || c > 3)
                        {
                            board[i][j] = 0;
                            updated.insert(make_pair(i, j));
                        }
                    }
                    else
                    {
                        if (c == 3)
                        {
                            board[i][j] = 1;
                            updated.insert(make_pair(i, j));
                        }
                    }
                }
            }
        }
        void gameOfLife2(vector<vector<int>> &board)
        {
            if (board.empty() || board[0].empty())
                return;
            int m = board.size();
            int n = board[0].size();
            function<int(int, int)> isLive = [&](int i, int j) -> int
            {
                if (0 <= i && i < m && 0 <= j && j < n)
                {
                    if (board[i][j] == 1 || board[i][j] == -1)
                        return 1;
                    else if (board[i][j] == 0 || board[i][j] == 2)
                        return 0;
                }
                return 0;
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    int c = 0;
                    c += isLive(i - 1, j - 1);
                    c += isLive(i - 1, j);
                    c += isLive(i - 1, j + 1);
                    c += isLive(i, j - 1);
                    c += isLive(i, j + 1);
                    c += isLive(i + 1, j - 1);
                    c += isLive(i + 1, j);
                    c += isLive(i + 1, j + 1);
                    if (board[i][j] == 1)
                    {
                        if (c < 2 || c > 3)
                        {
                            board[i][j] = -1;
                        }
                    }
                    else
                    {
                        if (c == 3)
                        {
                            board[i][j] = 2;
                        }
                    }
                }
            }
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j] == -1)
                        board[i][j] = 0;
                    else if (board[i][j] == 2)
                        board[i][j] = 1;
                }
            }
        }

        // 290. Word Pattern
        // Given a pattern and a string s, find if s follows the same pattern.
        // Here follow means a full match, such that there is a bijection between
        // a letter in pattern and a non-empty word in s.
        // Example 1:
        // Input: pattern = "abba", s = "dog cat cat dog"
        // Output: true
        // Example 2:
        // Input: pattern = "abba", s = "dog cat cat fish"
        // Output: false
        // Example 3:
        // Input: pattern = "aaaa", s = "dog cat cat dog"
        // Output: false
        // Example 4:
        // Input: pattern = "abba", s = "dog dog dog dog"
        // Output: false
        // Constraints:
        // 1 <= pattern.length <= 300
        // pattern contains only lower-case English letters.
        // 1 <= s.length <= 3000
        // s contains only lower-case English letters and spaces ' '.
        // s does not contain any leading or trailing spaces.
        // All the words in s are separated by a single space.
        bool wordPattern(string pattern, string s)
        {
            map<char, int> m;
            map<string, int> n;
            int i = 0;
            int j = 0;
            while (i < (int)pattern.size() && j < (int)s.size())
            {
                if (m.find(pattern[i]) == m.end())
                {
                    m[pattern[i]] = j;
                    while (j < (int)s.size() && s[j] != ' ')
                        j++;
                    string t = s.substr(m[pattern[i]], j - m[pattern[i]]);
                    if (n.find(t) != n.end())
                        return false;
                    n[t] = i;
                }
                else
                {
                    int p = m[pattern[i]];
                    int k = j;
                    while (j < (int)s.size() && s[j] != ' ')
                    {
                        if (s[p] != s[j])
                            return false;
                        p++;
                        j++;
                    }
                    if (s[p] != ' ')
                        return false;
                    string t = s.substr(k, j - k);
                    if (n.find(t) == n.end())
                        return false;
                    if (pattern[n[t]] != pattern[i])
                        return false;
                }
                i++;
                if (j < (int)s.size())
                    j++;
            }
            return i == (int)pattern.size() && j == (int)s.size();
        }

        // 292. Nim Game
        // You are playing the following Nim Game with your friend:
        // Initially, there is a heap of stones on the table.
        // You and your friend will alternate taking turns, and you go first.
        // On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
        // The one who removes the last stone is the winner.
        // Given n, the number of stones in the heap, return true if you can win the game
        // assuming both you and your friend play optimally, otherwise return false.
        // Example 1:
        // Input: n = 4
        // Output: false
        // Explanation: These are the possible outcomes:
        // 1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
        // 2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
        // 3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
        // In all outcomes, your friend wins.
        // Example 2:
        // Input: n = 1
        // Output: true
        // Example 3:
        // Input: n = 2
        // Output: true
        // Constraints:
        // 1 <= n <= 2^31 - 1
        bool canWinNim(int n)
        {
            return (n % 4) != 0;
        }
        bool canWinNim2(int n)
        {
            return (n & 3) != 0;
        }

        // 295. Find Median from Data Stream
        // Median is the middle value in an ordered integer list.
        // If the size of the list is even, there is no middle value.
        // So the median is the mean of the two middle value.
        // For example,
        // [2,3,4], the median is 3
        // [2,3], the median is (2 + 3) / 2 = 2.5
        // Design a data structure that supports the following two operations:
        // void addNum(int num) - Add a integer number from the data stream to the data structure.
        // double findMedian() - Return the median of all elements so far.
        // Example:
        // addNum(1)
        // addNum(2)
        // findMedian() -> 1.5
        // addNum(3)
        // findMedian() -> 2
        // Follow up:
        // If all integer numbers from the stream are between 0 and 100, how would you optimize it?
        // If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
        class MedianFinder
        {
        private:
            unsigned long long count;
            int median;
            vector<int> low;
            vector<int> high;
            function<bool(int, int)> less;

        public:
            MedianFinder()
            {
                count = 0;
                less = [&](int x, int y) -> bool
                { return x > y; };
            }
            void addNum(int num)
            {
                if ((count & 1) == 0)
                {
                    if (!low.empty() && num < low.front())
                    {
                        pop_heap(low.begin(), low.end());
                        median = low.back();
                        low.pop_back();
                        low.push_back(num);
                        push_heap(low.begin(), low.end());
                    }
                    else if (!high.empty() && num > high.front())
                    {
                        pop_heap(high.begin(), high.end(), less);
                        median = high.back();
                        high.pop_back();
                        high.push_back(num);
                        push_heap(high.begin(), high.end(), less);
                    }
                    else
                    {
                        median = num;
                    }
                }
                else
                {
                    if (num < median)
                    {
                        low.push_back(num);
                        push_heap(low.begin(), low.end());
                        high.push_back(median);
                        push_heap(high.begin(), high.end(), less);
                    }
                    else
                    {
                        low.push_back(median);
                        push_heap(low.begin(), low.end());
                        high.push_back(num);
                        push_heap(high.begin(), high.end(), less);
                    }
                    median = 0;
                }
                count++;
            }
            double findMedian()
            {
                if ((count & 1) == 0)
                    return (low.front() + high.front()) / 2.0;
                else
                    return median;
            }
        };

        class Codec
        {
        public:
            // 297. Serialize and Deserialize Binary Tree
            // Serialization is the process of converting a data structure or object into a
            // sequence of bits so that it can be stored in a file or memory buffer, or
            // transmitted across a network connection link to be reconstructed later in the
            // same or another computer environment. Design an algorithm to serialize and
            // deserialize a binary tree. There is no restriction on how your
            // serialization/deserialization algorithm should work. You just need to ensure
            // that a binary tree can be serialized to a string and this string can be
            // deserialized to the original tree structure. Example: You may serialize the
            // following tree:
            //     1
            //    / \
            //   2   3
            //      / \
            //     4   5
            // as "[1,2,3,null,null,4,5]"
            // Clarification: The above format is the same as how LeetCode serializes a
            // binary tree. You do not necessarily need to follow this format, so please be
            // creative and come up with different approaches yourself. Note: Do not use
            // class member/global/static variables to store states. Your serialize and
            // deserialize algorithms should be stateless. Encodes a tree to a single
            // string.
            static string serialize(TreeNode *root)
            {
                ostringstream oss;
                function<void(TreeNode *)> solve = [&](TreeNode *n)
                {
                    if (n == nullptr)
                    {
                        oss << "#";
                        return;
                    }
                    oss << n->val << ",";
                    solve(n->left);
                    oss << ",";
                    solve(n->right);
                };
                solve(root);
                return oss.str();
            }
            // Decodes your encoded data to tree.
            static TreeNode *deserialize(string data)
            {
                size_t i = 0;
                function<TreeNode *()> solve = [&]() -> TreeNode *
                {
                    size_t j = data.find(',', i);
                    string s = data.substr(i, j - i);
                    i = j + 1;
                    if (s.compare("#") == 0)
                        return nullptr;
                    int v = stoi(s);
                    TreeNode *n = new TreeNode(v);
                    n->left = solve();
                    n->right = solve();
                    return n;
                };
                return solve();
            }
        };
        class Codec2
        {
        public:
            // Encodes a tree to a single string.
            static string serialize(TreeNode *root)
            {
                ostringstream oss;
                if (root == nullptr)
                    return oss.str();
                queue<TreeNode *> q[2];
                q[0].push(root);
                int l = 0;
                bool first = true;
                while (!q[0].empty() || !q[1].empty())
                {
                    queue<TreeNode *> &current = q[l % 2];
                    queue<TreeNode *> &next = q[(l + 1) % 2];
                    bool nextAllNulls = true;
                    while (!current.empty())
                    {
                        TreeNode *n = current.front();
                        current.pop();
                        if (!first)
                            oss << ",";
                        if (n == nullptr)
                            oss << "#";
                        else
                            oss << n->val;
                        if (first)
                            first = false;
                        if (n != nullptr)
                        {
                            next.push(n->left);
                            next.push(n->right);
                            nextAllNulls &= (n->left == nullptr && n->right == nullptr);
                        }
                    }
                    if (nextAllNulls)
                        break;
                    else
                        l++;
                }
                return oss.str();
            }
            // Decodes your encoded data to tree.
            static TreeNode *deserialize(string data)
            {
                if (data.empty())
                    return nullptr;
                size_t i = 0;
                size_t j = data.find(",", i);
                TreeNode *root;
                if (j == string::npos)
                {
                    root = new TreeNode(stoi(data.substr(i)));
                    i = data.size();
                }
                else
                {
                    root = new TreeNode(stoi(data.substr(i, j - i)));
                    i = j + 1;
                }
                queue<TreeNode *> q;
                q.push(root);
                while (!q.empty() && i < data.size())
                {
                    TreeNode *n = q.front();
                    q.pop();
                    if (data[i] == '#')
                    {
                        n->left = nullptr;
                        i += 2;
                    }
                    else
                    {
                        j = data.find(",", i);
                        if (j == string::npos)
                        {
                            n->left = new TreeNode(stoi(data.substr(i)));
                            i = data.size();
                        }
                        else
                        {
                            n->left = new TreeNode(stoi(data.substr(i, j - i)));
                            i = j + 1;
                        }
                        q.push(n->left);
                    }
                    if (i >= data.size())
                        break;
                    if (data[i] == '#')
                    {
                        n->right = nullptr;
                        i += 2;
                    }
                    else
                    {
                        j = data.find(",", i);
                        if (j == string::npos)
                        {
                            n->right = new TreeNode(stoi(data.substr(i)));
                            i = data.size();
                        }
                        else
                        {
                            n->right = new TreeNode(stoi(data.substr(i, j - i)));
                            i = j + 1;
                        }
                        q.push(n->right);
                    }
                }
                return root;
            }
        };

        // 299. Bulls and Cows
        // You are playing the Bulls and Cows game with your friend.
        // You write down a secret number and ask your friend to guess what the number is.
        // When your friend makes a guess, you provide a hint with the following info:
        // The number of "bulls", which are digits in the guess that are in the correct position.
        // The number of "cows", which are digits in the guess that are in your secret number
        // but are located in the wrong position. Specifically, the non-bull digits in the guess
        // that could be rearranged such that they become bulls.
        // Given the secret number secret and your friend's guess guess, return the hint for
        // your friend's guess.
        // The hint should be formatted as "xAyB", where x is the number of bulls and y is
        // the number of cows. Note that both secret and guess may contain duplicate digits.
        // Example 1:
        // Input: secret = "1807", guess = "7810"
        // Output: "1A3B"
        // Explanation: Bulls are connected with a '|' and cows are underlined:
        // "1807"
        //   |
        // "7810"
        // Example 2:
        // Input: secret = "1123", guess = "0111"
        // Output: "1A1B"
        // Explanation: Bulls are connected with a '|' and cows are underlined:
        // "1123"        "1123"
        //   |      or     |
        // "0111"        "0111"
        // Note that only one of the two unmatched 1s is counted as a cow since the non-bull digits
        // can only be rearranged to allow one 1 to be a bull.
        // Example 3:
        // Input: secret = "1", guess = "0"
        // Output: "0A0B"
        // Example 4:
        // Input: secret = "1", guess = "1"
        // Output: "1A0B"
        // Constraints:
        // 1 <= secret.length, guess.length <= 1000
        // secret.length == guess.length
        // secret and guess consist of digits only.
        string getHint(string secret, string guess)
        {
            map<char, int> s;
            map<char, int> g;
            int a = 0;
            for (size_t i = 0; i < guess.size(); i++)
            {
                if (guess[i] == secret[i])
                {
                    a++;
                }
                else
                {
                    if (s.find(secret[i]) == s.end())
                        s[secret[i]] = 1;
                    else
                        s[secret[i]]++;
                    if (g.find(guess[i]) == g.end())
                        g[guess[i]] = 1;
                    else
                        g[guess[i]]++;
                }
            }
            int b = 0;
            for (const auto &p : g)
            {
                if (s.find(p.first) != s.end())
                    b += min(s[p.first], p.second);
            }
            ostringstream oss;
            oss << a << "A" << b << "B";
            return oss.str();
        }

        // 300. Longest Increasing Subsequence
        // Given an integer array nums, return the length of the longest strictly
        // increasing subsequence. A subsequence is a sequence that can be derived
        // from an array by deleting some or no elements without changing the order
        // of the remaining elements. For example, [3,6,2,7] is a subsequence of
        // the array [0,3,1,6,2,2,7].
        // Example 1:
        // Input: nums = [10,9,2,5,3,7,101,18]
        // Output: 4
        // Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
        // Example 2:
        // Input: nums = [0,1,0,3,2,3]
        // Output: 4
        // Example 3:
        // Input: nums = [7,7,7,7,7,7,7]
        // Output: 1
        // Constraints:
        // 1 <= nums.length <= 2500
        // -10^4 <= nums[i] <= 10^4
        // Follow up:
        // Could you come up with the O(n2) solution?
        // Could you improve it to O(n log(n)) time complexity?
        int lengthOfLIS(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            vector<int> l(nums.size(), 0);
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                int t = 0;
                for (size_t j = 0; j < i; j++)
                {
                    if (nums[j] < nums[i])
                        t = max(t, l[j]);
                }
                l[i] = t + 1;
                m = max(m, l[i]);
            }
            return m;
        }
        int lengthOfLIS2(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            vector<int> m(1, 0);
            for (int i = 1; i < (int)nums.size(); i++)
            {
                int l = 0;
                int h = m.size();
                // loop invariant nums[m[l]] < nums[i] <= nums[m[h]]
                while (l < h)
                {
                    int t = l + ((h - l) >> 1);
                    if (nums[m[t]] < nums[i])
                        l = t + 1;
                    else
                        h = t;
                }
                if (l == (int)m.size())
                {
                    m.push_back(i);
                }
                else // nums[i] <= nums[m[l]]
                {
                    m[l] = i;
                }
            }
            return m.size();
        }
        int lengthOfLIS3(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            function<int(int, int, int)> lis = [&](int i, int p, int l) -> int
            {
                if (i >= (int)nums.size())
                    return l;
                int l1 = 0;
                if (p < 0 || nums[p] < nums[i])
                    l1 = lis(i + 1, i, l + 1);
                int l2 = lis(i + 1, p, l);
                return max(l1, l2);
            };
            return lis(0, -1, 0);
        }
        int lengthOfLIS4(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            function<int(int, int)> lis = [&](int i, int p) -> int
            {
                if (i >= (int)nums.size())
                    return 0;
                int l1 = 0;
                if (p < 0 || nums[p] < nums[i])
                    l1 = 1 + lis(i + 1, i);
                int l2 = lis(i + 1, p);
                return max(l1, l2);
            };
            return lis(0, -1);
        }
        // Wrong
        // Input [10,9,2,5,3,7,101,18]
        // Output 3
        // Expected 4
        int lengthOfLIS5(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            map<pair<int, int>, int> m;
            function<int(int, int, int)> lis = [&](int i, int p, int l) -> int
            {
                // cout << string(i, ' ') << "(" << i << "," << p << "," << l << ")" << endl;
                pair<int, int> t = make_pair(i, p);
                if (m.find(t) != m.end())
                    return m[t];
                if (i >= (int)nums.size())
                {
                    m[t] = l;
                }
                else
                {
                    int l1 = 0;
                    if (p < 0 || nums[p] < nums[i])
                    {
                        cout << string(i, ' ') << "(" << i << "," << p << "," << l << ")";
                        cout << " => (" << i + 1 << "," << i << "," << l + 1 << ")" << endl;
                        l1 = lis(i + 1, i, l + 1);
                    }
                    cout << string(i, ' ') << "(" << i << "," << p << "," << l << ")";
                    cout << " => (" << i + 1 << "," << p << "," << l << ")" << endl;
                    int l2 = lis(i + 1, p, l);
                    m[t] = max(l1, l2);
                }
                return m[t];
            };
            return lis(0, -1, 0);
        }
        // https://en.wikipedia.org/wiki/Longest_increasing_subsequence
        // For each i, compute M[j], j = 0, 1, 2, 3, ......, i
        // which traks the indices of the minimum ending elements of all increasing subsequences of length j+1.
        // So M[j] tracks the increasing subsequence of length j+1 that is most likely to be extended
        // when scanning the rest of elements in I.
        // At i, there may be multiple longest subsequenes of the same length L, e.g.,
        // Given sequence {1, 0, 3, 2, 5, 4, 7, 6}, there are multiple longest subsequences at each i > 0
        // i = 3,
        // {1, 3}
        // {0, 3}
        // {1, 2}
        // {0, 2}
        // so 3 and 2 are the ending elements of length 2 at i = 3. We want to track 2 because it will be
        // easier to extend the subsequences ending with 2 than those ending with 3.
        // At i = 3, the longest length is 2, so set M[1] = 3 (the index of 2).
        // If L is the length of longest increasing subsequence up to I[i] (0 <= L-1 <= i),
        // then M[0] < M[1] < M[2] < ...... < M[L-1] <= i
        static void LongestIncreasingSubsequence(int *input, int length)
        {
            if (input == nullptr || length <= 0)
                return;
            cout << "Input:";
            for (int i = 0; i < length; i++)
            {
                cout << " " << input[i];
            }
            cout << endl;
            unique_ptr<int[]> m(new int[length]);
            unique_ptr<int[]> p(new int[length]);
            int L = 1; // The length of longest increasing subsequence so far
            m[0] = 0;  // Longest length 1 is achieved at index 0
            p[0] = -1; // Previous element in the increasing subsequence
            for (int i = 1; i < length; i++)
            {
                // Out of {m[0], m[1], ..., m[L-1]}, find the longest m[j-1] which can be extended by input[i]
                // Should have used binary search.
                int j = L;
                while (j > 0 && input[i] <= input[m[j - 1]])
                    j--;

                if (j > 0)
                {
                    // input[m[j-1]] < input[i]
                    // So input[i] extends the increasing subsequence ending at m[j-1]
                    // and previous element is at m[j-1]
                    p[i] = m[j - 1];
                }
                else // j == 0
                {
                    // input[i] does not extend any increasing subsequence so far
                    // no previous element
                    p[i] = -1;
                }

                if (j == L)
                {
                    // If j == L, then input[m[L-1]] < input[i]
                    // input[i] is the first element to end an increasing subsequence of
                    // length L + 1
                    m[j] = i;
                    L++;
                }
                else if (input[i] < input[m[j]])
                {
                    // (1). 0 < j < L, and input[m[j-1]] < input[i] < input[m[j]]
                    // (2). j == 0, input[i] < input[m[0]]
                    // input[i] extends the increasing subsequence of length j ending at
                    // m[j-1], and it is smaller than existing ending element at m[j].
                    m[j] = i;
                }
            }

            stack<int> e;
            int i = m[L - 1];
            while (i >= 0)
            {
                e.push(input[i]);
                i = p[i];
            }

            cout << "Longest increasing subsequence:";
            while (!e.empty())
            {
                cout << " " << e.top();
                e.pop();
            }

            cout << endl;
        }

    } // namespace LeetCode
} // namespace Test

#endif
