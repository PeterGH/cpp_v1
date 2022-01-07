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
