#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include "Log.h"
#include "Util.h"
#include <algorithm>
#include <bitset>
#include <chrono>
#include <functional>
#include <limits.h>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        template <class T>
        static void print(const string &s, const vector<T> &v)
        {
            cout << s << ": {";
            for (size_t i = 0; i < v.size(); i++)
            {
                if (i > 0)
                    cout << ", ";
                cout << v[i];
            }
            cout << "}" << endl;
        }

        static void GetMedianIndex(int i, int j, int &lowMedianIndex, int &highMedianIndex)
        {
            lowMedianIndex = -1;
            highMedianIndex = -1;
            if (i > j)
                return;
            if (((j - i) & 0x1) == 0)
            {
                // odd numbers [i..j]
                lowMedianIndex = (i + j) / 2; // = i + ((j - i) / 2)
                highMedianIndex = lowMedianIndex;
            }
            else
            {
                // even numbers [i..j]
                lowMedianIndex = (i + j - 1) / 2;  // i + ((j - i - 1) / 2)
                highMedianIndex = (i + j + 1) / 2; // i + ((j - i + 1) / 2)
            }
        }

        struct ListNode
        {
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(nullptr) {}
        };

        // Get the node at the index (zero-based)
        static ListNode *GetNode(ListNode *head, int index)
        {
            if (index < 0)
                return nullptr;
            ListNode *p = head;
            int i = 0; // i is at the index of head
            while (i < index && p != nullptr)
            {
                // Hop p and i together
                p = p->next;
                i++;
            }
            // 1. i == index, p != nullptr
            // 2. i == index, p == nullptr
            // 3. i < index, p == nullptr
            return p;
        }
        static ListNode *GetNode2(ListNode *head, int index)
        {
            if (index < 0)
                return nullptr;
            ListNode *p = head;
            int i = 1; // i is at the index of head->next;
            while (i < index && p != nullptr)
            {
                p = p->next; // move p to catch i
                i++;         // but i moves again
                // so i will always be one step ahead
            }
            // 1. index == 0, p == head
            // 2. i == index, p != nullptr, p is at (i - 1)
            // 3. i == index, p == nullptr, p is at (i - 1)
            // 4. i < index, p == nullptr, p is at (i - 1)
            if (index > 0 && p != nullptr)
            {
                // If need to get the prev of the node at index, then just return p
                p = p->next;
            }
            return p;
        }

        // Assume the list has at least one node
        static ListNode *GetLowerMedian(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            // p and q are at the 1st node
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (1 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q->next == nullptr, p is the median
            // 2. q->next->next == nullptr, p is the lower median
            return p;
        }

        // Assume the list has at least 3 nodes
        static ListNode *GetLowerMedianPrev(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
                return nullptr;
            // p is the 1st node
            ListNode *p = head;
            // q is the 3rd node
            ListNode *q = head->next->next;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (3 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q->next == nullptr, p is the prev to the median at (2 + k)-th node
            // 2. q->next->next == nullptr, p is the prev to the lower median at (2 + k)-th node
            return p;
        }

        // Assume the list has at least one node
        static ListNode *GetHigherMedian(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            // p and q are at the 1st node
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (1 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q == nullptr, i.e, the list has 2k nodes and p is at (1 + k)-th node
            // 2. q->next == nullptr, i.e., the list has (1 + 2k) nodes and p is at (1 + k)-th node
            return p;
        }

        // Assume the list has at least 2 nodes
        static ListNode *GetHigherMedianPrev(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return nullptr;
            ListNode *p = head;
            ListNode *q = head->next;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (2 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // q->next == nullptr, p is the prev to the higher median at (2 + k)-th node
            // q->next->next == nullptr, p is the prev to the median at (2 + k)-th node
            return p;
        }

        void Print(ListNode *node)
        {
            if (node == nullptr)
                return;
            while (node != nullptr)
            {
                cout << node->val << "->";
                node = node->next;
            }
            cout << "null" << endl;
        }

        void DeleteList(ListNode *node)
        {
            if (node == nullptr)
                return;
            ListNode *p = node;
            while (p != nullptr)
            {
                node = p->next;
                delete p;
                p = node;
            }
        }

        ListNode *ToList(const vector<int> &numbers)
        {
            ListNode *list = nullptr;
            if (numbers.empty())
                return list;
            list = new ListNode(numbers[0]);
            ListNode *n = list;
            for (size_t i = 1; i < numbers.size(); i++)
            {
                n->next = new ListNode(numbers[i]);
                n = n->next;
            }
            return list;
        }

        ListNode *DuplicateList(ListNode *node)
        {
            ListNode *list = nullptr;
            ListNode *node2 = nullptr;
            while (node != nullptr)
            {
                if (list == nullptr)
                {
                    list = new ListNode(node->val);
                    node2 = list;
                }
                else
                {
                    node2->next = new ListNode(node->val);
                    node2 = node2->next;
                }
                node = node->next;
            }
            return list;
        }

        int CompareLists(ListNode *node1, ListNode *node2)
        {
            while (node1 != nullptr && node2 != nullptr)
            {
                if (node1->val < node2->val)
                    return -1;
                if (node1->val > node2->val)
                    return 1;
                node1 = node1->next;
                node2 = node2->next;
            }
            if (node1 == nullptr && node2 == nullptr)
                return 0;
            if (node1 == nullptr)
                return -1;
            return 1;
        }

        vector<int> ToVector(ListNode *node)
        {
            vector<int> v;
            while (node != nullptr)
            {
                v.push_back(node->val);
                node = node->next;
            }
            return v;
        }

        bool IsSorted(ListNode *node)
        {
            while (node != nullptr && node->next != nullptr)
            {
                if (node->val > node->next->val)
                    return false;
                node = node->next;
            }
            return true;
        }

        struct TreeNode
        {
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        };

        void Print(TreeNode *node)
        {
            function<void(stringstream *, int, char)> printChar = [&](stringstream *s,
                                                                      int n, char c)
            {
                if (n > 0)
                {
                    string chars(n, c);
                    *s << chars;
                }
            };
            function<void(TreeNode *, unsigned int, int &, int &,
                          vector<stringstream *> &)>
                toString =
                    [&](TreeNode *n,               // current node to print
                        unsigned int y,            // current node level
                        int &x,                    // x-axis position of root of last printed sub tree
                        int &r,                    // x-axis position of right-most boundary of last
                                                   // printed sub tree
                        vector<stringstream *> &ss // output streams, one per level
                    )
            {
                if (n == nullptr)
                    return;
                if (ss.size() <= y)
                    ss.push_back(new stringstream());
                // print left tree, update x and r accordingly
                toString(n->left, y + 1, x, r, ss);
                stringstream *s = ss[y];
                int l = (int)(s->str().length());
                if (l < x)
                    printChar(s, x - l, ' ');
                if (n->left != nullptr && r > x)
                {
                    *s << '/';
                    printChar(s, r - x - 1, '-');
                }
                string nc = to_string(n->val);
                *s << nc;
                x = (r + (nc.length() >> 1));
                r = r + nc.length();
                int rx = r;
                int rr = r;
                toString(n->right, y + 1, rx, rr, ss);
                if (n->right != nullptr && rx >= r)
                {
                    printChar(s, rx - r - 1, '-');
                    *s << '\\';
                }
                // Update the right most boundary
                r = rr;
            };
            vector<stringstream *> streams;
            int x = 0;
            int r = 0;
            toString(node, 0, x, r, streams);
            for_each(streams.begin(), streams.end(), [&](stringstream *s)
                     {
                         cout << s->str() << endl;
                         delete s;
                     });
        }

        void DeleteTree(TreeNode *root)
        {
            if (root == nullptr)
                return;
            if (root->left != nullptr)
            {
                DeleteTree(root->left);
                root->left = nullptr;
            }
            if (root->right != nullptr)
            {
                DeleteTree(root->right);
                root->right = nullptr;
            }
            delete root;
        }

        TreeNode *Clone(TreeNode *root)
        {
            if (root == nullptr)
                return nullptr;
            TreeNode *clone = new TreeNode(root->val);
            clone->left = Clone(root->left);
            clone->right = Clone(root->right);
            return clone;
        }

        TreeNode *CloneReverse(TreeNode *root)
        {
            if (root == nullptr)
                return nullptr;
            TreeNode *clone = new TreeNode(root->val);
            clone->left = CloneReverse(root->right);
            clone->right = CloneReverse(root->left);
            return clone;
        }

        TreeNode *RandomTree(const vector<int> &values)
        {
            if (values.empty())
                return nullptr;
            function<TreeNode *(const vector<int> &, int, int)> create =
                [&](const vector<int> &v, int i, int j) -> TreeNode *
            {
                if (i > j)
                    return nullptr;
                TreeNode *n = nullptr;
                int k = rand() % 3;
                switch (k)
                {
                case 0: // preorder
                    n = new TreeNode(v[i]);
                    k = i + 1 + (rand() % (j - i + 1));
                    n->left = create(v, i + 1, k - 1);
                    n->right = create(v, k, j);
                    break;
                case 1: // inorder
                    k = i + (rand() % (j - i + 1));
                    n = new TreeNode(v[k]);
                    n->left = create(v, i, k - 1);
                    n->right = create(v, k + 1, j);
                    break;
                case 2: // postorder
                    n = new TreeNode(v[j]);
                    k = i - 1 + (rand() % (j - i + 1));
                    n->left = create(v, i, k);
                    n->right = create(v, k + 1, j - 1);
                    break;
                }
                return n;
            };
            return create(values, 0, values.size() - 1);
        }

        TreeNode *RandomTree(int num)
        {
            if (num <= 0)
                return nullptr;
            int t = 0;
            function<TreeNode *(int, int)> create = [&](int i, int j) -> TreeNode *
            {
                if (i > j || t >= num)
                    return nullptr;
                TreeNode *n = new TreeNode(t++);
                if (t >= num)
                    return n;
                int k = rand() % 3;
                switch (k)
                {
                case 0: // preorder
                    k = i + 1 + (rand() % (j - i + 1));
                    n->left = create(i + 1, k - 1);
                    n->right = create(k, j);
                    break;
                case 1: // inorder
                    k = i + (rand() % (j - i + 1));
                    n->left = create(i, k - 1);
                    n->right = create(k + 1, j);
                    break;
                case 2: // postorder
                    k = i - 1 + (rand() % (j - i + 1));
                    n->left = create(i, k);
                    n->right = create(k + 1, j - 1);
                    break;
                }
                return n;
            };
            return create(0, num - 1);
        }

        TreeNode *RandomTreeFromInOrder(const vector<int> &values)
        {
            if (values.empty())
                return nullptr;
            function<TreeNode *(const vector<int> &, int, int)> create =
                [&](const vector<int> &v, int i, int j) -> TreeNode *
            {
                if (i > j)
                    return nullptr;
                int k = i + (rand() % (j - i + 1));
                TreeNode *n = new TreeNode(v[k]);
                n->left = create(v, i, k - 1);
                n->right = create(v, k + 1, j);
                return n;
            };
            return create(values, 0, values.size() - 1);
        }

        TreeNode *RandomSymmetricTree(const vector<int> &values)
        {
            int i = rand() % values.size();
            int v = values[i];
            vector<int> w(values);
            w.erase(w.begin() + i);
            TreeNode *n = new TreeNode(v);
            n->left = RandomTree(w);
            n->right = CloneReverse(n->left);
            return n;
        }

        struct NodeWithNextLink
        {
            int val;
            NodeWithNextLink *left;
            NodeWithNextLink *right;
            NodeWithNextLink *next;
        };

        // Definition for a Node.
        class Node
        {
        public:
            int val;
            vector<Node *> neighbors;

            Node()
            {
                val = 0;
                neighbors = vector<Node *>();
            }

            Node(int _val)
            {
                val = _val;
                neighbors = vector<Node *>();
            }

            Node(int _val, vector<Node *> _neighbors)
            {
                val = _val;
                neighbors = _neighbors;
            }
        };

        Node *RandomGraph(const vector<int> &v)
        {
            if (v.empty())
                return nullptr;
            int l = v.size();
            vector<Node *> n(l, nullptr);
            transform(v.begin(), v.end(), n.begin(),
                      [&](int i)
                      { return new Node(i); });
            for (int i = 0; i < l; i++)
            {
                int c = 1 + (rand() % l);
                for (; c > 0; c--)
                {
                    int j = rand() % l;
                    if (j == 0)
                        j++;
                    j = (i + j) % l;
                    if (find(n[i]->neighbors.begin(), n[i]->neighbors.end(), n[j]) ==
                        n[i]->neighbors.end())
                        n[i]->neighbors.push_back(n[j]);
                }
            }
            // cout << "{" << endl;
            // for (size_t i = 0; i < n.size(); i++) {
            //     cout << "  " << n[i]->val << " : {";
            //     for (size_t j = 0; j < n[i]->neighbors.size(); j++) {
            //         if (j > 0)
            //             cout << ", ";
            //         cout << n[i]->neighbors[j]->val;
            //     }
            //     cout << "}" << endl;
            // }
            // cout << "}" << endl;
            return *n.begin();
        }

        void DeleteGraph(Node *node)
        {
            if (node == nullptr)
                return;
            set<Node *> m;
            m.insert(node);
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n)
                         {
                             if (m.find(n) == m.end())
                             {
                                 m.insert(n);
                                 q.push(n);
                             }
                         });
                f->neighbors.clear();
            }
            for_each(m.begin(), m.end(), [&](Node *n)
                     {
                         // cout << "delete " << n->val << endl;
                         delete n;
                     });
            m.clear();
        }

        // Assume every node has a unique value
        map<int, vector<int>> ToMap(Node *node)
        {
            map<int, vector<int>> m;
            if (node == nullptr)
                return m;
            m[node->val] = {};
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n)
                         {
                             if (m.find(n->val) == m.end())
                             {
                                 m[n->val] = {};
                                 q.push(n);
                             }
                             m[f->val].push_back(n->val);
                         });
            }
            return m;
        }

        // 172. Factorial Trailing Zeroes
        // Given an integer n, return the number of trailing zeroes in n!.
        // Example 1:
        // Input: 3
        // Output: 0
        // Explanation: 3! = 6, no trailing zero.
        // Example 2:
        // Input: 5
        // Output: 1
        // Explanation: 5! = 120, one trailing zero.
        // Note: Your solution should be in logarithmic time complexity.
        // n! = 1 * 2 * 3 * 4 * 5 * ... * 10 * ... * 15 * ... * n
        //    = 2^x * 5^y * z
        // Usually x >= y. So just need to count occurrence of 5.
        //   n:      1, 2, 3, 4, 5, 6, ..., 2*5, ..., 3*5, ..., n1*5, ..., n
        // n/5 = n1:             1,    ..., 2,   ..., 3,   ..., n2*5, ..., n1
        // n1/5 = n2:                                   1, ..., n3*5, ..., n2
        // n2/5 = n3: ...
        // ...
        int trailingZeroes(int n)
        {
            int c = 0;
            while (n >= 5)
            {
                n /= 5;
                c += n;
            }
            return c;
        }

        // 173. Binary Search Tree Iterator
        // Implement an iterator over a binary search tree (BST). Your iterator will be
        // initialized with the root node of a BST.
        // Calling next() will return the next smallest number in the BST.
        // Example:
        // BSTIterator iterator = new BSTIterator(root);
        // iterator.next();    // return 3
        // iterator.next();    // return 7
        // iterator.hasNext(); // return true
        // iterator.next();    // return 9
        // iterator.hasNext(); // return true
        // iterator.next();    // return 15
        // iterator.hasNext(); // return true
        // iterator.next();    // return 20
        // iterator.hasNext(); // return false
        // Note:
        // next() and hasNext() should run in average O(1) time and uses O(h) memory,
        // where h is the height of the tree. You may assume that next() call will
        // always be valid, that is, there will be at least a next smallest number in
        // the BST when next() is called.
        class BSTIterator
        {
        private:
            TreeNode *_node;
            stack<TreeNode *> _s;

        public:
            BSTIterator(TreeNode *root) { _node = root; }
            /** @return the next smallest number */
            int next()
            {
                int v;
                while (!_s.empty() || _node != nullptr)
                {
                    if (_node != nullptr)
                    {
                        _s.push(_node);
                        _node = _node->left;
                    }
                    else
                    {
                        v = _s.top()->val;
                        _node = _s.top()->right;
                        _s.pop();
                        break;
                    }
                }
                return v;
            }
            int next2()
            {
                while (_node != nullptr)
                {
                    _s.push(_node);
                    _node = _node->left;
                }
                TreeNode *t = _s.top();
                _s.pop();
                _node = t->right;
                return t->val;
            }

            /** @return whether we have a next smallest number */
            bool hasNext() { return !_s.empty() || _node != nullptr; }
        };

        // 174. Dungeon Game
        // The demons had captured the princess (P) and imprisoned her in the
        // bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
        // out in a 2D grid. Our valiant knight (K) was initially positioned in the
        // top-left room and must fight his way through the dungeon to rescue the
        // princess. The knight has an initial health point represented by a positive
        // integer. If at any point his health point drops to 0 or below, he dies
        // immediately. Some of the rooms are guarded by demons, so the knight loses
        // health (negative integers) upon entering these rooms; other rooms are either
        // empty (0's) or contain magic orbs that increase the knight's health (positive
        // integers). In order to reach the princess as quickly as possible, the knight
        // decides to move only rightward or downward in each step. Write a function to
        // determine the knight's minimum initial health so that he is able to rescue
        // the princess. For example, given the dungeon below, the initial health of the
        // knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT ->
        // DOWN -> DOWN. -2 (K) 	-3 	3 -5 	-10 	1 10 	30 	-5 (P)
        // Note: The knight's health has no upper bound. Any room can contain threats or
        // power-ups, even the first room the knight enters and the bottom-right room
        // where the princess is imprisoned.
        int calculateMinimumHP(const vector<vector<int>> &dungeon)
        {
            int m = dungeon.size();
            int n = dungeon[0].size();
            vector<int> health(n, 0);
            for (int i = m - 1; i >= 0; i--)
            {
                for (int j = n - 1; j >= 0; j--)
                {
                    if (i == m - 1)
                    {
                        if (j == n - 1)
                            health[j] = 1 + (dungeon[i][j] >= 0 ? 0 : -dungeon[i][j]);
                        else
                            health[j] = dungeon[i][j] >= health[j + 1]
                                            ? 1
                                            : health[j + 1] - dungeon[i][j];
                    }
                    else
                    {
                        if (j == n - 1)
                            health[j] = dungeon[i][j] >= health[j]
                                            ? 1
                                            : health[j] - dungeon[i][j];
                        else
                        {
                            int m = min(health[j], health[j + 1]);
                            health[j] = dungeon[i][j] > m ? 1 : m - dungeon[i][j];
                        }
                    }
                }
                // for (int j = 0; j < n; j++) {
                //     cout << "  " << health[j];
                // }
                // cout << endl;
            }
            return health[0];
        }

        // 175. Combine Two Tables
        // SQL Schema
        // Table: Person
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | PersonId    | int     |
        // | FirstName   | varchar |
        // | LastName    | varchar |
        // +-------------+---------+
        // PersonId is the primary key column for this table.
        // Table: Address
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | AddressId   | int     |
        // | PersonId    | int     |
        // | City        | varchar |
        // | State       | varchar |
        // +-------------+---------+
        // AddressId is the primary key column for this table.
        // Write a SQL query for a report that provides the following information for
        // each person in the Person table, regardless if there is an address for each
        // of those people:
        // FirstName, LastName, City, State
        // # Write your MySQL query statement below
        // SELECT FirstName, LastName, City, State
        // FROM Person LEFT JOIN Address ON Person.PersonId = Address.PersonId

        // 179. Largest Number
        // Given a list of non negative integers, arrange them such that they form the
        // largest number. Example 1: Input: [10,2] Output: "210" Example 2: Input:
        // [3,30,34,5,9] Output: "9534330" Note: The result may be very large, so you
        // need to return a string instead of an integer.
        string largestNumber(const vector<int> &nums)
        {
            vector<string> s;
            s.resize(nums.size());
            transform(nums.begin(), nums.end(), s.begin(),
                      [&](int i)
                      { return std::to_string(i); });
            sort(s.begin(), s.end(), [&](const string &a, const string &b) -> bool
                 {
                     string ab = a + b;
                     string ba = b + a;
                     for (size_t i = 0; i < ab.size(); i++)
                     {
                         if (ab[i] > ba[i])
                             return true;
                         else if (ab[i] < ba[i])
                             return false;
                     }
                     return false;
                 });
            if (s[0] == "0")
                return "0";
            ostringstream ss;
            for_each(s.cbegin(), s.cend(), [&](const string &i)
                     { ss << i; });
            return ss.str();
        }
        string largestNumber2(const vector<int> &nums)
        {
            vector<string> strs;
            strs.resize(nums.size());
            transform(nums.begin(), nums.end(), strs.begin(), [&](int i)
                      {
                          ostringstream oss;
                          oss << i;
                          return oss.str();
                      });
            sort(strs.begin(), strs.end(), [&](const string &str1, const string &str2)
                 {
                     string str12(str1);
                     str12.append(str2);
                     string str21(str2);
                     str21.append(str1);
                     return str12.compare(str21) > 0;
                 });
            string result;
            if (strs[0] == "0")
            {
                result = "0";
            }
            else
            {
                for_each(strs.begin(), strs.end(),
                         [&](const string &str)
                         { result.append(str); });
            }
            return result;
        }

        // 187. Repeated DNA Sequences
        // All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
        // for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
        // identify repeated sequences within the DNA. Write a function to find all the
        // 10-letter-long sequences (substrings) that occur more than once in a DNA
        // molecule. Example: Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT" Output:
        // ["AAAAACCCCC", "CCCCCAAAAA"]
        // A is 0x41 = 01000001,
        // C is 0x43 = 01000011,
        // G is 0x47 = 01000111,
        // T is 0x54 = 01000100.
        // Using bit 3 and 2 to encode each one
        vector<string> findRepeatedDnaSequences(const string &s)
        {
            vector<string> result;
            map<int, int> m;
            int t = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                t = ((t << 2) | (s[i] >> 1 & 0x3)) & 0xFFFFF;
                if (i >= 9)
                {
                    if (m.find(t) == m.end())
                        m[t] = 1;
                    else
                    {
                        if (m[t] == 1)
                            result.push_back(s.substr(i - 9, 10));
                        m[t]++;
                    }
                }
            }
            return result;
        }
        vector<string> findRepeatedDnaSequences2(const string &s)
        {
            vector<string> result;
            for (size_t i = 0; i + 10 < s.size(); i++)
            {
                string t = s.substr(i, 10);
                if (find(result.cbegin(), result.cend(), t) == result.cend())
                {
                    size_t j = i + 1;
                    int stop = false;
                    while (!stop && j + 10 <= s.size())
                    {
                        if (s[i] == s[j])
                        {
                            size_t k = 1;
                            while (k < 10 && s[i + k] == s[j + k])
                                k++;
                            if (k == 10)
                            {
                                result.push_back(s.substr(i, k));
                                stop = true;
                            }
                        }
                        j++;
                    }
                }
            }
            return result;
        }

        // 188. Best Time to Buy and Sell Stock IV
        // Say you have an array for which the i-th element is the price of a given
        // stock on day i. Design an algorithm to find the maximum profit. You may
        // complete at most k transactions. Note: You may not engage in multiple
        // transactions at the same time (ie, you must sell the stock before you buy
        // again). Example 1: Input: [2,4,1], k = 2 Output: 2 Explanation: Buy on day 1
        // (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2. Example 2:
        // Input: [3,2,6,5,0,3], k = 2
        // Output: 7
        // Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit =
        // 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit
        // = 3-0 = 3. Let p[i] be the price on day i Let P(i,k) be the max profit with k
        // transactions on day i
        //            k               1                         2                   3
        //            ......      k-1                          k
        // i     p[i]
        // 0     p[0]     -p[0]
        // 1     p[1]     -p[1]   P(1,1)     -p[1]+P(1,1)
        // 2     p[2]     -p[2]   P(2,1)     -p[2]+P(2,1)   P(2,2) -p[2]+P(2,2)
        // 3     p[3]     -p[3]   P(3,1)     -p[3]+P(3,1)   P(3,2) -p[3]+P(3,2) P(3,3)
        // 4     p[4]     -p[4]   P(4,1)     -p[4]+P(4,1)   P(4,2) -p[4]+P(4,2) P(4,3)
        // ......
        // k-1 p[k-1]   -p[k-1] P(k-1,1) -p[k-1]+P(k-1,1) P(k-1,2) ......
        // -p[k-1]+P(k-1,k-2) P(k-1,k-1) -p[k-1]+P(k-1,k-1) k     p[k]     -p[k] P(k,1)
        // -p[k]+P(k,1)   P(k,2) ......     -p[k]+P(k,k-2)   P(k,k-1)     -p[k]+P(k,k-1)
        // P(k,k) k+1 p[k+1]   -p[k+1] P(k+1,1) -p[k+1]+P[k+1,1] P(k+1,2) ......
        // -p[k+1]+P(k+1,k-2) P(k+1,k-1) -p[k+1]+P(k+1,k-1) P(k+1,k)
        // ......
        // i-1 p[i-1]   -p[i-1] P(i-1,1) -p[i-1]+P(i-1,1) P(i-1,2) ......
        // -p[i-1]+P(i-1,k-2) P(i-1,k-1) -p[i-1]+P(i-1,k-1) P(i-1,k) i     p[i] P(i,1)
        // P(i,2) ......                      P(i,k-1)                      P(i,k)

        // P(i,1) = max(P(i-1,1),
        //              p[i] + max{-p[i-1],
        //                         -p[i-2],
        //                         ......
        //                         -p[2],
        //                         -p[1],
        //                         -p[0]}
        // P(i,2) = max{P(i-1, 2),
        //              p[i] + max{-p[i-1] + P(i-1, 1),
        //                         -p[i-2] + P(i-2, 1),
        //                         ......
        //                         -p[2] + P(2, 1),
        //                         -p[1] + P(1, 1)}}
        // P(i,3) = max{P(i-1, 3),
        //              p[i] + max{-p[i-1] + P(i-1, 2),
        //                         -p[i-2] + P(i-2, 2),
        //                         ......
        //                         -p[3] + P(3, 2),
        //                         -p[2] + P(2, 2)}}
        // ......
        // P(i,k-1) = max{P(i-1, k-1),
        //              p[i] + max{-p[i-1] + P(i-1, k-2),
        //                         -p[i-2] + P(i-2, k-2),
        //                         ......
        //                         -p[k-1] + P(k-1, k-2),
        //                         -p[k-2] + P(k-2, k-2)}}
        // P(i,k) = max{P(i-1, k),
        //              p[i] + max{-p[i-1] + P(i-1, k-1),
        //                         -p[i-2] + P(i-2, k-1),
        //                         ......
        //                         -p[k] + P(k, k-1),
        //                         -p[k-1] + P(k-1, k-1)}}
        int maxProfit(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == i)
                    {
                        if (j == 1)
                            c[j - 1] = -prices[i - 1];
                        else
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                        p[j - 1] = prices[i] + c[j - 1];
                    }
                    else
                    {
                        if (j == 1)
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                        else
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                        p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }
        int maxProfit2(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == 1)
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                    else
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }

        // 189. Rotate Array
        // Given an array, rotate the array to the right by k steps, where k is
        // non-negative. Example 1: Input: [1,2,3,4,5,6,7] and k = 3 Output:
        // [5,6,7,1,2,3,4] Explanation: rotate 1 steps to the right: [7,1,2,3,4,5,6]
        // rotate 2 steps to the right: [6,7,1,2,3,4,5]
        // rotate 3 steps to the right: [5,6,7,1,2,3,4]
        // Example 2:
        // Input: [-1,-100,3,99] and k = 2
        // Output: [3,99,-1,-100]
        // Explanation:
        // rotate 1 steps to the right: [99,-1,-100,3]
        // rotate 2 steps to the right: [3,99,-1,-100]
        // Note: Try to come up as many solutions as you can, there are at least 3
        // different ways to solve this problem. Could you do it in-place with O(1)
        // extra space?
        void rotate(vector<int> &nums, int k)
        {
            k = k % nums.size();
            if (k == 0)
                return;
            function<void(int, int)> Swap = [&](int i, int j)
            {
                while (i < j)
                {
                    swap(nums[i], nums[j]);
                    i++;
                    j--;
                }
            };
            Swap(0, (int)nums.size() - 1);
            Swap(0, k - 1);
            Swap(k, (int)nums.size() - 1);
        }
        void rotate2(vector<int> &nums, int k)
        {
            k %= nums.size();
            if (k == 0)
                return;
            function<void(int, int, int)> Swap = [&](int p, int q, int n)
            {
                for (int m = 0; m < n; m++)
                    swap(nums[p + m], nums[q + m]);
            };
            int i = 0;
            int j = nums.size() - 1;
            int t = j - k + 1;
            // input[i..t-1] and input[t..j];
            while (i < t && t <= j)
            {
                if (t - i < j - t + 1)
                {
                    // Left range is shorter. Swap it to the right, and
                    // repeat with the rest on its left.
                    // input[i..t-1], input[t..j-(t-i)], input[j-(t-i)+1..j]
                    Swap(i, j - (t - i) + 1, t - i);
                    j = j - (t - i);
                }
                else if (t - i > j - t + 1)
                {
                    // Right range is shorter. Swap it to the left, and
                    // repeat with the rest on its right.
                    // input[i..i+(j-t)], input(i+(j-t)+1..t-1], input[t..j]
                    Swap(i, t, j - t + 1);
                    i = i + (j - t) + 1;
                }
                else
                {
                    // Both ranges have the same length
                    Swap(i, t, t - i);
                    break;
                }
            }
        }
        void rotate3(vector<int> &nums, int k)
        {
            if (nums.empty())
                return;
            int n = (int)nums.size();
            k %= n;
            if (k == 0)
                return;
            vector<int> b(k, 0);
            for (int i = 0; i < k; i++)
            {
                if (b[i] == 1)
                    continue;
                int j = i;
                int x = nums[j];
                while (true)
                {
                    int t = j + k;
                    while (t < n)
                    {
                        swap(x, nums[t]);
                        t += k;
                    }
                    t %= n;
                    swap(x, nums[t]);
                    b[t] = 1;
                    if (j == t || t == i)
                        break;
                    j = t;
                }
            }
        }
        // This one works only if n and k are co-prime
        // 0, k, 2k, 3k, ..., (n-1)k, nk
        // 0, k % n, 2k % n, 3k % n, ..., (n-1)k % n, nk % n = 0
        void rotate4(vector<int> &nums, int k)
        {
            if (nums.empty())
                return;
            k %= nums.size();
            if (k == 0)
                return;
            size_t i = 0;
            do
            {
                i = (i + k) % nums.size();
                swap(nums[0], nums[i]);
            } while (i != 0);
        }

        // 190. Reverse Bits
        // Reverse bits of a given 32 bits unsigned integer.
        // Example 1:
        // Input: 00000010100101000001111010011100
        // Output: 00111001011110000010100101000000
        // Explanation: The input binary string 00000010100101000001111010011100
        // represents the unsigned integer 43261596, so return 964176192 which its
        // binary representation is 00111001011110000010100101000000.
        // Example 2:
        // Input: 11111111111111111111111111111101
        // Output: 10111111111111111111111111111111
        // Explanation: The input binary string 11111111111111111111111111111101
        // represents the unsigned integer 4294967293, so return 3221225471 which
        // its binary representation is 10111111111111111111111111111111.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, both input and output will be given as signed integer
        // type and should not affect your implementation, as the internal binary
        // representation of the integer is the same whether it is signed or unsigned.
        // In Java, the compiler represents the signed integers using 2's complement
        // notation. Therefore, in Example 2 above the input represents the signed
        // integer -3 and the output represents the signed integer -1073741825.
        // Follow up: If this function is called many times, how would you optimize it?
        uint32_t reverseBits(uint32_t n)
        {
            n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
            n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
            n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
            n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
            n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
            return n;
        }

        // 191. Number of 1 Bits
        // Write a function that takes an unsigned integer and return the number of '1'
        // bits it has (also known as the Hamming weight).
        // Example 1:
        // Input: 00000000000000000000000000001011
        // Output: 3
        // Explanation: The input binary string 00000000000000000000000000001011 has a
        // total of three '1' bits.
        // Example 2:
        // Input: 00000000000000000000000010000000
        // Output: 1
        // Explanation: The input binary string 00000000000000000000000010000000 has a
        // total of one '1' bit.
        // Example 3:
        // Input: 11111111111111111111111111111101
        // Output: 31
        // Explanation: The input binary string 11111111111111111111111111111101 has a
        // total of thirty one '1' bits.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, the input will be given as signed integer type and should
        // not affect your implementation, as the internal binary representation of the
        // integer is the same whether it is signed or unsigned. In Java, the compiler
        // represents the signed integers using 2's complement notation. Therefore, in
        // Example 3 above the input represents the signed integer -3.
        // Follow up: If this function is called many times, how would you optimize it?
        int hammingWeight(uint32_t n)
        {
            int c = 0;
            while (n > 0)
            {
                n &= (n - 1);
                c++;
            }
            return c;
        }

        // 198. House Robber
        // You are a professional robber planning to rob houses along a street. Each
        // house has a certain amount of money stashed, the only constraint stopping you
        // from robbing each of them is that adjacent houses have security system
        // connected and it will automatically contact the police if two adjacent houses
        // were broken into on the same night. Given a list of non-negative integers
        // representing the amount of money of each house, determine the maximum amount
        // of money you can rob tonight without alerting the police. Example 1: Input:
        // [1,2,3,1] Output: 4 Explanation: Rob house 1 (money = 1) and then rob house 3
        // (money = 3). Total amount you can rob = 1 + 3 = 4. Example 2: Input:
        // [2,7,9,3,1] Output: 12 Explanation: Rob house 1 (money = 2), rob house 3
        // (money = 9) and rob house 5 (money = 1). Total amount you can rob = 2 + 9 + 1
        // = 12.
        // Let m[i] be the max amount for p[0..i]
        // m[i] = max{m[i - 1],
        //            p[i] + max{m[i - 2],
        //                       m[i - 1],
        //                       ......
        //                       m[2],
        //                       m[1] = max{p[1], p[0]},
        //                       m[0] = p[0]}}
        int rob(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            if (nums.size() == 1)
                return nums[0];
            int s = nums[0];               // i = 0
            int m = max(nums[0], nums[1]); // i = 1
            for (size_t i = 2; i < nums.size(); i++)
            {
                int t = m;               // m[i-1]
                m = max(m, nums[i] + s); // m[i] = max(m[i-1], n[i] + m[i-2])
                s = max(s, t);
            }
            return m;
        }
        int rob2(const vector<int> &nums)
        {
            int a = 0; // max at i - 2
            int b = 0; // max at i - 1
            int c;     // max at i
            for (size_t i = 0; i < nums.size(); i++)
            {
                c = max(a + nums[i], b);
                a = b;
                b = c;
            }
            return b;
        }

        // 199. Binary Tree Right Side View
        // Given a binary tree, imagine yourself standing on the right side of it,
        // return the values of the nodes you can see ordered from top to bottom.
        // Example:
        // Input: [1,2,3,null,5,null,4]
        // Output: [1, 3, 4]
        // Explanation:
        //    1            <---
        //  /   \
        // 2     3         <---
        //  \     \
        //   5     4       <---
        vector<int> rightSideView(TreeNode *root)
        {
            vector<int> v;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int d = 1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (d > (int)v.size())
                        v.push_back(n->val);
                    s.push(make_pair(n, d));
                    d++;
                    n = n->right;
                }
                else
                {
                    n = s.top().first->left;
                    d = s.top().second + 1;
                    s.pop();
                }
            }
            return v;
        }
        vector<int> rightSideView2(TreeNode *root)
        {
            vector<int> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int level = 0;
            int current = 0;
            int next = 0;
            TreeNode *p;
            while (!q[0].empty() || !q[1].empty())
            {
                current = level % 2;
                next = (level + 1) % 2;
                p = q[current].front();
                result.push_back(p->val);
                while (!q[current].empty())
                {
                    p = q[current].front();
                    q[current].pop();
                    if (p->right != nullptr)
                        q[next].push(p->right);
                    if (p->left != nullptr)
                        q[next].push(p->left);
                }
                level++;
            }
            return result;
        }

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
                    b = b >> 1;
                    continue;
                }
                if (b <= m)
                {
                    r |= b;
                    m -= b;
                    n -= b;
                    b = b >> 1;
                }
                else
                {
                    break;
                }
            }
            return r;
        }
        int rangeBitwiseAnd2(int m, int n)
        {
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
                if (!s.empty())
                    cout << ", ";
                cout << n;
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
            cout << (s.empty() ? "" : ", ") << n << endl;
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
            function<bool(int, set<int> &)> hasCircle = [&](int i,
                                                            set<int> &visited) -> bool
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
        // This BFS is wrong, e.g., for inputs 3 and [[0,1],[0,2],[1,2]]
        bool canFinish2(int numCourses, const vector<vector<int>> &prerequisites)
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
                set<int> visited;
                queue<int> q;
                q.push(it->first);
                visited.insert(it->first);
                while (!q.empty())
                {
                    int t = q.front();
                    q.pop();
                    if (g.find(t) == g.end())
                        continue;
                    for (size_t i = 0; i < g[t].size(); i++)
                    {
                        if (visited.find(g[t][i]) != visited.end())
                            return false;
                        q.push(g[t][i]);
                        visited.insert(g[t][i]);
                    }
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

        // Add and Search Word - Data structure design
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
                cout << "addWord(" << word << ")" << endl;
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
                Print();
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
                cout << "search(" << word << ") = " << f << endl;
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
                    cout << "<'" << node->val << "', " << i << ">" << endl;
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
                cout << "search2(" << word << ") = " << found << endl;
                return found;
            }
        };

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
        vector<int> findOrder(int numCourses,
                              const vector<vector<int>> &prerequisites)
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
                function<Node *(Node *, size_t &)> match = [&](Node *node,
                                                               size_t &i) -> Node *
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
                function<bool(Node *, size_t)> match = [&](Node *node,
                                                           size_t i) -> bool
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
                             result.push_back(w);
                     });
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

        // Palindrome Pairs
        // Given a list of unique words, find all pairs of distinct indices (i, j)
        // in the given list, so that the concatenation of the two words, i.e.
        // words[i] + words[j] is a palindrome.
        // Example 1:
        // Input: ["abcd","dcba","lls","s","sssll"]
        // Output: [[0,1],[1,0],[3,2],[2,4]]
        // Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
        // Example 2:
        // Input: ["bat","tab","cat"]
        // Output: [[0,1],[1,0]]
        // Explanation: The palindromes are ["battab","tabbat"]
        // Example 3:
        // Input: ["a", ""]
        // Output: [[0,1],[1,0]]
        // Example 4:
        // Input: ["a","b","c","ab","ac","aa"]
        // Expected: [[3,0],[1,3],[4,0],[2,4],[5,0],[0,5]]
        vector<vector<int>> palindromePairs(const vector<string> &words)
        {
            struct Node
            {
                char val;
                vector<int> completeIndices;
                vector<int> childIndices;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> before(new Node('\0', false));
            unique_ptr<Node> after(new Node('\0', false));
            function<void(int)> add = [&](int j)
            {
                Node *node = before.get();
                int i = 0;
                const string &w = words[j];
                while (i < (int)w.size())
                {
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node->childIndices.push_back(j);
                    node = node->next[w[i++]];
                }
                while (i < (int)w.size())
                {
                    node->next[w[i]] = new Node(w[i], false);
                    node->childIndices.push_back(j);
                    node = node->next[w[i++]];
                }
                node->childIndices.push_back(j);
                node->completeIndices.push_back(j);
                node->complete = true;
                node = after.get();
                i = (int)w.size() - 1;
                while (i >= 0)
                {
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node->childIndices.push_back(j);
                    node = node->next[w[i--]];
                }
                while (i >= 0)
                {
                    node->next[w[i]] = new Node(w[i], false);
                    node->childIndices.push_back(j);
                    node = node->next[w[i--]];
                }
                node->childIndices.push_back(j);
                node->completeIndices.push_back(j);
                node->complete = true;
            };
            function<bool(const string &, int, int)> isPalindrome = [&](const string &w, int i, int j) -> bool
            {
                while (i < j)
                {
                    if (w[i++] != w[j--])
                        return false;
                }
                return true;
            };
            vector<vector<int>> result;
            function<void(int)> findBefore = [&](int j)
            {
                Node *node = before.get();
                const string &w = words[j];
                int i = (int)w.size() - 1;
                while (i >= 0)
                {
                    if (node->complete)
                    {
                        if (isPalindrome(w, 0, i))
                        {
                            for (int k : node->completeIndices)
                                result.push_back(vector<int>{k, j});
                        }
                    }
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node = node->next[w[i--]];
                }
                if (i < 0)
                {
                    for (int k : node->childIndices)
                    {
                        if (isPalindrome(words[k], (int)w.size(), (int)words[k].size() - 1))
                            result.push_back(vector<int>{k, j});
                    }
                }
            };
            function<void(int)> findAfter = [&](int j)
            {
                Node *node = after.get();
                const string &w = words[j];
                int i = 0;
                while (i < (int)w.size())
                {
                    if (node->complete)
                    {
                        if (isPalindrome(w, i, (int)w.size() - 1))
                        {
                            for (int k : node->completeIndices)
                                result.push_back(vector<int>{j, k});
                        }
                    }
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node = node->next[w[i++]];
                }
                if (i >= (int)w.size())
                {
                    for (int k : node->childIndices)
                    {
                        if (isPalindrome(words[k], 0, (int)words[k].size() - (int)w.size() - 1))
                            result.push_back(vector<int>{j, k});
                    }
                }
            };
            for (int i = 0; i < (int)words.size(); i++)
            {
                findBefore(i);
                findAfter(i);
                add(i);
            }
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
            string w = s + "#" + r;
            // Using KMP
            vector<int> p(w.size(), 0);
            int c = 0;
            for (int i = 1; i < (int)w.size(); i++)
            {
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

        // 349. Intersection of Two Arrays
        // Given two arrays, write a function to compute their intersection.
        // Example 1:
        // Input: nums1 = [1,2,2,1], nums2 = [2,2]
        // Output: [2]
        // Example 2:
        // Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
        // Output: [9,4]
        // Note: Each element in the result must be unique. The result can be in any
        // order.
        vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            function<void(vector<int> &, vector<int> &)> solve = [&](vector<int> &n1,
                                                                     vector<int> &n2)
            {
                for (int i = 0; i < (int)n1.size(); i++)
                {
                    if (i > 0 && n1[i - 1] == n1[i])
                        continue;
                    int b = 0;
                    int e = (int)n2.size() - 1;
                    while (b <= e)
                    {
                        int m = b + ((e - b) >> 1);
                        if (n2[m] < n1[i])
                            b = m + 1;
                        else if (n2[m] > n1[i])
                            e = m - 1;
                        else
                        {
                            result.push_back(n1[i]);
                            break;
                        }
                    }
                }
            };
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return result;
        }
        vector<int> intersection2(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            set<int> s1(nums1.cbegin(), nums1.cend());
            set<int> s2(nums2.cbegin(), nums2.cend());
            result.resize(min(s1.size(), s2.size()));
            auto it = set_intersection(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(),
                                       result.begin());
            result.resize(it - result.begin());
            return result;
        }
        vector<int> intersection3(const vector<int> &nums1, const vector<int> &nums2)
        {
            vector<int> o;
            function<void(const vector<int> &, const vector<int> &)> solve =
                [&](const vector<int> &n1, const vector<int> &n2)
            {
                set<int> s(n1.cbegin(), n1.cend());
                set<int> u;
                for (int n : n2)
                {
                    if (s.find(n) != s.end() && u.find(n) == u.end())
                    {
                        o.push_back(n);
                        u.insert(n);
                    }
                }
            };
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return o;
        }
        vector<int> intersection4(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> o;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            size_t i = 0;
            size_t j = 0;
            while (i < nums1.size() && j < nums2.size())
            {
                if (nums1[i] < nums2[j])
                    i++;
                else if (nums1[i] > nums2[j])
                    j--;
                else
                {
                    o.push_back(nums1[i]);
                    while (i + 1 < nums1.size() && nums1[i] == nums1[i + 1])
                        i++;
                    i++;
                    while (j + 1 < nums2.size() && nums2[j] == nums2[j + 1])
                        j++;
                    j++;
                }
            }
            return o;
        }

        // 350. Intersection of Two Arrays II
        // Given two arrays, write a function to compute their intersection.
        // Example 1:
        // Input: nums1 = [1,2,2,1], nums2 = [2,2]
        // Output: [2,2]
        // Example 2:
        // Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
        // Output: [4,9]
        // Note: Each element in the result should appear as many times as it shows in
        // both arrays. The result can be in any order.
        // Follow up:
        // What if the given array is already sorted? How would you optimize your
        // algorithm? What if nums1's size is small compared to nums2's size? Which
        // algorithm is better? What if elements of nums2 are stored on disk, and the
        // memory is limited such that you cannot load all elements into the memory at
        // once?
        vector<int> intersectII(const vector<int> &nums1, const vector<int> &nums2)
        {
            function<map<int, int>(const vector<int> &)> count =
                [&](const vector<int> &n) -> map<int, int>
            {
                map<int, int> m;
                for (int x : n)
                {
                    if (m.find(x) == m.end())
                        m[x] = 1;
                    else
                        m[x]++;
                }
                return m;
            };
            map<int, int> m1 = count(nums1);
            map<int, int> m2 = count(nums2);
            vector<int> result;
            for (auto it = m1.begin(); it != m1.end(); it++)
            {
                if (m2.find(it->first) != m2.end())
                    result.insert(result.end(), min(it->second, m2[it->first]),
                                  it->first);
            }
            return result;
        }
        vector<int> intersectII2(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            result.resize(min(nums1.size(), nums2.size()));
            auto it = set_intersection(nums1.cbegin(), nums1.cend(), nums2.cbegin(),
                                       nums2.cend(), result.begin());
            result.resize(it - result.begin());
            return result;
        }
        vector<int> intersectII3(const vector<int> &nums1, const vector<int> &nums2)
        {
            vector<int> o;
            function<void(const vector<int> &, const vector<int> &)> solve =
                [&](const vector<int> &n1, const vector<int> &n2)
            {
                map<int, int> m;
                for (int n : n1)
                {
                    if (m.find(n) == m.end())
                        m[n] = 1;
                    else
                        m[n]++;
                }
                for (int n : n2)
                {
                    if (m.find(n) != m.end())
                    {
                        o.push_back(n);
                        m[n]--;
                        if (m[n] == 0)
                            m.erase(n);
                    }
                }
            };
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return o;
        }
        vector<int> intersectII4(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> o;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            size_t i = 0;
            size_t j = 0;
            while (i < nums1.size() && j < nums2.size())
            {
                if (nums1[i] < nums2[j])
                    i++;
                else if (nums1[i] > nums2[j])
                    j++;
                else
                {
                    o.push_back(nums1[i]);
                    i++;
                    j++;
                }
            }
            return o;
        }

        // 367. Valid Perfect Square
        // Given a positive integer num, write a function which returns True if num is a
        // perfect square else False. Note: Do not use any built-in library function
        // such as sqrt. Example 1: Input: 16 Output: true Example 2: Input: 14 Output:
        // false
        bool isPerfectSquare(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b <= e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m + 1;
                else if (s > x)
                    e = m - 1;
                else
                    return true;
            }
            return false;
        }
        bool isPerfectSquare2(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b < e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m + 1;
                else if (s > x)
                    e = m;
                else
                    return true;
            }
            return b == e && b * b == x;
        }
        bool isPerfectSquare3(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b + 1 < e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m;
                else if (s > x)
                    e = m;
                else
                    return true;
            }
            if (b <= e)
            {
                if (b * b == x)
                    return true;
                if (b < e && e * e == x)
                    return true;
            }
            return false;
        }

        // 374. Guess Number Higher or Lower
        // We are playing the Guess Game. The game is as follows:
        // I pick a number from 1 to n. You have to guess which number I picked.
        // Every time you guess wrong, I'll tell you whether the number is higher or
        // lower. You call a pre-defined API guess(int num) which returns 3 possible
        // results: -1 : My number is lower
        //  1 : My number is higher
        //  0 : Congrats! You got it!
        // Example :
        // Input: n = 10, pick = 6
        // Output: 6
        int guess(int x, int pick)
        {
            if (pick < x)
                return -1;
            else if (pick > x)
                return 1;
            else
                return 0;
        }
        int guessNumber(int n, int pick)
        {
            int b = 1;
            int e = n;
            int m = b;
            while (b <= e)
            {
                m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m - 1;
                else if (c == 1)
                    b = m + 1;
                else
                    break;
            }
            return m;
        }
        int guessNumber2(int n, int pick)
        {
            int b = 1;
            int e = n;
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m;
                else if (c == 1)
                    b = m + 1;
                else
                    return m;
            }
            return b;
        }
        int guessNumber3(int n, int pick)
        {
            int b = 1;
            int e = n;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m;
                else if (c == 1)
                    b = m;
                else
                    return m;
            }
            return guess(b, pick) == 0 ? b : e;
        }

        // 410. Split Array Largest Sum
        // Given an array which consists of non-negative integers and an integer m, you
        // can split the array into m non-empty continuous subarrays. Write an algorithm
        // to minimize the largest sum among these m subarrays. Note: If n is the length
        // of array, assume the following constraints are satisfied:
        // 1 <= n <= 1000
        // 1 <= m <= min(50, n)
        // Examples:
        // Input:
        // nums = [7,2,5,10,8]
        // m = 2
        // Output:
        // 18
        // Explanation:
        // There are four ways to split nums into two subarrays.
        // The best way is to split it into [7,2,5] and [10,8],
        // where the largest sum among the two subarrays is only 18.
        int splitArray(const vector<int> &nums, int m)
        {
            long long l = 0;
            long long h = 0;
            for (int n : nums)
            {
                l = max(l, (long long)n);
                h += n;
            }
            while (l < h)
            {
                long long t = l + ((h - l) >> 1);
                int c = 0;
                long long s = 0;
                for (size_t i = 0; i < nums.size(); i++)
                {
                    s += nums[i];
                    if (s > t)
                    {
                        c++;
                        s = nums[i];
                    }
                }
                if (s > 0)
                    c++;
                if (c > m)
                    l = t + 1;
                else
                    h = t;
            }
            return l;
        }

        // 658. Find K Closest Elements
        // Given a sorted array, two integers k and x, find the k closest elements to x
        // in the array. The result should also be sorted in ascending order. If there
        // is a tie, the smaller elements are always preferred. Example 1: Input:
        // [1,2,3,4,5], k=4, x=3 Output: [1,2,3,4] Example 2: Input: [1,2,3,4,5], k=4,
        // x=-1 Output: [1,2,3,4] Note: The value k is positive and will always be
        // smaller than the length of the sorted array. Length of the given array is
        // positive and will not exceed 10^4. Absolute value of elements in the array
        // and x will not exceed 10^4. UPDATE (2017/9/19): The arr parameter had been
        // changed to an array of integers (instead of a list of integers). Please
        // reload the code definition to get the latest changes. arr: [1,2,3,4,5] k: 4
        // x: -1
        vector<int> findClosestElements(const vector<int> &arr, int k, int x)
        {
            if (arr.empty())
                return {};
            if (arr.size() == 1)
                return arr;
            int b = 0;
            int e = (int)arr.size() - 1;
            int m;
            while (b + 1 < e)
            {
                m = b + ((e - b) >> 1);
                if (arr[m] < x)
                    b = m;
                else if (arr[m] > x)
                    e = m;
                else
                    break;
            }
            vector<int> result;
            if (b + 1 < e)
            {
                // Must have found x
                result.push_back(arr[m]);
                b = m - 1;
                e = m + 1;
            }
            else if (arr[b] >= x)
            {
                // b = 0, e = 1, x <= arr[b] <= arr[e]
                result.push_back(arr[b--]);
            }
            else if (arr[e] <= x)
            {
                // b = e - 1, e = arr.size - 1, arr[b] < arr[e] <= x
                result.push_back(arr[e++]);
            }
            else
            {
                // 0 < b < b + 1 == e < arr.size - 1
                // arr[b] < x << arr[e]
            }
            // b and e point to next possible candidates
            while (e - b - 1 < k)
            {
                if (b < 0)
                    result.push_back(arr[e++]);
                else if (e >= (int)arr.size())
                    result.insert(result.begin(), 1, arr[b--]);
                else if (x - arr[b] <= arr[e] - x)
                    result.insert(result.begin(), 1, arr[b--]);
                else
                    result.push_back(arr[e++]);
            }
            return result;
        }
        // This may not output the smaller ones on tie
        // arr:[0,0,1,2,3,3,4,7,7,8]
        // k: 3
        // x: 5
        // Output: [4,7,7]
        // Expected: [3,3,4]
        vector<int> findClosestElements2(vector<int> &arr, int k, int x)
        {
            vector<int> result;
            int b = 0;
            int e = (int)arr.size() - 1;
            int i = b;
            while (b <= e)
            {
                i = b;
                int j = e - 1;
                while (i <= j)
                {
                    if (abs(arr[i] - x) > abs(arr[e] - x))
                        swap(arr[i], arr[j--]);
                    else
                        i++;
                }
                swap(arr[i++], arr[e]);
                if (i - b < k)
                {
                    k -= i - b;
                    b = i;
                }
                else if (i - b > k)
                {
                    e = i - 2;
                }
                else
                {
                    break;
                }
            }
            result.insert(result.begin(), arr.begin(), arr.begin() + i);
            sort(result.begin(), result.end());
            return result;
        }

        // 719. Find K-th Smallest Pair Distance
        // Given an integer array, return the k-th smallest distance among all the
        // pairs. The distance of a pair (A, B) is defined as the absolute difference
        // between A and B. Example 1: Input: nums = [1,3,1] k = 1 Output: 0
        // Explanation:
        // Here are all the pairs:
        // (1,3) -> 2
        // (1,1) -> 0
        // (3,1) -> 2
        // Then the 1st smallest distance pair is (1,1), and its distance is 0.
        // Note:
        // 2 <= len(nums) <= 10000.
        // 0 <= nums[i] < 1000000.
        // 1 <= k <= len(nums) * (len(nums) - 1) / 2.
        // Approach #2: Binary Search + Prefix Sum [Accepted]
        // Let's binary search for the answer. It's definitely in the range [0, W],
        // where W = max(nums) - min(nums)]. Let possible(guess) be true if and only
        // if there are k or more pairs with distance less than or equal to guess.
        // We will focus on evaluating our possible function quickly.
        // Algorithm
        // Let countLessOrEqual[v] be the number of points in nums less than or equal to
        // v. Also, let countEqualOnLeft[j] be the number of points i with i < j and
        // nums[i] == nums[j]. We can record both of these with a simple linear scan.
        // Now, for every point i, the number of points j with i < j and nums[j] -
        // nums[i] <= guess is countLessOrEqual[nums[i]+guess] -
        // countLessOrEqual[nums[i]] + (countTotal[i] - countEqualOnLeft[i]), where
        // countTotal[i] is the number of ocurrences of nums[i] in nums. The sum of this
        // over all i is the number of pairs with distance <= guess. Finally, because
        // the sum of countTotal[i] - countEqualOnLeft[i] is the same as the sum of
        // countEqualOnLeft[i] when the sum is over all elements having the same value
        // nums[i], we could just replace that term with countEqualOnLeft[i] without
        // affecting the answer.
        // Approach #3: Binary Search + Sliding Window [Accepted]
        // As in Approach #2, let's binary search for the answer, and we will focus on
        // evaluating our possible function quickly.
        // Algorithm
        // We will use a sliding window approach to count the number of pairs with
        // distance <= guess. For every possible right, we maintain the loop invariant:
        // left is the smallest value such that nums[right] - nums[left] <= guess. Then,
        // the number of pairs with right as it's right-most endpoint is right - left,
        // and we add all of these up.
        int smallestDistancePair(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            int l = 0;
            int h = nums[nums.size() - 1] - nums[0];
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                int count = 0;
                int i = 0;
                for (int j = 0; j < (int)nums.size(); j++)
                {
                    while (nums[j] - nums[i] > m)
                        i++;
                    count += j - i;
                }
                if (count < k)
                    l = m + 1;
                else
                    h = m;
            }
            return l;
        }
        int smallestDistancePair2(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            int min = nums[0];
            int max = nums[nums.size() - 1];
            // let d = max - min
            //     min, min+1, ..., max-1, max
            // i = 0,   1,     ..., d-1,   d
            // countLessOrEqual[i] is the count of elements in nums whose value is
            // less than or equal to (min + i)
            vector<int> countLessOrEqual(max - min + 1, 0);
            int i = 0; // walk through nums
            for (int v = min; v <= max; v++)
            {
                // Since nums is sorted, only need to walk towards right until
                // the first element greater than v
                // Thw while loop will be skiped if v < nums[i]
                while (i < (int)nums.size() && nums[i] == v)
                    i++;
                // There are i elements <= v
                countLessOrEqual[v - min] = i;
            }
            vector<int> countEqualOnLeft(nums.size(), 0);
            for (i = 1; i < (int)nums.size(); i++)
            {
                // Since nums is sorted, just need to compare with previous one
                // to count the equal elements
                if (nums[i] == nums[i - 1])
                    countEqualOnLeft[i] = countEqualOnLeft[i - 1] + 1;
            }
            int l = 0;
            int h = max - min;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                int count = 0;
                for (i = 0; i < (int)nums.size(); i++)
                {
                    // countLessOrEqual[guessHigh] will be elements <= nums[i] + m
                    // countLessOrEqual[guessLow] will be elements <= nums[i]
                    int guessLow = nums[i] - min;
                    int guessHigh = guessLow + m;
                    count += (guessHigh >= (int)countLessOrEqual.size()
                                  ? (int)nums.size()
                                  : countLessOrEqual[guessHigh]);
                    // This excludes all elements == nums[i], so need to compensate
                    // by adding countEqualOnLeft[i]
                    count -= countLessOrEqual[guessLow];
                    count += countEqualOnLeft[i];
                }
                if (count < k)
                    l = m + 1;
                else
                    h = m;
            }
            return l;
        }
        int smallestDistancePair3(const vector<int> &nums, int k)
        {
            priority_queue<int> q;
            for (size_t i = 0; i + 1 < nums.size(); i++)
            {
                for (size_t j = i + 1; j < nums.size(); j++)
                {
                    int d = abs(nums[j] - nums[i]);
                    if ((int)q.size() < k || d < q.top())
                        q.push(d);
                    if ((int)q.size() > k)
                        q.pop();
                }
            }
            return q.top();
        }
        int smallestDistancePair4(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            priority_queue<int> q;
            for (int i = 1; i < (int)nums.size(); i++)
            {
                for (int j = i - 1; j >= 0; j--)
                {
                    int d = abs(nums[i] - nums[j]);
                    if ((int)q.size() < k || d < q.top())
                    {
                        q.push(d);
                        if ((int)q.size() > k)
                            q.pop();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return q.top();
        }
        // This is wrong
        int smallestDistancePair5(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            priority_queue<int> q;
            int t = 1;
            while ((int)q.size() < k && t <= (int)nums.size() - 1)
            {
                for (size_t i = 0; i + t < nums.size(); i++)
                {
                    int d = abs(nums[i + t] - nums[i]);
                    if ((int)q.size() < k || d < q.top())
                        q.push(d);
                    if ((int)q.size() > k)
                        q.pop();
                }
                t++;
            }
            return q.top();
        }

        // 744. Find Smallest Letter Greater Than Target
        // Given a list of sorted characters letters containing only lowercase letters,
        // and given a target letter target, find the smallest element in the list that
        // is larger than the given target. Letters also wrap around. For example, if
        // the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.
        // Examples:
        // Input:
        // letters = ["c", "f", "j"]
        // target = "a"
        // Output: "c"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "c"
        // Output: "f"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "d"
        // Output: "f"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "g"
        // Output: "j"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "j"
        // Output: "c"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "k"
        // Output: "c"
        // Note: letters has a length in range [2, 10000]. letters consists of lowercase
        // letters, and contains at least 2 unique letters. target is a lowercase
        // letter.
        char nextGreatestLetter(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size() - 1;
            while (b <= e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                {
                    if (m < e)
                        b = m + 1;
                    else
                        return letters[0];
                }
                else
                {
                    if (m < e)
                        e = m;
                    else
                        return letters[m];
                }
            }
            throw runtime_error("not found");
        }
        char nextGreatestLetter2(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size();
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                    b = m + 1;
                else
                    e = m;
            }
            if (b == (int)letters.size())
                return letters[0];
            else
                return letters[b];
        }
        char nextGreatestLetter3(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size() - 1;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                    b = m;
                else
                    e = m;
            }
            if (target < letters[b])
                return letters[b];
            if (target < letters[e])
                return letters[e];
            return letters[0];
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

        // Search in a Binary Search Tree
        // Given the root node of a binary search tree (BST) and a value. You need to
        // find the node in the BST that the node's value equals the given value. Return
        // the subtree rooted with that node. If such node doesn't exist, you should
        // return NULL. For example, Given the tree:
        //         4
        //        / \
        //       2   7
        //      / \
        //     1   3
        // And the value to search: 2
        // You should return this subtree:
        //       2
        //      / \   
        //     1   3
        // In the example above, if we want to search the value 5, since there is no node
        // with value 5, we should return NULL.
        TreeNode *searchBST(TreeNode *root, int val)
        {
            TreeNode *n = root;
            while (n != nullptr)
            {
                if (n->val == val)
                    break;
                if (n->val > val)
                    n = n->left;
                else
                    n = n->right;
            }
            return n;
        }
        TreeNode *searchBST2(TreeNode *root, int val)
        {
            if (root == nullptr || root->val == val)
                return root;
            return val < root->val ? searchBST2(root->left, val) : searchBST2(root->right, val);
        }

        // Insert into a Binary Search Tree
        // Given the root node of a binary search tree (BST) and a value to be inserted
        // into the tree, insert the value into the BST. Return the root node of the BST
        // after the insertion. It is guaranteed that the new value does not exist in the
        // original BST. Note that there may exist multiple valid ways for the insertion,
        // as long as the tree remains a BST after insertion. You can return any of them.
        // For example, Given the tree:
        //         4
        //        / \
        //       2   7
        //      / \
        //     1   3
        // And the value to insert: 5
        // You can return this binary search tree:
        //          4
        //        /   \
        //       2     7
        //      / \   /
        //     1   3 5
        // This tree is also valid:
        //          5
        //        /   \
        //       2     7
        //      / \   
        //     1   3
        //          \
        //           4
        TreeNode *insertIntoBST(TreeNode *root, int val)
        {
            TreeNode *p = nullptr;
            TreeNode *n = root;
            while (n != nullptr)
            {
                p = n;
                if (n->val > val)
                    n = n->left;
                else
                    n = n->right;
            }
            n = new TreeNode(val);
            if (p == nullptr)
            {
                root = n;
            }
            else
            {
                if (p->val > val)
                    p->left = n;
                else
                    p->right = n;
            }
            return root;
        }

        // Delete Node in a BST
        // Given a root node reference of a BST and a key, delete the node with the given
        // key in the BST. Return the root node reference (possibly updated) of the BST.
        // Basically, the deletion can be divided into two stages:
        // Search for a node to remove.
        // If the node is found, delete the node.
        // Note: Time complexity should be O(height of tree).
        // Example:
        // root = [5,3,6,2,4,null,7]
        // key = 3
        //     5
        //    / \
        //   3   6
        //  / \   \
        // 2   4   7
        // Given key to delete is 3. So we find the node with value 3 and delete it.
        // One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
        //     5
        //    / \
        //   4   6
        //  /     \
        // 2       7
        // Another valid answer is [5,2,6,null,4,null,7].
        //     5
        //    / \
        //   2   6
        //    \   \
        //     4   7
        TreeNode *deleteNode(TreeNode *root, int key)
        {
            function<bool(TreeNode **, TreeNode **)> findNode = [&](TreeNode **parent, TreeNode **node) -> bool
            {
                *parent = nullptr;
                *node = root;
                while (*node != nullptr)
                {
                    if ((*node)->val == key)
                        break;
                    *parent = *node;
                    if ((*node)->val > key)
                        *node = (*node)->left;
                    else
                        *node = (*node)->right;
                }
                return (*node) != nullptr;
            };
            function<bool(TreeNode *, TreeNode **, TreeNode **)> findSuccessor =
                [&](TreeNode *node, TreeNode **parent, TreeNode **successor) -> bool
            {
                if (node == nullptr || node->right == nullptr)
                    return false;
                *parent = node;
                *successor = node->right;
                while ((*successor)->left != nullptr)
                {
                    *parent = *successor;
                    *successor = (*successor)->left;
                }
                return true;
            };
            TreeNode *parent = nullptr;
            TreeNode *node = nullptr;
            if (!findNode(&parent, &node))
                return root;
            TreeNode *successorParent = nullptr;
            TreeNode *successor = nullptr;
            if (!findSuccessor(node, &successorParent, &successor))
            {
                if (node == root)
                    root = node->left;
                else if (node == parent->left)
                    parent->left = node->left;
                else if (node == parent->right)
                    parent->right = node->left;
                node->left = nullptr;
                delete node;
                node = nullptr;
                return root;
            }
            TreeNode *successorChild = successor->right;
            if (successor == successorParent->left)
                successorParent->left = successorChild;
            else if (successor == successorParent->right)
                successorParent->right = successorChild;
            successor->right = nullptr;
            successor->left = node->left;
            successor->right = node->right;
            node->left = nullptr;
            node->right = nullptr;
            if (node == root)
                root = successor;
            else if (node == parent->left)
                parent->left = successor;
            else if (node == parent->right)
                parent->right = successor;
            delete node;
            node = nullptr;
            return root;
        }

        // Kth Largest Element in a Stream
        // Design a class to find the kth largest element in a stream. Note that it is
        // the kth largest element in the sorted order, not the kth distinct element.
        // Your KthLargest class will have a constructor which accepts an integer k and
        // an integer array nums, which contains initial elements from the stream. For
        // each call to the method KthLargest.add, return the element representing the
        // kth largest element in the stream.
        // Example:
        // int k = 3;
        // int[] arr = [4,5,8,2];
        // KthLargest kthLargest = new KthLargest(3, arr);
        // kthLargest.add(3);   // returns 4
        // kthLargest.add(5);   // returns 5
        // kthLargest.add(10);  // returns 5
        // kthLargest.add(9);   // returns 8
        // kthLargest.add(4);   // returns 8
        // Note: You may assume that nums' length >= k-1 and k >= 1.
        class KthLargest
        {
        private:
            struct Node
            {
                int val;
                Node *left;
                Node *right;
                int count;
                Node(int v) : val(v), left(nullptr), right(nullptr), count(1) {}
            };
            Node *_root;
            int _k;

            void insert(int v)
            {
                Node *parent = nullptr;
                Node *node = _root;
                while (node != nullptr)
                {
                    parent = node;
                    parent->count++;
                    if (node->val > v)
                        node = node->left;
                    else
                        node = node->right;
                }
                node = new Node(v);
                if (parent == nullptr)
                    _root = node;
                else if (parent->val > v)
                    parent->left = node;
                else
                    parent->right = node;
            }

            int find(int k)
            {
                Node *node = _root;
                while (node != nullptr)
                {
                    int rightCount = node->count - (node->left == nullptr ? 0 : node->left->count);
                    if (rightCount < k)
                    {
                        node = node->left;
                        k -= rightCount;
                    }
                    else if (rightCount > k)
                    {
                        node = node->right;
                    }
                    else
                    {
                        break;
                    }
                }
                if (node == nullptr)
                    throw runtime_error("Not found");
                return node->val;
            }

        public:
            KthLargest(int k, vector<int> &nums)
                : _root(nullptr), _k(k)
            {
                for (int n : nums)
                    insert(n);
            }

            int add(int val)
            {
                insert(val);
                return find(_k);
            }
        };

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
                            return true;
                        map<int, int>::iterator it2 = it;
                        it2++;
                        if (it2 == m.end())
                            break;
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

        // 222. Count Complete Tree Nodes
        // Given the root of a complete binary tree, return the number of the nodes in the tree.
        // According to Wikipedia, every level, except possibly the last, is completely filled in
        // a complete binary tree, and all nodes in the last level are as far left as possible.
        // It can have between 1 and 2h nodes inclusive at the last level h.
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

        // Max Consecutive Ones
        // Given a binary array, find the maximum number of consecutive 1s in this array.
        // Example 1:
        // Input: [1,1,0,1,1,1]
        // Output: 3
        // Explanation: The first two digits or the last three digits are consecutive 1s.
        // The maximum number of consecutive 1s is 3. Note: The input array will only contain 0 and 1.
        // The length of input array is a positive integer and will not exceed 10,000
        int findMaxConsecutiveOnes(const vector<int> &nums)
        {
            int c = 0;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] == 0)
                {
                    m = max(m, c);
                    c = 0;
                }
                else
                {
                    c++;
                }
            }
            m = max(m, c);
            return m;
        }

        // Find Numbers with Even Number of Digits
        // Given an array nums of integers, return how many of them contain an even number of digits.
        // Example 1:
        // Input: nums = [12,345,2,6,7896]
        // Output: 2
        // Explanation:
        // 12 contains 2 digits (even number of digits).
        // 345 contains 3 digits (odd number of digits).
        // 2 contains 1 digit (odd number of digits).
        // 6 contains 1 digit (odd number of digits).
        // 7896 contains 4 digits (even number of digits).
        // Therefore only 12 and 7896 contain an even number of digits.
        // Example 2:
        // Input: nums = [555,901,482,1771]
        // Output: 1
        // Explanation:
        // Only 1771 contains an even number of digits.
        // Constraints:
        // 1 <= nums.length <= 500
        // 1 <= nums[i] <= 10^5
        int findNumbers(const vector<int> &nums)
        {
            int c = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                int n = nums[i];
                int d = 0;
                while (n > 0)
                {
                    d++;
                    n /= 10;
                }
                if ((d & 0x1) == 0)
                    c++;
            }
            return c;
        }

        // Squares of a Sorted Array
        // Given an array of integers A sorted in non-decreasing order, return an array
        // of the squares of each number, also in sorted non-decreasing order.
        // Example 1:
        // Input: [-4,-1,0,3,10]
        // Output: [0,1,9,16,100]
        // Example 2:
        // Input: [-7,-3,2,3,11]
        // Output: [4,9,9,49,121]
        // Note:
        // 1 <= A.length <= 10000
        // -10000 <= A[i] <= 10000
        // A is sorted in non-decreasing order.
        vector<int> sortedSquares(const vector<int> &A)
        {
            vector<int> r;
            r.resize(A.size());
            int i = 0;
            int j = (int)A.size() - 1;
            int k = j;
            while (i <= j)
            {
                int a = abs(A[i]);
                int b = abs(A[j]);
                if (a <= b)
                {
                    r[k--] = b * b;
                    j--;
                }
                else
                {
                    r[k--] = a * a;
                    i++;
                }
            }
            return r;
        }
        vector<int> sortedSquares2(const vector<int> &A)
        {
            int i = 0;
            int n = (int)A.size();
            int j = n - 1;
            int k = -1;
            while (i + 1 < j)
            {
                k = i + ((j - i) >> 1);
                if (A[k] > 0)
                    j = k;
                else if (A[k] < 0)
                    i = k;
                else
                    break;
            }
            vector<int> r;
            if (i > j)
                return r;
            r.resize(n);
            int t = 0;
            if (i == j)
            {
                r[t++] = A[i] * A[i];
                return r;
            }
            if (i + 1 < j)
            {
                r[t++] = 0;
                i = k - 1;
                j = k + 1;
            }
            while (0 <= i || j < n)
            {
                if (0 <= i && j < n)
                {
                    int a = A[i] * A[i];
                    int b = A[j] * A[j];
                    if (a <= b)
                    {
                        r[t++] = a;
                        i--;
                    }
                    else
                    {
                        r[t++] = b;
                        j++;
                    }
                }
                else if (0 <= i)
                {
                    r[t++] = A[i] * A[i];
                    i--;
                }
                else
                {
                    r[t++] = A[j] * A[j];
                    j++;
                }
            }
            return r;
        }

        // Duplicate Zeros
        // Given a fixed length array arr of integers, duplicate each occurrence of zero,
        // shifting the remaining elements to the right. Note that elements beyond the
        // length of the original array are not written. Do the above modifications to
        // the input array in place, do not return anything from your function.
        // Example 1:
        // Input: [1,0,2,3,0,4,5,0]
        // Output: null
        // Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
        // Example 2:
        // Input: [1,2,3]
        // Output: null
        // Explanation: After calling your function, the input array is modified to: [1,2,3]
        // Note:
        // 1 <= arr.length <= 10000
        // 0 <= arr[i] <= 9
        void duplicateZeros(vector<int> &arr)
        {
            int n = (int)arr.size();
            int c = 0;
            for (int i = 0; i < n; i++)
            {
                if (arr[i] == 0)
                    c++;
            }
            for (int i = n - 1; i >= 0 && c > 0; i--)
            {
                int j = i + c;
                if (j < n)
                    arr[j] = arr[i];
                if (arr[i] == 0)
                {
                    if (j - 1 < n)
                        arr[j - 1] = 0;
                    c--;
                }
            }
        }

        // Check If N and Its Double Exist
        // Given an array arr of integers, check if there exists two integers N and M
        // such that N is the double of M ( i.e. N = 2 * M). More formally check if
        // there exists two indices i and j such that :
        // i != j
        // 0 <= i, j < arr.length
        // arr[i] == 2 * arr[j]
        // Example 1:
        // Input: arr = [10,2,5,3]
        // Output: true
        // Explanation: N = 10 is the double of M = 5,that is, 10 = 2 * 5.
        // Example 2:
        // Input: arr = [7,1,14,11]
        // Output: true
        // Explanation: N = 14 is the double of M = 7,that is, 14 = 2 * 7.
        // Example 3:
        // Input: arr = [3,1,7,11]
        // Output: false
        // Explanation: In this case does not exist N and M, such that N = 2 * M.
        // Constraints:
        // 2 <= arr.length <= 500
        // -10^3 <= arr[i] <= 10^3
        bool checkIfExist(const vector<int> &arr)
        {
            set<int> s;
            for (int i : arr)
            {
                if (s.find(i) != s.end())
                    return true;
                int j;
                if (i >= 0)
                    j = i << 1;
                else
                    j = -((-i) << 1);
                if (s.find(j) == s.end())
                    s.insert(j);
                if ((i & 0x1) == 0)
                {
                    j = i >> 1;
                    if (s.find(j) == s.end())
                        s.insert(j);
                }
            }
            return false;
        }

        // Valid Mountain Array
        // Given an array A of integers, return true if and only if it is a valid
        // mountain array. Recall that A is a mountain array if and only if:
        // A.length >= 3
        // There exists some i with 0 < i < A.length - 1 such that:
        // A[0] < A[1] < ... A[i-1] < A[i]
        // A[i] > A[i+1] > ... > A[A.length - 1]
        // Example 1:
        // Input: [2,1]
        // Output: false
        // Example 2:
        // Input: [3,5,5]
        // Output: false
        // Example 3:
        // Input: [0,3,2,1]
        // Output: true
        // Note:
        // 0 <= A.length <= 10000
        // 0 <= A[i] <= 10000
        bool validMountainArray(const vector<int> &A)
        {
            size_t i = 0;
            while (i + 1 < A.size() && A[i] < A[i + 1])
                i++;
            if (i == 0 || i + 1 >= A.size() || A[i] == A[i + 1])
                return false;
            while (i + 1 < A.size() && A[i] > A[i + 1])
                i++;
            return i + 1 == A.size();
        }
        bool validMountainArray2(const vector<int> &A)
        {
            if (A.size() < 3)
                return false;
            bool up = true;
            for (size_t i = 1; i < A.size(); i++)
            {
                if (A[i - 1] == A[i])
                    return false;
                if (A[i - 1] > A[i])
                {
                    if (i == 1)
                        return false;
                    if (up)
                        up = false;
                }
                else
                {
                    if (!up)
                        return false;
                }
            }
            return !up;
        }

        // Replace Elements with Greatest Element on Right Side
        // Given an array arr, replace every element in that array with the greatest
        // element among the elements to its right, and replace the last element with -1.
        // After doing so, return the array.
        // Example 1:
        // Input: arr = [17,18,5,4,6,1]
        // Output: [18,6,6,6,1,-1]
        // Constraints:
        // 1 <= arr.length <= 10^4
        // 1 <= arr[i] <= 10^5
        vector<int> replaceElements(vector<int> &arr)
        {
            int m = -1;
            for (int i = (int)arr.size() - 1; i >= 0; i--)
            {
                int t = arr[i];
                arr[i] = m;
                m = max(m, t);
            }
            return arr;
        }

        // Sort Array By Parity
        // Given an array A of non-negative integers, return an array consisting of all
        // the even elements of A, followed by all the odd elements of A.
        // You may return any answer array that satisfies this condition. Example 1:
        // Input: [3,1,2,4]
        // Output: [2,4,3,1]
        // The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
        // Note:
        // 1 <= A.length <= 5000
        // 0 <= A[i] <= 5000
        vector<int> sortArrayByParity(vector<int> &A)
        {
            int i = 0;
            int j = (int)A.size() - 1;
            while (i < j)
            {
                if ((A[i] & 0x1) == 0)
                    i++;
                else if ((A[j] & 0x1) == 1)
                    j--;
                else
                    swap(A[i++], A[j--]);
            }
            return A;
        }

        // Height Checker
        // Students are asked to stand in non-decreasing order of heights for an annual
        // photo. Return the minimum number of students that must move in order for all
        // students to be standing in non-decreasing order of height. Notice that when a
        // group of students is selected they can reorder in any possible way between
        // themselves and the non selected students remain on their seats.
        // Example 1:
        // Input: heights = [1,1,4,2,1,3]
        // Output: 3
        // Explanation:
        // Current array : [1,1,4,2,1,3]
        // Target array  : [1,1,1,2,3,4]
        // On index 2 (0-based) we have 4 vs 1 so we have to move this student.
        // On index 4 (0-based) we have 1 vs 3 so we have to move this student.
        // On index 5 (0-based) we have 3 vs 4 so we have to move this student.
        // Example 2:
        // Input: heights = [5,1,2,3,4]
        // Output: 5
        // Example 3:
        // Input: heights = [1,2,3,4,5]
        // Output: 0
        // Constraints:
        // 1 <= heights.length <= 100
        // 1 <= heights[i] <= 100
        int heightChecker(const vector<int> &heights)
        {
            vector<int> s(heights.begin(), heights.end());
            sort(s.begin(), s.end());
            int c = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (s[i] != heights[i])
                    c++;
            }
            return c;
        }

        // Third Maximum Number
        // Given a non-empty array of integers, return the third maximum number in this
        // array. If it does not exist, return the maximum number. The time complexity
        // must be in O(n).
        // Example 1:
        // Input: [3, 2, 1]
        // Output: 1
        // Explanation: The third maximum is 1.
        // Example 2:
        // Input: [1, 2]
        // Output: 2
        // Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
        // Example 3:
        // Input: [2, 2, 3, 1]
        // Output: 1
        // Explanation: Note that the third maximum here means the third maximum distinct number.
        // Both numbers with value 2 are both considered as second maximum.
        int thirdMax(const vector<int> &nums)
        {
            vector<int> m;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (m.empty())
                {
                    m.push_back(nums[i]);
                }
                else if (m.size() == 1)
                {
                    if (m[0] < nums[i])
                        m.push_back(nums[i]);
                    else if (m[0] > nums[i])
                        m.insert(m.begin(), nums[i]);
                }
                else if (m.size() == 2)
                {
                    if (m[1] < nums[i])
                        m.push_back(nums[i]);
                    else if (m[0] < nums[i] && nums[i] < m[1])
                        m.insert(m.begin() + 1, nums[i]);
                    else if (nums[i] < m[0])
                        m.insert(m.begin(), nums[i]);
                }
                else
                {
                    if (m[2] < nums[i])
                    {
                        m[0] = m[1];
                        m[1] = m[2];
                        m[2] = nums[i];
                    }
                    else if (m[1] < nums[i] && nums[i] < m[2])
                    {
                        m[0] = m[1];
                        m[1] = nums[i];
                    }
                    else if (m[0] < nums[i] && nums[i] < m[1])
                    {
                        m[0] = nums[i];
                    }
                }
            }
            return m.size() == 3 ? m[0] : m.back();
        }

        // Find All Numbers Disappeared in an Array
        // Given an array of integers where 1 <= a[i] <= n (n = size of array), some
        // elements appear twice and others appear once. Find all the elements of
        // [1, n] inclusive that do not appear in this array. Could you do it without
        // extra space and in O(n) runtime? You may assume the returned list does not
        // count as extra space. Example:
        // Input: [4,3,2,7,8,2,3,1]
        // Output: [5,6]
        vector<int> findDisappearedNumbers(vector<int> &nums)
        {
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (nums[i] != i + 1 and nums[i] != nums[nums[i] - 1])
                {
                    int t = nums[i];
                    nums[i] = nums[t - 1];
                    nums[t - 1] = t;
                }
            }
            vector<int> r;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (nums[i] != i + 1)
                    r.push_back(i + 1);
            }
            return r;
        }

        // Design Linked List
        // Design your implementation of the linked list. You can choose to use the
        // singly linked list or the doubly linked list. A node in a singly linked list
        // should have two attributes: val and next. val is the value of the current
        // node, and next is a pointer/reference to the next node. If you want to use
        // the doubly linked list, you will need one more attribute prev to indicate the
        // previous node in the linked list. Assume all nodes in the linked list are 0-indexed.
        // Implement these functions in your linked list class:
        // get(index) : Get the value of the index-th node in the linked list. If the index
        // is invalid, return -1.
        // addAtHead(val) : Add a node of value val before the first element of the linked
        // list. After the insertion, the new node will be the first node of the linked list.
        // addAtTail(val) : Append a node of value val to the last element of the linked list.
        // addAtIndex(index, val) : Add a node of value val before the index-th node in the
        // linked list. If index equals to the length of linked list, the node will be appended
        // to the end of linked list. If index is greater than the length, the node will not be inserted.
        // deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
        // Example:
        // Input:
        // ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
        // [[],[1],[3],[1,2],[1],[1],[1]]
        // Output:
        // [null,null,null,null,2,null,3]
        // Explanation:
        // MyLinkedList linkedList = new MyLinkedList(); // Initialize empty LinkedList
        // linkedList.addAtHead(1);
        // linkedList.addAtTail(3);
        // linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
        // linkedList.get(1);            // returns 2
        // linkedList.deleteAtIndex(1);  // now the linked list is 1->3
        // linkedList.get(1);            // returns 3
        // Constraints:
        // 0 <= index,val <= 1000
        // Please do not use the built-in LinkedList library.
        // At most 2000 calls will be made to get, addAtHead, addAtTail,  addAtIndex and deleteAtIndex.
        class MyLinkedList
        {
        private:
            struct Node
            {
                int val;
                Node *next;
                Node(int v) : val(v), next(nullptr) {}
            };

            Node *head;
            Node *tail;

        public:
            /** Initialize your data structure here. */
            MyLinkedList()
            {
                head = nullptr;
                tail = nullptr;
            }

            /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
            int get(int index)
            {
                Node *p = head;
                for (int i = 0; i < index && p != nullptr; i++)
                    p = p->next;
                return p == nullptr ? -1 : p->val;
            }

            /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
            void addAtHead(int val)
            {
                Node *n = new Node(val);
                n->next = head;
                head = n;
                if (tail == nullptr)
                    tail = n;
            }

            /** Append a node of value val to the last element of the linked list. */
            void addAtTail(int val)
            {
                Node *n = new Node(val);
                if (tail == nullptr)
                    head = n;
                else
                    tail->next = n;
                tail = n;
            }

            /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
            void addAtIndex(int index, int val)
            {
                if (index == 0)
                {
                    addAtHead(val);
                    return;
                }
                Node *p = head;
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index)
                {
                    Node *n = new Node(val);
                    n->next = p->next;
                    p->next = n;
                    if (n->next == nullptr)
                        tail = n;
                }
            }

            /** Delete the index-th node in the linked list, if the index is valid. */
            void deleteAtIndex(int index)
            {
                Node *p = head;
                if (index == 0)
                {
                    if (head != nullptr)
                    {
                        Node *p = head;
                        head = head->next;
                        delete p;
                        p = nullptr;
                        if (head == nullptr || head->next == nullptr)
                            tail = head;
                    }
                    return;
                }
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index && p->next != nullptr)
                {
                    Node *t = p->next;
                    if (tail == t)
                        tail = p;
                    p->next = t->next;
                    delete t;
                    t = nullptr;
                }
            }
        };
        class MyDoubleLinkedList
        {
        private:
            struct Node
            {
                int val;
                Node *prev;
                Node *next;
                Node(int v) : val(v), prev(nullptr), next(nullptr) {}
            };

            Node *head;
            Node *tail;

        public:
            /** Initialize your data structure here. */
            MyDoubleLinkedList()
            {
                head = nullptr;
                tail = nullptr;
            }

            /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
            int get(int index)
            {
                Node *p = head;
                for (int i = 0; i < index && p != nullptr; i++)
                    p = p->next;
                return p == nullptr ? -1 : p->val;
            }

            /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
            void addAtHead(int val)
            {
                Node *n = new Node(val);
                n->next = head;
                if (head != nullptr)
                    head->prev = n;
                head = n;
                if (tail == nullptr)
                    tail = n;
            }

            /** Append a node of value val to the last element of the linked list. */
            void addAtTail(int val)
            {
                Node *n = new Node(val);
                if (tail == nullptr)
                    head = n;
                else
                    tail->next = n;
                n->prev = tail;
                tail = n;
            }

            /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
            void addAtIndex(int index, int val)
            {
                if (index == 0)
                {
                    addAtHead(val);
                    return;
                }
                Node *p = head;
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index)
                {
                    Node *n = new Node(val);
                    n->next = p->next;
                    if (p->next != nullptr)
                        p->next->prev = n;
                    p->next = n;
                    n->prev = p;
                    if (n->next == nullptr)
                        tail = n;
                }
            }

            /** Delete the index-th node in the linked list, if the index is valid. */
            void deleteAtIndex(int index)
            {
                Node *p = head;
                if (index == 0)
                {
                    if (head != nullptr)
                    {
                        Node *p = head;
                        head = head->next;
                        delete p;
                        p = nullptr;
                        if (head == nullptr || head->next == nullptr)
                            tail = head;
                        else
                            head->prev = nullptr;
                    }
                    return;
                }
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index && p->next != nullptr)
                {
                    Node *t = p->next;
                    if (tail == t)
                        tail = p;
                    p->next = t->next;
                    if (t->next != nullptr)
                        t->next->prev = p;
                    delete t;
                    t = nullptr;
                }
            }
        };

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

        class MultilevelDoubleLinkedList
        {
        public:
            struct Node
            {
                int val;
                Node *prev;
                Node *next;
                Node *child;
            };

            // Flatten a Multilevel Doubly Linked List
            // You are given a doubly linked list which in addition to the next and previous
            // pointers, it could have a child pointer, which may or may not point to a
            // separate doubly linked list. These child lists may have one or more children
            // of their own, and so on, to produce a multilevel data structure, as shown in
            // the example below.
            // Flatten the list so that all the nodes appear in a single-level, doubly linked
            // list. You are given the head of the first level of the list.
            // Example 1:
            // Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
            // Output: [1,2,3,7,8,11,12,9,10,4,5,6]
            // Explanation:
            // The multilevel linked list in the input is as follows:
            // After flattening the multilevel linked list it becomes:
            // Example 2:
            // Input: head = [1,2,null,3]
            // Output: [1,3,2]
            // Explanation:
            // The input multilevel linked list is as follows:
            //   1---2---NULL
            //   |
            //   3---NULL
            // Example 3:
            // Input: head = []
            // Output: []
            // How multilevel linked list is represented in test case:
            // We use the multilevel linked list from Example 1 above:
            //  1---2---3---4---5---6--NULL
            //          |
            //          7---8---9---10--NULL
            //              |
            //              11--12--NULL
            // The serialization of each level is as follows:
            // [1,2,3,4,5,6,null]
            // [7,8,9,10,null]
            // [11,12,null]
            // To serialize all levels together we will add nulls in each level to signify no node connects to the upper node of the previous level. The serialization becomes:
            // [1,2,3,4,5,6,null]
            // [null,null,7,8,9,10,null]
            // [null,11,12,null]
            // Merging the serialization of each level and removing trailing nulls we obtain:
            // [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
            // Constraints:
            // Number of Nodes will not exceed 1000.
            // 1 <= Node.val <= 10^5
            Node *flatten(Node *head)
            {
                if (head == nullptr)
                    return nullptr;
                function<Node *(Node *)> flat = [&](Node *h) -> Node *
                {
                    Node *t = h;
                    while (h != nullptr)
                    {
                        if (h->child == nullptr)
                        {
                            t = h;
                            h = h->next;
                        }
                        else
                        {
                            Node *ch = h->child;
                            Node *ct = flat(ch);
                            ct->next = h->next;
                            if (h->next != nullptr)
                                h->next->prev = ct;
                            h->next = ch;
                            ch->prev = h;
                            h->child = nullptr;
                            t = ct;
                            h = ct->next;
                        }
                    }
                    return t;
                };
                flat(head);
                return head;
            }
            Node *flatten2(Node *head)
            {
                stack<Node *> s;
                Node *n = head;
                Node *t = head;
                while (!s.empty() || n != nullptr)
                {
                    if (n != nullptr)
                    {
                        if (n->child == nullptr)
                        {
                            t = n;
                            n = n->next;
                        }
                        else
                        {
                            s.push(n);
                            n = n->child;
                            t = n;
                        }
                    }
                    else
                    {
                        n = s.top();
                        s.pop();
                        t->next = n->next;
                        if (n->next != nullptr)
                            n->next->prev = t;
                        n->next = n->child;
                        n->child->prev = n;
                        n->child = nullptr;
                        n = t->next;
                    }
                }
                return head;
            }
        };

        // Find Pivot Index
        // Given an array of integers nums, write a method that returns the "pivot"
        // index of this array. We define the pivot index as the index where the sum
        // of the numbers to the left of the index is equal to the sum of the numbers
        // to the right of the index. If no such index exists, we should return -1. If
        // there are multiple pivot indexes, you should return the left-most pivot index.
        // Example 1:
        // Input:
        // nums = [1, 7, 3, 6, 5, 6]
        // Output: 3
        // Explanation:
        // The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the
        // sum of numbers to the right of index 3. Also, 3 is the first index where this occurs.
        // Example 2:
        // Input:
        // nums = [1, 2, 3]
        // Output: -1
        // Explanation:
        // There is no index that satisfies the conditions in the problem statement.
        // Note:
        // The length of nums will be in the range [0, 10000].
        // Each element nums[i] will be an integer in the range [-1000, 1000].
        // Hide Hint #1
        // We can precompute prefix sums P[i] = nums[0] + nums[1] + ... + nums[i-1]. Then
        // for each index, the left sum is P[i], and the right sum is P[P.length - 1] - P[i] - nums[i].
        int pivotIndex(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            vector<int> p(nums.size());
            int s = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                s += nums[i];
                p[i] = s;
            }
            if (p[nums.size() - 1] - nums[0] == 0)
                return 0;
            for (size_t i = 1; i + 1 < nums.size(); i++)
            {
                if (p[i - 1] == p[nums.size() - 1] - nums[i] - p[i - 1])
                    return i;
            }
            if (p[nums.size() - 1] - nums[nums.size() - 1] == 0)
                return nums.size() - 1;
            return -1;
        }

        // Largest Number At Least Twice of Others
        // In a given integer array nums, there is always exactly one largest element.
        // Find whether the largest element in the array is at least twice as much as
        // every other number in the array. If it is, return the index of the largest
        // element, otherwise return -1.
        // Example 1:
        // Input: nums = [3, 6, 1, 0]
        // Output: 1
        // Explanation: 6 is the largest integer, and for every other number in the array x,
        // 6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
        // Example 2:
        // Input: nums = [1, 2, 3, 4]
        // Output: -1
        // Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.
        // Note:
        // nums will have a length in the range [1, 50].
        // Every nums[i] will be an integer in the range [0, 99].
        // Hide Hint #1
        // Scan through the array to find the unique largest element m, keeping track of
        // it's index maxIndex. Scan through the array again. If we find some x != m
        // with m < 2*x, we should return -1. Otherwise, we should return maxIndex.
        int dominantIndex(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            if (nums.size() == 1)
                return 0;
            int a;
            int b;
            if (nums[0] <= nums[1])
            {
                a = 0;
                b = 1;
            }
            else
            {
                a = 1;
                b = 0;
            }
            for (size_t i = 2; i < nums.size(); i++)
            {
                if (nums[b] <= nums[i])
                {
                    a = b;
                    b = i;
                }
                else if (nums[a] <= nums[i])
                {
                    a = i;
                }
            }
            if ((nums[a] << 1) <= nums[b])
                return b;
            else
                return -1;
        }

        // Diagonal Traverse
        // Given a matrix of M x N elements (M rows, N columns), return all elements of
        // the matrix in diagonal order as shown in the below image.
        // Example:
        // Input:
        // [
        //  [ 1, 2, 3 ],
        //  [ 4, 5, 6 ],
        //  [ 7, 8, 9 ]
        // ]
        // Output:  [1,2,4,7,5,3,6,8,9]
        // The total number of elements of the given matrix will not exceed 10,000.
        vector<int> findDiagonalOrder(const vector<vector<int>> &matrix)
        {
            vector<int> o;
            if (matrix.empty() || matrix[0].empty())
                return o;
            bool up = true;
            int m = (int)matrix.size();
            int n = (int)matrix[0].size();
            for (int j = 0; j < n; j++)
            {
                if (up)
                {
                    for (int i = min(m - 1, j); i >= 0; i--)
                        o.push_back(matrix[i][j - i]);
                }
                else
                {
                    for (int i = 0; i <= min(m - 1, j); i++)
                        o.push_back(matrix[i][j - i]);
                }
                up = !up;
            }
            for (int i = 1; i < m; i++)
            {
                if (up)
                {
                    for (int j = max(0, n - m + i); j < n; j++)
                        o.push_back(matrix[n - 1 - j + i][j]);
                }
                else
                {
                    for (int j = n - 1; j >= max(0, n - m + i); j--)
                        o.push_back(matrix[n - 1 - j + i][j]);
                }
                up = !up;
            }
            return o;
        }

        // Reverse String
        // Write a function that reverses a string. The input string is given as
        // an array of characters char[]. Do not allocate extra space for another
        // array, you must do this by modifying the input array in-place with O(1)
        // extra memory. You may assume all the characters consist of printable
        // ascii characters.
        // Example 1:
        // Input: ["h","e","l","l","o"]
        // Output: ["o","l","l","e","h"]
        // Example 2:
        // Input: ["H","a","n","n","a","h"]
        // Output: ["h","a","n","n","a","H"]
        void reverseString(vector<char> &s)
        {
            int i = 0;
            int j = (int)s.size() - 1;
            while (i < j)
                swap(s[i++], s[j--]);
        }
        void reverseString2(vector<char> &s)
        {
            function<void(int, int)> reverse = [&](int i, int j)
            {
                if (i >= j)
                    return;
                swap(s[i], s[j]);
                reverse(i + 1, j - 1);
            };
            reverse(0, (int)s.size() - 1);
        }

        // Array Partition I
        // Given an array of 2n integers, your task is to group these integers into n
        // pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of
        // min(ai, bi) for all i from 1 to n as large as possible.
        // Example 1:
        // Input: [1,4,3,2]
        // Output: 4
        // Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
        // Note:
        // n is a positive integer, which is in the range of [1, 10000].
        // All the integers in the array will be in the range of [-10000, 10000].
        // Suppose a0 < a1 < a2 < a3, then
        // min(a0, a1) + min(a2, a3) > min(a0, a2) + min(a1, a3)
        int arrayPairSum(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            int s = 0;
            for (size_t i = 0; i < nums.size(); i += 2)
                s += nums[i];
            return s;
        }

        // Design Circular Queue
        // Design your implementation of the circular queue. The circular queue is a
        // linear data structure in which the operations are performed based on FIFO
        // (First In First Out) principle and the last position is connected back to
        // the first position to make a circle. It is also called "Ring Buffer".
        // One of the benefits of the circular queue is that we can make use of the
        // spaces in front of the queue. In a normal queue, once the queue becomes
        // full, we cannot insert the next element even if there is a space in front
        // of the queue. But using the circular queue, we can use the space to store
        // new values. Your implementation should support following operations:
        // MyCircularQueue(k): Constructor, set the size of the queue to be k.
        // Front: Get the front item from the queue. If the queue is empty, return -1.
        // Rear: Get the last item from the queue. If the queue is empty, return -1.
        // enQueue(value): Insert an element into the circular queue. Return true if the operation is successful.
        // deQueue(): Delete an element from the circular queue. Return true if the operation is successful.
        // isEmpty(): Checks whether the circular queue is empty or not.
        // isFull(): Checks whether the circular queue is full or not.
        // Example:
        // MyCircularQueue circularQueue = new MyCircularQueue(3); // set the size to be 3
        // circularQueue.enQueue(1);  // return true
        // circularQueue.enQueue(2);  // return true
        // circularQueue.enQueue(3);  // return true
        // circularQueue.enQueue(4);  // return false, the queue is full
        // circularQueue.Rear();  // return 3
        // circularQueue.isFull();  // return true
        // circularQueue.deQueue();  // return true
        // circularQueue.enQueue(4);  // return true
        // circularQueue.Rear();  // return 4
        // Note:
        // All values will be in the range of [0, 1000].
        // The number of operations will be in the range of [1, 1000].
        // Please do not use the built-in Queue library.
        class MyCircularQueue
        {
        private:
            vector<int> que;
            int head;
            int tail;

        public:
            /** Initialize your data structure here. Set the size of the queue to be k. */
            MyCircularQueue(int k)
            {
                que.resize(k);
                head = -1;
                tail = -1;
            }

            /** Insert an element into the circular queue. Return true if the operation is successful. */
            bool enQueue(int value)
            {
                if (isFull())
                    return false;
                if (head == -1)
                {
                    head = 0;
                    tail = 0;
                }
                else
                {
                    tail = (tail + 1) % (int)que.size();
                }
                que[tail] = value;
                return true;
            }

            /** Delete an element from the circular queue. Return true if the operation is successful. */
            bool deQueue()
            {
                if (isEmpty())
                    return false;
                if (head == tail)
                {
                    head = -1;
                    tail = -1;
                }
                else
                {
                    head = (head + 1) % (int)que.size();
                }
                return true;
            }

            /** Get the front item from the queue. */
            int Front()
            {
                return isEmpty() ? -1 : que[head];
            }

            /** Get the last item from the queue. */
            int Rear()
            {
                return isEmpty() ? -1 : que[tail];
            }

            /** Checks whether the circular queue is empty or not. */
            bool isEmpty()
            {
                return head == -1;
            }

            /** Checks whether the circular queue is full or not. */
            bool isFull()
            {
                return ((tail + 1) % (int)que.size()) == head;
            }
        };

        // Open the Lock
        // You have a lock in front of you with 4 circular wheels. Each wheel has 10
        // slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can
        // rotate freely and wrap around: for example we can turn '9' to be '0', or
        // '0' to be '9'. Each move consists of turning one wheel one slot.
        // The lock initially starts at '0000', a string representing the state of the 4 wheels.
        // You are given a list of deadends dead ends, meaning if the lock displays
        // any of these codes, the wheels of the lock will stop turning and you will
        // be unable to open it. Given a target representing the value of the wheels
        // that will unlock the lock, return the minimum total number of turns required
        // to open the lock, or -1 if it is impossible.
        // Example 1:
        // Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
        // Output: 6
        // Explanation:
        // A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
        // Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
        // because the wheels of the lock become stuck after the display becomes the dead end "0102".
        // Example 2:
        // Input: deadends = ["8888"], target = "0009"
        // Output: 1
        // Explanation:
        // We can turn the last wheel in reverse to move from "0000" -> "0009".
        // Example 3:
        // Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
        // Output: -1
        // Explanation:
        // We can't reach the target without getting stuck.
        // Example 4:
        // Input: deadends = ["0000"], target = "8888"
        // Output: -1
        // Note:
        // The length of deadends will be in the range [1, 500].
        // target will not be in the list deadends.
        // Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.
        int openLock(const vector<string> &deadends, const string &target)
        {
            set<string> deadendset(deadends.begin(), deadends.end());
            if (deadendset.find("0000") != deadendset.end())
                return -1;
            set<string> visited;
            queue<string> currentq;
            currentq.push("0000");
            visited.insert("0000");
            queue<string> nextq;
            int c = 0;
            while (!currentq.empty())
            {
                while (!currentq.empty())
                {
                    string s = currentq.front();
                    currentq.pop();
                    if (s == target)
                        return c;
                    for (int i = 0; i < 4; i++)
                    {
                        string n = s;
                        n[i] = '0' + ((s[i] - '0' + 9) % 10);
                        if (deadendset.find(n) == deadendset.end() && visited.find(n) == visited.end())
                        {
                            nextq.push(n);
                            visited.insert(n);
                        }
                        n = s;
                        n[i] = '0' + ((s[i] - '0' + 1) % 10);
                        if (deadendset.find(n) == deadendset.end() && visited.find(n) == visited.end())
                        {
                            nextq.push(n);
                            visited.insert(n);
                        }
                    }
                }
                c++;
                currentq.swap(nextq);
            }
            return -1;
        }

        // Daily Temperatures
        // Given a list of daily temperatures T, return a list such that, for each day
        // in the input, tells you how many days you would have to wait until a warmer
        // temperature. If there is no future day for which this is possible, put 0 instead.
        // For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73],
        // your output should be [1, 1, 4, 2, 1, 1, 0, 0].
        // Note: The length of temperatures will be in the range [1, 30000]. Each
        // temperature will be an integer in the range [30, 100].
        vector<int> dailyTemperatures(const vector<int> &T)
        {
            vector<int> o(T.size(), 0);
            stack<int> s;
            for (int i = 0; i < (int)T.size(); i++)
            {
                while (!s.empty() && T[s.top()] < T[i])
                {
                    int j = s.top();
                    s.pop();
                    o[j] = i - j;
                }
                s.push(i);
            }
            return o;
        }
        vector<int> dailyTemperatures2(const vector<int> &T)
        {
            vector<int> o(T.size(), 0);
            stack<int> s;
            for (int i = (int)T.size() - 1; i >= 0; i--)
            {
                while (!s.empty() && T[i] >= T[s.top()])
                    s.pop();
                if (s.empty())
                    o[i] = 0;
                else
                    o[i] = s.top() - i;
                s.push(i);
            }
            return o;
        }

        // Target Sum
        // You are given a list of non-negative integers, a1, a2, ..., an, and a
        // target, S. Now you have 2 symbols + and -. For each integer, you should
        // choose one from + and - as its new symbol. Find out how many ways to
        // assign symbols to make sum of integers equal to target S.
        // Example 1:
        // Input: nums is [1, 1, 1, 1, 1], S is 3.
        // Output: 5
        // Explanation:
        // -1+1+1+1+1 = 3
        // +1-1+1+1+1 = 3
        // +1+1-1+1+1 = 3
        // +1+1+1-1+1 = 3
        // +1+1+1+1-1 = 3
        // There are 5 ways to assign symbols to make the sum of nums be target 3.
        // Note:
        // The length of the given array is positive and will not exceed 20.
        // The sum of elements in the given array will not exceed 1000.
        // Your output answer is guaranteed to be fitted in a 32-bit integer.
        int findTargetSumWays(const vector<int> &nums, int S)
        {
            map<pair<int, long long>, int> m;
            // Use long long because may overflow if it is INT_MAX
            function<int(int, long long)> count = [&](int i, long long a) -> int
            {
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ")" << endl;
                if (i >= (int)nums.size())
                    return a == 0 ? 1 : 0;
                pair<int, long long> p = make_pair(i, a);
                if (m.find(p) == m.end())
                    m[p] = count(i + 1, a + nums[i]) + count(i + 1, a - nums[i]);
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ") = " << m[p] << endl;
                return m[p];
            };
            return count(0, S);
        }
        int findTargetSumWays2(const vector<int> &nums, int S)
        {
            map<pair<int, long long>, int> m;
            // Use long long because may overflow if it is INT_MAX
            function<int(int, long long)> count = [&](int i, long long a) -> int
            {
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ")" << endl;
                if (i >= (int)nums.size())
                    return 0;
                pair<int, long long> p = make_pair(i, a);
                if (m.find(p) == m.end())
                {
                    if (i + 1 == (int)nums.size())
                        m[p] = ((a == nums[i] || -a == nums[i]) ? (a == 0 ? 2 : 1) : 0);
                    else
                        m[p] = count(i + 1, a + nums[i]) + count(i + 1, a - nums[i]);
                }
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ") = " << m[p] << endl;
                return m[p];
            };
            return count(0, S);
        }
        int findTargetSumWays3(const vector<int> &nums, int S)
        {
            int c = 0;
            function<void(int, int)> count = [&](int i, int a)
            {
                if (i >= (int)nums.size())
                {
                    if (a == S)
                        c++;
                    return;
                }
                count(i + 1, a - nums[i]);
                count(i + 1, a + nums[i]);
            };
            count(0, 0);
            return c;
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
        // F(CBA) = F(C00 - 1) + F(BA) + C == 1 ? (BA + 1) : 0
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
        vector<int> maxSlidingWindow3(vector<int> &nums, int k)
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

        // Decode String
        // Given an encoded string, return its decoded string.
        // The encoding rule is: k[encoded_string], where the encoded_string inside the
        // square brackets is being repeated exactly k times. Note that k is guaranteed
        // to be a positive integer. You may assume that the input string is always valid;
        // No extra white spaces, square brackets are well-formed, etc. Furthermore, you
        // may assume that the original data does not contain any digits and that digits
        // are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
        // Examples:
        // s = "3[a]2[bc]", return "aaabcbc".
        // s = "3[a2[c]]", return "accaccacc".
        // s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
        string decodeString(const string &s)
        {
            function<string(size_t &)> decode = [&](size_t &i) -> string
            {
                if (i >= s.size())
                    return "";
                ostringstream oss;
                while (i < s.size())
                {
                    while (i < s.size() && (s[i] < '0' || s[i] > '9') && s[i] != ']')
                        oss << s[i++];
                    if (i >= s.size())
                        break;
                    if (s[i] == ']')
                    {
                        i++;
                        break;
                    }
                    int k = 0;
                    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
                        k = (k * 10) + s[i++] - '0';
                    i++; // skip '['
                    string c = decode(i);
                    for (; k > 0; k--)
                        oss << c;
                }
                return oss.str();
            };
            size_t i = 0;
            return decode(i);
        }
        string decodeString2(const string &s)
        {
            stack<pair<string, int>> stk;
            string o;
            size_t i = 0;
            while (i < s.size())
            {
                if ((s[i] < '0' || s[i] > '9') && s[i] != ']')
                {
                    o.append(1, s[i++]);
                }
                else if (s[i] == ']')
                {
                    pair<string, int> p = stk.top();
                    stk.pop();
                    for (; p.second > 0; p.second--)
                        p.first.append(o);
                    o = p.first;
                    i++;
                }
                else
                {
                    int k = 0;
                    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
                        k = k * 10 + s[i++] - '0';
                    i++; // skip '['
                    stk.push(make_pair(o, k));
                    o = "";
                }
            }
            return o;
        }

        // Flood Fill
        // An image is represented by a 2-D array of integers, each integer representing
        // the pixel value of the image (from 0 to 65535). Given a coordinate (sr, sc)
        // representing the starting pixel (row and column) of the flood fill, and a pixel
        // value newColor, "flood fill" the image. To perform a "flood fill", consider
        // the starting pixel, plus any pixels connected 4-directionally to the starting
        // pixel of the same color as the starting pixel, plus any pixels connected
        // 4-directionally to those pixels (also with the same color as the starting pixel),
        // and so on. Replace the color of all of the aforementioned pixels with the newColor.
        // At the end, return the modified image.
        // Example 1:
        // Input:
        // image = [[1,1,1],
        //          [1,1,0],
        //          [1,0,1]]
        // sr = 1, sc = 1, newColor = 2
        // Output: [[2,2,2],
        //          [2,2,0],
        //          [2,0,1]]
        // Explanation:
        // From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
        // by a path of the same color as the starting pixel are colored with the new color.
        // Note the bottom corner is not colored 2, because it is not 4-directionally connected
        // to the starting pixel. Note:
        // The length of image and image[0] will be in the range [1, 50].
        // The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
        // The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
        vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            if (c == newColor)
                return image; // no change needed
            int m = (int)image.size();
            int n = (int)image[0].size();
            function<void(int, int)> flood = [&](int i, int j)
            {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                image[i][j] = newColor;
                flood(i - 1, j);
                flood(i, j + 1);
                flood(i + 1, j);
                flood(i, j - 1);
            };
            flood(sr, sc);
            return image;
        }
        vector<vector<int>> floodFill2(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            int m = (int)image.size();
            int n = (int)image[0].size();
            stack<pair<int, int>> path;
            set<pair<int, int>> visited;
            path.push(make_pair(sr, sc));
            visited.insert(path.top());
            function<void(int, int)> check = [&](int i, int j)
            {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                pair<int, int> p = make_pair(i, j);
                if (visited.find(p) == visited.end())
                {
                    path.push(p);
                    visited.insert(p);
                }
            };
            while (!path.empty())
            {
                pair<int, int> p = path.top();
                path.pop();
                image[p.first][p.second] = newColor;
                check(p.first - 1, p.second);
                check(p.first, p.second + 1);
                check(p.first + 1, p.second);
                check(p.first, p.second - 1);
            }
            return image;
        }
        vector<vector<int>> floodFill3(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            int m = (int)image.size();
            int n = (int)image[0].size();
            queue<pair<int, int>> front;
            set<pair<int, int>> visited;
            front.push(make_pair(sr, sc));
            visited.insert(front.front());
            function<void(int, int)> check = [&](int i, int j)
            {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                pair<int, int> p = make_pair(i, j);
                if (visited.find(p) == visited.end())
                {
                    front.push(p);
                    visited.insert(p);
                }
            };
            while (!front.empty())
            {
                pair<int, int> p = front.front();
                front.pop();
                image[p.first][p.second] = newColor;
                check(p.first - 1, p.second);
                check(p.first, p.second + 1);
                check(p.first + 1, p.second);
                check(p.first, p.second - 1);
            }
            return image;
        }

        // 01 Matrix
        // Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
        // The distance between two adjacent cells is 1.
        // Example 1:
        // Input:
        // [[0,0,0],
        //  [0,1,0],
        //  [0,0,0]]
        // Output:
        // [[0,0,0],
        //  [0,1,0],
        //  [0,0,0]]
        // Example 2:
        // Input:
        // [[0,0,0],
        //  [0,1,0],
        //  [1,1,1]]
        // Output:
        // [[0,0,0],
        //  [0,1,0],
        //  [1,2,1]]
        // Note:
        // The number of elements of the given matrix will not exceed 10,000.
        // There are at least one 0 in the given matrix.
        // The cells are adjacent in only four directions: up, down, left and right.
        vector<vector<int>> updateMatrix(const vector<vector<int>> &matrix)
        {
            vector<vector<int>> d(matrix);
            int m = (int)matrix.size();
            int n = (int)matrix[0].size();
            function<void(int, int)> search = [&](int i, int j)
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return;
                queue<pair<int, int>> current;
                queue<pair<int, int>> next;
                set<pair<int, int>> visited;
                pair<int, int> p = make_pair(i, j);
                current.push(p);
                visited.insert(p);
                int l = 0;
                function<void(int, int)> check = [&](int a, int b)
                {
                    if (a < 0 || a >= m || b < 0 || b >= n)
                        return;
                    pair<int, int> t = make_pair(a, b);
                    if (visited.find(t) == visited.end())
                    {
                        next.push(t);
                        visited.insert(t);
                    }
                };
                while (!current.empty())
                {
                    while (!current.empty())
                    {
                        p = current.front();
                        current.pop();
                        if (matrix[p.first][p.second] == 0)
                        {
                            d[i][j] = l;
                            return;
                        }
                        check(p.first - 1, p.second);
                        check(p.first, p.second + 1);
                        check(p.first + 1, p.second);
                        check(p.first, p.second - 1);
                    }
                    l++;
                    current.swap(next);
                }
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    search(i, j);
                }
            }
            return d;
        }

        // Keys and Rooms
        // There are N rooms and you start in room 0.  Each room has a distinct number
        // in 0, 1, 2, ..., N-1, and each room may have some keys to access the next room.
        // Formally, each room i has a list of keys rooms[i], and each key rooms[i][j]
        // is an integer in [0, 1, ..., N-1] where N = rooms.length.
        // A key rooms[i][j] = v opens the room with number v.
        // Initially, all the rooms start locked (except for room 0).
        // You can walk back and forth between rooms freely.
        // Return true if and only if you can enter every room.
        // Example 1:
        // Input: [[1],[2],[3],[]]
        // Output: true
        // Explanation:
        // We start in room 0, and pick up key 1.
        // We then go to room 1, and pick up key 2.
        // We then go to room 2, and pick up key 3.
        // We then go to room 3.  Since we were able to go to every room, we return true.
        // Example 2:
        // Input: [[1,3],[3,0,1],[2],[0]]
        // Output: false
        // Explanation: We can't enter the room with number 2.
        // Note:
        // 1 <= rooms.length <= 1000
        // 0 <= rooms[i].length <= 1000
        // The number of keys in all rooms combined is at most 3000.
        bool canVisitAllRooms(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            stack<int> path;
            path.push(0);
            visited.insert(0);
            while (!path.empty())
            {
                int i = path.top();
                path.pop();
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                    {
                        path.push(r);
                        visited.insert(r);
                    }
                }
            }
            return visited.size() == rooms.size();
        }
        bool canVisitAllRooms2(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            function<void(int)> visit = [&](int i)
            {
                if (i >= (int)rooms.size())
                    return;
                visited.insert(i);
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                        visit(r);
                }
            };
            visit(0);
            return visited.size() == rooms.size();
        }
        bool canVisitAllRooms3(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            queue<int> q;
            q.push(0);
            visited.insert(0);
            while (!q.empty())
            {
                int i = q.front();
                q.pop();
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                    {
                        q.push(r);
                        visited.insert(r);
                    }
                }
            }
            return visited.size() == rooms.size();
        }

        // Design HashSet
        // Design a HashSet without using any built-in hash table libraries.
        // To be specific, your design should include these functions:
        // add(value): Insert a value into the HashSet.
        // contains(value) : Return whether the value exists in the HashSet or not.
        // remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.
        // Example:
        // MyHashSet hashSet = new MyHashSet();
        // hashSet.add(1);
        // hashSet.add(2);
        // hashSet.contains(1);    // returns true
        // hashSet.contains(3);    // returns false (not found)
        // hashSet.add(2);
        // hashSet.contains(2);    // returns true
        // hashSet.remove(2);
        // hashSet.contains(2);    // returns false (already removed)
        // Note:
        // All values will be in the range of [0, 1000000].
        // The number of operations will be in the range of [1, 10000].
        // Please do not use the built-in HashSet library.
        class MyHashSet
        {
        private:
            vector<vector<int>> set;
            int n;

        public:
            /** Initialize your data structure here. */
            MyHashSet()
            {
                n = 10000;
                set.resize(n);
            }

            void add(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end() && (*it != key))
                    it++;
                if (it == set[k].end())
                    set[k].push_back(key);
            }

            void remove(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end())
                {
                    if (*it == key)
                    {
                        set[k].erase(it);
                        break;
                    }
                    else
                    {
                        it++;
                    }
                }
            }

            /** Returns true if this set contains the specified element */
            bool contains(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end() && (*it != key))
                    it++;
                return it != set[k].end();
            }
        };

        // Design HashMap
        // Design a HashMap without using any built-in hash table libraries.
        // To be specific, your design should include these functions:
        // put(key, value) : Insert a (key, value) pair into the HashMap.
        // If the value already exists in the HashMap, update the value.
        // get(key): Returns the value to which the specified key is mapped,
        // or -1 if this map contains no mapping for the key.
        // remove(key) : Remove the mapping for the value key if this map
        // contains the mapping for the key.
        // Example:
        // MyHashMap hashMap = new MyHashMap();
        // hashMap.put(1, 1);
        // hashMap.put(2, 2);
        // hashMap.get(1);            // returns 1
        // hashMap.get(3);            // returns -1 (not found)
        // hashMap.put(2, 1);          // update the existing value
        // hashMap.get(2);            // returns 1
        // hashMap.remove(2);          // remove the mapping for 2
        // hashMap.get(2);            // returns -1 (not found)
        // Note:
        // All keys and values will be in the range of [0, 1000000].
        // The number of operations will be in the range of [1, 10000].
        // Please do not use the built-in HashMap library.
        class MyHashMap
        {
        private:
            vector<vector<pair<int, int>>> v;
            int n;

        public:
            /** Initialize your data structure here. */
            MyHashMap()
            {
                n = 10000;
                v.resize(n);
            }

            /** value will always be non-negative. */
            void put(int key, int value)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                if (it == v[k].end())
                    v[k].push_back(make_pair(key, value));
                else
                    it->second = value;
            }

            /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
            int get(int key)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                return it == v[k].end() ? -1 : it->second;
            }

            /** Removes the mapping of the specified value key if this map contains a mapping for the key */
            void remove(int key)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                if (it != v[k].end())
                    v[k].erase(it);
            }
        };

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

        // Minimum Index Sum of Two Lists
        // Suppose Andy and Doris want to choose a restaurant for dinner, and
        // they both have a list of favorite restaurants represented by strings.
        // You need to help them find out their common interest with the least
        // list index sum. If there is a choice tie between answers, output all
        // of them with no order requirement. You could assume there always exists an answer.
        // Example 1:
        // Input:
        // ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        // ["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
        // Output: ["Shogun"]
        // Explanation: The only restaurant they both like is "Shogun".
        // Example 2:
        // Input:
        // ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        // ["KFC", "Shogun", "Burger King"]
        // Output: ["Shogun"]
        // Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
        // Note:
        // The length of both lists will be in the range of [1, 1000].
        // The length of strings in both lists will be in the range of [1, 30].
        // The index is starting from 0 to the list length minus 1.
        // No duplicates in both lists.
        vector<string> findRestaurant(const vector<string> &list1, const vector<string> &list2)
        {
            vector<string> o;
            function<void(const vector<string> &, const vector<string> &)> solve =
                [&](const vector<string> &l1, const vector<string> &l2)
            {
                map<string, int> m;
                int minIndex = INT_MAX;
                for (int i = 0; i < (int)l1.size(); i++)
                    m[l1[i]] = i;
                for (int i = 0; i < (int)l2.size(); i++)
                {
                    if (m.find(l2[i]) != m.end())
                    {
                        int j = m[l2[i]] + i;
                        if (j < minIndex)
                        {
                            o.clear();
                            o.push_back(l2[i]);
                            minIndex = j;
                        }
                        else if (j == minIndex)
                        {
                            o.push_back(l2[i]);
                        }
                    }
                }
            };
            if (list1.size() < list2.size())
                solve(list1, list2);
            else
                solve(list2, list1);
            return o;
        }

        // First Unique Character in a String
        // Given a string, find the first non-repeating character in it
        // and return it's index. If it doesn't exist, return -1.
        // Examples:
        // s = "leetcode"
        // return 0.
        // s = "loveleetcode",
        // return 2.
        // Note: You may assume the string contain only lowercase letters.
        int firstUniqChar(const string &s)
        {
            map<char, int> m;
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (m.find(s[i]) == m.end())
                    m[s[i]] = 1;
                else
                    m[s[i]]++;
            }
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (m[s[i]] == 1)
                    return i;
            }
            return -1;
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

        // Find Duplicate Subtrees
        // Given a binary tree, return all duplicate subtrees. For each kind of duplicate
        // subtrees, you only need to return the root node of any one of them.
        // Two trees are duplicate if they have the same structure with same node values.
        // Example 1:
        //         1
        //        / \
        //       2   3
        //      /   / \
        //     4   2   4
        //        /
        //       4
        // The following are two duplicate subtrees:
        //       2
        //      /
        //     4
        // and
        //     4
        // Therefore, you need to return above trees' root in the form of a list.
        vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
        {
            vector<TreeNode *> dup;
            map<string, int> m;
            map<int, int> c;
            int id = 0;
            function<int(TreeNode *)> getId = [&](TreeNode *n) -> int
            {
                if (n == nullptr)
                    return 0;
                string k = to_string(n->val) + "," + to_string(getId(n->left)) + "," + to_string(getId(n->right));
                if (m.find(k) == m.end())
                    m[k] = (++id);
                if (c.find(m[k]) == c.end())
                    c[m[k]] = 1;
                else
                    c[m[k]]++;
                if (c[m[k]] == 2) // c[m[k]] can be greater than 2, but we only count it once
                    dup.push_back(n);
                return m[k];
            };
            getId(root);
            return dup;
        }
        vector<TreeNode *> findDuplicateSubtrees2(TreeNode *root)
        {
            vector<TreeNode *> dup;
            map<TreeNode *, string> m;
            map<string, int> mid;
            map<int, int> c;
            int id = 0;
            stack<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
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
                        string k = to_string(t->val) + "," + (t->left == nullptr ? "" : to_string(mid[m[t->left]])) + "," + (t->right == nullptr ? "" : to_string(mid[m[t->right]]));
                        m[t] = k;
                        if (mid.find(k) == mid.end())
                            mid[k] = (++id);
                        if (c.find(mid[k]) == c.end())
                            c[mid[k]] = 1;
                        else
                            c[mid[k]]++;
                        if (c[mid[k]] == 2)
                            dup.push_back(t);
                        s.pop();
                        last = t;
                    }
                }
            }
            // cout << "{" << endl;
            // for (auto it = m.begin(); it != m.end(); it++)
            // {
            //     cout << it->first << ":" << it->first->val << ":" << it->second << endl;
            // }
            // cout << "}" << endl;
            // cout << "{" << endl;
            // for (auto it = mid.begin(); it != mid.end(); it++)
            // {
            //     cout << it->first << ":" << it->second << endl;
            // }
            // cout << "}" << endl;
            // cout << "{" << endl;
            // for (auto it = c.begin(); it != c.end(); it++)
            // {
            //     cout << it->first << ":" << it->second << endl;
            // }
            // cout << "}" << endl;

            return dup;
        }

        // Jewels and Stones
        // You're given strings J representing the types of stones that are jewels,
        // and S representing the stones you have.  Each character in S is a type of
        // stone you have.  You want to know how many of the stones you have are also jewels.
        // The letters in J are guaranteed distinct, and all characters in J and S
        // are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".
        // Example 1:
        // Input: J = "aA", S = "aAAbbbb"
        // Output: 3
        // Example 2:
        // Input: J = "z", S = "ZZ"
        // Output: 0
        // Note:
        // S and J will consist of letters and have length at most 50.
        // The characters in J are distinct.
        int numJewelsInStones(const string &J, const string &S)
        {
            set<char> j(J.cbegin(), J.cend());
            return accumulate(S.cbegin(), S.cend(), 0, [&](int c, char s)
                              { return c + (j.find(s) == j.end() ? 0 : 1); });
        }

        // Top K Frequent Elements
        // Given a non-empty array of integers, return the k most frequent elements.
        // Example 1:
        // Input: nums = [1,1,1,2,2,3], k = 2
        // Output: [1,2]
        // Example 2:
        // Input: nums = [1], k = 1
        // Output: [1]
        // Note:
        // You may assume k is always valid, 1 <= k <= number of unique elements.
        // Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
        // It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
        // You can return the answer in any order.
        vector<int> topKFrequent(const vector<int> &nums, int k)
        {
            map<int, int> m;
            vector<int> h;
            function<bool(int, int)> less = [&](int i, int j) -> bool
            {
                return m[i] > m[j];
            };
            for (int n : nums)
            {
                if (m.find(n) == m.end())
                    m[n] = 1;
                else
                    m[n]++;
            }
            for (const auto &it : m)
            {
                if ((int)h.size() < k)
                {
                    h.push_back(it.first);
                }
                else if (it.second > m[h[0]])
                {
                    pop_heap(h.begin(), h.end(), less);
                    h[k - 1] = it.first;
                }
                push_heap(h.begin(), h.end(), less);
            }
            return h;
        }
        vector<int> topKFrequent2(vector<int> &nums, int k)
        {
            map<int, int> m;
            vector<int> h;
            function<bool(int, int)> less = [&](int i, int j) -> bool
            {
                return m[i] > m[j];
            };
            for (int n : nums)
            {
                if (m.find(n) == m.end())
                {
                    m[n] = 1;
                    h.push_back(n);
                }
                else
                {
                    m[n]++;
                }
            }
            sort(h.begin(), h.end(), less);
            h.resize(k);
            return h;
        }

        // Insert Delete GetRandom O(1)
        // Design a data structure that supports all following operations in average O(1) time.
        // insert(val): Inserts an item val to the set if not already present.
        // remove(val): Removes an item val from the set if present.
        // getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
        // Example:
        // // Init an empty set.
        // RandomizedSet randomSet = new RandomizedSet();
        // // Inserts 1 to the set. Returns true as 1 was inserted successfully.
        // randomSet.insert(1);
        // // Returns false as 2 does not exist in the set.
        // randomSet.remove(2);
        // // Inserts 2 to the set, returns true. Set now contains [1,2].
        // randomSet.insert(2);
        // // getRandom should return either 1 or 2 randomly.
        // randomSet.getRandom();
        // // Removes 1 from the set, returns true. Set now contains [2].
        // randomSet.remove(1);
        // // 2 was already in the set, so return false.
        // randomSet.insert(2);
        // // Since 2 is the only number in the set, getRandom always return 2.
        // randomSet.getRandom();
        class RandomizedSet
        {
        private:
            vector<vector<int>> v;
            map<int, int> m;
            int k;

        public:
            /** Initialize your data structure here. */
            RandomizedSet()
            {
                k = 1000;
            }

            /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
            bool insert(int val)
            {
                int i = val % k;
                if (m.find(i) == m.end())
                {
                    v.push_back({val});
                    m[i] = (int)v.size() - 1;
                    return true;
                }
                else
                {
                    int j = m[i];
                    vector<int>::iterator it = v[j].begin();
                    while (it != v[j].end() && *it != val)
                        it++;
                    if (it == v[j].end())
                    {
                        v[j].push_back(val);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            /** Removes a value from the set. Returns true if the set contained the specified element. */
            bool remove(int val)
            {
                int i = val % k;
                if (m.find(i) == m.end())
                {
                    return false;
                }
                else
                {
                    int j = m[i];
                    vector<int>::iterator it = v[j].begin();
                    while (it != v[j].end() && *it != val)
                        it++;
                    if (it == v[j].end())
                    {
                        return false;
                    }
                    else
                    {
                        v[j].erase(it);
                        if (v[j].empty())
                            m.erase(i);
                        return true;
                    }
                }
            }

            /** Get a random element from the set. */
            int getRandom()
            {
                int i = rand() % m.size();
                map<int, int>::iterator it = m.begin();
                while (i > 0)
                {
                    it++;
                    i--;
                }
                int j = it->second;
                int t = rand() % v[j].size();
                return v[j][t];
            }
        };

        // Maximum XOR of Two Numbers in an Array
        // Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 <= ai < 2^31.
        // Find the maximum result of ai XOR aj, where 0 <= i, j < n.
        // Could you do this in O(n) runtime?
        // Example:
        // Input: [3, 10, 5, 25, 2, 8]
        // Output: 28
        // Explanation: The maximum result is 5 ^ 25 = 28.
        int findMaximumXOR(vector<int> &nums)
        {
            int m = 0;
            for (size_t i = 0; i + 1 < nums.size(); i++)
            {
                for (size_t j = i + 1; j < nums.size(); j++)
                    m = max(m, (nums[i] ^ nums[j]));
            }
            return m;
        }
        int findMaximumXOR2(vector<int> &nums)
        {
            struct Node
            {
                char bit;
                map<char, Node *> next;
                Node(char b) : bit(b) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> root(new Node('\0'));
            function<char(int, int)> getBit = [&](int n, int p) -> char
            {
                return (char)((n >> p) & 0x1);
            };
            function<void(int)> add = [&](int n)
            {
                Node *node = root.get();
                int i = 0;
                while (i < 32)
                {
                    char b = getBit(n, 31 - i);
                    if (node->next.find(b) == node->next.end())
                        node->next[b] = new Node(b);
                    node = node->next[b];
                    i++;
                }
            };
            for (int n : nums)
                add(n);
            int m = 0;
            function<void(Node *, Node *, int)> find = [&](Node *n0, Node *n1, int x)
            {
                if (n0->next.empty() || n1->next.empty())
                {
                    m = max(m, x);
                    return;
                }
                if (n0->next.size() == 1 && n1->next.size() == 1 && n0->next.cbegin()->first == n1->next.cbegin()->first)
                {
                    find(n0->next.cbegin()->second, n1->next.cbegin()->second, (x << 1));
                }
                else
                {
                    if (n0->next.find(0) != n0->next.end() && n1->next.find(1) != n1->next.end())
                    {
                        find(n0->next[0], n1->next[1], ((x << 1) ^ 0x1));
                    }
                    if (n0->next.find(1) != n0->next.end() && n1->next.find(0) != n1->next.end())
                    {
                        find(n0->next[1], n1->next[0], ((x << 1) ^ 0x1));
                    }
                }
            };
            find(root.get(), root.get(), 0);
            return m;
        }
        int findMaximumXOR3(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            function<void(int, int, int, int &, int &, int &, int &)> getBitRange =
                [&](int b, int e, int i, int &b0, int &e0, int &b1, int &e1)
            {
                b0 = -1;
                e0 = -1;
                b1 = -1;
                e1 = -1;
                int x = 0x1 << i;
                for (int j = b; j <= e; j++)
                {
                    switch ((nums[j] & x) >> i)
                    {
                    case 0:
                        if (b0 == -1)
                            b0 = j;
                        e0 = j;
                        break;
                    case 1:
                        if (b1 == -1)
                            b1 = j;
                        e1 = j;
                        break;
                    }
                }
            };
            int m = 0;
            function<void(int, int, int, int, int, int)> find =
                [&](int b0, int e0, int b1, int e1, int i, int x)
            {
                if (i < 0)
                {
                    m = max(m, x);
                    return;
                }
                int b00, e00, b01, e01, b10, e10, b11, e11;
                getBitRange(b0, e0, i, b00, e00, b01, e01);
                getBitRange(b1, e1, i, b10, e10, b11, e11);
                if ((b00 == -1 && b10 == -1) || (b01 == -1 && b11 == -1))
                {
                    find(b0, e0, b1, e1, i - 1, x << 1);
                }
                else
                {
                    if (b00 != -1 && b11 != -1)
                        find(b00, e00, b11, e11, i - 1, ((x << 1) ^ 0x1));
                    if (b01 != -1 && b10 != -1)
                        find(b01, e01, b10, e10, i - 1, ((x << 1) ^ 0x1));
                }
            };
            find(0, (int)nums.size() - 1, 0, (int)nums.size() - 1, 31, 0);
            return m;
        }

        class NaryTree
        {
        public:
            class Node
            {
            public:
                int val;
                vector<Node *> children;

                Node() {}

                Node(int _val)
                {
                    val = _val;
                }

                Node(int _val, vector<Node *> _children)
                {
                    val = _val;
                    children = _children;
                }
            };
            vector<int> preorder(Node *root)
            {
                vector<int> result;
                if (root == nullptr)
                    return result;
                stack<Node *> s;
                s.push(root);
                while (!s.empty())
                {
                    Node *node = s.top();
                    s.pop();
                    result.push_back(node->val);
                    for (int i = (int)node->children.size() - 1; i >= 0; i--)
                    {
                        if (node->children[i] != nullptr)
                            s.push(node->children[i]);
                    }
                }
                return result;
            }
            vector<int> postorder(Node *root)
            {
                vector<int> result;
                if (root == nullptr)
                    return result;
                stack<Node *> s;
                s.push(root);
                set<Node *> visited;
                while (!s.empty())
                {
                    Node *node = s.top();
                    if (node->children.empty() || visited.find(node->children[0]) != visited.end())
                    {
                        result.push_back(node->val);
                        visited.insert(node);
                        s.pop();
                    }
                    else
                    {
                        for (int i = (int)node->children.size() - 1; i >= 0; i--)
                            s.push(node->children[i]);
                    }
                }
                return result;
            }
            vector<vector<int>> levelOrder(Node *root)
            {
                vector<vector<int>> result;
                if (root == nullptr)
                    return result;
                vector<Node *> current;
                vector<Node *> next;
                current.push_back(root);
                while (!current.empty())
                {
                    vector<int> level;
                    for (Node *node : current)
                    {
                        level.push_back(node->val);
                        for (Node *child : node->children)
                        {
                            if (child != nullptr)
                                next.push_back(child);
                        }
                    }
                    result.push_back(level);
                    current.clear();
                    current.swap(next);
                }
                return result;
            }
            int maxDepth(Node *root)
            {
                function<int(Node *)> depth = [&](Node *node) -> int
                {
                    if (node == nullptr)
                        return 0;
                    if (node->children.empty())
                        return 1;
                    int m = 0;
                    for (Node *child : node->children)
                    {
                        m = max(m, depth(child));
                    }
                    return m + 1;
                };
                return depth(root);
            }
        };

        // Fibonacci Number
        // The Fibonacci numbers, commonly denoted F(n) form a sequence, called the
        // Fibonacci sequence, such that each number is the sum of the two preceding
        // ones, starting from 0 and 1. That is,
        // F(0) = 0,   F(1) = 1
        // F(N) = F(N - 1) + F(N - 2), for N > 1.
        // Given N, calculate F(N).
        // Example 1:
        // Input: 2
        // Output: 1
        // Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
        // Example 2:
        // Input: 3
        // Output: 2
        // Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
        // Example 3:
        // Input: 4
        // Output: 3
        // Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
        // Note:
        // 0 <= N <= 30.
        int fib(int N)
        {
            map<int, int> m;
            function<int(int)> f = [&](int n) -> int
            {
                if (n < 0)
                    return 0;
                if (n == 1 || n == 0)
                    return n;
                if (m.find(n - 2) == m.end())
                    m[n - 2] = f(n - 2);
                if (m.find(n - 1) == m.end())
                    m[n - 1] = f(n - 1);
                return m[n - 1] + m[n - 2];
            };
            return f(N);
        }

        // K-th Symbol in Grammar
        // On the first row, we write a 0. Now in every subsequent row, we look at
        // the previous row and replace each occurrence of 0 with 01, and each
        // occurrence of 1 with 10. Given row N and index K, return the K-th indexed
        // symbol in row N. (The values of K are 1-indexed.) (1 indexed).
        // Examples:
        // Input: N = 1, K = 1
        // Output: 0
        // Input: N = 2, K = 1
        // Output: 0
        // Input: N = 2, K = 2
        // Output: 1
        // Input: N = 4, K = 5
        // Output: 1
        // Explanation:
        // row 1: 0
        // row 2: 01
        // row 3: 0110
        // row 4: 01101001
        // Note:
        // N will be an integer in the range [1, 30].
        // K will be an integer in the range [1, 2^(N-1)].
        // N:   1   2   3   4   ... K-1             K       K+1             ... 2^(N-1)
        // N+1: 1 2 3 4 5 6 7 8 ... 2(K-1)-1 2(K-1) 2K-1 2K 2(K+1)-1 2(K+1) ... 2^N-1 2^N
        int kthGrammar(int N, int K)
        {
            function<int(int, int)> g = [&](int n, int k) -> int
            {
                if (n == 1)
                    return 0;
                int b = g(n - 1, (k + 1) >> 1);
                return ((k & 0x1) == 1) ? b : 1 - b;
            };
            return g(N, K);
        }

        // Sort an Array
        // Given an array of integers nums, sort the array in ascending order.
        // Example 1:
        // Input: nums = [5,2,3,1]
        // Output: [1,2,3,5]
        // Example 2:
        // Input: nums = [5,1,1,2,0,0]
        // Output: [0,0,1,1,2,5]
        // Constraints:
        // 1 <= nums.length <= 50000
        // -50000 <= nums[i] <= 50000
        // Bottom-up merge sort
        vector<int> sortArray(vector<int> &nums)
        {
            int n = (int)nums.size();
            int l = 1;
            while (l < n)
            {
                for (int i = 0; i + l < n; i += (l + l))
                {
                    int j = i;
                    int k = i + l;
                    while (j < k && k < i + l + l && k < n)
                    {
                        if (nums[j] <= nums[k])
                        {
                            j++;
                        }
                        else
                        {
                            int t = nums[k];
                            for (int p = k; p > j; p--)
                            {
                                nums[p] = nums[p - 1];
                            }
                            nums[j] = t;
                            j++;
                            k++;
                        }
                    }
                }
                l = l << 1;
            }
            return nums;
        }
        // Bottom-up merge sort
        vector<int> sortArray2(vector<int> &nums)
        {
            int n = (int)nums.size();
            int l = 1;
            while (l < n)
            {
                // make a copy of nums. If some elements at the end of nums are
                // not participating the sorting in the for-loop, they are kept
                // in temp and thus not lost.
                vector<int> temp(nums);
                for (int i = 0; i + l < n; i += (l + l))
                {
                    int j = i;
                    int k = i + l;
                    int q = i;
                    while (j < i + l && k < i + l + l && k < n)
                    {
                        if (nums[j] <= nums[k])
                            temp[q++] = nums[j++];
                        else
                            temp[q++] = nums[k++];
                    }
                    while (j < i + l)
                        temp[q++] = nums[j++];
                    while (k < i + l + l && k < n)
                        temp[q++] = nums[k++];
                }
                l = l << 1;
                temp.swap(nums);
            }
            return nums;
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
                     return false;
                 });
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
                    else
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

    } // namespace LeetCode

    namespace sql
    {

        // 176. Second Highest Salary
        // SQL Schema
        // Write a SQL query to get the second highest salary from the Employee table.
        // +----+--------+
        // | Id | Salary |
        // +----+--------+
        // | 1  | 100    |
        // | 2  | 200    |
        // | 3  | 300    |
        // +----+--------+
        // For example, given the above Employee table, the query should return 200 as the second highest salary. If there is no second highest salary, then the query should return null.
        // +---------------------+
        // | SecondHighestSalary |
        // +---------------------+
        // | 200                 |
        // +---------------------+
        //
        // SELECT IFNULL((SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT 1, 1), NULL) AS SecondHighestSalary;

        // 177. Nth Highest Salary
        // Write a SQL query to get the nth highest salary from the Employee table.
        // +----+--------+
        // | Id | Salary |
        // +----+--------+
        // | 1  | 100    |
        // | 2  | 200    |
        // | 3  | 300    |
        // +----+--------+
        // For example, given the above Employee table, the nth highest salary where n = 2 is 200. If there is no nth highest salary, then the query should return null.
        // +------------------------+
        // | getNthHighestSalary(2) |
        // +------------------------+
        // | 200                    |
        // +------------------------+
        // CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
        // BEGIN
        //   DECLARE m INT;
        //   SET m = N-1;
        //   RETURN (
        //       IFNULL((SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT m,1), NULL)
        //   );
        // END

        // 178. Rank Scores
        // Write a SQL query to rank scores. If there is a tie between two scores, both should have the same ranking. Note that after a tie, the next ranking number should be the next consecutive integer value. In other words, there should be no "holes" between ranks.
        // +----+-------+
        // | Id | Score |
        // +----+-------+
        // | 1  | 3.50  |
        // | 2  | 3.65  |
        // | 3  | 4.00  |
        // | 4  | 3.85  |
        // | 5  | 4.00  |
        // | 6  | 3.65  |
        // +----+-------+
        // For example, given the above Scores table, your query should generate the following report (order by highest score):
        // +-------+---------+
        // | score | Rank    |
        // +-------+---------+
        // | 4.00  | 1       |
        // | 4.00  | 1       |
        // | 3.85  | 2       |
        // | 3.65  | 3       |
        // | 3.65  | 3       |
        // | 3.50  | 4       |
        // +-------+---------+
        // Important Note: For MySQL solutions, to escape reserved words used as column names, you can use an apostrophe before and after the keyword. For example `Rank`.
        // SELECT s.Score, COUNT(t.Score) AS `Rank` FROM
        // (SELECT DISTINCT Score FROM Scores) AS t, Scores AS s
        // WHERE s.Score <= t.Score
        // GROUP BY s.Id, s.Score
        // ORDER BY s.Score DESC;

        // 180. Consecutive Numbers
        // Table: Logs
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | id          | int     |
        // | num         | varchar |
        // +-------------+---------+
        // id is the primary key for this table.
        // Write an SQL query to find all numbers that appear at least three times consecutively.
        // Return the result table in any order.
        // The query result format is in the following example:
        // Logs table:
        // +----+-----+
        // | Id | Num |
        // +----+-----+
        // | 1  | 1   |
        // | 2  | 1   |
        // | 3  | 1   |
        // | 4  | 2   |
        // | 5  | 1   |
        // | 6  | 2   |
        // | 7  | 2   |
        // +----+-----+
        // Result table:
        // +-----------------+
        // | ConsecutiveNums |
        // +-----------------+
        // | 1               |
        // +-----------------+
        // 1 is the only number that appears consecutively for at least three times.
        // select distinct l1.num as ConsecutiveNums from logs l1
        // join logs l2 on l1.id = l2.id - 1
        // join logs l3 on l2.id = l3.id - 1
        // where l1.num = l2.num and l2.num = l3.num;

        // 181. Employees Earning More Than Their Managers
        // The Employee table holds all employees including their managers.
        // Every employee has an Id, and there is also a column for the manager Id.
        // +----+-------+--------+-----------+
        // | Id | Name  | Salary | ManagerId |
        // +----+-------+--------+-----------+
        // | 1  | Joe   | 70000  | 3         |
        // | 2  | Henry | 80000  | 4         |
        // | 3  | Sam   | 60000  | NULL      |
        // | 4  | Max   | 90000  | NULL      |
        // +----+-------+--------+-----------+
        // Given the Employee table, write a SQL query that finds out employees
        // who earn more than their managers. For the above table, Joe is the only employee
        // who earns more than his manager.
        // +----------+
        // | Employee |
        // +----------+
        // | Joe      |
        // +----------+
        // select e.Name as Employee from Employee e
        // join Employee m on e.ManagerId = m.Id
        // where e.Salary > m.Salary

        // 182. Duplicate Emails
        // Write a SQL query to find all duplicate emails in a table named Person.
        // +----+---------+
        // | Id | Email   |
        // +----+---------+
        // | 1  | a@b.com |
        // | 2  | c@d.com |
        // | 3  | a@b.com |
        // +----+---------+
        // For example, your query should return the following for the above table:
        // +---------+
        // | Email   |
        // +---------+
        // | a@b.com |
        // +---------+
        // Note: All emails are in lowercase.
        // select Email from (select Email, count(Id) as Count from Person group by Email) e where Count > 1;

        // 183. Customers Who Never Order
        // Suppose that a website contains two tables, the Customers table and the Orders table.
        // Write a SQL query to find all customers who never order anything.
        // Table: Customers.
        // +----+-------+
        // | Id | Name  |
        // +----+-------+
        // | 1  | Joe   |
        // | 2  | Henry |
        // | 3  | Sam   |
        // | 4  | Max   |
        // +----+-------+
        // Table: Orders.
        // +----+------------+
        // | Id | CustomerId |
        // +----+------------+
        // | 1  | 3          |
        // | 2  | 1          |
        // +----+------------+
        // Using the above tables as example, return the following:
        // +-----------+
        // | Customers |
        // +-----------+
        // | Henry     |
        // | Max       |
        // +-----------+
        // select Name as Customers from Customers where Id not in (select CustomerId from Orders);

        // 184. Department Highest Salary
        // The Employee table holds all employees. Every employee has an Id, a salary,
        // and there is also a column for the department Id.
        // +----+-------+--------+--------------+
        // | Id | Name  | Salary | DepartmentId |
        // +----+-------+--------+--------------+
        // | 1  | Joe   | 70000  | 1            |
        // | 2  | Jim   | 90000  | 1            |
        // | 3  | Henry | 80000  | 2            |
        // | 4  | Sam   | 60000  | 2            |
        // | 5  | Max   | 90000  | 1            |
        // +----+-------+--------+--------------+
        // The Department table holds all departments of the company.
        // +----+----------+
        // | Id | Name     |
        // +----+----------+
        // | 1  | IT       |
        // | 2  | Sales    |
        // +----+----------+
        // Write a SQL query to find employees who have the highest salary in each of
        // the departments. For the above tables, your SQL query should return the following
        // rows (order of rows does not matter).
        // +------------+----------+--------+
        // | Department | Employee | Salary |
        // +------------+----------+--------+
        // | IT         | Max      | 90000  |
        // | IT         | Jim      | 90000  |
        // | Sales      | Henry    | 80000  |
        // +------------+----------+--------+
        // Explanation:
        // Max and Jim both have the highest salary in the IT department and Henry has the highest salary in the Sales department.
        // select d.Name as Department, e.Name as Employee, e.Salary
        // from Employee e
        // join (
        //     select DepartmentId, max(Salary) as MaxSalary
        //     from Employee group by DepartmentId
        // ) m on e.DepartmentId = m.DepartmentId and e.Salary = m.MaxSalary
        // join Department d on e.DepartmentId = d.Id;

        // 185. Department Top Three Salaries
        // The Employee table holds all employees. Every employee has an Id, and there
        // is also a column for the department Id.
        // +----+-------+--------+--------------+
        // | Id | Name  | Salary | DepartmentId |
        // +----+-------+--------+--------------+
        // | 1  | Joe   | 85000  | 1            |
        // | 2  | Henry | 80000  | 2            |
        // | 3  | Sam   | 60000  | 2            |
        // | 4  | Max   | 90000  | 1            |
        // | 5  | Janet | 69000  | 1            |
        // | 6  | Randy | 85000  | 1            |
        // | 7  | Will  | 70000  | 1            |
        // +----+-------+--------+--------------+
        // The Department table holds all departments of the company.
        // +----+----------+
        // | Id | Name     |
        // +----+----------+
        // | 1  | IT       |
        // | 2  | Sales    |
        // +----+----------+
        // Write a SQL query to find employees who earn the top three salaries in each of
        // the department. For the above tables, your SQL query should return the following
        // rows (order of rows does not matter).
        // +------------+----------+--------+
        // | Department | Employee | Salary |
        // +------------+----------+--------+
        // | IT         | Max      | 90000  |
        // | IT         | Randy    | 85000  |
        // | IT         | Joe      | 85000  |
        // | IT         | Will     | 70000  |
        // | Sales      | Henry    | 80000  |
        // | Sales      | Sam      | 60000  |
        // +------------+----------+--------+
        // Explanation:
        // In IT department, Max earns the highest salary, both Randy and Joe earn the second
        // highest salary, and Will earns the third highest salary. There are only two employees
        // in the Sales department, Henry earns the highest salary while Sam earns the second
        // highest salary.
        // select d.Name as Department, f.Name as Employee, f.Salary
        // from (
        //     select DepartmentId, Name, Salary
        //     from (
        //         select Name, Salary, DepartmentId, dense_rank() over (partition by DepartmentId order by Salary desc) R
        //         from employee
        //     ) e
        //     where e.R <= 3
        // ) f
        // join Department d on f.DepartmentId = d.Id;

        // 192. Word Frequency
        // Write a bash script to calculate the frequency of each word in a text file words.txt.
        // For simplicity sake, you may assume:
        // words.txt contains only lowercase characters and space ' ' characters.
        // Each word must consist of lowercase characters only.
        // Words are separated by one or more whitespace characters.
        // Example:
        // Assume that words.txt has the following content:
        // the day is sunny the the
        // the sunny is is
        // Your script should output the following, sorted by descending frequency:
        // the 4
        // is 3
        // sunny 2
        // day 1
        // Note:
        // Don't worry about handling ties, it is guaranteed that each word's frequency count is unique.
        // Could you write it in one-line using Unix pipes?
        // for w in $(cat words.txt | cut -d ' ' -f1-); do echo $w; done | sort | uniq -c | sort -r | awk '{print $2" "$1}'

        // 193. Valid Phone Numbers
        // Given a text file file.txt that contains list of phone numbers (one per line),
        // write a one liner bash script to print all valid phone numbers.
        // You may assume that a valid phone number must appear in one of the following two
        // formats: (xxx) xxx-xxxx or xxx-xxx-xxxx. (x means a digit)
        // You may also assume each line in the text file must not contain leading or
        // trailing white spaces.
        // Example:
        // Assume that file.txt has the following content:
        // 987-123-4567
        // 123 456 7890
        // (123) 456-7890
        // Your script should output the following valid phone numbers:
        // 987-123-4567
        // (123) 456-7890
        // grep -E "^([0-9]{3}-|\([0-9]{3}\)\ )[0-9]{3}-[0-9]{4}$" file.txt

        // 194. Transpose File
        // Given a text file file.txt, transpose its content.
        // You may assume that each row has the same number of columns and each field is
        // separated by the ' ' character.
        // Example:
        // If file.txt has the following content:
        // name age
        // alice 21
        // ryan 30
        // Output the following:
        // name alice ryan
        // age 21 30
        // for i in $(seq 1 1 $(head -1 file.txt | wc -w)); do cut -d ' ' -f $i file.txt | tr '\n' ' ' | awk {print} | sed 's/ \n/\n/g'; done
        // Wrong Answer
        // Input
        // 'a'
        // Output
        // 'a '
        // Expected
        // 'a'

        // 195. Tenth Line
        // Given a text file file.txt, print just the 10th line of the file.
        // Example:
        // Assume that file.txt has the following content:
        // Line 1
        // Line 2
        // Line 3
        // Line 4
        // Line 5
        // Line 6
        // Line 7
        // Line 8
        // Line 9
        // Line 10
        // Your script should output the tenth line, which is:
        // Line 10
        // Note:
        // 1. If the file contains less than 10 lines, what should you output?
        // 2. There's at least three different solutions. Try to explore all possibilities.
        // if [ $(cat file.txt | wc -l) -ge 10 ]; then head -10 file.txt | tail -1; fi
        // sed -n '10p' file.txt

        // 196. Delete Duplicate Emails
        // Write a SQL query to delete all duplicate email entries in a table named Person,
        // keeping only unique emails based on its smallest Id.
        // +----+------------------+
        // | Id | Email            |
        // +----+------------------+
        // | 1  | john@example.com |
        // | 2  | bob@example.com  |
        // | 3  | john@example.com |
        // +----+------------------+
        // Id is the primary key column for this table.
        // For example, after running your query, the above Person table should have the
        // following rows:
        // +----+------------------+
        // | Id | Email            |
        // +----+------------------+
        // | 1  | john@example.com |
        // | 2  | bob@example.com  |
        // +----+------------------+
        // Note:
        // Your output is the whole Person table after executing your sql. Use delete statement.
        // Solution:
        // with minIds as (select min(Id)as Id from Person group by Email)
        // delete from Person where Id not in (select Id from minIds);
        // Wrong solution: You can't specify target table 'Person' for update in FROM clause
        // delete from Person where Id not in (select mind(Id) from Person group by Email);

        // 197. Rising Temperature
        // Table: Weather
        // +---------------+---------+
        // | Column Name   | Type    |
        // +---------------+---------+
        // | id            | int     |
        // | recordDate    | date    |
        // | temperature   | int     |
        // +---------------+---------+
        // id is the primary key for this table.
        // This table contains information about the temperature in a certain day.
        // Write an SQL query to find all dates' id with higher temperature compared to
        // its previous dates (yesterday).
        // Return the result table in any order.
        // The query result format is in the following example:
        // Weather
        // +----+------------+-------------+
        // | id | recordDate | Temperature |
        // +----+------------+-------------+
        // | 1  | 2015-01-01 | 10          |
        // | 2  | 2015-01-02 | 25          |
        // | 3  | 2015-01-03 | 20          |
        // | 4  | 2015-01-04 | 30          |
        // +----+------------+-------------+
        // Result table:
        // +----+
        // | id |
        // +----+
        // | 2  |
        // | 4  |
        // +----+
        // In 2015-01-02, temperature was higher than the previous day (10 -> 25).
        // In 2015-01-04, temperature was higher than the previous day (20 -> 30).
        // select w1.id from Weather w1
        // join Weather w2 on w1.recordDate = date_add(w2.recordDate, interval 1 day)
        // where w1.Temperature > w2.Temperature;

    } // namespace sql
} // namespace Test

#endif
