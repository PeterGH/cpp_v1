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
        bool checkIfExist2(const vector<int> &arr)
        {
            set<int> s;
            for (int i : arr)
            {
                int j;
                if (i >= 0)
                    j = i << 1;
                else
                    j = -((-i) << 1);
                if (s.find(j) != s.end())
                    return true;
                if ((i & 0x1) == 0)
                {
                    j = i >> 1;
                    if (s.find(j) != s.end())
                        return true;
                }
                s.insert(i);
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
                    Node *t = h; // tail at current level
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
        // wrong
        int pivotIndex2(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            int i = 0;
            int j = nums.size() - 1;
            int l = nums[i];
            int r = nums[j];
            while (i < j)
            {
                // cout << "i=" << i << " l=" << l << " j=" << j << " r=" << r << endl;
                if (l == r)
                {
                    if (i + 1 == j)
                        return -1;
                    if (i + 2 == j)
                        return i + 1;
                }
                int a = abs(l + nums[i + 1] - r);
                int b = abs(l - r - nums[j - 1]);
                if (a < b)
                {
                    l += nums[++i];
                }
                else
                {
                    r += nums[--j];
                }
            }
            // cout << "i=" << i << " l=" << l << " j=" << j << " r=" << r << endl;
            if (l == r)
                return i;
            int t = l + r - nums[i];
            if (t == nums[0])
                return 0;
            if (t == nums[nums.size() - 1])
                return nums.size() - 1;
            return -1;
        }
        // wrong
        int pivotIndex3(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            int i = 0;
            int j = nums.size() - 1;
            int l = nums[i];
            int r = nums[j];
            while (i < j)
            {
                if (l < r)
                {
                    l += nums[++i];
                }
                else if (l > r)
                {
                    r += nums[--j];
                }
                else if (i + 2 == j)
                {
                    return i + 1;
                }
                else if (i + 1 == j)
                {
                    return -1;
                }
                else
                {
                    r += nums[--j];
                }
            }
            if (l == r)
                return i;
            int t = l + r - nums[i];
            if (t == nums[0])
                return 0;
            if (t == nums[nums.size() - 1])
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
