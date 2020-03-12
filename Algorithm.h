#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>
#include "String.h"

using namespace std;

namespace Test {

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