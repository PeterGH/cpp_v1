#ifndef _LEETCODE7_H_
#define _LEETCODE7_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
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

    }
}

#endif
