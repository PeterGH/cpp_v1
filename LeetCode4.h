#ifndef _LEETCODE4_H_
#define _LEETCODE4_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 400. Nth Digit
        // Given an integer n, return the nth digit of the infinite integer sequence
        // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
        // Example 1:
        // Input: n = 3
        // Output: 3
        // Example 2:
        // Input: n = 11
        // Output: 0
        // Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0,
        // which is part of the number 10.
        // Constraints:
        // 1 <= n <= 2^31 - 1
        // Group numbers into ranges per number of digits:
        // [1..9]
        // [10..99]
        // [100..999]
        // [1000..9999]
        // [10000..99999]
        // ......
        int findNthDigit(int n)
        {
            long long b = 1;         // base for a range
            long long c = 1;         // count digits per number in a range
            long long a = 9 * b * c; // accumulated count of digits
            while (a < n)
            {
                b *= 10;
                c++;
                a += 9 * b * c;
            }
            a -= 9 * b * c;
            n -= a;
            n--;
            // Now n is the index (0-based) of the target digit in the
            // range where every number has c digits and the base is b.
            // Find the number having the target digit.
            int d = b + n / c;
            // Find the index of the target digit in the target number.
            n %= c;
            while (n + 1 < c)
            {
                d /= 10;
                c--;
            }
            return d % 10;
        }

        // 401. Binary Watch
        // A binary watch has 4 LEDs on the top which represent the hours (0-11),
        // and the 6 LEDs on the bottom represent the minutes (0-59). Each LED represents
        // a zero or one, with the least significant bit on the right.
        // Hour LEDs: 8, 4, 2, 1
        // Minute LEDS: 32, 16, 8, 4, 2, 1
        // For example, the below binary watch reads "4:51".
        // Given an integer turnedOn which represents the number of LEDs that are currently
        // on, return all possible times the watch could represent. You may return the answer in any order.
        // The hour must not contain a leading zero.
        // For example, "01:00" is not valid. It should be "1:00".
        // The minute must be consist of two digits and may contain a leading zero.
        // For example, "10:2" is not valid. It should be "10:02".
        // Example 1:
        // Input: turnedOn = 1
        // Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
        // Example 2:
        // Input: turnedOn = 9
        // Output: []
        // Constraints:
        // 0 <= turnedOn <= 10
        vector<string> readBinaryWatch(int turnedOn)
        {
            vector<string> output;
            for (unsigned int h = 0; h < 12; h++)
            {
                for (unsigned int m = 0; m < 60; m++)
                {
                    bitset<10> t((h << 6) | m);
                    if ((int)t.count() == turnedOn)
                    {
                        ostringstream s;
                        s << h << ":";
                        if (m < 10)
                            s << "0";
                        s << m;
                        output.push_back(s.str());
                    }
                }
            }
            return output;
        }
        vector<string> readBinaryWatch2(int turnedOn)
        {
            vector<int> led{8, 4, 2, 1, 32, 16, 8, 4, 2, 1};
            vector<string> output;
            function<void(size_t, int, int, int)>
                read = [&](size_t i, int n, int h, int m)
            {
                if (n == turnedOn)
                {
                    if (0 <= h && h < 12 && 0 <= m && m < 60)
                    {
                        ostringstream s;
                        s << h << ":";
                        if (m < 10)
                            s << "0";
                        s << m;
                        output.push_back(s.str());
                    }
                    return;
                }
                if (i >= led.size() || h >= 12 || m >= 60)
                    return;
                read(i + 1, n, h, m);
                if (i < 4)
                    h += led[i];
                else
                    m += led[i];
                read(i + 1, n + 1, h, m);
            };
            read(0, 0, 0, 0);
            return output;
        }

        // 402. Remove K Digits
        // Given string num representing a non-negative integer num, and an integer k,
        // return the smallest possible integer after removing k digits from num.
        // Example 1:
        // Input: num = "1432219", k = 3
        // Output: "1219"
        // Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
        // Example 2:
        // Input: num = "10200", k = 1
        // Output: "200"
        // Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
        // Example 3:
        // Input: num = "10", k = 2
        // Output: "0"
        // Explanation: Remove all the digits from the number and it is left with nothing which is 0.
        // Constraints:
        // 1 <= k <= num.length <= 10^5
        // num consists of only digits.
        // num does not have any leading zeros except for the zero itself.
        string removeKdigits(const string &num, int k)
        {
            int n = num.size();
            int i = -1; // index of the last digit preserved
            string o;
            // keep the min digit of k+1 digits after i
            int j = 0;
            while (j + k < n)
            {
                int l = j++;
                while (j < n && j <= i + k + 1)
                {
                    if (num[l] > num[j])
                    {
                        l = j;
                    }
                    j++;
                }
                // now l points to min in num[(i+1)..(i+k+1)]
                if (!o.empty() || num[l] != '0')
                    o.append(1, num[l]); // only append if not a leading zero
                k -= l - i - 1;
                i = l;
                j = i + 1;
            }
            if (o.empty())
                o = "0";
            return o;
        }
        string removeKdigits2(const string &num, int k)
        {
            string o;
            for (char c : num)
            {
                while (!o.empty() && o.back() > c && k > 0)
                {
                    o.pop_back();
                    k--;
                }
                if (!o.empty() || c != '0')
                    o.push_back(c);
            }
            while (!o.empty() && k > 0)
            {
                o.pop_back();
                k--;
            }
            return o.empty() ? "0" : o;
        }

        // 403. Frog Jump
        // A frog is crossing a river. The river is divided into some number of units,
        // and at each unit, there may or may not exist a stone. The frog can jump on a
        // stone, but it must not jump into the water.
        // Given a list of stones positions (in units) in sorted ascending order, determine
        // if the frog can cross the river by landing on the last stone. Initially, the
        // frog is on the first stone and assumes the first jump must be 1 unit.
        // If the frog last jump was k units, its next jump must be either k - 1, k, or k + 1
        // units. The frog can only jump in the forward direction.
        // Example 1:
        // Input: stones = [0,1,3,5,6,8,12,17]
        // Output: true
        // Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone,
        // then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th
        // stone, 4 units to the 7th stone, and 5 units to the 8th stone.
        // Example 2:
        // Input: stones = [0,1,2,3,4,8,9,11]
        // Output: false
        // Explanation: There is no way to jump to the last stone as the gap between the 5th
        // and 6th stone is too large.
        // Constraints:
        // 2 <= stones.length <= 2000
        // 0 <= stones[i] <= 2^31 - 1
        // stones[0] == 0
        // stones is sorted in a strictly increasing order.
        bool canCross(const vector<int> &stones)
        {
            map<int, set<int>> m;
            for (int s : stones)
                m[s] = {};
            m[stones[0]].insert(1);
            for (int s : stones)
            {
                if (s == stones.back())
                    break;
                for (int k : m[s])
                {
                    int t = s + k;
                    if (t == stones.back())
                        return true;
                    if (m.find(t) != m.end())
                    {
                        if (k > 1)
                            m[t].insert(k - 1);
                        if (k > 0)
                            m[t].insert(k);
                        m[t].insert(k + 1);
                    }
                }
            }
            return false;
        }
        bool canCross2(const vector<int> &stones)
        {
            map<size_t, map<int, bool>> m;
            function<bool(size_t, int)> cross = [&](size_t i, int k) -> bool
            {
                if (i + 1 == stones.size())
                    return true;
                if (m.find(i) != m.end() && m[i].find(k) != m[i].end())
                    return m[i][k];
                size_t j = i;
                int a = stones[i++];
                for (int t = k - 1; t <= k + 1; t++)
                {
                    if (t > 0)
                    {
                        int b = a + t;
                        while (i < stones.size() && stones[i] < b)
                            i++;
                        if (i < stones.size() && stones[i] == b && cross(i, t))
                        {
                            m[j][k] = true;
                            return true;
                        }
                    }
                }
                m[j][k] = false;
                return false;
            };
            return cross(0, 0);
        }
        bool canCross3(const vector<int> &stones)
        {
            function<bool(vector<int>::const_iterator, int)>
                cross = [&](vector<int>::const_iterator i, int k) -> bool
            {
                if (i + 1 == stones.cend())
                    return true;
                int a = *i;
                i++;
                for (int t = k - 1; t <= k + 1; t++)
                {
                    if (t > 0)
                    {
                        int b = a + t;
                        i = lower_bound(i, stones.cend(), b);
                        if (i != stones.cend() && *i == b && cross(i, t))
                            return true;
                    }
                }
                return false;
            };
            return cross(stones.cbegin(), 0);
        }
        bool canCross4(const vector<int> &stones)
        {
            set<long long> valid;
            for (int e : stones)
                valid.insert(e);
            set<pair<long long, int>> visited;
            stack<pair<long long, int>> s;
            pair<long long, int> n = make_pair(stones[0], 0);
            pair<long long, int> last;
            long long target = stones.back();
            while (!s.empty() || n.first <= target)
            {
                if (n.first <= target)
                {
                    if (n.first == target)
                        return true;
                    last = n;
                    if (valid.find(n.first) == valid.end() || visited.find(n) != visited.end())
                    {
                        n.first = target + 1;
                    }
                    else
                    {
                        s.push(n);
                        visited.insert(n);
                        if (n.second > 1)
                            n.second--;
                        else if (n.second == 0)
                            n.second++;
                        n.first += n.second;
                    }
                }
                else
                {
                    auto p = s.top();
                    if (last.first == p.first + last.second && last.second < p.second + 1)
                    {
                        n.second = last.second + 1;
                        n.first = p.first + n.second;
                    }
                    else
                    {
                        s.pop();
                        last = p;
                    }
                }
            }
            return false;
        }

        // 404. Sum of Left Leaves
        // Given the root of a binary tree, return the sum of all left leaves.
        // Example 1:
        // Input: root = [3,9,20,null,null,15,7]
        // Output: 24
        // Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.
        // Example 2:
        // Input: root = [1]
        // Output: 0
        // Constraints:
        // The number of nodes in the tree is in the range [1, 1000].
        // -1000 <= Node.val <= 1000
        int sumOfLeftLeaves(TreeNode *root)
        {
            function<void(TreeNode *, TreeNode *, int &)>
                sum = [&](TreeNode *p, TreeNode *n, int &s)
            {
                if (n == nullptr)
                    return;
                if (n->left == nullptr && n->right == nullptr && p != nullptr && p->left == n)
                {
                    s += n->val;
                    return;
                }
                sum(n, n->left, s);
                sum(n, n->right, s);
            };
            int s = 0;
            sum(nullptr, root, s);
            return s;
        }
        int sumOfLeftLeaves2(TreeNode *root)
        {
            stack<TreeNode *> s;
            TreeNode *n = root;
            int o = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (n->left == nullptr && n->right == nullptr && !s.empty() && s.top()->left == n)
                        o += n->val;
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    s.pop();
                    if (t->right != nullptr)
                        n = t->right;
                }
            }
            return o;
        }
        int sumOfLeftLeaves3(TreeNode *root)
        {
            stack<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            int o = 0;
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
                    if (t->right == nullptr || t->right == last)
                    {
                        s.pop();
                        if (t->left == nullptr && t->right == nullptr && !s.empty() && s.top()->left == t)
                            o += t->val;
                        last = t;
                    }
                    else
                    {
                        n = t->right;
                    }
                }
            }
            return o;
        }

        // 405. Convert a Number to Hexadecimal
        // Given an integer num, return a string representing its hexadecimal
        // representation. For negative integers, two complement method is used.
        // All the letters in the answer string should be lowercase characters,
        // and there should not be any leading zeros in the answer except for the zero itself.
        // Note: You are not allowed to use any built-in library method to directly solve this problem.
        // Example 1:
        // Input: num = 26
        // Output: "1a"
        // Example 2:
        // Input: num = -1
        // Output: "ffffffff"
        // Constraints:
        // -2^31 <= num <= 2^31 - 1
        string toHex(int num)
        {
            const vector<char> c{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
            int n = (sizeof(num)) << 1;
            vector<char> s(n);
            for (int i = 0; i < n; i++)
            {
                s[n - i - 1] = c[num & 0xF];
                num >>= 4;
            }
            int j = 0;
            while (j < n && s[j] == '0')
                j++;
            if (j == n)
                return "0";
            string o;
            while (j < n)
                o.append(1, s[j++]);
            return o;
        }
        string toHex2(int num)
        {
            const vector<char> c{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
            int n = (sizeof(num)) << 1;
            unsigned int u = num;
            string o;
            while (u != 0 && n > 0)
            {
                o.push_back(c[u & 0xF]);
                u >>= 4;
            }
            if (o.empty())
                return "0";
            reverse(o.begin(), o.end());
            return o;
        }

        // 406. Queue Reconstruction by Height
        // You are given an array of people, people, which are the attributes of some
        // people in a queue (not necessarily in order). Each people[i] = [hi, ki] represents
        // the ith person of height hi with exactly ki other people in front who have a
        // height greater than or equal to hi.
        // Reconstruct and return the queue that is represented by the input array people.
        // The returned queue should be formatted as an array queue, where queue[j] = [hj, kj]
        // is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).
        // Example 1:
        // Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
        // Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
        // Explanation:
        // Person 0 has height 5 with no other people taller or the same height in front.
        // Person 1 has height 7 with no other people taller or the same height in front.
        // Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
        // Person 3 has height 6 with one person taller or the same height in front, which is person 1.
        // Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
        // Person 5 has height 7 with one person taller or the same height in front, which is person 1.
        // Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
        // Example 2:
        // Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
        // Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
        // Constraints:
        // 1 <= people.length <= 2000
        // 0 <= hi <= 10^6
        // 0 <= ki < people.length
        // It is guaranteed that the queue can be reconstructed.
        // Output people who have no others in front, i.e., ki = 0.
        // For the rest of perople, decrease their counters by the count of output people who
        // are taller than or same height as them. Any people in rest with counter = 0 means
        // they need to be moved to the output queue.
        vector<vector<int>> reconstructQueue(const vector<vector<int>> &people)
        {
            vector<vector<int>> output;
            vector<vector<int>> input;
            for (const auto &p : people)
            {
                if (p[1] == 0)
                    output.push_back(p);
                else
                    input.push_back({p[0], p[1], p[1]});
            }
            sort(output.begin(), output.end());
            auto l = output.begin();
            vector<vector<int>> a;
            while (!input.empty() && l != output.end())
            {
                auto p = input.begin();
                while (p != input.end())
                {
                    if ((*l)[0] >= (*p)[0])
                        (*p)[2]--;
                    if ((*p)[2] == 0)
                    {
                        a.push_back({(*p)[0], (*p)[1]});
                        p = input.erase(p);
                    }
                    else
                    {
                        p++;
                    }
                }
                if (a.empty())
                {
                    l++;
                }
                else
                {
                    sort(a.begin(), a.end());
                    // instead of l++, use iterator returned by insert.
                    // insert updates the vector and thus invalidates the original l.
                    l = output.insert(l + 1, a.begin(), a.end());
                    a.clear();
                }
            }
            return output;
        }
        vector<vector<int>> reconstructQueue2(vector<vector<int>> &people)
        {
            sort(people.begin(), people.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 {
                     if (x[0] == y[0])
                         return x[1] < y[1]; // same height, smaller k goes first
                     return x[0] < y[0]; });
            vector<vector<int>> output(people.size(), {0, -1});
            for (const auto &p : people)
            {
                int c = p[1];
                for (size_t i = 0; i < output.size(); i++)
                {
                    if (c == 0 && output[i][1] == -1)
                    {
                        output[i] = p;
                        break;
                    }
                    else if (c > 0 && (output[i][1] == -1 || output[i][0] >= p[0]))
                    {
                        c--;
                    }
                }
            }
            return output;
        }
        vector<vector<int>> reconstructQueue3(vector<vector<int>> &people)
        {
            sort(people.begin(), people.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 {
                     if (x[0] == y[0])
                         return x[1] > y[1]; // same height, larger k goes first
                     return x[0] < y[0]; });
            vector<vector<int>> output(people.size(), {0, -1});
            for (const auto &p : people)
            {
                int c = p[1];
                for (size_t i = 0; i < output.size(); i++)
                {
                    if (c == 0 && output[i][1] == -1)
                    {
                        output[i] = p;
                        break;
                    }
                    else if (c > 0 && output[i][1] == -1)
                    {
                        c--;
                    }
                }
            }
            return output;
        }
        vector<vector<int>> reconstructQueue4(vector<vector<int>> &people)
        {
            // sort by height from the tallest to the lowest
            sort(people.begin(), people.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 {
                     if (x[0] == y[0])
                         return x[1] < y[1]; // same height with smaller k is "taller"
                     return x[0] > y[0]; });
            vector<vector<int>> output;
            for (const auto &p : people)
            {
                output.insert(output.begin() + p[1], p);
            }
            return output;
        }
        vector<vector<int>> reconstructQueue5(vector<vector<int>> &people)
        {
            // sort increasingly
            sort(people.begin(), people.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 { return x[0] == y[0] ? x[1] > y[1] : x[0] < y[0]; });
            int n = people.size();
            vector<int> c(n, 0); // BIT to track count of empty elements
            function<int(int)> lsb = [&](int i) -> int
            {
                return i & (~i + 1); // least significant bit
            };
            function<void(int, int)> add = [&](int i, int x)
            {
                i++; // convert from array index (0-based) to BIT index (1-based)
                while (i <= n)
                {
                    c[i - 1] += x;
                    i += lsb(i);
                }
            };
            // build BIT
            for (int i = 0; i < n; i++)
            {
                add(i, 1);
            }
            // count empty elements upto array index i inclusively
            function<int(int)> count = [&](int i) -> int
            {
                i++; // convert from array index (0-based) to BIT index (1-based)
                int s = 0;
                while (i > 0)
                {
                    s += c[i - 1];
                    i -= lsb(i);
                }
                return s;
            };
            vector<vector<int>> output(n);
            for (const auto &p : people)
            {
                int l = 0;
                int h = n;
                while (l < h)
                {
                    int m = l + ((h - l) >> 1);
                    if (count(m) - 1 < p[1])
                        l = m + 1;
                    else
                        h = m;
                }
                output[l] = p;
                add(l, -1);
            }
            return output;
        }
        vector<vector<int>> reconstructQueue6(vector<vector<int>> &people)
        {
            sort(people.begin(), people.end(), [&](const vector<int> &x, const vector<int> &y) -> bool
                 { return x[0] == y[0] ? x[1] > y[1] : x[0] < y[0]; });
            vector<int> rank;
            for (const auto &p : people)
                rank.push_back(p[1]);
            function<void(size_t, size_t, size_t)> merge = [&](size_t l, size_t m, size_t h)
            {
                vector<vector<int>> p;
                vector<int> r;
                int inversionCount = 0;
                size_t i = l;
                size_t j = m + 1;
                while (i <= m || j <= h)
                {
                    if (i <= m && j <= h)
                    {
                        int t = rank[i] - inversionCount;
                        if (t < rank[j])
                        {
                            p.push_back(people[i]);
                            r.push_back(t);
                            i++;
                        }
                        else if (t > rank[j])
                        {
                            p.push_back(people[j]);
                            r.push_back(rank[j]);
                            j++;
                            inversionCount++;
                        }
                        else if (people[i][0] < people[j][0])
                        {
                            p.push_back(people[i]);
                            r.push_back(t);
                            i++;
                        }
                        else
                        {
                            p.push_back(people[j]);
                            r.push_back(rank[j]);
                            j++;
                            inversionCount++;
                        }
                    }
                    else if (i <= m)
                    {
                        p.push_back(people[i]);
                        r.push_back(rank[i] - inversionCount);
                        i++;
                    }
                    else
                    {
                        p.push_back(people[j]);
                        r.push_back(rank[j]);
                        j++;
                        inversionCount++;
                    }
                }
                for (size_t i = 0; i <= h - l; i++)
                {
                    people[l + i] = p[i];
                    rank[l + i] = r[i];
                }
            };
            function<void(size_t, size_t)> mergesort = [&](size_t l, size_t h)
            {
                if (l >= h)
                    return;
                size_t m = l + ((h - l) >> 1);
                mergesort(l, m);
                mergesort(m + 1, h);
                merge(l, m, h);
            };
            mergesort(0, people.size() - 1);
            return people;
        }

        // 407. Trapping Rain Water II
        // Given an m x n integer matrix heightMap representing the height of each unit cell
        // in a 2D elevation map, return the volume of water it can trap after raining.
        // Example 1:
        // Input: heightMap =
        // [[1,4,3,1,3,2]
        // ,[3,2,1,3,2,4]
        // ,[2,3,3,2,3,1]]
        // Output: 4
        // Explanation: After the rain, water is trapped between the blocks.
        // We have two small ponds 1 and 3 units trapped.
        // The total volume of water trapped is 4.
        // Example 2:
        // Input: heightMap =
        // [[3,3,3,3,3]
        // ,[3,2,2,2,3]
        // ,[3,2,1,2,3]
        // ,[3,2,2,2,3]
        // ,[3,3,3,3,3]]
        // Output: 10
        // Constraints:
        // m == heightMap.length
        // n == heightMap[i].length
        // 1 <= m, n <= 200
        // 0 <= heightMap[i][j] <= 2 * 10^4
        int trapRainWater(const vector<vector<int>> &heightMap)
        {
            int volume = 0;
            int m = heightMap.size();
            int n = heightMap[0].size();
            vector<vector<int>> height(heightMap);
            vector<vector<int>> exclude(m, vector<int>(n, 0));
            function<bool(int &, int &)> minheightindex = [&](int &r, int &c) -> bool
            {
                int h = INT_MAX;
                bool found = false;
                for (int i = 1; i < m - 1; i++)
                {
                    for (int j = 1; j < n - 1; j++)
                    {
                        if (height[i][j] < h && exclude[i][j] == 0)
                        {
                            h = height[i][j];
                            r = i;
                            c = j;
                            found = true;
                        }
                    }
                }
                return found;
            };
            function<void(int, int, int, set<pair<int, int>> &, bool &, int &)>
                expand = [&](int h, int i, int j, set<pair<int, int>> &area, bool &excludearea, int &nexth)
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return;
                if (height[i][j] != h)
                {
                    if (height[i][j] > h)
                        nexth = min(nexth, height[i][j]);
                    else
                        excludearea = true;
                    return;
                }
                pair<int, int> p = make_pair(i, j);
                if (area.find(p) != area.end())
                    return;
                area.insert(p);
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                    excludearea = true;
                expand(h, i - 1, j, area, excludearea, nexth);
                expand(h, i, j + 1, area, excludearea, nexth);
                expand(h, i + 1, j, area, excludearea, nexth);
                expand(h, i, j - 1, area, excludearea, nexth);
            };
            function<void(const set<pair<int, int>> &, bool, int)>
                fillarea = [&](const set<pair<int, int>> &area, bool excludearea, int nexth)
            {
                for (const auto p : area)
                {
                    if (excludearea)
                    {
                        exclude[p.first][p.second] = 1;
                    }
                    else
                    {
                        volume += nexth - height[p.first][p.second];
                        height[p.first][p.second] = nexth;
                    }
                }
            };
            while (true)
            {
                int minr;
                int minc;
                if (!minheightindex(minr, minc))
                    break;
                set<pair<int, int>> area;
                bool excludearea = false;
                int nexth = INT_MAX;
                expand(height[minr][minc], minr, minc, area, excludearea, nexth);
                fillarea(area, excludearea, nexth);
            }
            return volume;
        }
        int trapRainWater2(const vector<vector<int>> &heightMap)
        {
            int volume = 0;
            int m = heightMap.size();
            int n = heightMap[0].size();
            vector<vector<int>> height(heightMap);
            set<pair<int, int>> index;
            for (int i = 1; i < m - 1; i++)
            {
                for (int j = 1; j < n - 1; j++)
                    index.insert(make_pair(i, j));
            }
            function<bool(int &, int &)> minheightindex = [&](int &r, int &c) -> bool
            {
                int h = INT_MAX;
                bool found = false;
                for (const auto &i : index)
                {
                    if (height[i.first][i.second] < h)
                    {
                        h = height[i.first][i.second];
                        r = i.first;
                        c = i.second;
                        found = true;
                    }
                }
                return found;
            };
            function<bool(int, int, int, set<pair<int, int>> &, set<pair<int, int>> &, bool &, int &)>
                expand = [&](int h, int i, int j, set<pair<int, int>> &area, set<pair<int, int>> &boundary, bool &excludearea, int &nexth) -> bool
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return false;
                if (height[i][j] != h)
                {
                    if (height[i][j] > h)
                        nexth = min(nexth, height[i][j]);
                    else
                        excludearea = true;
                    return false;
                }
                pair<int, int> p = make_pair(i, j);
                if (area.find(p) != area.end())
                    return true;
                area.insert(p);
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                    excludearea = true;
                bool isboundary = false;
                if (!expand(h, i - 1, j, area, boundary, excludearea, nexth))
                    isboundary = true;
                if (!expand(h, i, j + 1, area, boundary, excludearea, nexth))
                    isboundary = true;
                if (!expand(h, i + 1, j, area, boundary, excludearea, nexth))
                    isboundary = true;
                if (!expand(h, i, j - 1, area, boundary, excludearea, nexth))
                    isboundary = true;
                if (isboundary)
                    boundary.insert(p);
                return true;
            };
            function<void(const set<pair<int, int>> &, bool, int)>
                fillarea = [&](const set<pair<int, int>> &area, bool excludearea, int nexth)
            {
                for (const auto &p : area)
                {
                    if (excludearea)
                    {
                        index.erase(p);
                    }
                    else
                    {
                        volume += nexth - height[p.first][p.second];
                        height[p.first][p.second] = nexth;
                    }
                }
            };
            set<pair<int, int>> area;
            set<pair<int, int>> boundary;
            while (true)
            {
                bool excludearea = false;
                int nexth = INT_MAX;
                if (area.empty())
                {
                    int minr;
                    int minc;
                    if (!minheightindex(minr, minc))
                        break;
                    expand(height[minr][minc], minr, minc, area, boundary, excludearea, nexth);
                }
                else
                {
                    set<pair<int, int>> nextboundary;
                    for (const auto &p : boundary)
                    {
                        bool isboundary = false;
                        if (!expand(height[p.first][p.second], p.first - 1, p.second, area, nextboundary, excludearea, nexth))
                            isboundary = true;
                        if (!expand(height[p.first][p.second], p.first, p.second + 1, area, nextboundary, excludearea, nexth))
                            isboundary = true;
                        if (!expand(height[p.first][p.second], p.first + 1, p.second, area, nextboundary, excludearea, nexth))
                            isboundary = true;
                        if (!expand(height[p.first][p.second], p.first, p.second - 1, area, nextboundary, excludearea, nexth))
                            isboundary = true;
                        if (isboundary)
                            nextboundary.insert(p);
                    }
                    boundary.swap(nextboundary);
                }
                fillarea(area, excludearea, nexth);
                if (excludearea)
                {
                    area.clear();
                    boundary.clear();
                }
            }
            return volume;
        }
        int trapRainWater3(const vector<vector<int>> &heightMap)
        {
            int volume = 0;
            int m = heightMap.size();
            int n = heightMap[0].size();
            vector<vector<int>> height(heightMap);
            function<bool(const pair<int, int> &, const pair<int, int> &)>
                higher = [&](const pair<int, int> &x, const pair<int, int> &y) -> bool
            {
                return height[x.first][x.second] > height[y.first][y.second];
            };
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(higher)> boundary(higher);
            set<pair<int, int>> visited;
            pair<int, int> p;
            for (int i = 0; i < m; i++)
            {
                p = make_pair(i, 0);
                boundary.push(p);
                visited.insert(p);
                p = make_pair(i, n - 1);
                boundary.push(p);
                visited.insert(p);
            }
            for (int j = 0; j < n; j++)
            {
                p = make_pair(0, j);
                boundary.push(p);
                visited.insert(p);
                p = make_pair(m - 1, j);
                boundary.push(p);
                visited.insert(p);
            }
            function<void(int, int, int)> visit = [&](int i, int j, int h)
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return;
                auto x = make_pair(i, j);
                if (visited.find(x) != visited.end())
                    return;
                if (height[i][j] < h)
                {
                    volume += h - height[i][j];
                    height[i][j] = h;
                }
                boundary.push(x);
                visited.insert(x);
            };
            while (!boundary.empty())
            {
                p = boundary.top();
                boundary.pop();
                visit(p.first - 1, p.second, height[p.first][p.second]);
                visit(p.first, p.second + 1, height[p.first][p.second]);
                visit(p.first + 1, p.second, height[p.first][p.second]);
                visit(p.first, p.second - 1, height[p.first][p.second]);
            }
            return volume;
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

    }
}

#endif
