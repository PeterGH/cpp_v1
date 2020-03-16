#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "String.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Test {

// Assume the input is sorted.
// Cases:
// 1. empty input
// 2. target exists
// 3. target not exists
int BinarySearch(const vector<int> &input, int target) {
    int b = 0;
    int e = (int)input.size() - 1;
    // [b..e] contain possible answers
    while (b <= e) {
        int m = b + ((e - b) >> 1);
        if (input[m] < target)
            b = m + 1;
        else if (input[m] > target)
            e = m - 1;
        else
            return m;
    }
    return -1;
}
int BinarySearch2(const vector<int> &input, int target) {
    int b = 0;
    int e = (int)input.size();
    // [b..e) contain possible answers
    while (b < e) {
        int m = b + (e - b) / 2;
        if (input[m] < target)
            b = m + 1;
        else if (input[m] > target)
            e = m;
        else
            return m;
    }
    // Post-processing: End Condition: b == e
    if (b != (int)input.size() && input[b] == target)
        return b;
    return -1;
}
int BinarySearch3(const vector<int> &input, int target) {
    if (input.size() == 0)
        return -1;
    int b = 0;
    int e = input.size() - 1;
    // (b..e) contain possible answers
    while (b + 1 < e) {
        int m = b + (e - b) / 2;
        if (input[m] == target)
            return m;
        else if (input[m] < target)
            b = m;
        else
            e = m;
    }
    // Post-processing: End Condition: b + 1 == e
    if (input[b] == target)
        return b;
    if (input[e] == target)
        return e;
    return -1;
}

class KMP {
  private:
    unique_ptr<char[]> pattern;
    unique_ptr<int[]> prefix;
    int length;

  public:
    KMP(const char *pattern) {
        if (pattern == nullptr)
            throw invalid_argument("pattern is nullptr");
        this->length = (int)strlen(pattern);
        if (this->length <= 0)
            throw invalid_argument(
                String::Format("length %d <= 0", this->length));
        this->pattern.reset(new char[this->length + 1]);
        strcpy(this->pattern.get(), pattern);
        this->prefix.reset(new int[this->length]);
        memset(this->prefix.get(), 0, this->length * sizeof(int));
        // Maintain prefix[i] = k, update prefix[i+1] by checking pattern[i+1]
        // vs pattern[k+1]. The goal is for each input i, find k such that
        // pattern[0..k] is suffix of input[0..i].
        int k = -1;
        this->prefix[0] = k;
        for (int i = 1; i < this->length; i++) {
            while (k > -1 && this->pattern[k + 1] != this->pattern[i]) {
                // Keep searching backward for minimum k
                // such that pattern[0..k)] is a suffix of pattern[0..(i-1)]
                k = this->prefix[k];
            }
            // The while loop terminates when
            // 1. there is a k such that pattern[0..(k+1)] is a suffix of
            // pattern[0..i], or
            // 2. k = -1 (i.e., pattern[0] != pattern[i])
            if (this->pattern[k + 1] == this->pattern[i]) {
                // One more match
                k = k + 1;
            } else {
                // k = -1
            }
            this->prefix[i] = k;
        }
    }
    void Print(void) {
        for (int i = 0; i < this->length; i++) {
            printf("\t%d", i);
        }
        printf("\n");
        for (int i = 0; i < this->length; i++) {
            printf("\t%d", this->prefix[i]);
        }
        printf("\n");
    }
    vector<int> SearchString(const char *input, int length) {
        vector<int> indices;
        if (input == nullptr || input[0] == '\0' || length <= 0)
            return indices;
        int k = -1;
        for (int i = 0; i < length; i++) {
            while (k > -1 && this->pattern[k + 1] != input[i])
                k = this->prefix[k];
            if (this->pattern[k + 1] == input[i])
                k = k + 1;
            if (k == this->length - 1) {
                indices.push_back(i - k);
                k = this->prefix[k];
            }
        }
        return indices;
    }
};

} // namespace Test
#endif