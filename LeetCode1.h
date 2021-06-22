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

        // 110. Balanced Binary Tree
        // Given a binary tree, determine if it is height-balanced.
        // For this problem, a height-balanced binary tree is defined as:
        // a binary tree in which the left and right subtrees of every node differ
        // in height by no more than 1.
        // Example 1:
        // Given the following tree [3,9,20,null,null,15,7]:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // Return true.
        // Example 2:
        // Given the following tree [1,2,2,3,3,null,null,4,4]:
        //        1
        //       / \
        //      2   2
        //     / \
        //    3   3
        //   / \
        //  4   4
        // Return false.
        bool isBalanced(TreeNode *root)
        {
            function<bool(TreeNode *, int &)>
                balanced = [&](TreeNode *n, int &h) -> bool
            {
                if (n == nullptr)
                {
                    h = 0;
                    return true;
                }
                int hl = 0;
                if (!balanced(n->left, hl))
                    return false;
                int hr = 0;
                if (!balanced(n->right, hr))
                    return false;
                h = 1 + max(hl, hr);
                return abs(hl - hr) <= 1;
            };
            int h = 0;
            return balanced(root, h);
        }
        bool isBalanced2(TreeNode *root)
        {
            stack<TreeNode *> s;
            map<TreeNode *, int> m;
            TreeNode *node = root;
            TreeNode *last = nullptr;
            while (!s.empty() || node != nullptr)
            {
                if (node != nullptr)
                {
                    s.push(node);
                    m[node] = 0;
                    node = node->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->left != nullptr && t->left == last)
                        m[t] = m[t->left]; // Record the left height temporarily
                    if (t->right != nullptr && t->right != last)
                    {
                        node = t->right;
                    }
                    else
                    {
                        s.pop();
                        int rightHeight = t->right == nullptr ? 0 : m[t->right];
                        if (abs(m[t] - rightHeight) > 1)
                            return false;
                        m[t] = 1 + max(m[t], rightHeight); // Record the real height
                    }
                    last = t;
                }
            }
            return true;
        }

        // 111. Minimum Depth of Binary Tree
        // Given a binary tree, find its minimum depth.
        // The minimum depth is the number of nodes along the shortest path
        // from the root node down to the nearest leaf node.
        // Note: A leaf is a node with no children.
        // Example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its minimum depth = 2.
        int minDepth(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            int m = INT_MAX;
            function<void(TreeNode *, int)> depth = [&](TreeNode *n, int d)
            {
                if (n == nullptr)
                    return;
                d++;
                if (n->left == nullptr && n->right == nullptr)
                    m = min(m, d);
                if (n->left != nullptr)
                    depth(n->left, d);
                if (n->right != nullptr)
                    depth(n->right, d);
            };
            depth(root, 0);
            return m;
        }
        int minDepth2(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int m = INT_MAX;
            int d = 1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (n->left == nullptr && n->right == nullptr)
                        m = min(m, d);
                    s.push(make_pair(n, d));
                    n = n->left;
                    d++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    d = p.second + 1;
                }
            }
            return m;
        }
        int minDepth3(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            queue<TreeNode *> q;
            q.push(root);
            int d = 1;
            queue<TreeNode *> t;
            TreeNode *n;
            while (!q.empty())
            {
                n = q.front();
                q.pop();
                if (n->left == nullptr && n->right == nullptr)
                    break;
                if (n->left != nullptr)
                    t.push(n->left);
                if (n->right != nullptr)
                    t.push(n->right);
                if (q.empty())
                {
                    swap(q, t);
                    d++;
                }
            }
            return d;
        }
        int minDepth4(TreeNode *root)
        {
            function<int(TreeNode *, int)>
                solve = [&](TreeNode *node, int depth) -> int
            {
                if (node == nullptr)
                    return depth;
                depth++;
                if (node->left == nullptr)
                    return solve(node->right, depth);
                else if (node->right == nullptr)
                    return solve(node->left, depth);
                else
                    return min(solve(node->left, depth), solve(node->right, depth));
            };
            return solve(root, 0);
        }

        // 112. Path Sum
        // Given a binary tree and a sum, determine if the tree has a root-to-leaf
        // path such that adding up all the values along the path equals the given sum.
        // Note: A leaf is a node with no children. Example:
        // Given the below binary tree and sum = 22,
        //       5
        //      / \
        //     4   8
        //    /   / \
        //   11  13  4
        //  /  \      \
        // 7    2      1
        // return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
        bool hasPathSum(TreeNode *root, int sum)
        {
            function<bool(TreeNode *, int)> solve = [&](TreeNode *n, int s) -> bool
            {
                if (n == nullptr)
                    return false;
                s = s + n->val;
                if (s == sum && n->left == nullptr && n->right == nullptr)
                    return true;
                return solve(n->left, s) || solve(n->right, s);
            };
            return solve(root, 0);
        }
        bool hasPathSum2(TreeNode *root, int sum)
        {
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int t = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    t = t + n->val;
                    if (n->left == nullptr && n->right == nullptr && t == sum)
                        return true;
                    s.push(make_pair(n, t));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    t = p.second;
                }
            }
            return false;
        }
        int pickPathSum(TreeNode *root)
        {
            int sum = 0;
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s)
            {
                if (n == nullptr)
                    return;
                s += n->val;
                if (n->left == nullptr && n->right == nullptr)
                {
                    sum = s;
                    if (rand() < (RAND_MAX >> 1))
                        return;
                }
                solve(n->left, s);
                solve(n->right, s);
            };
            solve(root, 0);
            return sum;
        }

        // 113. Path Sum II
        // Given a binary tree and a sum, find all root-to-leaf paths where each
        // path's sum equals the given sum. Note: A leaf is a node with no children.
        // Example: Given the below binary tree and sum = 22,
        //       5
        //      / \
        //     4   8
        //    /   / \
        //   11  13  4
        //  /  \    / \
        // 7    2  5   1
        // Return:
        // [
        //    [5,4,11,2],
        //    [5,8,4,5]
        // ]
        vector<vector<int>> pathSum(TreeNode *root, int sum)
        {
            vector<vector<int>> result;
            function<void(TreeNode *, int, vector<int> &)> solve =
                [&](TreeNode *n, int s, vector<int> &v)
            {
                if (n == nullptr)
                    return;
                s += n->val;
                v.push_back(n->val);
                if (s == sum && n->left == nullptr && n->right == nullptr)
                    result.push_back(v);
                else
                {
                    if (n->left != nullptr)
                        solve(n->left, s, v);
                    if (n->right != nullptr)
                        solve(n->right, s, v);
                }
                v.pop_back();
            };
            vector<int> w;
            solve(root, 0, w);
            return result;
        }
        vector<vector<int>> pathSum2(TreeNode *root, int sum)
        {
            vector<vector<int>> result;
            vector<int> v;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int t = 0;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    t += n->val;
                    v.push_back(n->val);
                    if (n->left == nullptr && n->right == nullptr && t == sum)
                        result.push_back(v);
                    s.push(make_pair(n, t));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    if (p.first->right != nullptr && last != p.first->right)
                    {
                        n = p.first->right;
                        t = p.second;
                    }
                    else
                    {
                        last = p.first;
                        s.pop();
                        v.pop_back();
                    }
                }
            }
            return result;
        }
        void setPathSum(TreeNode *root, int sum)
        {
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s)
            {
                if (n == nullptr)
                    return;
                if (n->left == nullptr && n->right == nullptr)
                {
                    if (rand() < (RAND_MAX >> 1))
                    {
                        n->val = sum - s;
                        return;
                    }
                }
                s += n->val;
                solve(n->left, s);
                solve(n->right, s);
            };
            solve(root, 0);
        }

        // 114. Flatten Binary Tree to Linked List
        // Given a binary tree, flatten it to a linked list in-place.
        // For example, given the following tree:
        //     1
        //    / \
        //   2   5
        //  / \   \
        // 3   4   6
        // The flattened tree should look like:
        // 1
        //  \
        //   2
        //    \
        //     3
        //      \
        //       4
        //        \
        //         5
        //          \
        //           6
        void flatten(TreeNode *root)
        {
            function<void(TreeNode *, TreeNode *&, TreeNode *&)> flat =
                [&](TreeNode *n, TreeNode *&l, TreeNode *&r)
            {
                if (n == nullptr)
                {
                    l = nullptr;
                    r = nullptr;
                    return;
                }
                TreeNode *ll = nullptr;
                TreeNode *lr = nullptr;
                flat(n->left, ll, lr);
                TreeNode *rl = nullptr;
                TreeNode *rr = nullptr;
                flat(n->right, rl, rr);
                if (ll == nullptr)
                {
                    l = n;
                    r = rl == nullptr ? n : rr;
                    return;
                }
                lr->right = rl;
                n->right = ll;
                n->left = nullptr;
                l = n;
                r = rl == nullptr ? lr : rr;
            };
            TreeNode *l = nullptr;
            TreeNode *r = nullptr;
            flat(root, l, r);
        }
        void flatten2(TreeNode *root)
        {
            function<TreeNode *(TreeNode *)> solve =
                [&](TreeNode *node) -> TreeNode *
            {
                if (node == nullptr)
                    return nullptr;
                if (node->left == nullptr && node->right == nullptr)
                {
                    return node;
                }
                TreeNode *leftTail = solve(node->left);
                TreeNode *rightTail = solve(node->right);
                if (leftTail != nullptr)
                {
                    leftTail->right = node->right;
                    node->right = node->left;
                    node->left = nullptr;
                }
                return rightTail == nullptr ? leftTail : rightTail;
            };
            solve(root);
        }
        void flatten3(TreeNode *root)
        {
            stack<TreeNode *> s;
            map<TreeNode *, TreeNode *> m; // map a node to the tail of list at node
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    m[n] = n;
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
                        TreeNode *l = t->left;
                        TreeNode *r = t->right;
                        if (l != nullptr)
                        {
                            m[l]->right = r;
                            t->right = l;
                            t->left = nullptr;
                        }
                        m[t] = (r == nullptr ? (l == nullptr ? m[t] : m[l]) : m[r]);
                        s.pop();
                    }
                    last = t;
                }
            }
        }

        // 115. Distinct Subsequences
        // Given a string S and a string T, count the number of distinct subsequences
        // of S which equals T. A subsequence of a string is a new string which is
        // formed from the original string by deleting some (can be none) of the
        // characters without disturbing the relative positions of the remaining
        // characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
        // Example 1:
        // Input: S = "rabbbit", T = "rabbit"
        // Output: 3
        // Explanation: As shown below, there are 3 ways you can generate "rabbit" from
        // S. (The caret symbol ^ means the chosen letters)
        // rabbbit
        // ^^^^ ^^
        // rabbbit
        // ^^ ^^^^
        // rabbbit
        // ^^^ ^^^
        // Example 2:
        // Input: S = "babgbag", T = "bag"
        // Output: 5
        // Explanation: As shown below, there are 5 ways you can generate "bag" from S.
        // (The caret symbol ^ means the chosen letters)
        // babgbag
        // ^^ ^
        // babgbag
        // ^^    ^
        // babgbag
        // ^    ^^
        // babgbag
        //   ^  ^^
        // babgbag
        //     ^^^
        int numDistinct(const string &s, const string &t)
        {
            map<pair<size_t, size_t>, int> m;
            function<int(size_t, size_t)> solve = [&](size_t i, size_t j) -> int
            {
                pair<size_t, size_t> p = make_pair(i, j);
                if (m.find(p) != m.end())
                    return m[p];
                if (j == t.size())
                {
                    m[p] = 1;
                    return m[p];
                }
                while (i < s.size() && s[i] != t[j])
                    i++;
                if (i == s.size())
                    m[p] = 0;
                else
                    m[p] = solve(i + 1, j + 1) + solve(i + 1, j);
                return m[p];
            };
            return solve(0, 0);
        }
        // c(i, j) is the count for s[0..i] and t[0..j]
        // c(i, j) = 0                              if i < j
        //         = c(i - 1, j)                    if j == 0 && s[i] != t[j]
        //         = c(i - 1, j) + 1                if j == 0 && s[i] == t[j]
        //         = c(i - 1, j)                    if s[i] != t[j]
        //         = c(i - 1, j - 1) + c(i - 1, j)  if s[i] == t[j]
        //   t     0        1    ......     n-2        n-1
        // s 0 c(0,0)   c(0,1)   ...... c(0,n-2)   c(0,n-1)
        //   1 c(1,0)   c(1,1)   ...... c(1,n-2)   c(1,n-1)
        //   2 c(2,0)   c(2,1)   ...... c(2,n-2)   c(2,n-1)
        //     ......
        // n-2 c(n-2,0) c(n-2,1) ...... c(n-2,n-2) c(n-2,n-1)
        // n-1 c(n-1,0) c(n-1,1) ...... c(n-1,n-2) c(n-1,n-1)
        //     ......
        // m-n c(m-n,0) c(m-n,1) ...... c(m-n,n-2) c(m-n,n-1)
        //     ......
        // m-2 c(m-2,0) c(m-2,1) ...... c(m-2,n-2) c(m-2,n-1)
        // m-1 c(m-1,0) c(m-1,1) ...... c(m-1,n-2) c(m-1,n-1)
        int numDistinct2(const string &s, const string &t)
        {
            if (s.size() < t.size())
                return 0;
            vector<unsigned long long> c(t.size(), 0);
            c[0] = s[0] == t[0] ? 1 : 0;
            for (int i = 1; i < (int)s.size(); i++)
            {
                for (int j = t.size() - 1; j > 0; j--)
                {
                    if (s[i] == t[j])
                        c[j] += c[j - 1];
                }
                if (s[i] == t[0])
                    c[0]++;
            }
            return c[t.size() - 1];
        }

        // 116. Populating Next Right Pointers in Each Node
        // You are given a perfect binary tree where all leaves are on the same level,
        // and every parent has two children. The binary tree has the following
        // definition: struct Node {
        //   int val;
        //   Node *left;
        //   Node *right;
        //   Node *next;
        // }
        // Populate each next pointer to point to its next right node. If there is no
        // next right node, the next pointer should be set to NULL. Initially, all next
        // pointers are set to NULL. Follow up: You may only use constant extra space.
        // Recursive approach is fine, you may assume implicit stack space does not
        // count as extra space for this problem. Example 1: Input: root =
        // [1,2,3,4,5,6,7] Output: [1,#,2,3,#,4,5,6,7,#] Explanation: Given the above
        // perfect binary tree (Figure A), your function should populate each next
        // pointer to point to its next right node, just like in Figure B. The
        // serialized output is in level order as connected by the next pointers, with
        // '#' signifying the end of each level. Constraints: The number of nodes in the
        // given tree is less than 4096. -1000 <= node.val <= 1000
        NodeWithNextLink *connect(NodeWithNextLink *root)
        {
            NodeWithNextLink *left = root;
            while (left != nullptr && left->left != nullptr)
            {
                NodeWithNextLink *n = left;
                while (n != nullptr)
                {
                    n->left->next = n->right;
                    if (n->next != nullptr)
                        n->right->next = n->next->left;
                    n = n->next;
                }
                left = left->left;
            }
            return root;
        }
        NodeWithNextLink *connect2(NodeWithNextLink *root)
        {
            NodeWithNextLink *leftMost = root;
            while (leftMost != nullptr && leftMost->left != nullptr)
            {
                NodeWithNextLink *node = leftMost;
                leftMost = leftMost->left;
                NodeWithNextLink *left = nullptr;
                while (node != nullptr)
                {
                    if (left != nullptr)
                        left->next = node->left;
                    node->left->next = node->right;
                    left = node->right;
                    node = node->next;
                }
            }
            return root;
        }
        NodeWithNextLink *connect3(NodeWithNextLink *root)
        {
            if (root != nullptr && root->left != nullptr && root->right != nullptr)
            {
                root->left->next = root->right;
                if (root->next != nullptr)
                    root->right->next = root->next->left;
                connect3(root->left);
                connect3(root->right);
            }
            return root;
        }

        // 117. Populating Next Right Pointers in Each Node II
        // Given a binary tree
        // struct Node {
        //   int val;
        //   Node *left;
        //   Node *right;
        //   Node *next;
        // }
        // Populate each next pointer to point to its next right node. If there is no
        // next right node, the next pointer should be set to NULL. Initially, all next
        // pointers are set to NULL. Follow up: You may only use constant extra space.
        // Recursive approach is fine, you may assume implicit stack space does not
        // count as extra space for this problem. Example 1: Input: root =
        // [1,2,3,4,5,null,7] Output: [1,#,2,3,#,4,5,7,#] Explanation: Given the above
        // binary tree (Figure A), your function should populate each next pointer to
        // point to its next right node, just like in Figure B. The serialized output is
        // in level order as connected by the next pointers, with '#' signifying the end
        // of each level. Constraints: The number of nodes in the given tree is less
        // than 6000. -100 <= node.val <= 100
        NodeWithNextLink *connectII(NodeWithNextLink *root)
        {
            NodeWithNextLink *node = root;
            while (node != nullptr)
            {
                NodeWithNextLink *left = nullptr;
                NodeWithNextLink *prev = nullptr;
                while (node != nullptr)
                {
                    if (node->left != nullptr)
                    {
                        if (left == nullptr)
                            left = node->left;
                        if (prev != nullptr)
                            prev->next = node->left;
                        prev = node->left;
                    }
                    if (node->right != nullptr)
                    {
                        if (left == nullptr)
                            left = node->right;
                        if (prev != nullptr)
                            prev->next = node->right;
                        prev = node->right;
                    }
                    node = node->next;
                }
                node = left;
            }
            return root;
        }
        NodeWithNextLink *connectII2(NodeWithNextLink *root)
        {
            if (root != nullptr && (root->left != nullptr || root->right != nullptr))
            {
                NodeWithNextLink *prev = nullptr;
                if (root->left != nullptr)
                    prev = root->left;
                if (root->right != nullptr)
                {
                    if (prev != nullptr)
                        prev->next = root->right;
                    prev = root->right;
                }
                NodeWithNextLink *n = root->next;
                while (n != nullptr)
                {
                    if (n->left != nullptr)
                    {
                        prev->next = n->left;
                        prev = n->left;
                    }
                    if (n->right != nullptr)
                    {
                        prev->next = n->right;
                        prev = n->right;
                    }
                    n = n->next;
                }
                connectII2(root->left);
                connectII2(root->right);
            }
            return root;
        }
        NodeWithNextLink *connectII3(NodeWithNextLink *root)
        {
            if (root != nullptr)
            {
                NodeWithNextLink *prev = nullptr;
                NodeWithNextLink *n = root;
                while (n != nullptr)
                {
                    if (n->left != nullptr)
                    {
                        if (prev != nullptr)
                            prev->next = n->left;
                        prev = n->left;
                    }
                    if (n->right != nullptr)
                    {
                        if (prev != nullptr)
                            prev->next = n->right;
                        prev = n->right;
                    }
                    n = n->next;
                }
                connectII3(root->left);
                connectII3(root->right);
            }
            return root;
        }

        // 118. Pascal's Triangle
        // Given a non-negative integer numRows, generate the first numRows of Pascal's
        // triangle. In Pascal's triangle, each number is the sum of the two numbers
        // directly above it. Example: Input: 5 Output:
        // [
        //      [1],
        //     [1,1],
        //    [1,2,1],
        //   [1,3,3,1],
        //  [1,4,6,4,1]
        // ]
        vector<vector<int>> generate(int numRows)
        {
            vector<vector<int>> result;
            vector<int> v;
            for (int i = 1; i <= numRows; i++)
            {
                v.push_back(1);
                for (int j = v.size() - 2; j > 0; j--)
                    v[j] += v[j - 1];
                result.push_back(v);
            }
            return result;
        }

        // 119. Pascal's Triangle II
        // Given a non-negative index k where k ≤ 33, return the kth index row of
        // the Pascal's triangle. Note that the row index starts from 0.
        // In Pascal's triangle, each number is the sum of the two numbers directly
        // above it. Example: Input: 3 Output: [1,3,3,1] Follow up: Could you optimize
        // your algorithm to use only O(k) extra space?
        vector<int> getRow(int rowIndex)
        {
            vector<int> v = {1};
            for (int i = 1; i <= rowIndex; i++)
            {
                v.push_back(1);
                for (int j = v.size() - 2; j > 0; j--)
                    v[j] += v[j - 1];
            }
            return v;
        }
        vector<int> getRow2(int rowIndex)
        {
            vector<int> row;
            for (int k = 0; k <= rowIndex; k++)
            {
                row.push_back(1);
                for (int i = row.size() - 2; i > 0; i--)
                {
                    row[i] += row[i - 1];
                }
            }
            return row;
        }
        vector<int> getRow3(int rowIndex)
        {
            if (rowIndex <= 0)
                return vector<int>{1};
            vector<int> row = getRow3(rowIndex - 1);
            for (int i = (int)row.size() - 1; i > 0; i--)
                row[i] += row[i - 1];
            row.push_back(1);
            return row;
        }

        // 120. Triangle
        // Given a triangle, find the minimum path sum from top to bottom. Each step you
        // may move to adjacent numbers on the row below.
        // For example, given the following triangle
        // [
        //      [2],
        //     [3,4],
        //    [6,5,7],
        //   [4,1,8,3]
        // ]
        // The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
        // Note: Bonus point if you are able to do this using only O(n) extra space,
        // where n is the total number of rows in the triangle.
        int minimumTotal(const vector<vector<int>> &triangle)
        {
            vector<int> v(triangle.size(), 0);
            for (size_t i = 0; i < triangle.size(); i++)
            {
                v[i] = triangle[i][i];
                if (i > 0)
                    v[i] += v[i - 1];
                for (int j = i - 1; j > 0; j--)
                    v[j] = triangle[i][j] + min(v[j - 1], v[j]);
                if (i > 0)
                    v[0] += triangle[i][0];
            }
            int m = INT_MAX;
            for (size_t i = 0; i < v.size(); i++)
                m = min(m, v[i]);
            return m;
        }
        int minimumTotal2(const vector<vector<int>> &triangle)
        {
            vector<int> row(triangle[0]);
            for (size_t i = 1; i < triangle.size(); i++)
            {
                size_t n = triangle[i].size();
                row.push_back(row[n - 2] + triangle[i][n - 1]);
                for (int j = n - 2; j > 0; j--)
                    row[j] = triangle[i][j] + min(row[j - 1], row[j]);
                row[0] += triangle[i][0];
            }
            int min = row[0];
            for (size_t i = 1; i < row.size(); i++)
            {
                if (row[i] < min)
                    min = row[i];
            }
            return min;
        }

        // 121. Best Time to Buy and Sell Stock
        // Say you have an array for which the ith element is the price of a given stock
        // on day i. If you were only permitted to complete at most one transaction
        // (i.e., buy one and sell one share of the stock), design an algorithm to find
        // the maximum profit. Note that you cannot sell a stock before you buy one.
        // Example 1:
        // Input: [7,1,5,3,6,4]
        // Output: 5
        // Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6),
        // profit = 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than
        // buying price. Example 2: Input: [7,6,4,3,1] Output: 0 Explanation: In this
        // case, no transaction is done, i.e. max profit = 0.
        int maxProfit(const vector<int> &prices)
        {
            size_t low = 0;
            int profit = 0;
            for (size_t i = 1; i < prices.size(); i++)
            {
                if (prices[i] < prices[low])
                    low = i;
                else
                    profit = max(profit, prices[i] - prices[low]);
            }
            return profit;
        }

        // 122. Best Time to Buy and Sell Stock II
        // Say you have an array for which the ith element is the price of a given
        // stock on day i. Design an algorithm to find the maximum profit. You may
        // complete as many transactions as you like (i.e., buy one and sell one share
        // of the stock multiple times). Note: You may not engage in multiple
        // transactions at the same time (i.e., you must sell the stock before you buy
        // again).
        // Example 1:
        // Input: [7,1,5,3,6,4]
        // Output: 7
        // Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5),
        // profit = 5-1 = 4. Then buy on day 4 (price = 3) and sell on day 5
        // (price = 6), profit = 6-3 = 3.
        // Example 2:
        // Input: [1,2,3,4,5]
        // Output: 4
        // Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5),
        // profit = 5-1 = 4.
        // Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
        // are engaging multiple transactions at the same time. You must sell before
        // buying again. Example 3: Input: [7,6,4,3,1] Output: 0 Explanation: In this
        // case, no transaction is done, i.e. max profit = 0.
        int maxProfitII(const vector<int> &prices)
        {
            int p = 0;
            for (size_t i = 1; i < prices.size(); i++)
                p += (prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0);
            return p;
        }

        // 123. Best Time to Buy and Sell Stock III
        // Say you have an array for which the ith element is the price of a given stock
        // on day i. Design an algorithm to find the maximum profit. You may complete at
        // most two transactions. Note: You may not engage in multiple transactions at
        // the same time (i.e., you must sell the stock before you buy again). Example
        // 1: Input: [3,3,5,0,0,3,1,4] Output: 6 Explanation: Buy on day 4 (price = 0)
        // and sell on day 6 (price = 3), profit = 3-0 = 3. Then buy on day 7 (price =
        // 1) and sell on day 8 (price = 4), profit = 4-1 = 3. Example 2: Input:
        // [1,2,3,4,5] Output: 4 Explanation: Buy on day 1 (price = 1) and sell on day 5
        // (price = 5), profit = 5-1 = 4. Note that you cannot buy on day 1, buy on day
        // 2 and sell them later, as you are engaging multiple transactions at the same
        // time. You must sell before buying again. Example 3: Input: [7,6,4,3,1]
        // Output: 0
        // Explanation: In this case, no transaction is done, i.e. max profit = 0.
        // Dynamic Programming
        // Let p[k, j] be the profit when k transactions are done at index j
        // Let p[j] = prices[j]
        // p[k, j] = max(p[k, j - 1],
        //               p[k - 1, j - 2] + p[j] - p[j - 1],
        //               p[k - 1, j - 3] + p[j] - p[j - 2],
        //               ......
        //               p[k - 1, 2(k - 1) - 1] + p[j] - p[2(k - 1)])
        // For k = 2
        // p[2, j] = max(p[2, j - 1],
        //               p[j] - p[j - 1] + p[1, j - 2],
        //               p[j] - p[j - 2] + p[1, j - 3],
        //               ......
        //               p[j] - p[2] + p[1, 1])
        // p[2, j - 1] = max(p[2, j - 2],
        //                   p[j - 1] - p[j - 2] + p[1, j - 3],
        //                   p[j - 1] - p[j - 3] + p[1, j - 4],
        //                   ......
        //                   p[j - 1] - p[2] + p[1, 1])
        // p[1, j] = max(p[1, j - 1],
        //               p[j] - p[j - 1] + p[0, j - 2],
        //               p[j] - p[j - 2] + p[0, j - 3],
        //               ......
        //               p[j] - p[1] + p[0, 0])
        //               p[j] - p[0] + p[0, -1])
        // p[1, j - 1] = max(p[1, j - 2],
        //                   p[j - 1] - p[j - 2] + p[0, j - 3],
        //                   p[j - 1] - p[j - 3] + p[0, j - 4],
        //                   ......
        //                   p[j - 1] - p[1] + p[0, 0])
        //                   p[j - 1] - p[0] + p[0, -1])
        //   j 0
        //       p[0]   p[1]   p[2]         p[3]         p[4]      ......    p[j-2]          p[j-1]          p[j]
        // max{ -p[0]  -p[1]  -p[2]        -p[3]        -p[4]      ......   -p[j-2]         -p[j-1]         -p[j] }
        // k 1        p[1,1] p[1,2]       p[1,3]       p[1,4]      ...... p[1,(j-2)]      p[1,(j-1)]       p[1,j]
        //              max{ p[1,1]-p[2]  p[1,2]-p[3]  p[1,3]-p[4] ...... p[1,(j-3)]-p[j-2] p[1,(j-2)]-p[j-1] }
        //   2                            p[2,3]       p[2,4]      ...... p[2,(j-2)]      p[2,(j-1)]        p[2,j]
        int maxProfitIII(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
            int m1 = INT_MIN;
            int m2 = INT_MIN;
            int p1 = INT_MIN;
            int p2 = INT_MIN;
            for (size_t j = 0; j < prices.size(); j++)
            {
                if (j == 0)
                {
                    m1 = -prices[0];
                }
                else if (j == 1)
                {
                    p1 = prices[1] - prices[0];
                    m1 = max(m1, -prices[1]);
                }
                else if (j == 2)
                {
                    m2 = p1 - prices[2];
                    p1 = max(p1, prices[2] + m1);
                    m1 = max(m1, -prices[2]);
                }
                else if (j == 3)
                {
                    p2 = prices[3] + m2;
                    m2 = max(m2, p1 - prices[3]);
                    p1 = max(p1, prices[3] + m1);
                    m1 = max(m1, -prices[3]);
                }
                else
                {
                    p2 = max(p2, prices[j] + m2);
                    m2 = max(m2, p1 - prices[j]);
                    p1 = max(p1, prices[j] + m1);
                    m1 = max(m1, -prices[j]);
                }
            }
            int m = max(p1, p2);
            return m < 0 ? 0 : m;
        }
        int maxProfitIII2(const vector<int> &prices)
        {
            if (prices.empty())
                return 0;
            vector<vector<int>> p(3, vector<int>(prices.size(), 0));
            for (size_t j = 1; j < prices.size(); j++)
            {
                if (j == 1)
                {
                    p[1][1] = prices[1] - prices[0];
                }
                else if (j == 2)
                {
                    p[1][2] =
                        max(p[1][1], max(prices[2] - prices[1], prices[2] - prices[0]));
                }
                else
                {
                    int m = -prices[0];
                    for (size_t i = 1; i < j; i++)
                        m = max(m, p[0][i - 1] - prices[i]);
                    p[1][j] = max(p[1][j - 1], prices[j] + m);
                    m = INT_MIN;
                    for (size_t i = 2; i < j; i++)
                        m = max(m, p[1][i - 1] - prices[i]);
                    p[2][j] = max(p[2][j - 1], prices[j] + m);
                }
            }
            return max(p[1][prices.size() - 1], p[2][prices.size() - 1]);
        }
        int maxProfitIII3(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
            // Record the maximum two transactions
            int buy1 = 0;
            int sell1 = 0;
            int buy2 = 0;
            int sell2 = 0;
            // Record the maximum transactions
            int buym = 0;
            int sellm = 0;
            // Record the latest potential sell-buy candidate
            int i = 0;
            int j = 0;
            int length = prices.size();
            while (j < length)
            {
                while (j + 1 < length && prices[j] >= prices[j + 1])
                {
                    // Find the next local minimum
                    j++;
                }
                if (i < sell2 || prices[i] >= prices[j])
                {
                    // i is the minimal in the range [sell2, j]
                    // [sell2, j] may contain multiple increasing ranges, because
                    // [i, j] may not overlap with previous [buy2, sell2]
                    i = j;
                }
                while (j + 1 < length && prices[j] < prices[j + 1])
                {
                    // Find the next local maximum
                    j++;
                }
                if (i == j)
                {
                    j++; // Why this can happen?
                    continue;
                }
                // now input[i..j] is next potential sell-buy candidate.
                // input[i..j] may contain more than one increasing ranges.
                if (buy1 == sell1)
                {
                    // Get the first two increasing ranges
                    buy1 = buy2;
                    sell1 = sell2;
                    buy2 = i;
                    sell2 = j;
                }
                else
                {
                    // Given [buy1, sell1], [buy2, sell2] and [i, j]
                    // Compute new [buy1, sell1] and [buy2, sell2]
                    // Need to compare following cases:
                    // 1. [buy1, sell1], [buy2, sell2]
                    // 2. [buy1, sell1], [buy2, j]
                    // 3. [buy1, sell1], [i, j]
                    // 4. [buy2, sell2], [i, j]
                    // 5. [buy1, sell2], [i, j]
                    // Start with case 1
                    int b1 = buy1;
                    int s1 = sell1;
                    int b2 = buy2;
                    int s2 = sell2;
                    if (prices[j] > prices[s2])
                    {
                        // Covered case 2
                        s2 = j;
                    }
                    if (prices[j] - prices[i] + prices[sellm] - prices[buym] >
                        prices[s2] - prices[b2] + prices[s1] - prices[b1])
                    {
                        // Covered case 3, 4 and 5
                        b1 = buym;
                        s1 = sellm;
                        b2 = i;
                        s2 = j;
                    }
                    buy1 = b1;
                    sell1 = s1;
                    buy2 = b2;
                    sell2 = s2;
                }
                if (prices[sell1] - prices[buy1] > prices[sellm] - prices[buym])
                {
                    buym = buy1;
                    sellm = sell1;
                }
                if (prices[sell2] - prices[buy2] > prices[sellm] - prices[buym])
                {
                    buym = buy2;
                    sellm = sell2;
                }
                if (prices[sell2] - prices[buy1] > prices[sellm] - prices[buym])
                {
                    buym = buy1;
                    sellm = sell2;
                }
                j++;
            }
            if (prices[sellm] - prices[buym] >=
                prices[sell2] - prices[buy2] + prices[sell1] - prices[buy1])
            {
                return prices[sellm] - prices[buym];
            }
            else
            {
                return prices[sell1] - prices[buy1] + prices[sell2] - prices[buy2];
            }
        }
        int maxProfitIII4(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
            // Find one transaction during input[begin..end]
            auto maxProfit = [&](int begin, int end, int &buy, int &sell, int &profit)
            {
                int min = begin;
                buy = begin;
                sell = begin;
                profit = 0;
                if (end == begin)
                    return;
                for (int i = begin + 1; i <= end; i++)
                {
                    if (prices[i] < prices[min])
                    {
                        min = i;
                    }
                    else
                    {
                        if (prices[i] - prices[min] > profit)
                        {
                            buy = min;
                            sell = i;
                            profit = prices[i] - prices[min];
                        }
                    }
                }
            };
            int profit1 = 0;
            int profit2 = 0;
            int b1 = 0;
            int s1 = 0;
            int p1 = 0;
            int b2 = 0;
            int s2 = 0;
            int p2 = 0;
            int i = 0;
            int length = prices.size();
            while (i < length - 1)
            {
                // Increase i so that [0..i] contains one more increasing subarray
                while (i < length - 1 && prices[i + 1] <= prices[i])
                    i++;
                if (i == length - 1)
                    break;
                while (i < length - 1 && prices[i + 1] > prices[i])
                    i++;
                // Find the max transaction before i
                maxProfit(b1, i, b1, s1, p1);
                // Find the max transaction after i
                if (i > b2)
                {
                    // If i <= b2, then no need to reevaluate because b2/s2 is already
                    // maximum after i
                    maxProfit(i, length - 1, b2, s2, p2);
                }
                if (p1 + p2 > profit1 + profit2)
                {
                    profit1 = p1;
                    profit2 = p2;
                }
                i++;
            }
            int b3;
            int s3;
            int p3;
            maxProfit(0, length - 1, b3, s3, p3);
            if (p3 > profit1 + profit2)
            {
                return p3;
            }
            else
            {
                return profit1 + profit2;
            }
        }

        // 124. Binary Tree Maximum Path Sum
        // Given a non-empty binary tree, find the maximum path sum. For this problem,
        // a path is defined as any sequence of nodes from some starting node to any
        // node in the tree along the parent-child connections. The path must contain
        // at least one node and does not need to go through the root.
        // Example 1:
        // Input: [1,2,3]
        //        1
        //       / \
        //      2   3
        // Output: 6
        // Example 2:
        // Input: [-10,9,20,null,null,15,7]
        //    -10
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // Output: 42
        int maxPathSum(TreeNode *root)
        {
            function<void(TreeNode *, int &, int &)> solve =
                [&](TreeNode *n, int &pathSum, int &maxSum)
            {
                if (n == nullptr)
                    return;
                if (n->left == nullptr && n->right == nullptr)
                {
                    pathSum = n->val;
                    maxSum = n->val;
                    return;
                }
                int leftPathSum = INT_MIN;
                int leftMaxSum = INT_MIN;
                if (n->left != nullptr)
                    solve(n->left, leftPathSum, leftMaxSum);
                if (leftPathSum < 0)
                    leftPathSum = 0; // Ignore left path
                int rightPathSum = INT_MIN;
                int rightMaxSum = INT_MIN;
                if (n->right != nullptr)
                    solve(n->right, rightPathSum, rightMaxSum);
                if (rightPathSum < 0)
                    rightPathSum = 0; // Ignore right path
                if (n->left == nullptr)
                {
                    pathSum = n->val + rightPathSum;
                    maxSum = max(pathSum, rightMaxSum);
                }
                else if (n->right == nullptr)
                {
                    pathSum = n->val + leftPathSum;
                    maxSum = max(pathSum, leftMaxSum);
                }
                else
                {
                    pathSum = n->val + max(leftPathSum, rightPathSum);
                    maxSum = max(leftPathSum + n->val + rightPathSum,
                                 max(leftMaxSum, rightMaxSum));
                }
            };
            int p;
            int m;
            solve(root, p, m);
            return m;
        }
        int maxPathSum2(TreeNode *root)
        {
            stack<TreeNode *> p;
            map<TreeNode *, pair<int, int>> s; // <path sum at node, max path sum under node>
            TreeNode *n = root;
            int m = INT_MIN; // node val may be negative
            TreeNode *last = n;
            while (!p.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s[n] = make_pair<int, int>(0, 0);
                    p.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = p.top();
                    if (t->right != nullptr && t->right != last)
                    {
                        n = t->right;
                    }
                    else
                    {
                        if (t->left != nullptr)
                        {
                            m = max(m, s[t->left].second);
                        }
                        if (t->right != nullptr)
                        {
                            m = max(m, s[t->right].second);
                        }
                        // check the path including t
                        // left child path or right child path may be negative so ignore if needed
                        m = max(m,
                                (t->val + (t->left == nullptr ? 0 : max(0, s[t->left].first)) + (t->right == nullptr ? 0 : max(0, s[t->right].first))));
                        s[t].second = m;
                        s[t].first = t->val + max(t->left == nullptr ? 0 : max(0, s[t->left].first),
                                                  t->right == nullptr ? 0 : max(0, s[t->right].first));
                        p.pop();
                    }
                    last = t;
                }
            }
            return m;
        }

        // 125. Valid Palindrome
        // Given a string, determine if it is a palindrome, considering only
        // alphanumeric characters and ignoring cases. Note: For the purpose of this
        // problem, we define empty string as valid palindrome. Example 1: Input: "A
        // man, a plan, a canal: Panama" Output: true Example 2: Input: "race a car"
        // Output: false
        bool isPalindrome(const string &s)
        {
            function<bool(char)> isAlphaNumeric = [&](char c) -> bool
            {
                return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
                       ('0' <= c && c <= '9');
            };
            int i = 0;
            int j = (int)s.size() - 1;
            while (i < j)
            {
                if (!isAlphaNumeric(s[i]))
                {
                    i++;
                }
                else if (!isAlphaNumeric(s[j]))
                {
                    j--;
                }
                else
                {
                    if ('a' <= s[i] && s[i] <= 'z')
                    {
                        if ((s[i] - 'a' != s[j] - 'a') && (s[i] - 'a' != s[j] - 'A'))
                            return false;
                    }
                    else if ('A' <= s[i] && s[i] <= 'Z')
                    {
                        if ((s[i] - 'A' != s[j] - 'a') && (s[i] - 'A' != s[j] - 'A'))
                            return false;
                    }
                    else if ('0' <= s[i] && s[i] <= '9')
                    {
                        if (s[i] - '0' != s[j] - '0')
                            return false;
                    }
                    i++;
                    j--;
                }
            }
            return true;
        }
        bool isPalindrome2(const string &s)
        {
            function<bool(char)> isDigit = [&](char c) -> bool
            {
                return '0' <= c && c <= '9';
            };
            function<bool(char)> isLower = [&](char c) -> bool
            {
                return 'a' <= c && c <= 'z';
            };
            function<bool(char)> isUpper = [&](char c) -> bool
            {
                return 'A' <= c && c <= 'Z';
            };
            int i = 0;
            int j = s.size() - 1;
            while (i < j)
            {
                char a = s[i];
                if (!isDigit(a) && !isLower(a) && !isUpper(a))
                {
                    i++;
                    continue;
                }
                char b = s[j];
                if (!isDigit(b) && !isLower(b) && !isUpper(b))
                {
                    j--;
                    continue;
                }
                if (isDigit(a) != isDigit(b))
                    return false;
                if (isDigit(a) && a != b)
                    return false;
                if (isLower(a) && a - 'a' != b - 'a' && a - 'a' != b - 'A')
                    return false;
                if (isUpper(a) && a - 'A' != b - 'a' && a - 'A' != b - 'A')
                    return false;
                i++;
                j--;
            }
            return true;
        }
        bool isPalindrome3(const string &s)
        {
            if (s.empty())
                return true;
            auto isAlphaNumeric = [&](char c) -> bool
            {
                return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                       (c >= '0' && c <= '9');
            };
            auto equal = [&](char a, char b) -> bool
            {
                if (a >= 'a' && a <= 'z' &&
                    ((b - 'a' == a - 'a') || (b - 'A' == a - 'a')))
                    return true;
                else if (a >= 'A' && a <= 'Z' &&
                         ((b - 'a' == a - 'A') || (b - 'A' == a - 'A')))
                    return true;
                else if (a >= '0' && a <= '9' && b == a)
                    return true;
                return false;
            };
            int i = 0;
            int j = s.size() - 1;
            while (i <= j)
            {
                while (i <= j && !isAlphaNumeric(s[i]))
                    i++;
                while (i <= j && !isAlphaNumeric(s[j]))
                    j--;
                if (i > j)
                    return true;
                if (!equal(s[i], s[j]))
                    return false;
                i++;
                j--;
            }
            return true;
        }

        // 126. Word Ladder II
        // Given two words (beginWord and endWord), and a dictionary's word list, find
        // all shortest transformation sequence(s) from beginWord to endWord, such that:
        // Only one letter can be changed at a time and each transformed word must exist
        // in the word list. Note that beginWord is not a transformed word. Note: Return
        // an empty list if there is no such transformation sequence. All words have the
        // same length. All words contain only lowercase alphabetic characters. You may
        // assume no duplicates in the word list. You may assume beginWord and endWord
        // are non-empty and are not the same.
        // Example 1:
        // Input:
        // beginWord = "hit",
        // endWord = "cog",
        // wordList = ["hot","dot","dog","lot","log","cog"]
        // Output:
        // [
        //   ["hit","hot","dot","dog","cog"],
        //   ["hit","hot","lot","log","cog"]
        // ]
        // Example 2:
        // Input:
        // beginWord = "hit"
        // endWord = "cog"
        // wordList = ["hot","dot","dog","lot","log"]
        // Output: []
        // Explanation: The endWord "cog" is not in wordList, therefore no possible
        // transformation.
        vector<vector<string>> findLadders(const string &beginWord,
                                           const string &endWord,
                                           const vector<string> &wordList)
        {
            vector<vector<string>> results;
            map<string, bool> visited;
            for_each(wordList.cbegin(), wordList.cend(),
                     [&](const string &s)
                     { visited[s] = false; });
            if (visited.find(endWord) == visited.end())
                return results;
            size_t minLen = wordList.size() + 1;
            function<void(string &, vector<string> &)>
                solve = [&](string &w, vector<string> &v)
            {
                if (v.size() >= minLen)
                    return;
                for (size_t i = 0; i < w.size(); i++)
                {
                    string s = w;
                    char c = s[i];
                    for (char k = 'a'; k <= 'z'; k++)
                    {
                        s[i] = k;
                        if (k == c || visited.find(s) == visited.end() || visited[s])
                            continue;
                        visited[s] = true;
                        v.push_back(s);
                        if (s.compare(endWord) == 0)
                        {
                            if (v.size() <= minLen)
                            {
                                results.push_back(v);
                                minLen = v.size();
                            }
                        }
                        else if (v.size() < minLen)
                        {
                            solve(s, v);
                        }
                        v.pop_back();
                        visited[s] = false;
                    }
                }
            };
            vector<string> p(1, beginWord);
            string word = beginWord;
            solve(word, p);
            auto it = results.begin();
            while (it != results.end())
            {
                if (it->size() > minLen)
                    it = results.erase(it);
                else
                    it++;
            }
            return results;
        }
        vector<vector<string>> findLadders2(const string &beginWord,
                                            const string &endWord,
                                            const vector<string> &wordList)
        {
            vector<vector<string>> ladders = {};
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return ladders;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return ladders;
            unordered_map<string, vector<vector<string>>>
                path; // Record paths ending at a word
            unordered_map<string, int> level;
            queue<string> q[2];
            int step = 0;
            bool stop = false;
            q[0].push(beginWord);
            level[beginWord] = step;
            path[beginWord] = vector<vector<string>>{};
            path[beginWord].push_back(vector<string>{beginWord});
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    string temp;
                    for (size_t i = 0; i < word.size(); i++)
                    {
                        temp = word;
                        for (char j = 'a'; j <= 'z'; j++)
                        {
                            temp[i] = j;
                            if (temp.compare(endWord) == 0)
                            {
                                for_each(path[word].begin(), path[word].end(),
                                         [&](vector<string> &p)
                                         {
                                             vector<string> r(p);
                                             r.push_back(temp);
                                             ladders.push_back(r);
                                         });
                                stop = true;
                            }
                            else if (find(wordList.cbegin(), wordList.cend(), temp) !=
                                     wordList.cend())
                            {
                                if (level.find(temp) == level.end())
                                {
                                    level[temp] = step + 1;
                                    next.push(temp);
                                    path[temp] = vector<vector<string>>{};
                                }
                                if (level[temp] > step)
                                {
                                    for_each(path[word].begin(), path[word].end(),
                                             [&](vector<string> &p)
                                             {
                                                 vector<string> r(p);
                                                 r.push_back(temp);
                                                 path[temp].push_back(r);
                                             });
                                }
                            }
                        }
                    }
                }
                if (stop)
                    break; // Found the shortest paths. If need to find all, then do not
                           // stop.
                step++;
            }
            return ladders;
        }
        vector<vector<string>> findLadders3(const string &beginWord, const string &endWord, const vector<string> &wordList)
        {
            set<string> wordSet(wordList.begin(), wordList.end());
            vector<vector<string>> ladders;
            function<void(string &, vector<string> &)> solve =
                [&](string &word, vector<string> &ladder)
            {
                for (size_t i = 0; i < word.size(); i++)
                {
                    char c = word[i];
                    for (char j = 1; j < 26; j++)
                    {
                        word[i] = 'a' + ((c - 'a' + j) % 26);
                        if (wordSet.find(word) == wordSet.end())
                            continue;
                        if (word.compare(endWord) == 0)
                        {
                            vector<string> v(ladder.begin(), ladder.end());
                            v.push_back(word);
                            if (ladders.empty())
                                ladders.push_back(v);
                            else if (v.size() < ladders.begin()->size())
                            {
                                ladders.clear();
                                ladders.push_back(v);
                            }
                            else if (v.size() == ladders.begin()->size())
                            {
                                ladders.push_back(v);
                            }
                            break;
                        }
                        else if (std::find(ladder.begin(), ladder.end(), word) == ladder.end())
                        {
                            ladder.push_back(word);
                            solve(word, ladder);
                            ladder.pop_back();
                        }
                    }
                    word[i] = c;
                }
            };
            vector<string> l;
            l.push_back(beginWord);
            string begin(beginWord);
            solve(begin, l);
            return ladders;
        }

        // 127. Word Ladder
        // Given two words (beginWord and endWord), and a dictionary's word list,
        // find the length of shortest transformation sequence from beginWord to
        // endWord, such that: Only one letter can be changed at a time. Each
        // transformed word must exist in the word list. Note that beginWord is
        // not a transformed word. Note: Return 0 if there is no such transformation
        // sequence. All words have the same length. All words contain only lowercase
        // alphabetic characters. You may assume no duplicates in the word list. You
        // may assume beginWord and endWord are non-empty and are not the same.
        // Example 1:
        // Input:
        // beginWord = "hit",
        // endWord = "cog",
        // wordList = ["hot","dot","dog","lot","log","cog"]
        // Output: 5
        // Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" ->
        // "dog" -> "cog", return its length 5. Example 2: Input: beginWord = "hit"
        // endWord = "cog"
        // wordList = ["hot","dot","dog","lot","log"]
        // Output: 0
        // Explanation: The endWord "cog" is not in wordList, therefore no possible
        // transformation.
        int ladderLength(const string &beginWord, const string &endWord,
                         const vector<string> &wordList)
        {
            map<string, bool> visited;
            for_each(wordList.cbegin(), wordList.cend(),
                     [&](const string &s)
                     { visited[s] = false; });
            queue<vector<string>> paths;
            paths.push(vector<string>(1, beginWord));
            while (!paths.empty())
            {
                vector<string> path = paths.front();
                paths.pop();
                for (size_t i = 0; i < path.back().size(); i++)
                {
                    string s = path.back();
                    char c = s[i];
                    for (char k = 'a'; k <= 'z'; k++)
                    {
                        s[i] = k;
                        if (k == c || visited.find(s) == visited.end() || visited[s])
                            continue;
                        if (s.compare(endWord) == 0)
                            return path.size() + 1;
                        visited[s] = true;
                        vector<string> path1(path.cbegin(), path.cend());
                        path1.push_back(s);
                        paths.push(path1);
                    }
                }
            }
            return 0;
        }
        int ladderLength2(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            function<int(bool, const string &, const vector<string> &)> search =
                [&](bool transformed, const string &word,
                    const vector<string> &list) -> int
            {
                vector<string> list2(list);
                auto it = find(list2.begin(), list2.end(), word);
                if (it == list2.end())
                {
                    if (transformed)
                        return 0;
                }
                else
                {
                    list2.erase(it);
                }
                if (word == endWord)
                    return 1;
                int min = INT_MAX;
                for (size_t i = 0; i < word.length(); i++)
                {
                    string word2(word);
                    for (char j = 0; j < 26; j++)
                    {
                        if (word[i] != 'a' + j)
                        {
                            word2[i] = 'a' + j;
                            int m = search(true, word2, list2);
                            if (m > 0 && m < min)
                                min = m;
                        }
                    }
                }
                if (min != INT_MAX)
                    return min + 1;
                else
                    return 0;
            };
            return search(false, beginWord, wordList);
        }
        int ladderLength3(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> dict;
            dict.insert(wordList.begin(), wordList.end());
            if (dict.find(beginWord) == dict.end())
                dict.insert(beginWord);
            if (dict.find(endWord) == dict.end())
                dict.insert(endWord);
            map<string, vector<string>> graph;
            for_each(dict.begin(), dict.end(),
                     [&](string word)
                     { graph[word] = vector<string>{}; });
            for_each(dict.begin(), dict.end(), [&](string word)
                     {
                         int wordLen = word.length();
                         for (map<string, vector<string>>::iterator it = graph.begin();
                              it != graph.end(); it++)
                         {
                             if (wordLen == (int)it->first.length())
                             {
                                 int diff = 0;
                                 for (int i = 0; i < wordLen; i++)
                                 {
                                     if (word[i] != it->first[i])
                                         diff++;
                                     if (diff > 1)
                                         break;
                                 }
                                 if (diff == 1)
                                     it->second.push_back(word);
                             }
                         }
                     });
            bool found = false;
            unordered_set<string> visited;
            queue<string> q[2];
            int step = 0;
            q[0].push(beginWord);
            visited.insert(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    for (size_t i = 0; i < graph[word].size(); i++)
                    {
                        if (graph[word][i].compare(endWord) == 0)
                        {
                            found = true;
                            break;
                        }
                        if (visited.find(graph[word][i]) == visited.end())
                        {
                            visited.insert(graph[word][i]);
                            next.push(graph[word][i]);
                        }
                    }
                    if (found)
                        return step + 2;
                }
                step++;
            }
            return 0;
        }
        int ladderLength4(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> dict;
            dict.insert(wordList.begin(), wordList.end());
            auto diff1 = [&](const string &first, const string &second) -> bool
            {
                if (first.size() != second.size())
                    return false;
                int diff = 0;
                for (size_t i = 0; i < first.length(); i++)
                {
                    if (first[i] != second[i])
                        diff++;
                    if (diff > 1)
                        return false;
                }
                return diff == 1;
            };
            vector<string> q[2];
            int step = 0;
            q[0].push_back(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                vector<string> &current = q[step & 0x1];
                vector<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.erase(current.begin());
                    for (unordered_set<string>::iterator it = dict.begin();
                         it != dict.end(); it++)
                    {
                        if (diff1(word, *it))
                        {
                            if ((*it).compare(endWord) == 0)
                                return step + 2;
                            else
                                next.push_back(*it);
                        }
                    }
                }
                for_each(next.begin(), next.end(), [&](string &s)
                         { dict.erase(s); });
                step++;
            }
            return 0;
        }
        int ladderLength5(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> visited;
            queue<string> q[2];
            int step = 0;
            q[0].push(beginWord);
            visited.insert(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    int wordLen = word.size();
                    string temp;
                    for (int i = 0; i < wordLen; i++)
                    {
                        temp = word;
                        for (char j = 'a'; j <= 'z'; j++)
                        {
                            temp[i] = j;
                            if (temp.compare(endWord) == 0)
                                return step + 2;
                            if (find(wordList.cbegin(), wordList.cend(), temp) !=
                                    wordList.cend() &&
                                visited.find(temp) == visited.end())
                            {
                                visited.insert(temp);
                                next.push(temp);
                            }
                        }
                    }
                }
                step++;
            }
            return 0;
        }

        // 128. Longest Consecutive Sequence
        // Given an unsorted array of integers, find the length of the longest
        // consecutive elements sequence. Your algorithm should run in O(n) complexity.
        // Example:
        // Input: [100, 4, 200, 1, 3, 2]
        // Output: 4
        // Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
        // Therefore its length is 4.
        // Keep a list of open ranges in two maps:
        // (b0, e0), (b1, e1), ......, (bi, ei)
        // endWith = {
        //   e0: b0,
        //   e1: b1,
        //   ......
        //   ei: bi
        // }
        // beginWith = {
        //   b0: e0,
        //   b1: e1,
        //   ......
        //   bi: ei
        // }
        // Make sure no overlapping beginning points and ending points, i.e.,
        // {b0, b1, ......, bi} should be distinct, and so should be
        // {e0, e1, ......, ei}. For each new number j, check whether j can:
        // 1. merge two existing ranges (b, j) and (j, e)
        // 2. extend one exsting range (b, j) or (j, e)
        // 3. insert a new range (j-1, j+1)
        // For #2 and #3, it may happen that the existing range and the new range is
        // already within a larger range, and in this case the larger range should be
        // preserved.
        int longestConsecutive(const vector<int> &nums)
        {
            map<int, int> endWith;
            map<int, int> beginWith;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                auto eit = endWith.find(nums[i]);
                auto bit = beginWith.find(nums[i]);
                if (eit != endWith.end() && bit != beginWith.end())
                {
                    // Merge (eit->second, nums[i]) and (nums[i], bit->second)
                    m = max(m, bit->second - eit->second - 1);
                    endWith[bit->second] = eit->second;
                    beginWith[eit->second] = bit->second;
                    endWith.erase(eit);
                    beginWith.erase(bit);
                }
                else if (eit != endWith.end())
                {
                    // Extend (eit->second, nums[i])
                    m = max(m, nums[i] - eit->second);
                    if (endWith.find(nums[i] + 1) == endWith.end() ||
                        endWith[nums[i] + 1] > eit->second)
                    {
                        beginWith[eit->second] = nums[i] + 1;
                        endWith[nums[i] + 1] = eit->second;
                        endWith.erase(eit);
                    }
                }
                else if (bit != beginWith.end())
                {
                    // Extend (nums[i], bit->second)
                    m = max(m, bit->second - nums[i]);
                    if (beginWith.find(nums[i] - 1) == beginWith.end() ||
                        beginWith[nums[i] - 1] < bit->second)
                    {
                        endWith[bit->second] = nums[i] - 1;
                        beginWith[nums[i] - 1] = bit->second;
                        beginWith.erase(bit);
                    }
                }
                else
                {
                    // Insert (nums[i] - 1, nums[i] + 1)
                    m = max(m, 1);
                    if (endWith.find(nums[i] + 1) == endWith.end() &&
                        beginWith.find(nums[i] - 1) == beginWith.end())
                    {
                        endWith[nums[i] + 1] = nums[i] - 1;
                        beginWith[nums[i] - 1] = nums[i] + 1;
                    }
                }
            }
            return m;
        }
        int longestConsecutive2(const vector<int> &nums)
        {
            map<int, int> endWith;
            map<int, int> beginWith;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                auto eit = endWith.find(nums[i]);
                auto bit = beginWith.find(nums[i]);
                int begin;
                int end;
                if (eit != endWith.end() && bit != beginWith.end())
                {
                    begin = eit->second;
                    end = bit->second;
                    endWith.erase(bit->second);
                    beginWith.erase(eit->second);
                    endWith.erase(eit);
                    beginWith.erase(bit);
                }
                else if (eit != endWith.end())
                {
                    begin = eit->second;
                    end = nums[i] + 1;
                    beginWith.erase(eit->second);
                    endWith.erase(eit);
                }
                else if (bit != beginWith.end())
                {
                    begin = nums[i] - 1;
                    end = bit->second;
                    endWith.erase(bit->second);
                    beginWith.erase(bit);
                }
                else
                {
                    begin = nums[i] - 1;
                    end = nums[i] + 1;
                }
                if ((endWith.find(end) != endWith.end() && endWith[end] <= begin) ||
                    (beginWith.find(begin) != beginWith.end() &&
                     beginWith[begin] >= end))
                    continue;
                m = max(m, end - begin - 1);
                endWith[end] = begin;
                beginWith[begin] = end;
            }
            return m;
        }
        int longestConsecutive3(const vector<int> &nums)
        {
            vector<int> n(nums);
            sort(n.begin(), n.end());
            int c = 0;
            int m = 0;
            for (size_t i = 0; i < n.size(); i++)
            {
                if (i == 0 || n[i - 1] + 1 < n[i])
                {
                    m = max(m, c);
                    c = 1;
                }
                else if (n[i - 1] + 1 == n[i])
                {
                    c++;
                }
            }
            m = max(m, c);
            return m;
        }

        // 129. Sum Root to Leaf Numbers
        // Given a binary tree containing digits from 0-9 only, each root-to-leaf path
        // could represent a number. An example is the root-to-leaf path 1->2->3 which
        // represents the number 123. Find the total sum of all root-to-leaf numbers.
        // Note: A leaf is a node with no children.
        // Example:
        // Input: [1,2,3]
        //     1
        //    / \
        //   2   3
        // Output: 25
        // Explanation:
        // The root-to-leaf path 1->2 represents the number 12.
        // The root-to-leaf path 1->3 represents the number 13.
        // Therefore, sum = 12 + 13 = 25.
        // Example 2:
        // Input: [4,9,0,5,1]
        //     4
        //    / \
        //   9   0
        //  / \
        // 5   1
        // Output: 1026
        // Explanation:
        // The root-to-leaf path 4->9->5 represents the number 495.
        // The root-to-leaf path 4->9->1 represents the number 491.
        // The root-to-leaf path 4->0 represents the number 40.
        // Therefore, sum = 495 + 491 + 40 = 1026.
        int sumNumbers(TreeNode *root)
        {
            stack<pair<TreeNode *, int>> p;
            TreeNode *n = root;
            int t = 0;
            int s = 0;
            while (!p.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s = s * 10 + n->val;
                    if (n->left == nullptr && n->right == nullptr)
                        t += s;
                    p.push(make_pair(n, s));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> v = p.top();
                    p.pop();
                    n = v.first->right;
                    s = v.second;
                }
            }
            return t;
        }
        int sumNumbers2(TreeNode *root)
        {
            int t = 0;
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s)
            {
                if (n == nullptr)
                    return;
                s = s * 10 + n->val;
                if (n->left == nullptr && n->right == nullptr)
                    t += s;
                solve(n->left, s);
                solve(n->right, s);
            };
            int s = 0;
            solve(root, s);
            return t;
        }

        // 130. Surrounded Regions
        // Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
        // surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in
        // that surrounded region.
        // Example:
        // X X X X
        // X O O X
        // X X O X
        // X O X X
        // After running your function, the board should be:
        // X X X X
        // X X X X
        // X X X X
        // X O X X
        // Explanation:
        // Surrounded regions shouldn’t be on the border, which means that any 'O' on
        // the border of the board are not flipped to 'X'. Any 'O' that is not on the
        // border and it is not connected to an 'O' on the border will be flipped to
        // 'X'. Two cells are connected if they are adjacent cells connected
        // horizontally or vertically.
        void solve(vector<vector<char>> &board)
        {
            if (board.empty() || board[0].empty())
                return;
            int rows = board.size();
            int cols = board[0].size();
            function<void(int, int)> mark = [&](int i, int j)
            {
                if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != 'O')
                    return;
                board[i][j] = 'Y';
                mark(i - 1, j);
                mark(i + 1, j);
                mark(i, j - 1);
                mark(i, j + 1);
            };
            for (int i = 0; i < rows; i++)
            {
                if (board[i][0] == 'O')
                    mark(i, 0);
                if (board[i][cols - 1] == 'O')
                    mark(i, cols - 1);
            }
            for (int i = 0; i < cols; i++)
            {
                if (board[0][i] == 'O')
                    mark(0, i);
                if (board[rows - 1][i] == 'O')
                    mark(rows - 1, i);
            }
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (board[i][j] == 'O')
                        board[i][j] = 'X';
                    else if (board[i][j] == 'Y')
                        board[i][j] = 'O';
                }
            }
        }
        void solve2(vector<vector<char>> &board)
        {
            int height = board.size();
            if (height == 0)
                return;
            int width = board[0].size();
            set<pair<int, int>> nocapture;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                    {
                        pair<int, int> p = make_pair(i, j);
                        if (nocapture.find(p) != nocapture.end())
                            continue;
                        bool boundary =
                            i == 0 || i == height - 1 || j == 0 || j == width - 1;
                        set<pair<int, int>> region;
                        queue<pair<int, int>> q;
                        region.insert(p);
                        q.push(p);
                        while (!q.empty())
                        {
                            p = q.front();
                            q.pop();
                            pair<int, int> n;
                            if (p.first > 0 && board[p.first - 1][p.second] == 'O')
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
                            if (p.second > 0 && board[p.first][p.second - 1] == 'O')
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
                        if (boundary)
                        {
                            nocapture.insert(region.begin(), region.end());
                        }
                        else
                        {
                            for_each(region.begin(), region.end(),
                                     [&](pair<int, int> p)
                                     {
                                         board[p.first][p.second] = 'X';
                                     });
                        }
                    }
                }
            }
        }
        void solve3(vector<vector<char>> &board)
        {
            int height = board.size();
            if (height == 0)
                return;
            int width = board[0].size();
            auto search = [&](int i, int j)
            {
                if (board[i][j] == 'O')
                {
                    board[i][j] = 'C';
                    pair<int, int> p = make_pair(i, j);
                    queue<pair<int, int>> q;
                    q.push(p);
                    while (!q.empty())
                    {
                        p = q.front();
                        q.pop();
                        pair<int, int> n;
                        if (p.first > 0 && board[p.first - 1][p.second] == 'O')
                        {
                            board[p.first - 1][p.second] = 'C';
                            n = make_pair(p.first - 1, p.second);
                            q.push(n);
                        }
                        if (p.second > 0 && board[p.first][p.second - 1] == 'O')
                        {
                            board[p.first][p.second - 1] = 'C';
                            n = make_pair(p.first, p.second - 1);
                            q.push(n);
                        }
                        if (p.second < width - 1 &&
                            board[p.first][p.second + 1] == 'O')
                        {
                            board[p.first][p.second + 1] = 'C';
                            n = make_pair(p.first, p.second + 1);
                            q.push(n);
                        }
                        if (p.first < height - 1 &&
                            board[p.first + 1][p.second] == 'O')
                        {
                            board[p.first + 1][p.second] = 'C';
                            n = make_pair(p.first + 1, p.second);
                            q.push(n);
                        }
                    }
                }
            };
            for (int i = 0; i < height; i++)
            {
                search(i, 0);
                search(i, width - 1);
            }
            for (int i = 0; i < width; i++)
            {
                search(0, i);
                search(height - 1, i);
            }
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                        board[i][j] = 'X';
                    else if (board[i][j] == 'C')
                        board[i][j] = 'O';
                }
            }
        }

        // 131. Palindrome Partitioning
        // Given a string s, partition s such that every substring of the partition
        // is a palindrome. Return all possible palindrome partitioning of s.
        // Example:
        // Input: "aab"
        // Output:
        // [
        //   ["aa","b"],
        //   ["a","a","b"]
        // ]
        // Let p[i] be the solution for s[i..(n-1)], then
        // p[i] = {{s[i], p[i+1]},
        //         {s[i..(i+1)], p[i+2]},    if s[i..(i+1)] is a palindrome
        //         {s[i..(i+2)], p[i+3]},    if s[i..(i+2)] is a palindrome
        //         ......
        //         {s[i..(n-3)], p[n-2]},    if s[i..(n-3)] is a palindrome
        //         {s[i..(n-2)], p[n-1]},    if s[i..(n-2)] is a palindrome
        //         {s[i..(n-1)]}       if s[i..(n-1)] is a palindrome
        //        }
        vector<vector<string>> partition(const string &s)
        {
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool
            {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            map<int, vector<vector<string>>> m;
            int n = s.size();
            for (int i = n - 1; i >= 0; i--)
            {
                m[i] = {};
                for (int j = i; j < n - 1; j++)
                {
                    if (isPalindrome(i, j))
                    {
                        string p = s.substr(i, j - i + 1);
                        for_each(m[j + 1].begin(), m[j + 1].end(),
                                 [&](const vector<string> &v)
                                 {
                                     vector<string> v1 = {p};
                                     v1.insert(v1.end(), v.cbegin(), v.cend());
                                     m[i].push_back(v1);
                                 });
                    }
                }
                if (isPalindrome(i, n - 1))
                    m[i].push_back({s.substr(i, n - i)});
            }
            return m[0];
        }
        vector<vector<string>> partition2(const string &s)
        {
            map<int, vector<vector<string>>> m;
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool
            {
                while (i < j)
                {
                    if (s[i] != s[j])
                        return false;
                    i++;
                    j--;
                }
                return true;
            };
            function<void(int)> solve = [&](int i)
            {
                if (i < 0 || i >= (int)s.size() || m.find(i) != m.end())
                    return;
                m[i] = {};
                if (i == (int)s.size() - 1)
                {
                    m[i].push_back({s.substr(i, 1)});
                }
                else
                {
                    for (int j = i; j < (int)s.size(); j++)
                    {
                        if (isPalindrome(i, j))
                        {
                            if (j == (int)s.size() - 1)
                                m[i].push_back({s.substr(i, j - i + 1)});
                            else
                            {
                                if (m.find(j + 1) == m.end())
                                    solve(j + 1);
                                for (size_t k = 0; k < m[j + 1].size(); k++)
                                {
                                    vector<string> v(1, s.substr(i, j - i + 1));
                                    v.insert(v.end(), m[j + 1][k].begin(),
                                             m[j + 1][k].end());
                                    m[i].push_back(v);
                                }
                            }
                        }
                    }
                }
            };
            solve(0);
            return m[0];
        }
        vector<vector<string>> partition3(const string &s)
        {
            vector<vector<string>> result;
            if (s.empty())
                return result;
            function<bool(size_t, size_t)>
                isPalindrome = [&](size_t i, size_t j) -> bool
            {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            function<void(size_t, vector<string> &)>
                solve = [&](size_t i, vector<string> &p)
            {
                if (i == s.length())
                {
                    result.push_back(p);
                    return;
                }
                for (size_t j = i; j < s.length(); j++)
                {
                    if (isPalindrome(i, j))
                    {
                        vector<string> p2(p);
                        p2.push_back(s.substr(i, j - i + 1));
                        solve(j + 1, p2);
                    }
                }
            };
            vector<string> r;
            solve(0, r);
            return result;
        }

        // 132. Palindrome Partitioning II
        // Given a string s, partition s such that every substring of the partition is
        // a palindrome. Return the minimum cuts needed for a palindrome partitioning of
        // s. Example: Input: "aab" Output: 1 Explanation: The palindrome partitioning
        // ["aa","b"] could be produced using 1 cut. Let p[i] be the solution for
        // s[0..i], then
        // p[i] = min{p[i-1] + 1, since s[i..i] is a palindrome
        //            p[i-2] + 1, if s[(i-1)..i] is a palindrome
        //            p[i-3] + 1, if s[(i-2)..i] is a palindrome
        //            ......
        //            p[2] + 1, if s[3..i] is a palindrome
        //            p[1] + 1, if s[2..i] is a palindrome
        //            p[0] + 1, if s[1..i] is a palindrome
        //            0         if s[0..i] is a palindrome
        //           }
        int minCut(const string &s)
        {
            if (s.empty())
                return 0;
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool
            {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            vector<int> p(s.size(), 0);
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (!isPalindrome(0, i))
                {
                    p[i] = INT_MAX;
                    for (int j = 0; j < i; j++)
                    {
                        if (isPalindrome(j + 1, i))
                            p[i] = min(p[i], p[j]);
                    }
                    p[i]++;
                }
            }
            return p[(int)s.size() - 1];
        }
        int minCut2(const string &s)
        {
            if (s.empty())
                return 0;
            map<pair<int, int>, bool> m;
            // function<void(void)> printm = [&]() {
            //     cout << "m = {" << endl;
            //     for_each(m.cbegin(), m.cend(),
            //              [&](const pair<pair<int, int>, bool> &p) {
            //                  cout << "  (" << p.first.first << ", " << p.first.second
            //                       << ") : " << p.second << endl;
            //              });
            //     cout << "}" << endl;
            // };
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool
            {
                // cout << "Enter m[(" << i << "," << j << ")]" << endl;
                // printm();
                pair<int, int> p = make_pair(i, j);
                if (m.find(p) == m.end())
                {
                    if (i >= j)
                    {
                        // cout << i << " >= " << j << endl;
                        m[p] = true;
                    }
                    else if (s[i] != s[j])
                    {
                        // cout << "s[" << i << "] != s[" << j << "]" << endl;
                        m[p] = false;
                    }
                    else
                    {
                        // pair<int, int> p1 = make_pair(i + 1, j - 1);
                        // if (m.find(p1) == m.end()) {
                        //     cout << "Call m[" << i + 1 << ", " << j - 1 << "]" <<
                        //     endl;
                        //     // m[p1] actually will create the p1 entry before calling
                        //     into
                        //     // isPalindrome, which returns immediately because it
                        //     will find
                        //     // the p1 entry already exists.
                        //     m[p1] = isPalindrome(i + 1, j - 1);
                        // }
                        // m[p] = m[p1];
                        m[p] = isPalindrome(i + 1, j - 1);
                    }
                }
                // cout << "Exit  m[(" << i << "," << j << ")] = " << m[p] << endl;
                return m[p];
            };
            vector<int> p(s.size(), 0);
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (!isPalindrome(0, i))
                {
                    p[i] = INT_MAX;
                    for (int j = 0; j < i; j++)
                    {
                        if (isPalindrome(j + 1, i))
                            p[i] = min(p[i], p[j]);
                    }
                    p[i]++;
                }
                // cout << "i = " << i << endl;
                // cout << "{";
                // for (size_t k = 0; k < p.size(); k++) {
                //     if (k > 0)
                //         cout << ", ";
                //     cout << p[k];
                // }
                // cout << "}" << endl;
            }
            return p[(int)s.size() - 1];
        }

        // 133. Clone Graph
        // Given a reference of a node in a connected undirected graph. Return a deep
        // copy (clone) of the graph. Each node in the graph contains a val (int) and
        // a list (List[Node]) of its neighbors.
        // class Node {
        //     public int val;
        //     public List<Node> neighbors;
        // }
        // Test case format:
        // For simplicity sake, each node's value is the same as the node's index
        // (1-indexed). For example, the first node with val = 1, the second node with
        // val = 2, and so on. The graph is represented in the test case using an
        // adjacency list. Adjacency list is a collection of unordered lists used to
        // represent a finite graph. Each list describes the set of neighbors of a node
        // in the graph. The given node will always be the first node with val = 1. You
        // must return the copy of the given node as a reference to the cloned graph.
        // Example 1:
        // Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
        // Output: [[2,4],[1,3],[2,4],[1,3]]
        // Explanation: There are 4 nodes in the graph.
        // 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
        // 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
        // 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
        // 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
        // Example 2:
        // Input: adjList = [[]]
        // Output: [[]]
        // Explanation: Note that the input contains one empty list. The graph consists
        // of only one node with val = 1 and it does not have any neighbors.
        // Example 3:
        // Input: adjList = []
        // Output: []
        // Explanation: This an empty graph, it does not have any nodes.
        // Example 4:
        // Input: adjList = [[2],[1]]
        // Output: [[2],[1]]
        // Constraints:
        // 1 <= Node.val <= 100
        // Node.val is unique for each node.
        // Number of Nodes will not exceed 100.
        // There is no repeated edges and no self-loops in the graph.
        // The Graph is connected and all nodes can be visited starting from the given
        // node.
        Node *cloneGraph(Node *node)
        {
            map<Node *, Node *> cloned;
            function<Node *(Node *)> clone = [&](Node *node) -> Node *
            {
                if (node == nullptr)
                    return nullptr;
                if (cloned.find(node) != cloned.end())
                    return cloned[node];
                Node *copy = new Node(node->val);
                cloned[node] = copy;
                for_each(node->neighbors.begin(), node->neighbors.end(),
                         [&](Node *n)
                         { copy->neighbors.push_back(clone(n)); });
                return copy;
            };
            return clone(node);
        }
        Node *cloneGraph2(Node *node)
        {
            if (node == nullptr)
                return nullptr;
            map<Node *, Node *> m;
            m[node] = new Node(node->val);
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n)
                         {
                             if (m.find(n) == m.end())
                             {
                                 m[n] = new Node(n->val);
                                 q.push(n);
                             }
                             m[f]->neighbors.push_back(m[n]);
                         });
            }
            return m[node];
        }

        // 134. Gas Station
        // There are N gas stations along a circular route, where the amount of gas at
        // station i is gas[i]. You have a car with an unlimited gas tank and it costs
        // cost[i] of gas to travel from station i to its next station (i+1). You begin
        // the journey with an empty tank at one of the gas stations. Return the
        // starting gas station's index if you can travel around the circuit once in the
        // clockwise direction, otherwise return -1. Note: If there exists a solution,
        // it is guaranteed to be unique. Both input arrays are non-empty and have the
        // same length. Each element in the input arrays is a non-negative integer.
        // Example 1:
        // Input:
        // gas  = [1,2,3,4,5]
        // cost = [3,4,5,1,2]
        // Output: 3
        // Explanation:
        // Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 +
        // 4 = 4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to station 0.
        // Your tank = 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 - 3 + 2 = 6
        // Travel to station 2. Your tank = 6 - 4 + 3 = 5
        // Travel to station 3. The cost is 5. Your gas is just enough to travel back to
        // station 3. Therefore, return 3 as the starting index. Example 2: Input: gas
        // = [2,3,4] cost = [3,4,3] Output: -1 Explanation: You can't start at station 0
        // or 1, as there is not enough gas to travel to the next station. Let's start
        // at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4 Travel to
        // station 0. Your tank = 4 - 3 + 2 = 3 Travel to station 1. Your tank = 3 - 3 +
        // 3 = 3 You cannot travel back to station 2, as it requires 4 unit of gas but
        // you only have 3. Therefore, you can't travel around the circuit once no
        // matter where you start.
        // Let t[i..j] be sum of gas[k]-cost[k] for k = i..j,
        // if j is the first index after i such that t[i..j] < 0
        // then t[i..k] > 0 && t[k..j] < 0 for any k = i..j
        int canCompleteCircuit(const vector<int> &gas, const vector<int> &cost)
        {
            size_t i = 0;
            while (i < gas.size())
            {
                int t = 0;
                size_t j = 0;
                while (j < gas.size())
                {
                    int k = (i + j) % gas.size();
                    t = t + gas[k] - cost[k];
                    if (t < 0)
                        break;
                    j++;
                }
                if (j == gas.size())
                    return i;
                i = i + j + 1;
            }
            return -1;
        }
        int canCompleteCircuit2(const vector<int> &gas, const vector<int> &cost)
        {
            size_t s = 0;
            while (s < gas.size())
            {
                size_t i = s;
                int t = 0;
                size_t j;
                while (t >= 0 && (i - s) < gas.size())
                {
                    j = (i++) % gas.size();
                    t += (gas[j] - cost[j]);
                }
                if (t >= 0)
                    return s;
                s = i;
            }
            return -1;
        }

        // 135. Candy
        // There are N children standing in a line. Each child is assigned a rating
        // value. You are giving candies to these children subjected to the following
        // requirements: Each child must have at least one candy. Children with a higher
        // rating get more candies than their neighbors. What is the minimum candies you
        // must give? Example 1: Input: [1,0,2] Output: 5 Explanation: You can allocate
        // to the first, second and third child with 2, 1, 2 candies respectively.
        // Example 2:
        // Input: [1,2,2]
        // Output: 4
        // Explanation: You can allocate to the first, second and third child with 1, 2,
        // 1 candies respectively. The third child gets 1 candy because it satisfies the
        // above two conditions.
        int candy(const vector<int> &ratings)
        {
            vector<int> c(ratings.size(), 1);
            for (int i = 1; i < (int)c.size(); i++)
            {
                if (ratings[i - 1] < ratings[i])
                    c[i] = c[i - 1] + 1;
            }
            int t = c[c.size() - 1];
            for (int i = c.size() - 2; i >= 0; i--)
            {
                if (ratings[i] > ratings[i + 1] && c[i] <= c[i + 1])
                    c[i] = c[i + 1] + 1;
                t += c[i];
            }
            return t;
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