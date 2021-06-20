#ifndef _LEETCODETEST1_H_
#define _LEETCODETEST1_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init1(void)
{
    Add("100. Same Tree", [&]() {
        auto checkTree = [&](TreeNode *t, TreeNode *t2) {
            Print(t);
            Print(t2);
            bool r = isSameTree(t, t2);
            bool r2 = isSameTree2(t, t2);
            bool r3 = isSameTree3(t, t2);
            Logger() << "isSameTree " << r << ", " << r2 << ", " << r3 << endl;
            DeleteTree(t);
            DeleteTree(t2);
            ASSERT1(r == r2);
            ASSERT1(r == r3);
        };
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            TreeNode *t2 = RandomTree(v);
            TreeNode *t3 = Clone(t);
            TreeNode *t4 = Clone(t);
            checkTree(t, t2);
            checkTree(t3, t4);
        };
        {
            TreeNode *t = new TreeNode(10);
            t->left = new TreeNode(5);
            t->left->left = new TreeNode(15);
            TreeNode *t2 = new TreeNode(10);
            t2->left = new TreeNode(5);
            t2->left->right = new TreeNode(15);
            checkTree(t, t2);
        }
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(40, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("101. Symmetric Tree", [&]() {
        auto check = [&](const vector<int> &v,
                         bool createSymmetricTree = false) {
            Logger() << v;
            TreeNode *t;
            if (createSymmetricTree)
                t = RandomSymmetricTree(v);
            else
                t = RandomTree(v);
            Print(t);
            bool r = isSymmetric(t);
            bool r2 = isSymmetric2(t);
            bool r3 = isSymmetric3(t);
            Logger() << "isSymmetric: " << r << ", " << r2 << ", " << r3
                     << endl;
            DeleteTree(t);
            ASSERT1(r == r2);
            ASSERT1(r == r3);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
            check(v, true);
        }
    });

    Add("102. Binary Tree Level Order Traversal", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = levelOrder(t);
            vector<vector<int>> r2 = levelOrder2(t);
            vector<vector<int>> r3 = levelOrder3(t);
            Logger() << "levelOrder: " << r << endl;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
            ASSERT1(0 == Util::Compare(r, r3));
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("103. Binary Tree Zigzag Level Order Traversal", [&]() {
        auto checkTree = [&](TreeNode *t) {
            Print(t);
            vector<vector<int>> r = zigzagLevelOrder(t);
            vector<vector<int>> r2 = zigzagLevelOrder2(t);
            Logger() << r;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
        };
        auto checkVector = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            checkTree(t);
        };
        {
            TreeNode *t = new TreeNode(3);
            t->left = new TreeNode(9);
            t->right = new TreeNode(20);
            t->right->left = new TreeNode(15);
            t->right->right = new TreeNode(7);
            checkTree(t);
        }
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            checkVector(v);
        }
    });

    Add("104. Maximum Depth of Binary Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int d = maxDepth(t);
            int d2 = maxDepth2(t);
            int d3 = maxDepth3(t);
            Logger() << "maxDepth: " << d << ", " << d2 << ", " << d3 << endl;
            DeleteTree(t);
            ASSERT1(d == d2);
            ASSERT1(d == d3);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("105. Construct Binary Tree from Preorder and Inorder Traversal",
        [&]() {
            auto check = [&](const vector<int> &v) {
                TreeNode *t = RandomTree(v);
                Print(t);
                vector<int> pre = preorderTraversal(t);
                Logger() << "PreOrder: " << pre;
                vector<int> in = inorderTraversal(t);
                Logger() << "InOrder:  " << in;
                TreeNode *t2 = buildTree(pre, in);
                Print(t2);
                bool r = isSameTree(t, t2);
                TreeNode *t3 = buildTree2(pre, in);
                Print(t3);
                bool r2 = isSameTree(t, t3);
                TreeNode *t4 = buildTree3(pre, in);
                Print(t4);
                bool r3 = isSameTree(t, t4);
                Logger() << "isSame: " << r << ", " << r2 << ", " << r3 << endl;
                DeleteTree(t);
                DeleteTree(t2);
                DeleteTree(t3);
                DeleteTree(t4);
                ASSERT1(r == true);
                ASSERT1(r2 == true);
                ASSERT1(r3 == true);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 1);
                vector<int> v = Util::IncreasingVector(n);
                check(v);
            }
        });

    Add("106. Construct Binary Tree from Inorder and Postorder Traversal",
        [&]() {
            auto check = [&](const vector<int> &v) {
                TreeNode *t = RandomTree(v);
                Print(t);
                vector<int> in = inorderTraversal(t);
                Logger() << "InOrder:   " << in;
                vector<int> post = postorderTraversal(t);
                Logger() << "PostOrder: " << post;
                TreeNode *t2 = buildTreeInOrderPostOrder(in, post);
                Print(t2);
                bool r = isSameTree(t, t2);
                TreeNode *t3 = buildTreeInOrderPostOrder2(in, post);
                Print(t3);
                bool r2 = isSameTree(t, t3);
                TreeNode *t4 = buildTreeInOrderPostOrder3(in, post);
                Print(t4);
                bool r3 = isSameTree(t, t4);
                Logger() << "isSame: " << r << ", " << r2 << ", " << r3 << endl;
                DeleteTree(t);
                DeleteTree(t2);
                DeleteTree(t3);
                DeleteTree(t4);
                ASSERT1(r == true);
                ASSERT1(r2 == true);
                ASSERT1(r3 == true);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 1);
                vector<int> v = Util::IncreasingVector(n);
                check(v);
            }
        });

    Add("107. Binary Tree Level Order Traversal II", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = levelOrderBottom(t);
            vector<vector<int>> r2 = levelOrderBottom2(t);
            Logger() << "levelOrderBottom: " << r << endl;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("108. Convert Sorted Array to Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << "Convert to balanced BST:" << v;
            TreeNode *t = sortedArrayToBST(v);
            Print(t);
            TreeNode *t2 = sortedArrayToBST2(v);
            Print(t2);
            bool r = isSameTree(t, t2);
            Logger() << "isSameTree: " << r << endl;
            DeleteTree(t);
            DeleteTree(t2);
            ASSERT1(r == true);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("109. Convert Sorted List to Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            ListNode *l = ToList(v);
            Logger() << "Convert to balanced BST:";
            Print(l);
            TreeNode *t = sortedListToBST(l);
            Print(t);
            TreeNode *t2 = sortedListToBST2(l);
            Print(t2);
            TreeNode *t3 = sortedListToBST3(l);
            Print(t3);
            bool b = isBalanced(t);
            bool b2 = isBalanced(t2);
            bool b3 = isBalanced(t3);
            Logger() << "isBalanced: " << b << ", " << b2 << ", " << b3 << endl;
            bool r = isSameTree(t, t2);
            bool r2 = isSameTree(t, t3);
            Logger() << "isSameTree: " << r << ", " << r2 << endl;
            DeleteTree(t);
            DeleteTree(t2);
            DeleteTree(t3);
            DeleteList(l);
            ASSERT1(b == true);
            ASSERT1(b2 == true);
            ASSERT1(b3 == true);
            // ASSERT1(r == true); sortedListToBST2 is a bit different
            ASSERT1(r2 == true);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("111. Minimum Depth of Binary Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int d = minDepth(t);
            int d2 = minDepth2(t);
            int d3 = minDepth3(t);
            DeleteTree(t);
            Logger() << "minDepth: " << d << ", " << d2 << ", " << d3 << endl;
            ASSERT1(d == d2);
            ASSERT1(d == d3);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("112. Path Sum", [&]() {
        auto check = [&](const vector<int> &v, int sum) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int r = hasPathSum(t, sum);
            int r2 = hasPathSum2(t, sum);
            int s = pickPathSum(t);
            int b = hasPathSum(t, s);
            int b2 = hasPathSum2(t, s);
            DeleteTree(t);
            Logger() << "hasPathSum(" << sum << "): " << r << ", " << r2
                     << endl;
            Logger() << "hasPathSum(" << s << "): " << b << ", " << b2 << endl;
            ASSERT1(r == r2);
            ASSERT1(b == true);
            ASSERT1(b2 == true);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v, Random::Int(200));
        }
    });

    Add("113. Path Sum II", [&]() {
        auto check = [&](const vector<int> &v, int sum) {
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = pathSum(t, sum);
            vector<vector<int>> r2 = pathSum2(t, sum);
            Logger() << "pathSum(" << sum << "):" << endl;
            Util::Sort(r);
            Util::Sort(r2);
            Logger() << r;
            setPathSum(t, sum);
            Print(t);
            vector<vector<int>> b = pathSum(t, sum);
            vector<vector<int>> b2 = pathSum2(t, sum);
            DeleteTree(t);
            Util::Sort(b);
            Util::Sort(b2);
            Logger() << "pathSum(" << sum << "):" << endl;
            Logger() << b;
            ASSERT1(0 == Util::Compare(r, r2));
            ASSERT1(0 == Util::Compare(b, b2));
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v, Random::Int(200));
        }
    });

    Add("114. Flatten Binary Tree to Linked List", [&]() {
        auto check = [&](int n) {
            TreeNode *t = RandomTree(n);
            Print(t);
            TreeNode *t2 = Clone(t);
            TreeNode *t3 = Clone(t);
            flatten(t);
            Print(t);
            flatten(t2);
            Print(t2);
            flatten(t3);
            Print(t3);
            vector<int> v = preorderTraversal(t);
            vector<int> v2 = preorderTraversal(t2);
            vector<int> v3 = preorderTraversal(t3);
            DeleteTree(t);
            DeleteTree(t2);
            DeleteTree(t3);
            ASSERT1(Util::IsIncreasing(v));
            ASSERT1(Util::IsIncreasing(v2));
            ASSERT1(Util::IsIncreasing(v3));
            ASSERT1(0 == Util::Compare(v, v2));
            ASSERT1(0 == Util::Compare(v, v3));
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            check(n);
        }
    });

    Add("115. Distinct Subsequences", [&]() {
        auto check = [&](const string &s, const string &t) {
            int c = numDistinct(s, t);
            int c2 = numDistinct2(s, t);
            Logger() << "numDistinct(" << endl;
            Logger() << "s: " << s << endl;
            Logger() << "t: " << t << endl;
            Logger() << ") = " << c << ", " << c2 << endl;
            ASSERT1(c == c2);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 2);
            int m = Random::Int(10, 1);
            string s = Random::String<char>(n, "abcdefg");
            string t = Random::String<char>(m, "abcd");
            check(s, t);
        }
    });

    Add("123. Best Time to Buy and Sell Stock III", [&]() {
        auto check = [&](const vector<int> &p) {
            Logger() << p;
            int m = maxProfitIII(p);
            int m2 = maxProfitIII2(p);
            int m3 = maxProfitIII3(p);
            int m4 = maxProfitIII4(p);
            Logger() << "maxProfitIII: " << m << ", " << m2 << ", " << m3
                     << ", " << m4 << endl;
            ASSERT1(m == m2);
            ASSERT1(m == m3);
            ASSERT1(m == m4);
        };
        check({1});
        check({1, 2});
        check({2, 2});
        check({1, 2, 3});
        check({1, 2, 2});
        check({2, 2, 2});
        check({1, 2, 3, 4});
        check({2, 7, 1, 6});
        check({3, 7, 1, 6});
        check({9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3});
        check({6, 1, 3, 2, 4, 7});
        for (int i = 0; i < 100; i++)
        {
            int len = Random::Int(100, 1);
            vector<int> v = Random::Vector(len, 100);
            check(v);
        }
    });

    Add("124. Binary Tree Maximum Path Sum", [&]() {
        auto check = [&](TreeNode *node, long long expect) {
            Print(node);
            long long sum = maxPathSum(node);
            long long sum2 = maxPathSum2(node);
            Logger().WriteInformation("Sum %lld %s %lld\n", sum,
                                      sum == expect ? "==" : "!=", expect);
            Logger().WriteInformation("Sum2 %lld %s %lld\n", sum2,
                                      sum2 == expect ? "==" : "!=", expect);
            ASSERT1(sum == expect);
            ASSERT1(sum2 == expect);
        };
        {
            TreeNode n1(1);
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            n1.left = &n2;
            check(&n1, 3);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            n1.left = &n2;
            check(&n1, 2);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            n1.left = &n2;
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(-2);
            n1.left = &n2;
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            n1.right = &n2;
            check(&n1, 3);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            n1.right = &n2;
            check(&n1, 2);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            n1.right = &n2;
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(-2);
            n1.right = &n2;
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 6);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(-2);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(-2);
            TreeNode n2(3);
            TreeNode n3(2);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 1);
        }
        {
            TreeNode n1(-4);
            TreeNode n2(-2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, -2);
        }
        {
            TreeNode n1(-4);
            TreeNode n2(-4);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, -3);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 10);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 6);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-4);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(-4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 6);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(3);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            check(&n1, 10);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            check(&n1, 11);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            TreeNode n6(6);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            n3.left = &n6;
            check(&n1, 17);
        }
        {
            TreeNode n1(-10);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            TreeNode n6(6);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            n3.left = &n6;
            check(&n1, 11);
        }
    });

    Add("125. Valid Palindrome", [&]() {
        auto check = [&](const string &s, bool e) {
            bool r = isPalindrome(s);
            bool r2 = isPalindrome2(s);
            bool r3 = isPalindrome3(s);
            Logger().WriteInformation("\"%s\" is palindrome: %d, %d, %d\n",
                                      s.c_str(), r, r2, r3);
            ASSERT1(r == e);
            ASSERT1(r2 == e);
            ASSERT1(r3 == e);
        };
        check("", true);
        check("1", true);
        check("a", true);
        check(",", true);
        check("22", true);
        check("23", false);
        check("ab", false);
        check("a1", false);
        check(":3", true);
        check("a;", true);
        check("?b", true);
        check("# #4**", true);
        check("# c**", true);
        check("a, b&*() A;", true);
        check("A man, a plan, a canal: Panama", true);
        check("race a car", false);
        check("^%(&*%$%(", true);
        check("A^%(&*%$%(a", true);
        check("^%9(&*%$9%(", true);
    });

    Add("126. Word Ladder II", [&]() {
        auto check = [&](const string &begin, const string &end,
                         const vector<string> &dic) {
            Logger() << dic;
            Logger() << "Search path: " << begin << " -> " << end << endl;
            vector<vector<string>> results = findLadders(begin, end, dic);
            vector<vector<string>> results2 = findLadders2(begin, end, dic);
            vector<vector<string>> results3 = findLadders3(begin, end, dic);
            Util::Sort(results);
            Util::Sort(results2);
            Util::Sort(results3);
            Logger() << "Results = " << results;
            ASSERT1(0 == Util::Compare(results, results2));
            ASSERT1(0 == Util::Compare(results, results3));
        };
        check("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"});
    });

    Add("127. Word Ladder", [&]() {
        auto check = [&](const string &start, const string &end,
                         const vector<string> &dict, int expect) {
            Logger() << "Dictionary:" << dict;
            Logger().WriteInformation("    Start:   %s\n", start.c_str());
            Logger().WriteInformation("    End:     %s\n", end.c_str());
            int length = ladderLength(start, end, dict);
            int length2 = ladderLength2(start, end, dict);
            int length3 = ladderLength3(start, end, dict);
            int length4 = ladderLength4(start, end, dict);
            int length5 = ladderLength5(start, end, dict);
            Logger().WriteInformation("    Length:  %d, %d, %d, %d, %d, %d\n",
                                      length, length2, length3, length4,
                                      length5, expect);
            ASSERT1(length == expect);
            ASSERT1(length2 == expect);
            ASSERT1(length3 == expect);
            ASSERT1(length4 == expect);
            ASSERT1(length5 == expect);
        };
        check("hit", "cog", {"hot"}, 0);
        check("hit", "cog", {"hot", "dot", "dog", "lot", "log"}, 0);
        check("hit", "cog", {"hot", "dot", "dog", "cog", "lot", "log"}, 5);
        check("red", "tax",
              {"ted", "tex", "reb", "tax", "tad", "den", "rex", "pee"}, 4);
        check("d", "c", vector<string>{"a", "b", "c"}, 2);
        check("qa", "sq",
              vector<string>{"si", "go", "se", "cm", "so", "ph", "mt", "db",
                             "mb", "sb", "kr", "ln", "tm", "le", "av", "sm",
                             "ar"},
              0);
    });

    Add("128. Longest Consecutive Sequence", [&]() {
        auto check = [&](const vector<int> &input, int expectLength,
                         bool ignoreE = false) {
            Logger() << input;
            int length = longestConsecutive(input);
            int length2 = longestConsecutive2(input);
            int length3 = longestConsecutive3(input);
            if (ignoreE)
            {
                Logger().WriteInformation("  Length: %d, %d, %d\n", length,
                                          length2, length3);
                ASSERT1(length == length2);
                ASSERT1(length == length3);
            }
            else
            {
                Logger().WriteInformation("  Length: %d, %d, %d, %d\n", length,
                                          length2, length3, expectLength);
                ASSERT1(length == expectLength);
                ASSERT1(length2 == expectLength);
                ASSERT1(length3 == expectLength);
            }
        };
        check({0}, 1);
        check({0, 0}, 1);
        check({0, 1}, 2);
        check({1, 0}, 2);
        check({0, 2}, 1);
        check({0, 1, 2}, 3);
        check({0, 1, 3}, 2);
        check({-1, 1, 2}, 2);
        check({0, -1, 2}, 2);
        check({3, 1, 2}, 3);
        check({0, 1, 1}, 2);
        check({1, 0, 1, 1}, 2);
        check({1, 0, 1, 0}, 2);
        check({1, 0, -1}, 3);
        check({0, 1, 2, 1}, 3);
        check({-7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7, 5, -1, -7}, 4);
        check({-6, 8, -5, 7, -9, -1, -7, -6, -9, -7, 5, 7, -1, -8, -8, -2, 0},
              5);
        check({1, 2, 3, 4, 5, 3, 2, 1}, 5);
        check({2, 1, 3, -1, 0, -2, 1}, 6);
        check({6, 5, 3, 4, 2, 5, 3, 4, 6}, 5);
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(200);
            vector<int> input = Random::Vector(n, 50, -50);
            check(input, 0, true);
        }
    });

    Add("129. Sum Root to Leaf Numbers", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *n = RandomTree(v);
            Print(n);
            int s = sumNumbers(n);
            int s2 = sumNumbers2(n);
            Logger() << "sumNumbers: " << s << ", " << s2 << endl;
            DeleteTree(n);
            ASSERT1(s == s2);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100);
            vector<int> input = Random::Vector(n, 9);
            check(input);
        }
    });

    Add("130. Surrounded Regions", [&]() {
        auto verify = [&](const vector<vector<char>> &board) {
            int height = board.size();
            int width = board[0].size();
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                    {
                        bool boundary = i == 0 || i == height - 1 || j == 0 ||
                                        j == width - 1;
                        pair<int, int> p = make_pair(i, j);
                        set<pair<int, int>> region;
                        queue<pair<int, int>> q;
                        region.insert(p);
                        q.push(p);
                        while (!q.empty())
                        {
                            p = q.front();
                            q.pop();
                            pair<int, int> n;
                            if (p.first > 0 &&
                                board[p.first - 1][p.second] == 'O')
                            {
                                if (p.first - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first - 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second > 0 &&
                                board[p.first][p.second - 1] == 'O')
                            {
                                if (p.second - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first, p.second - 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second < width - 1 &&
                                board[p.first][p.second + 1] == 'O')
                            {
                                if (p.second + 1 == width - 1)
                                    boundary = true;
                                n = make_pair(p.first, p.second + 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.first < height - 1 &&
                                board[p.first + 1][p.second] == 'O')
                            {
                                if (p.first + 1 == height - 1)
                                    boundary = true;
                                n = make_pair(p.first + 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                        }
                        ASSERT1(boundary);
                    }
                }
            }
        };
        auto check = [&](vector<vector<char>> &board) {
            Logger().WriteInformation("Input:\n");
            Logger().Print(board, "%c");
            vector<vector<char>> board2(board);
            vector<vector<char>> board3(board);
            solve(board);
            solve2(board2);
            solve3(board3);
            Logger().WriteInformation("Output1:\n");
            Logger() << board;
            Logger() << board2;
            Logger() << board3;
            verify(board);
            verify(board2);
            verify(board3);
            ASSERT1(0 == Util::Compare(board, board2));
            ASSERT1(0 == Util::Compare(board, board3));
        };
        {
            vector<vector<char>> board = {{'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X'}, {'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X'}, {'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O'}, {'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O'}, {'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'O', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'X', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'O'}, {'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'O', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'O', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'X', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'X', 'O'}};
            check(board);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'O', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {
                {'X', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {
                {'O', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {
                {'O', 'X', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            check(board);
        }
        {
            vector<vector<char>> board = {
                {'X', 'O', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            check(board);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int height = 1 + rand() % 100;
                int width = 1 + rand() % 100;
                Logger().WriteInformation("Run %d, %d X %d\n", i, height,
                                          width);
                vector<vector<char>> board;
                for (int j = 0; j < height; j++)
                {
                    vector<char> row;
                    for (int k = 0; k < width; k++)
                    {
                        int v = rand();
                        if ((v & 0x1) == 1)
                            row.push_back('X');
                        else
                            row.push_back('O');
                    }
                    board.push_back(row);
                }
                check(board);
            }
        }
    });

    Add("131. Palindrome Partitioning", [&]() {
        auto check = [&](const string &s) {
            Logger() << "Palindrom partition(\"" << s << "\") = " << endl;
            vector<vector<string>> r = partition(s);
            vector<vector<string>> r2 = partition2(s);
            vector<vector<string>> r3 = partition3(s);
            Logger() << r;
            Util::SortGrid(r);
            Util::SortGrid(r2);
            Util::SortGrid(r3);
            ASSERT1(0 == Util::Compare(r, r2));
            ASSERT1(0 == Util::Compare(r, r3));
            int c = minCut(s);
            int c2 = minCut2(s);
            Logger() << "minCut: " << c << ", " << c2 << endl;
            int m = INT_MAX;
            for_each(r.cbegin(), r.cend(), [&](const vector<string> &v) {
                m = min(m, (int)v.size());
            });
            m--;
            ASSERT1(c == m);
            ASSERT1(c2 == m);
        };
        check("aab");
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            string s = Random::String<char>(n, "abcde");
            check(s);
        }
    });

    Add("133. Clone Graph", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            Node *g = RandomGraph(v);
            Node *c = cloneGraph(g);
            Node *c2 = cloneGraph2(g);
            map<int, vector<int>> m = ToMap(c);
            map<int, vector<int>> m2 = ToMap(c2);
            DeleteGraph(g);
            DeleteGraph(c);
            DeleteGraph(c2);
            Util::Sort(m);
            Util::Sort(m2);
            Logger() << m;
            Logger() << m2;
            ASSERT1(Util::Equal(m, m2));
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("134. Gas Station", [&]() {
        auto check = [&](const vector<int> &g, const vector<int> &c) {
            Logger() << g;
            Logger() << c;
            int r = canCompleteCircuit(g, c);
            int r2 = canCompleteCircuit2(g, c);
            Logger() << "canCompleteCircuit = " << r << ", " << r2 << endl;
            ASSERT1(r == r2);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(50, 1);
            vector<int> g = Random::Vector(n, 10);
            vector<int> c = Random::Vector(n, 10);
            check(g, c);
        }
    });

    Add("137. Single Number II", [&]() {
        auto check = [&](const vector<int> &input, int expect,
                         bool ignoreE = false) {
            Logger() << input;
            int r = singleNumberII(input);
            int r2 = singleNumberII2(input);
            int r3 = singleNumberII3(input);
            Logger().WriteInformation("Single number: %d, %d, %d\n", r, r2, r3);
            if (ignoreE)
            {
                ASSERT1(r == r2);
                ASSERT1(r == r3);
            }
            else
            {
                ASSERT1(r == expect);
                ASSERT1(r2 == expect);
                ASSERT1(r3 == expect);
            }
        };
        check({2, 2, 3, 2}, 3);
        check({0, 1, 0, 0}, 1);
        check({(int)0xFFFFFFFF, 3, (int)0xFFFFFFFF, (int)0xFFFFFFFF}, 3);
        check({1, 2, 3, 1, 2, 3, 4, 1, 2, 3}, 4);
        check({0, 1, 0, 1, 0, 1, 99}, 99);
        for (int j = 0; j < 100; j++)
        {
            vector<int> n;
            int c;
            for (int i = 0; i < 10; i++)
            {
                c = 1 + rand() % INT_MAX;
                n.insert(n.end(), 3, c);
            }
            c = 1 + rand() % INT_MAX;
            n.insert(n.end(), 1, c);
            random_shuffle(n.begin(), n.end());
            check(n, 0, true);
        }
    });

    Add("139. Word Break", [&]() {
        auto check = [&](const string &s, const vector<string> &dict, bool e,
                         bool ignoreE = false) {
            Logger() << "Dictionary: " << dict;
            bool a = wordBreak(s, dict);
            bool a2 = wordBreak2(s, dict);
            bool a3 = wordBreak3(s, dict);
            vector<string> v = wordBreakII(s, dict);
            vector<string> v2 = wordBreakII2(s, dict);
            sort(v.begin(), v.end());
            sort(v2.begin(), v2.end());
            Logger() << "Break(\"" << s << "\") = " << a << ", " << a2 << ", "
                     << a3 << endl;
            Logger() << v << v2;
            if (ignoreE)
            {
                ASSERT1(a == a2);
                ASSERT1(a == a3);
            }
            else
            {
                ASSERT1(a == e);
                ASSERT1(a2 == e);
                ASSERT1(a3 == e);
            }
            ASSERT1(0 == Util::Compare(v, v2));
        };
        check("leetcode", {"leet", "code"}, true);
        check("applepenapple", {"apple", "pen"}, true);
        check("catsandog", {"cats", "dog", "sand", "and", "cat"}, false);
        check("catsanddog", {"cats", "dog", "sand", "and", "cat"}, true);
        const string alphabet = "abcdefg";
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            vector<string> dict = {};
            for (int j = 0; j < n; j++)
            {
                int m = Random::Int(10, 1);
                string s = Random::String<char>(m, alphabet);
                if (find(dict.begin(), dict.end(), s) == dict.end())
                    dict.push_back(s);
            }
            n = dict.size();
            string s1;
            string s2;
            for (int j = 0; j < 20; j++)
            {
                int k = rand() % n;
                s1.append(dict[k]);
                if (j % 2 == 0)
                    s2.append(dict[k]);
                else
                    s2.append(Random::String<char>(10, alphabet));
            }
            check(s1, dict, true);
            check(s2, dict, false, true);
        }
    });

    Add("149. Max Points on a Line", [&]() {
        auto check = [&](const vector<vector<int>> &points, int e) {
            Logger() << points;
            int c = maxPoints(points);
            vector<vector<int>> points2(points);
            int c2 = maxPoints2(points2);
            Logger() << "maxPoints: " << c << ", " << c2 << endl;
            ASSERT1(c == e);
            ASSERT1(c2 == e);
        };
        check({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}, 4);
        check({{1, 1}, {2, 2}, {3, 3}}, 3);
        check({{1, 1}, {2, 2}, {1, 1}, {2, 2}}, 4);
    });

    Add("150. Evaluate Reverse Polish Notation", [&]() {
        auto check = [&](const vector<string> &tokens, int expect) {
            Logger().WriteInformation("Expression:");
            Logger() << tokens;
            int r = evalRPN(tokens);
            int r2 = evalRPN2(tokens);
            Logger().WriteInformation("Result:     %d, %d\n", r, r2);
            ASSERT1(r == expect);
            ASSERT1(r2 == expect);
        };
        vector<string> t = {"2", "1", "+", "3", "*"};
        check(t, 9);
        t = {"4", "13", "5", "/", "+"};
        check(t, 6);
        t = {"-1", "-22", "+"};
        check(t, -23);
        t = {"1", "-22", "-"};
        check(t, 23);
        t = {"-2", "-3", "*"};
        check(t, 6);
        t = {"-22", "-2", "/"};
        check(t, 11);
    });

    Add("151. Reverse Words in a String", [&]() {
        auto check = [&](const string &s, const string &expect) {
            Logger().WriteInformation("\nInput:  \"%s\"\n", s.c_str());
            string r = reverseWords(s);
            string r2(s);
            reverseWords2(r2);
            Logger().WriteInformation("Output: \"%s\"\n", r.c_str());
            Logger().WriteInformation("Output: \"%s\"\n", r2.c_str());
            ASSERT1(r == expect);
            ASSERT1(r2 == expect);
        };
        check("a", "a");
        check("", "");
        check(" ", "");
        check("  ", "");
        check("ab", "ab");
        check("a b", "b a");
        check("a  b", "b a");
        check(" a b ", "b a");
        check("  a  b  ", "b a");
        check("  ab  cd  ", "cd ab");
        check("   This is a test!   ", "test! a is This");
    });

    Add("152. Maximum Product Subarray", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            int r = maxProduct(v);
            int r2 = maxProduct2(v);
            int r3 = maxProduct3(v);
            Logger() << "maxProduct: " << r << ", " << r2 << ", " << r3 << endl;
            ASSERT1(r == r2);
            ASSERT1(r == r3);
        };
        check({2});
        check({-2});
        check({1, 2});
        check({-1, 2});
        check({1, -2});
        check({1, 0, 2});
        check({2, 0, 1});
        check({-1, 0, 2});
        check({1, 0, -2});
        // check({4,  8, -3,  7,  -3, -2, 2, 4,  10, -7, -10, 3,  -2, -6, -8,
        //        10, 3, -10, 10, 3,  -2, 9, -7, -7, -6, -7,  1,  -7, -5, 5,
        //        9,  8, 0,   -5, 2,  5,  4, -9, -2, 1,  -5,  -3, -7, 1,  1});
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            vector<int> v = Random::Vector(n, 10, -10);
            check(v);
        }
    });

    Add("153. Find Minimum in Rotated Sorted Array", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            int e = *min_element(v.cbegin(), v.cend());
            int i = findMin(v);
            int i2 = findMin2(v);
            int i3 = findMin3(v);
            int i4 = findMin4(v);
            int i5 = findMin5(v);
            Logger() << "min: " << i << ", " << i2 << ", " << i3 << ", " << i4
                     << ", " << i5 << ", " << e << endl;
            ASSERT1(i == e);
            ASSERT1(i2 == e);
            ASSERT1(i3 == e);
            ASSERT1(i4 == e);
            ASSERT1(i5 == e);
        };
        check({4, 5, 6, 7, 0, 1, 2});
        check({1, 3});
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            int d = (i % 10) == 0 ? 0 : Random::Int(n);
            Util::RotateLeft(v, d);
            check(v);
        }
    });

    Add("154. Find Minimum in Rotated Sorted Array II", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            int e = *min_element(v.cbegin(), v.cend());
            int i = findMinII(v);
            int i2 = findMinII2(v);
            Logger() << "min: " << i << ", " << i2 << ", " << e << endl;
            ASSERT1(i == e);
            ASSERT1(i2 == e);
        };
        check({4, 5, 6, 7, 0, 1, 2});
        check({1, 3});
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, n >> 1);
            sort(v.begin(), v.end());
            int d = (i % 10) == 0 ? 0 : Random::Int(n);
            Util::RotateLeft(v, d);
            check(v);
        }
    });

    Add("162. Find Peak Element", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            vector<int> idx(6, -1);
            idx[0] = findPeakElement(v);
            idx[1] = findPeakElement2(v);
            idx[2] = findPeakElement3(v);
            idx[3] = findPeakElement4(v);
            idx[4] = findPeakElement5(v);
            idx[5] = findPeakElement6(v);
            Logger() << "Local peak:" << endl;
            for (int i : idx)
            {
                Logger() << "v[" << i << "] = " << v[i] << endl;
                if (i == 0 && v.size() > 1)
                    ASSERT1(v[0] >= v[1]);
                else if (i == (int)v.size() - 1 && v.size() > 1)
                    ASSERT1(v[i - 1] <= v[i]);
                else if (0 < i && i < (int)v.size() - 1)
                    ASSERT1(v[i - 1] <= v[i] && v[i] >= v[i + 1]);
            }
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, n);
            check(v);
        }
    });

    Add("164. Maximum Gap", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            int g = maximumGap(v);
            int g2 = maximumGap2(v);
            Logger() << "MaxGap: " << g << ", " << g2 << endl;
            ASSERT1(g == g2);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("165. Compare Version Numbers", [&]() {
        auto check = [&](const string &v1, const string &v2) {
            Logger() << "Compare(" << v1 << ", " << v2 << ")";
            int r = compareVersion(v1, v2);
            int r2 = compareVersion2(v1, v2);
            Logger() << " = " << r << ", " << r2 << endl;
            ASSERT1(r == r2);
        };
        auto version = [&]() -> string {
            int n = Random::Int(8, 1);
            string v;
            for (int i = 0; i < n; i++)
            {
                if (i > 0)
                    v.append(1, '.');
                v.append(Random::String<char>(Random::Int(6, 1), "0123456789"));
            }
            return v;
        };
        for (int i = 0; i < 100; i++)
        {
            string v1 = version();
            string v2 = version();
            check(v1, v2);
        }
    });

    Add("Excel", [&]() {
        auto check = [&](const string &input, unsigned long long expect) {
            Logger().WriteInformation("%s = ", input.c_str());
            unsigned long long r = titleToNumber(input);
            string e = convertToTitle(r);
            Logger().WriteInformation("%llu = %s\n", r, e.c_str());
            ASSERT1(r == expect);
            ASSERT1(e == input);
        };
        check("A", 1);
        check("B", 2);
        check("C", 3);
        check("X", 24);
        check("Y", 25);
        check("Z", 26);
        check("AA", 27);
        check("AB", 28);
        check("AY", 51);
        check("AZ", 52);
        check("BA", 53);
        check("BB", 54);
        check("BZ", 78);
        check("CA", 79);
        check("ZA", 677);
        check("ZY", 701);
        check("ZZ", 702);
        check("AAA", 703);
        check("AAB", 704);
        check("AAZ", 728);
        for (unsigned long long i = 1; i <= 1000; i++)
        {
            string code = convertToTitle(i);
            unsigned long long decode = titleToNumber(code);
            Logger().WriteInformation("%llu, %s, %llu\n", i, code.c_str(),
                                      decode);
            ASSERT1(decode == i);
        }
        for (unsigned int i = 0; i < 1000; i++)
        {
            unsigned long long n = rand();
            string code = convertToTitle(n);
            unsigned long long decode = titleToNumber(code);
            Logger().WriteInformation("%llu, %s, %llu\n", n, code.c_str(),
                                      decode);
            ASSERT1(decode == n);
        }
    });

    Add("174. Dungeon Game", [&]() {
        auto check = [&](const vector<vector<int>> &v, int e) {
            Logger() << v;
            int r = calculateMinimumHP(v);
            ASSERT1(r == e);
        };
        check({{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}}, 7);
    });

    Add("179. Largest Number", [&]() {
        auto check = [&](const vector<int> &nums, const string &expect,
                         bool ignoreE = false) {
            Logger() << nums;
            string actual = largestNumber(nums);
            string actual2 = largestNumber2(nums);
            Logger() << actual << ", " << actual2 << endl;
            if (ignoreE)
            {
                ASSERT1(actual.compare(actual2) == 0);
            }
            else
            {
                ASSERT1(actual.compare(expect) == 0);
                ASSERT1(actual2.compare(expect) == 0);
            }
        };
        check({1}, "1");
        check({3, 30, 34, 5, 9}, "9534330");
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(20, 1);
            vector<int> v = Random::Vector(n);
            check(v, "", true);
        }
    });

    Add("187. Repeated DNA Sequences", [&]() {
        auto check = [&](const string &s) {
            Logger() << s << endl;
            vector<string> r = findRepeatedDnaSequences(s);
            vector<string> r2 = findRepeatedDnaSequences2(s);
            sort(r.begin(), r.end());
            sort(r2.begin(), r2.end());
            Logger() << r << r2;
            ASSERT1(Util::Compare(r, r2) == 0);
        };
        check("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            string s;
            for (int j = 0; j < n; j++)
            {
                switch (rand() & 0x3)
                {
                case 0:
                    s.append(1, 'A');
                    break;
                case 1:
                    s.append(1, 'C');
                    break;
                case 2:
                    s.append(1, 'G');
                    break;
                case 3:
                    s.append(1, 'T');
                    break;
                }
                if ((rand() & 0x7) == 0)
                {
                    int i = s.size() > 10 ? s.size() - 10 : 0;
                    s.append(s.substr(i));
                }
            }
            check(s);
        }
    });

    Add("189. Rotate Array", [&]() {
        function<int(int, int)> gcd = [&](int a, int b) -> int {
            if (a < b)
                swap(a, b);
            while (b != 0)
            {
                int c = a % b;
                a = b;
                b = c;
            }
            return a;
        };
        auto check = [&](int length) {
            vector<int> v = Util::IncreasingVector(length);
            for (int i = 0; i <= 2 * length; i++)
            {
                Logger() << v;
                vector<int> v2(v);
                vector<int> v3(v);
                vector<int> v4(v);
                Logger() << "rotate to right by " << i << endl;
                rotate(v, i);
                rotate2(v2, i);
                rotate3(v3, i);
                Logger() << v << v2 << v3;
                ASSERT1(Util::Compare(v, v2) == 0);
                ASSERT1(Util::Compare(v, v3) == 0);
                if (i > 0 && gcd(length, i) == 1)
                {
                    rotate4(v4, i);
                    Logger() << v4;
                    ASSERT1(Util::Compare(v, v4) == 0);
                }
            }
        };
        for (int i = 1; i < 100; i++)
            check(i);
    });

    Add("198. House Robber", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            int m = rob(v);
            int m2 = rob2(v);
            Logger() << "rob: " << m << ", " << m2 << endl;
            ASSERT1(m == m2);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("199. Binary Tree Right Side View", [&]() {
        auto check = [&](int n) {
            TreeNode *t = RandomTree(n);
            Print(t);
            vector<int> v = rightSideView(t);
            vector<int> v2 = rightSideView2(t);
            Logger() << v << v2;
            DeleteTree(t);
            ASSERT1(Util::Compare(v, v2) == 0);
        };
        for (int i = 0; i < 100; i++)
            check(Random::Int(100, 1));
    });

}
#endif