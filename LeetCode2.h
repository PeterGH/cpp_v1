#ifndef _LEETCODE2_H_
#define _LEETCODE2_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
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
        vector<int> singleNumber(vector<int> &nums)
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
        vector<int> singleNumber2(vector<int> &nums)
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
            function<int(int, int)> divide = [&](int n, int d) -> int {
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
            function<void(int)> convert = [&](int n) {
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
            sort(citations.begin(), citations.end(), [&](int x, int y) -> bool {
                return x > y;
            });
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

    } // namespace LeetCode
} // namespace Test

#endif
