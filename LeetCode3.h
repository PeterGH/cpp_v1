#ifndef _LEETCODE3_H_
#define _LEETCODE3_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 301. Remove Invalid Parentheses
        // Remove the minimum number of invalid parentheses in order to make the input string valid.
        // Return all possible results.
        // Note: The input string may contain letters other than the parentheses ( and ).
        // Example 1:
        // Input: "()())()"
        // Output: ["()()()", "(())()"]
        // Example 2:
        // Input: "(a)())()"
        // Output: ["(a)()()", "(a())()"]
        // Example 3:
        // Input: ")("
        // Output: [""]
        vector<string> removeInvalidParentheses(string s)
        {
            vector<string> output;
            deque<char> d;
            for (const char &c : s)
            {
                if (c == '(')
                {
                    d.push_back(c);
                }
                else if (c == ')')
                {
                    if (!d.empty() && d.back() == '(')
                        d.pop_back();
                    else
                        d.push_back(c);
                }
            }
            function<void(size_t, string, int, int, const queue<char> &)> remove =
                [&](size_t i, string v, int l, int r, const queue<char> &q) {
                    while (i < s.size() && s[i] != '(' && s[i] != ')')
                    {
                        v.append(1, s[i++]);
                    }
                    if (i >= s.size())
                    {
                        // Need to remove duplicates
                        if (l == r && q.empty() && find(output.begin(), output.end(), v) == output.end())
                            output.push_back(v);
                        return;
                    }
                    // If we have "))" and need to remove one ')', the logic below will generate duplicates.
                    // Same will happen if need to remove two ')'s from ")))".
                    if (!q.empty() && s[i] == q.front())
                    {
                        queue<char> q1(q);
                        q1.pop();
                        remove(i + 1, v, l, r, q1);
                    }
                    if (s[i] == '(')
                    {
                        v.append(1, '(');
                        remove(i + 1, v, l + 1, r, q);
                    }
                    else if (l > r)
                    {
                        v.append(1, ')');
                        remove(i + 1, v, l, r + 1, q);
                    }
                };
            queue<char> e(d);
            string o;
            remove(0, o, 0, 0, e);
            return output;
        }
        vector<string> removeInvalidParentheses2(string s)
        {
            vector<string> output;
            deque<char> d;
            for (const char &c : s)
            {
                if (c == '(')
                {
                    d.push_back(c);
                }
                else if (c == ')')
                {
                    if (!d.empty() && d.back() == '(')
                        d.pop_back();
                    else
                        d.push_back(c);
                }
            }
            function<void(size_t, string, int, int, const queue<char> &)> remove =
                [&](size_t i, string v, int l, int r, const queue<char> &q) {
                    while (i < s.size() && s[i] != '(' && s[i] != ')')
                    {
                        v.append(1, s[i++]);
                    }
                    if (i >= s.size())
                    {
                        if (l == r && q.empty())
                            output.push_back(v);
                        return;
                    }
                    if (!q.empty() && s[i] == q.front())
                    {
                        queue<char> q1(q);
                        q1.pop();
                        remove(i + 1, v, l, r, q1);
                        while (i + 1 < s.size() && s[i] == s[i + 1])
                        {
                            i++;
                            v.append(1, s[i]);
                            if (s[i] == '(')
                            {
                                l++;
                            }
                            else
                            {
                                r++;
                            }
                        }
                    }
                    if (s[i] == '(')
                    {
                        v.append(1, '(');
                        remove(i + 1, v, l + 1, r, q);
                    }
                    else if (l > r)
                    {
                        v.append(1, ')');
                        remove(i + 1, v, l, r + 1, q);
                    }
                };
            queue<char> e(d);
            string o;
            remove(0, o, 0, 0, e);
            return output;
        }

    }
}

#endif
