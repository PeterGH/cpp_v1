#ifndef _LEETCODE1_H_
#define _LEETCODE1_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 100. Same Tree
        // Given two binary trees, write a function to check if they are the same or
        // not. Two binary trees are considered the same if they are structurally
        // identical and the nodes have the same value. Example 1:
        // Input:     1         1
        //           / \       / \
        //          2   3     2   3
        //         [1,2,3],   [1,2,3]
        // Output: true
        // Example 2:
        // Input:     1         1
        //           /           \
        //          2             2
        //         [1,2],     [1,null,2]
        // Output: false
        // Example 3:
        // Input:     1         1
        //           / \       / \
        //          2   1     1   2
        //         [1,2,1],   [1,1,2]
        // Output: false
        bool isSameTree(TreeNode *p, TreeNode *q)
        {
            function<bool(TreeNode *, TreeNode *)>
                same = [&](TreeNode *a, TreeNode *b) -> bool
            {
                if (a == nullptr && b == nullptr)
                    return true;
                if (a == nullptr || b == nullptr)
                    return false;
                if (a->val != b->val)
                    return false;
                return same(a->left, b->left) && same(a->right, b->right);
            };
            return same(p, q);
        }
        bool isSameTree2(TreeNode *p, TreeNode *q)
        {
            stack<TreeNode *> sp;
            stack<TreeNode *> sq;
            while (!sp.empty() || p != nullptr || !sq.empty() || q != nullptr)
            {
                if (sp.size() != sq.size())
                    return false;
                if ((p == nullptr) != (q == nullptr))
                    return false;
                if (p != nullptr)
                {
                    if (p->val != q->val)
                        return false;
                    sp.push(p);
                    p = p->left;
                    sq.push(q);
                    q = q->left;
                }
                else
                {
                    p = sp.top()->right;
                    sp.pop();
                    q = sq.top()->right;
                    sq.pop();
                }
            }
            return true;
        }
        bool isSameTree3(TreeNode *p, TreeNode *q)
        {
            function<vector<TreeNode *>(TreeNode *)> serialize =
                [&](TreeNode *n) -> vector<TreeNode *>
            {
                vector<TreeNode *> v;
                stack<TreeNode *> s;
                while (!s.empty() || n != nullptr)
                {
                    // Need to include nullptr to make sure
                    // the serialization is unique
                    v.push_back(n);
                    if (n != nullptr)
                    {
                        s.push(n);
                        n = n->left;
                    }
                    else
                    {
                        n = s.top()->right;
                        s.pop();
                    }
                }
                return v;
            };
            function<void(const vector<TreeNode *> &)> print =
                [&](const vector<TreeNode *> &v)
            {
                cout << "{";
                for (size_t i = 0; i < v.size(); i++)
                {
                    if (i > 0)
                        cout << ", ";
                    if (v[i] == nullptr)
                        cout << "null";
                    else
                        cout << v[i]->val;
                }
                cout << "}" << endl;
            };
            vector<TreeNode *> vp = serialize(p);
            vector<TreeNode *> vq = serialize(q);
            print(vp);
            print(vq);
            if (vp.size() != vq.size())
                return false;
            for (size_t i = 0; i < vp.size(); i++)
            {
                if ((vp[i] == nullptr) != (vq[i] == nullptr))
                    return false;
                if (vp[i] != nullptr && vp[i]->val != vq[i]->val)
                    return false;
            }
            return true;
        }

        // 101. Symmetric Tree
        // Given a binary tree, check whether it is a mirror of itself
        // (ie, symmetric around its center). For example, this binary
        // tree [1,2,2,3,4,4,3] is symmetric:
        //     1
        //    / \
        //   2   2
        //  / \ / \
        // 3  4 4  3
        // But the following [1,2,2,null,3,null,3] is not:
        //     1
        //    / \
        //   2   2
        //    \   \
        //    3    3
        // Note:
        // Bonus points if you could solve it both recursively and iteratively.
        bool isSymmetric(TreeNode *root)
        {
            function<bool(TreeNode *, TreeNode *)>
                same = [&](TreeNode *p, TreeNode *q) -> bool
            {
                if (p == nullptr && q == nullptr)
                    return true;
                if (p == nullptr || q == nullptr)
                    return false;
                if (p->val != q->val)
                    return false;
                return same(p->left, q->right) && same(p->right, q->left);
            };
            return same(root, root);
        }
        bool isSymmetric2(TreeNode *root)
        {
            deque<TreeNode *> deq;
            deq.push_front(root);
            deq.push_back(root);
            TreeNode *node1;
            TreeNode *node2;
            while (!deq.empty())
            {
                node1 = deq.front();
                deq.pop_front();
                node2 = deq.back();
                deq.pop_back();
                if (node1 == nullptr && node2 == nullptr)
                    continue;
                if (node1 == nullptr || node2 == nullptr)
                    return false;
                if (node1->val != node2->val)
                    return false;
                deq.push_front(node1->right);
                deq.push_front(node1->left);
                deq.push_back(node2->left);
                deq.push_back(node2->right);
            }
            return true;
        }
        bool isSymmetric3(TreeNode *root)
        {
            deque<TreeNode *> deq;
            TreeNode *p = root;
            TreeNode *q = root;
            while (!deq.empty() || p != nullptr || q != nullptr)
            {
                if ((p != nullptr) != (q != nullptr))
                    return false;
                if (p != nullptr && q != nullptr)
                {
                    if (p->val != q->val)
                        return false;
                    deq.push_front(p);
                    p = p->left;
                    deq.push_back(q);
                    q = q->right;
                }
                else
                {
                    p = deq.front()->right;
                    deq.pop_front();
                    q = deq.back()->left;
                    deq.pop_back();
                }
            }
            return true;
        }

        // 102. Binary Tree Level Order Traversal
        // Given a binary tree, return the level order traversal of its nodes' values.
        // (ie, from left to right, level by level).
        // For example: Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its level order traversal as:
        // [
        //   [3],
        //   [9,20],
        //   [15,7]
        // ]
        vector<vector<int>> levelOrder(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int l = 0;
            while (!q[0].empty() || !q[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!q[l].empty())
                {
                    v.push_back(q[l].front()->val);
                    if (q[l].front()->left != nullptr)
                        q[n].push(q[l].front()->left);
                    if (q[l].front()->right != nullptr)
                        q[n].push(q[l].front()->right);
                    q[l].pop();
                }
                result.push_back(v);
                l++;
            }
            return result;
        }
        vector<vector<int>> levelOrder2(TreeNode *root)
        {
            vector<vector<int>> result;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int l = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if ((int)result.size() <= l)
                        result.push_back({});
                    result[l].push_back(n->val);
                    s.push(make_pair(n, l));
                    n = n->left;
                    l++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    l = p.second + 1;
                }
            }
            return result;
        }
        vector<vector<int>> levelOrder3(TreeNode *root)
        {
            vector<vector<int>> result;
            function<void(TreeNode *, size_t)> visit = [&](TreeNode *n, size_t l)
            {
                if (n == nullptr)
                    return;
                if (result.size() < l)
                    result.push_back({});
                result[l - 1].push_back(n->val);
                visit(n->left, l + 1);
                visit(n->right, l + 1);
            };
            visit(root, 1);
            return result;
        }

        // 103. Binary Tree Zigzag Level Order Traversal
        // Given a binary tree, return the zigzag level order traversal of
        // its nodes' values. (ie, from left to right, then right to left for
        // the next level and alternate between).
        // For example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its zigzag level order traversal as:
        // [
        //   [3],
        //   [20,9],
        //   [15,7]
        // ]
        vector<vector<int>> zigzagLevelOrder(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            stack<TreeNode *> s[2];
            int l = 0;
            s[0].push(root);
            while (!s[0].empty() || !s[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!s[l].empty())
                {
                    v.push_back(s[l].top()->val);
                    if (l == 0) // left-to-right, children right-to-left
                    {
                        if (s[l].top()->left != nullptr)
                            s[n].push(s[l].top()->left);
                        if (s[l].top()->right != nullptr)
                            s[n].push(s[l].top()->right);
                    }
                    else // right-to-left, children left-to-right
                    {
                        if (s[l].top()->right != nullptr)
                            s[n].push(s[l].top()->right);
                        if (s[l].top()->left != nullptr)
                            s[n].push(s[l].top()->left);
                    }
                    s[l].pop();
                }
                result.push_back(v);
                l++;
            }
            return result;
        }
        vector<vector<int>> zigzagLevelOrder2(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            deque<TreeNode *> q[2];
            int level = 0;
            bool leftToRight = true;
            q[0].push_back(root);
            while (!q[0].empty() || !q[1].empty())
            {
                int currentLevel = level % 2;
                int nextLevel = (level + 1) % 2;
                vector<int> v;
                TreeNode *node;
                if (leftToRight)
                {
                    while (!q[currentLevel].empty())
                    {
                        node = q[currentLevel].front();
                        q[currentLevel].pop_front();
                        v.push_back(node->val);
                        if (node->left != nullptr)
                            q[nextLevel].push_back(node->left);
                        if (node->right != nullptr)
                            q[nextLevel].push_back(node->right);
                    }
                }
                else
                {
                    while (!q[currentLevel].empty())
                    {
                        node = q[currentLevel].back();
                        q[currentLevel].pop_back();
                        v.push_back(node->val);
                        if (node->right != nullptr)
                            q[nextLevel].push_front(node->right);
                        if (node->left != nullptr)
                            q[nextLevel].push_front(node->left);
                    }
                }
                result.push_back(v);
                level++;
                leftToRight = !leftToRight;
            }
            return result;
        }

        // 104. Maximum Depth of Binary Tree
        // Given a binary tree, find its maximum depth. The maximum depth is the
        // number of nodes along the longest path from the root node down to the
        // farthest leaf node. Note: A leaf is a node with no children.
        // Example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its depth = 3.
        int maxDepth(TreeNode *root)
        {
            stack<pair<TreeNode *, int>> s;
            int m = 0;
            TreeNode *n = root;
            int d = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    d++;
                    m = max(m, d);
                    s.push(make_pair(n, d));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    d = p.second;
                }
            }
            return m;
        }
        int maxDepth2(TreeNode *root)
        {
            function<int(TreeNode *)> depth = [&](TreeNode *node) -> int
            {
                if (node == nullptr)
                    return 0;
                if (node->left == nullptr && node->right == nullptr)
                    return 1;
                return 1 + max(depth(node->left), depth(node->right));
            };
            return depth(root);
        }
        int maxDepth3(TreeNode *root)
        {
            function<int(TreeNode *, int)> depth = [&](TreeNode *n, int d) -> int
            {
                if (n == nullptr)
                    return 0;
                if (n->left == nullptr && n->right == nullptr)
                    return d;
                return max(depth(n->left, d + 1), depth(n->right, d + 1));
            };
            return depth(root, 1);
        }
        // This is wrong
        int maxDepth4(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            stack<TreeNode *> path;
            path.push(root);
            TreeNode *node;
            int depth = 1;
            int maxDepth = 0;
            while (!path.empty())
            {
                if (depth > maxDepth)
                {
                    maxDepth = depth;
                }
                node = path.top();
                path.pop();
                if (node->right == nullptr && node->left == nullptr)
                {
                    depth--;
                }
                else
                {
                    depth++;
                    if (node->right != nullptr)
                        path.push(node->right);
                    if (node->left != nullptr)
                        path.push(node->left);
                }
            }
            return maxDepth;
        }

        // 105. Construct Binary Tree from Preorder and Inorder Traversal
        // Given preorder and inorder traversal of a tree, construct the binary tree.
        // Note: You may assume that duplicates do not exist in the tree.
        // For example, given
        // preorder = [3,9,20,15,7]
        // inorder = [9,3,15,20,7]
        // Return the following binary tree:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        TreeNode *buildTree(const vector<int> &preorder, const vector<int> &inorder)
        {
            map<int, int> m;
            for (int i = 0; i < (int)inorder.size(); i++)
                m[inorder[i]] = i;
            function<TreeNode *(int, int, int, int)>
                build = [&](int p1, int p2, int i1, int i2) -> TreeNode *
            {
                if (p2 - p1 != i2 - i1)
                    return nullptr;
                if (p1 > p2 || i1 > i2)
                    return nullptr;
                int i = m[preorder[p1]];
                if (i < i1)
                    return nullptr;
                TreeNode *n = new TreeNode(preorder[p1]);
                n->left = build(p1 + 1, p1 + i - i1, i1, i - 1);
                n->right = build(p1 + i - i1 + 1, p2, i + 1, i2);
                return n;
            };
            return build(0, preorder.size() - 1, 0, inorder.size() - 1);
        }
        TreeNode *buildTree2(const vector<int> &preorder, const vector<int> &inorder)
        {
            if (preorder.size() != inorder.size() || preorder.empty())
                return nullptr;
            stack<TreeNode *> path;
            int i = 0; // index current element in preOrder
            int j = 0; // index current element in inOrder
            int f = 0; // flag to insert to left or right
            // Root
            TreeNode *node = new TreeNode(preorder[i]);
            path.push(node);
            // Current insertion point
            TreeNode *t = node;
            i++;
            while (i < (int)preorder.size())
            {
                if (!path.empty() && path.top()->val == inorder[j])
                {
                    // Done with a left substree, start to insert the right subtree
                    t = path.top();
                    path.pop();
                    f = 1;
                    j++;
                }
                else
                {
                    if (f == 0)
                    {
                        t->left = new TreeNode(preorder[i]);
                        t = t->left;
                    }
                    else
                    {
                        f = 0;
                        t->right = new TreeNode(preorder[i]);
                        t = t->right;
                    }
                    path.push(t);
                    i++;
                }
            }
            return node;
        }
        TreeNode *buildTree3(const vector<int> &preorder, const vector<int> &inorder)
        {
            if (preorder.size() != inorder.size() || preorder.empty())
                return nullptr;
            int p = 0;
            int i = 0;
            function<TreeNode *(int)> build = [&](int val) -> TreeNode *
            {
                if (i >= (int)inorder.size() || inorder[i] == val)
                    return nullptr;
                TreeNode *n = new TreeNode(preorder[p]);
                p++;
                n->left = build(n->val);
                i++;
                n->right = build(val);
                return n;
            };
            return build(INT_MIN);
        }

        // 106. Construct Binary Tree from Inorder and Postorder Traversal
        // Given inorder and postorder traversal of a tree, construct the binary tree.
        // Note: You may assume that duplicates do not exist in the tree.
        // For example, given
        // inorder = [9,3,15,20,7]
        // postorder = [9,15,7,20,3]
        // Return the following binary tree:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        TreeNode *buildTreeInOrderPostOrder(const vector<int> &inorder,
                                            const vector<int> &postorder)
        {
            map<int, int> m;
            for (int i = 0; i < (int)inorder.size(); i++)
                m[inorder[i]] = i;
            function<TreeNode *(int, int, int, int)>
                build = [&](int i1, int i2, int p1, int p2) -> TreeNode *
            {
                if (i2 - i1 != p2 - p1 || i1 > i2 || p1 > p2)
                    return nullptr;
                TreeNode *n = new TreeNode(postorder[p2]);
                int i = m[postorder[p2]];
                n->left = build(i1, i - 1, p1, p1 + i - 1 - i1);
                n->right = build(i + 1, i2, p1 + i - i1, p2 - 1);
                return n;
            };
            return build(0, (int)inorder.size() - 1, 0, (int)postorder.size() - 1);
        }
        TreeNode *buildTreeInOrderPostOrder2(const vector<int> &inorder,
                                             const vector<int> &postorder)
        {
            if (inorder.size() != postorder.size() || inorder.empty())
                return nullptr;
            stack<TreeNode *> path;
            int i = (int)postorder.size() - 1; // index current element in postOrder
            int j = (int)inorder.size() - 1;   // index current element in inOrder
            int f = 0;                         // flag to insert to left or right
            // Root
            TreeNode *node = new TreeNode(postorder[i]);
            path.push(node);
            // Current insertion point
            TreeNode *t = node;
            i--;
            // Post {{l_0}, {{l_1}, {{l_2}, {r_2}, n_2}, n_1}, n_0}
            // In   {{l_0}, n_0, {{l_1}, n_1, {{l_2}, n_2, {r_2}}}}
            while (i >= 0)
            {
                if (!path.empty() && path.top()->val == inorder[j])
                {
                    // Done with a right subtree, start to insert the left subtree
                    // Pop the current top so that we can return to its parent after
                    // done with its left subtree
                    t = path.top();
                    path.pop();
                    f = 1;
                    j--;
                }
                else
                {
                    if (f == 0)
                    {
                        t->right = new TreeNode(postorder[i]);
                        t = t->right;
                    }
                    else
                    {
                        f = 0;
                        t->left = new TreeNode(postorder[i]);
                        t = t->left;
                    }
                    path.push(t);
                    i--;
                }
            }
            return node;
        }
        TreeNode *buildTreeInOrderPostOrder3(const vector<int> &inorder,
                                             const vector<int> &postorder)
        {
            if (inorder.size() != postorder.size() || inorder.empty())
                return nullptr;
            int p = (int)postorder.size() - 1;
            int i = (int)inorder.size() - 1;
            function<TreeNode *(int)> build = [&](int val) -> TreeNode *
            {
                if (i == -1 || inorder[i] == val)
                    return nullptr;
                TreeNode *n = new TreeNode(postorder[p]);
                p--;
                n->right = build(n->val);
                i--;
                n->left = build(val);
                return n;
            };
            return build(INT_MIN);
        }

        // 107. Binary Tree Level Order Traversal II
        // Given a binary tree, return the bottom-up level order traversal of its
        // nodes' values. (ie, from left to right, level by level from leaf to root).
        // For example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its bottom-up level order traversal as:
        // [
        //   [15,7],
        //   [9,20],
        //   [3]
        // ]
        vector<vector<int>> levelOrderBottom(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int l = 0;
            while (!q[0].empty() || !q[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!q[l].empty())
                {
                    v.push_back(q[l].front()->val);
                    if (q[l].front()->left != nullptr)
                        q[n].push(q[l].front()->left);
                    if (q[l].front()->right != nullptr)
                        q[n].push(q[l].front()->right);
                    q[l].pop();
                }
                result.insert(result.begin(), v);
                l++;
            }
            return result;
        }
        vector<vector<int>> levelOrderBottom2(TreeNode *root)
        {
            vector<vector<int>> result;
            stack<pair<TreeNode *, int>> s;
            int l = 0;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if ((int)result.size() <= l)
                    {
                        // Cannot use {} because it is seen as an empty
                        // initializer list, so insert() will not insert
                        // anything.
                        // result.insert(result.begin(), {});
                        result.insert(result.begin(), vector<int>());
                    }
                    result[(int)result.size() - l - 1].push_back(n->val);
                    s.push(make_pair(n, l));
                    n = n->left;
                    l++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    l = p.second + 1;
                }
            }
            return result;
        }

        // 108. Convert Sorted Array to Binary Search Tree
        // Given an array where elements are sorted in ascending order, convert it
        // to a height balanced BST. For this problem, a height-balanced binary tree
        // is defined as a binary tree in which the depth of the two subtrees of every
        // node never differ by more than 1.
        // Example:
        // Given the sorted array: [-10,-3,0,5,9],
        // One possible answer is: [0,-3,9,-10,null,5], which represents the following
        // height balanced BST:
        //       0
        //      / \
        //    -3   9
        //    /   /
        //  -10  5
        TreeNode *sortedArrayToBST(const vector<int> &nums)
        {
            function<TreeNode *(int, int)> bst = [&](int i, int j) -> TreeNode *
            {
                if (i > j || i < 0 || j >= (int)nums.size())
                    return nullptr;
                int k = i + ((j - i) >> 1);
                TreeNode *n = new TreeNode(nums[k]);
                n->left = bst(i, k - 1);
                n->right = bst(k + 1, j);
                return n;
            };
            return bst(0, (int)nums.size() - 1);
        }
        TreeNode *sortedArrayToBST2(const vector<int> &nums)
        {
            if (nums.empty())
                return nullptr;
            function<int(int, int)> middle = [&](int i, int j) -> int
            {
                return i + ((j - i) >> 1);
            };
            int i = 0;
            int j = (int)nums.size() - 1;
            int k = middle(i, j);
            stack<pair<TreeNode *, pair<int, int>>> s;
            TreeNode *root = nullptr;
            int last = -1;
            int f = 0;
            while (!s.empty() || i <= j)
            {
                if (i <= j)
                {
                    TreeNode *n = new TreeNode(nums[k]);
                    if (root == nullptr)
                        root = n;
                    if (!s.empty())
                    {
                        if (f == 0)
                            s.top().first->left = n;
                        else
                        {
                            s.top().first->right = n;
                            f = 0;
                        }
                    }
                    // Record the right range and then move to the left
                    s.push(make_pair(n, make_pair(k, j)));
                    j = k - 1;
                    k = middle(i, j);
                }
                else
                {
                    pair<TreeNode *, pair<int, int>> p = s.top();
                    int ti = p.second.first + 1;
                    int tj = p.second.second;
                    int tk = middle(ti, tj);
                    if (ti <= tj && last != tk)
                    {
                        f = 1;
                        i = ti;
                        j = tj;
                        k = tk;
                    }
                    else
                    {
                        last = ti - 1; // == p.second.first
                        s.pop();
                    }
                }
            }
            return root;
        }

        // 109. Convert Sorted List to Binary Search Tree
        // Given a singly linked list where elements are sorted in ascending order,
        // convert it to a height balanced BST. For this problem, a height-balanced
        // binary tree is defined as a binary tree in which the depth of the two
        // subtrees of every node never differ by more than 1.
        // Example:
        // Given the sorted linked list: [-10,-3,0,5,9],
        // One possible answer is: [0,-3,9,-10,null,5], which represents the following
        // height balanced BST:
        //       0
        //      / \
        //    -3   9
        //    /   /
        //  -10  5
        TreeNode *sortedListToBST(ListNode *head)
        {
            function<TreeNode *(ListNode *, ListNode *)> bst =
                [&](ListNode *b, ListNode *e) -> TreeNode *
            {
                if (b == e)
                    return nullptr;
                ListNode *p = b; // 1st
                ListNode *q = b; // 1st
                while (q->next != e && q->next->next != e)
                {
                    p = p->next;       // (1 + k)-th
                    q = q->next->next; // (1 + 2k)-th
                }
                // p is the median for odd length
                // or the lower median for even length
                TreeNode *n = new TreeNode(p->val);
                n->left = bst(b, p);
                n->right = bst(p->next, e);
                return n;
            };
            return bst(head, nullptr);
        }
        TreeNode *sortedListToBST2(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            if (head->next == nullptr)
                return new TreeNode(head->val);
            function<TreeNode *(ListNode *, ListNode *)> build =
                [&](ListNode *b, ListNode *e) -> TreeNode *
            {
                if (b == nullptr || e == nullptr)
                    return nullptr;
                TreeNode *node;
                if (b == e)
                {
                    node = new TreeNode(b->val);
                }
                else if (b->next == e)
                {
                    node = new TreeNode(b->val);
                    node->right = new TreeNode(e->val);
                }
                else
                {
                    ListNode *p = b;             // 1st
                    ListNode *q = p->next->next; // 3rd
                    while (q != e && q->next != e)
                    {
                        p = p->next; // (1 + k)-th
                        q = q->next;
                        q = q->next; // (3 + 2k)-th
                    }
                    // now p->next is the median for odd length
                    // or the lower-median for even length
                    node = new TreeNode(p->next->val);
                    node->left = build(b, p);
                    node->right = build(p->next->next, e);
                }
                return node;
            };
            ListNode *p = head;    // 1st
            ListNode *q = p->next; // 2nd
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next; // (1 + k)-th
                q = q->next;
                q = q->next; // (2 + 2k)-th
            }
            // p->next is median for odd length
            // or p is the lower median for even length
            TreeNode *node = new TreeNode(p->next->val);
            node->left = build(head, p);
            node->right = build(p->next->next, q->next == nullptr ? q : q->next);
            return node;
        }
        TreeNode *sortedListToBST3(ListNode *head)
        {
            ListNode *p = head;
            int c = 0;
            while (p != nullptr)
            {
                c++;
                p = p->next;
            }
            function<TreeNode *(ListNode *&, int, int)>
                bst = [&](ListNode *&h, int b, int e) -> TreeNode *
            {
                if (b > e)
                    return nullptr;
                int m = b + ((e - b) >> 1);
                TreeNode *left = bst(h, b, m - 1);
                TreeNode *n = new TreeNode(h->val);
                n->left = left;
                h = h->next;
                n->right = bst(h, m + 1, e);
                return n;
            };
            ListNode *h = head;
            return bst(h, 0, c - 1);
        }

        // 144. Binary Tree Preorder Traversal
        // Given a binary tree, return the preorder traversal of its nodes' values.
        // Example:
        // Input: [1,null,2,3]
        //    1
        //     \
        //      2
        //     /
        //    3
        // Output: [1,2,3]
        // Follow up: Recursive solution is trivial, could you do it iteratively?
        vector<int> preorderTraversal(TreeNode *root)
        {
            vector<int> v;
            // Simulate the stack in recursive traversal
            stack<TreeNode *> s;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    v.push_back(n->val);
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    n = s.top()->right;
                    // Pop the top. Do not want to come back to it
                    // after finishing its right tree.
                    s.pop();
                }
            }
            return v;
        }
        vector<int> preorderTraversal2(TreeNode *root)
        {
            vector<int> v;
            if (root == nullptr)
                return v;
            stack<TreeNode *> s;
            s.push(root);
            TreeNode *n;
            while (!s.empty())
            {
                n = s.top();
                s.pop();
                v.push_back(n->val);
                if (n->right != nullptr)
                    s.push(n->right);
                if (n->left != nullptr)
                    s.push(n->left);
            }
            return v;
        }
        vector<int> preorderTraversal3(TreeNode *root)
        {
            vector<int> v;
            if (root == nullptr)
                return v;
            // Track the path to the current node being visited
            stack<TreeNode *> path;
            path.push(root);
            TreeNode *prev = root;
            while (!path.empty())
            {
                TreeNode *n = path.top();
                if (prev == n->right)
                {
                    path.pop();
                }
                else if (n->left != nullptr && n->left != prev)
                {
                    v.push_back(n->val);
                    path.push(n->left);
                }
                else
                {
                    if (n->left == nullptr)
                        v.push_back(n->val);
                    if (n->right == nullptr)
                        path.pop();
                    else
                        path.push(n->right);
                }
                prev = n;
            }
            return v;
        }
        vector<int> preorderTraversal4(TreeNode *root)
        {
            vector<int> v;
            function<void(TreeNode *)> visit = [&](TreeNode *n)
            {
                if (n == nullptr)
                    return;
                v.push_back(n->val);
                visit(n->left);
                visit(n->right);
            };
            visit(root);
            return v;
        }

        // 145. Binary Tree Postorder Traversal
        // Given a binary tree, return the postorder traversal of its nodes' values.
        // Example:
        // Input: [1,null,2,3]
        //    1
        //     \
        //      2
        //     /
        //    3
        // Output: [3,2,1]
        // Follow up: Recursive solution is trivial, could you do it iteratively?
        vector<int> postorderTraversal(TreeNode *root)
        {
            vector<int> v;
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
                        v.push_back(t->val);
                        last = t;
                        s.pop();
                    }
                }
            }
            return v;
        }
        vector<int> postorderTraversal2(TreeNode *root)
        {
            vector<int> results;
            if (root == nullptr)
                return results;
            stack<TreeNode *> s;
            s.push(root);
            TreeNode *last = nullptr;
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if (n->right != nullptr && n->right == last)
                {
                    results.push_back(n->val);
                    s.pop();
                }
                else if (n->left != nullptr && n->left != last)
                {
                    s.push(n->left);
                }
                else
                {
                    if (n->right == nullptr)
                    {
                        results.push_back(n->val);
                        s.pop();
                    }
                    else
                    {
                        s.push(n->right);
                    }
                }
                last = n;
            }
            return results;
        }
        vector<int> postorderTraversal3(TreeNode *root)
        {
            vector<int> results;
            if (root == nullptr)
                return results;
            stack<TreeNode *> s;
            s.push(root);
            set<TreeNode *> visited;
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if ((n->right == nullptr || visited.find(n->right) != visited.end()) &&
                    (n->left == nullptr || visited.find(n->left) != visited.end()))
                {
                    results.push_back(n->val);
                    visited.insert(n);
                    s.pop();
                }
                else
                {
                    if (n->right != nullptr)
                        s.push(n->right);
                    if (n->left != nullptr)
                        s.push(n->left);
                }
            }
            return results;
        }
        vector<int> postorderTraversal4(TreeNode *root)
        {
            vector<int> v;
            function<void(TreeNode *)> trav = [&](TreeNode *n)
            {
                if (n == nullptr)
                    return;
                trav(n->left);
                trav(n->right);
                v.push_back(n->val);
            };
            trav(root);
            return v;
        }

    }
}

#endif