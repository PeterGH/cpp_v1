#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Random.h"
#include "Test.h"

using namespace Test;

class LeetCodeTest : public TestClass
{
  public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
};

void LeetCodeTest::Init(void)
{
    Add("TwoSum-UnsortedMultiSolutions", [&]() {
        auto check = [&](vector<int> &input, int sum) {
            auto pairs = LeetCode::TwoSum::unsortedMultiSolutions(input, sum);
            vector<int> input2(input);
            auto pairs2 = LeetCode::TwoSum::unsortedMultiSolutions2(input2, sum);
            sort(pairs.begin(), pairs.end());
            sort(pairs2.begin(), pairs2.end());
            Logger() << "Target " << sum << ", pairs count " << pairs.size()
                     << (pairs.size() == pairs2.size() ? "==" : "!=")
                     << pairs2.size() << endl;
            ASSERT1(pairs.size() == pairs2.size());
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (pairs[i] != pairs2[i])
                {
                    Logger() << "pairs " << i << "<" << pairs[i].first << "," << pairs[i].second
                             << "> != <" << pairs2[i].first << "," << pairs2[i].second << ">" << endl;
                }
                ASSERT1(pairs[i] == pairs2[i]);
            }
        };

        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Random::Vector(Random::Int(50, 2), 20, -20);
            int length = (int)input.size();
            Logger() << "Run " << i << ": " << length << " numbers" << endl;
            for (int j = 0; j < length - 1; j++)
            {
                for (int k = j + 1; k < length; k++)
                {
                    check(input, input[j] + input[k]);
                }
            }
        }
    });

    Add("TwoSum-SortedMultiSolutions", [&]() {
        auto check = [&](vector<int> &input, int sum) {
            auto pairs = LeetCode::TwoSum::sortedMultiSolutions(input, sum);
            auto pairs2 = LeetCode::TwoSum::sortedMultiSolutions2(input, sum);
            sort(pairs.begin(), pairs.end());
            sort(pairs2.begin(), pairs2.end());
            Logger() << "Target: " << sum << ", pairs count " << pairs.size()
                     << (pairs.size() == pairs2.size() ? "==" : "!=")
                     << pairs2.size() << endl;
            ASSERT1(pairs.size() == pairs2.size());
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (pairs[i] != pairs2[i])
                {
                    Logger() << "pairs " << i << "<" << pairs[i].first << "," << pairs[i].second
                             << "> != <" << pairs2[i].first << "," << pairs2[i].second << ">" << endl;
                }
                ASSERT1(pairs[i] == pairs2[i]);
            }
        };
        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Random::Vector(Random::Int(50, 2), 20, -20);
            sort(input.begin(), input.end());
            int length = (int)input.size();
            Logger() << "Run " << i << ": " << length << " numbers" << endl;
            for (int j = 0; j < length - 1; j++)
            {
                for (int k = j + 1; k < length; k++)
                {
                    check(input, input[j] + input[k]);
                }
            }
        }
    });
}
#endif