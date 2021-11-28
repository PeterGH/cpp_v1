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
        int maxProfit2(const vector<int> &prices)
        {
            if (prices.empty())
                return 0;
            int min = prices[0];
            int profit = 0;
            for (size_t i = 1; i < prices.size(); i++)
            {
                if (prices[i] - min > profit)
                {
                    profit = prices[i] - min;
                }
                else if (prices[i] < min)
                {
                    min = prices[i];
                }
            }
            return profit;
        }
        void maxProfit(const int *input, int length, int &buy, int &sell, int &profit)
        {
            buy = 0;
            sell = 0;
            profit = 0;
            stack<int>
                sellCandidates; // track the increasing values from end to beginning
            sellCandidates.push(length - 1);
            for (int i = length - 2; i > 0; i--)
            {
                if (input[i] >= input[sellCandidates.top()])
                {
                    // i is the possible sell date, because
                    // other dates later than i have less stock values
                    sellCandidates.push(i);
                }
            }
            int min = 0;
            for (int i = 0; i < length - 1; i++)
            {
                if (i == 0 || input[i] < input[min])
                {
                    min = i;
                    while (min >= sellCandidates.top())
                    {
                        // i may be way later than top candidates
                        sellCandidates.pop();
                    }
                    int diff = input[sellCandidates.top()] - input[min];
                    if (diff > profit)
                    {
                        buy = min;
                        sell = sellCandidates.top();
                        profit = diff;
                    }
                }
            }
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
        void maxProfitII2(const int *input, int length, vector<int> &buy,
                          vector<int> &sell, vector<int> &profit)
        {
            if (input == nullptr || length < 2)
                return;
            int i = 0;
            int j = 0;
            while (j < length)
            {
                while (j + 1 < length && input[j + 1] >= input[j])
                    j++;
                if (i < j)
                {
                    // input[i..j] is increasing
                    buy.push_back(i);
                    sell.push_back(j);
                    profit.push_back(input[j] - input[i]);
                }
                i = j + 1;
                j++;
            }
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
        //         = max(p[2, j - 1],
        //               p[j] + max(-p[j - 1] + p[1, j - 2],
        //                          -p[j - 2] + p[1, j - 3],
        //                          ......
        //                          -p[2] + p[1, 1]]))
        // p[2, j - 1] = max(p[2, j - 2],
        //                   p[j - 1] - p[j - 2] + p[1, j - 3],
        //                   p[j - 1] - p[j - 3] + p[1, j - 4],
        //                   ......
        //                   p[j - 1] - p[2] + p[1, 1])
        // p[1, j] = max(p[1, j - 1],
        //               p[j] - p[j - 1],
        //               p[j] - p[j - 2],
        //               ......
        //               p[j] - p[1],
        //               p[j] - p[0])
        //         = max(p[1, j - 1],
        //               p[j] + max(-p[j - 1],
        //                          -p[j - 2],
        //                          ......
        //                          -p[1],
        //                          -p[0]))
        // p[1, j - 1] = max(p[1, j - 2],
        //                   p[j - 1] - p[j - 2],
        //                   p[j - 1] - p[j - 3],
        //                   ......
        //                   p[j - 1] - p[1],
        //                   p[j - 1] - p[0])
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
                    // ensure i is the minimal in the range [sell2, j]
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

        // 136. Single Number
        // Given a non-empty array of integers, every element appears twice except for
        // one. Find that single one. Note: Your algorithm should have a linear runtime
        // complexity. Could you implement it without using extra memory?
        // Example 1:
        // Input: [2,2,1]
        // Output: 1
        // Example 2:
        // Input: [4,1,2,1,2]
        // Output: 4
        int singleNumber(const vector<int> &nums)
        {
            int r = 0;
            for_each(nums.begin(), nums.end(), [&](int n)
                     { r ^= n; });
            return r;
        }
        int singleNumber2(const vector<int> &nums)
        {
            return accumulate(nums.cbegin(), nums.cend(), 0, [&](int x, int n) -> int
                              { return x ^ n; });
        }

        // 137. Single Number II
        // Given a non-empty array of integers, every element appears three times except
        // for one, which appears exactly once. Find that single one. Note: Your
        // algorithm should have a linear runtime complexity. Could you implement it
        // without using extra memory? Example 1: Input: [2,2,3,2] Output: 3 Example 2:
        // Input: [0,1,0,1,0,1,99]
        // Output: 99
        int singleNumberII(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int n = 0;
            int bits = 8 * sizeof(int);
            for (int i = 0; i < bits; i++)
            {
                int count = 0;
                for (int j = 0; j < length; j++)
                    count += ((nums[j] >> i) & 0x1);
                n |= ((count % 3) << i);
            }
            return n;
        }
        int singleNumberII2(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int o0 = ~0; // positions that bit 1 occurred 0 or 3 times
            int o1 = 0;  // positions that bit 1 occurred 1 time
            int o2 = 0;  // positions that bit 1 occurred 2 times
            int t = 0;
            for (int i = 0; i < length; i++)
            {
                t = o2; // keep o2 temporarily to calculate o0 later
                o2 = (o1 & nums[i]) |
                     (o2 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // second time due to input[i], and keep the
                                      // positions that bit 1 already occurred two times
                                      // and not affected by input[i]
                o1 = (o0 & nums[i]) |
                     (o1 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // first time due to input[i], and keep the
                                      // positions that bit 1 already occurred one time
                                      // and not affected by input[i]
                o0 = (t & nums[i]) |
                     (o0 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // third time due to input[i], and keep the
                                      // positions that bit 1 already occurred zero or
                                      // three times and not affected by input[i]
            }
            return o1;
        }
        int singleNumberII3(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int o1 = 0; // positions that bit 1 occurred 0 or 3 times
            int o2 = 0; // positions that bit 1 occurred 1 time
            int o3 = 0; // positions that bit 1 occurred 2 times
            for (int i = 0; i < length; i++)
            {
                o2 |= o1 & nums[i];
                o1 ^= nums[i];
                o3 = o1 & o2;
                o1 &= ~o3;
                o2 &= ~o3;
            }
            return o1;
        }

        class NodeWithRandomLink
        {
        public:
            struct Node
            {
                int val;
                Node *next;
                Node *random;

                Node(int _val)
                {
                    val = _val;
                    next = nullptr;
                    random = nullptr;
                }
            };
            // 138. Copy List with Random Pointer
            // A linked list is given such that each node contains an additional random
            // pointer which could point to any node in the list or null. Return a deep
            // copy of the list. The Linked List is represented in the input/output as a
            // list of n nodes. Each node is represented as a pair of [val, random_index]
            // where: val: an integer representing Node.val, and random_index: the index
            // of the node (range from 0 to n-1) where random pointer points to, or null
            // if it does not point to any node.
            // Example 1:
            // Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
            // Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
            // Example 2:
            // Input: head = [[1,1],[2,1]]
            // Output: [[1,1],[2,1]]
            // Example 3:
            // Input: head = [[3,null],[3,0],[3,null]]
            // Output: [[3,null],[3,0],[3,null]]
            // Example 4:
            // Input: head = []
            // Output: []
            // Explanation: Given linked list is empty (null pointer), so return null.
            // Constraints: -10000 <= Node.val <= 10000. Node.random is null or pointing
            // to a node in the linked list. Number of Nodes will not exceed 1000.
            Node *copyRandomList(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy =
                    [&](Node *n) -> Node *
                {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) == m.end())
                    {
                        m[n] = new Node(n->val);
                        m[n]->next = copy(n->next);
                        m[n]->random = copy(n->random);
                    }
                    return m[n];
                };
                return copy(head);
            }
            Node *copyRandomList2(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy = [&](Node *n) -> Node *
                {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) != m.end())
                        return m[n];
                    Node *c = new Node(n->val);
                    m[n] = c; // save it before copying next and random
                    c->next = copy(n->next);
                    c->random = copy(n->random);
                    return c;
                };
                return copy(head);
            }
            Node *copyRandomList3(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy = [&](Node *n) -> Node *
                {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) == m.end())
                        m[n] = new Node(n->val);
                    return m[n];
                };
                Node *n = head;
                while (n != nullptr)
                {
                    Node *c = copy(n);
                    c->next = copy(n->next);
                    c->random = copy(n->random);
                    n = n->next;
                }
                return head == nullptr ? nullptr : m[head];
            }
            Node *copyRandomList4(Node *head)
            {
                Node *n = head;
                while (n != nullptr)
                {
                    Node *c = new Node(n->val);
                    c->next = n->next;
                    n->next = c;
                    n = c->next;
                }
                n = head;
                while (n != nullptr)
                {
                    if (n->random != nullptr)
                        n->next->random = n->random->next;
                    n = n->next->next;
                }
                Node *h = nullptr;
                Node *t = nullptr;
                n = head;
                while (n != nullptr)
                {
                    if (h == nullptr)
                        h = n->next;
                    else
                        t->next = n->next;
                    t = n->next;
                    n->next = t->next;
                    t->next = nullptr;
                    n = n->next;
                }
                return h;
            }
        };

        // 139. Word Break
        // Given a non-empty string s and a dictionary wordDict containing a list of
        // non-empty words, determine if s can be segmented into a space-separated
        // sequence of one or more dictionary words. Note: The same word in the
        // dictionary may be reused multiple times in the segmentation. You may assume
        // the dictionary does not contain duplicate words.
        // Example 1:
        // Input: s = "leetcode", wordDict = ["leet", "code"]
        // Output: true
        // Explanation: Return true because "leetcode" can be segmented as "leet code".
        // Example 2:
        // Input: s = "applepenapple", wordDict = ["apple", "pen"]
        // Output: true
        // Explanation: Return true because "applepenapple" can be segmented as "apple
        // pen apple". Note that you are allowed to reuse a dictionary word. Example 3:
        // Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
        // Output: false
        bool wordBreak(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)>
                same = [&](size_t i, const string &w) -> bool
            {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            map<size_t, bool> m;
            function<bool(size_t)> solve = [&](size_t i) -> bool
            {
                if (m.find(i) != m.end())
                    return m[i];
                if (i == s.size())
                    m[i] = true;
                else if (i > s.size())
                    m[i] = false;
                else
                {
                    bool match = false;
                    for (size_t j = 0; j < wordDict.size(); j++)
                    {
                        if (same(i, wordDict[j]) && solve(i + wordDict[j].size()))
                        {
                            match = true;
                            break;
                        }
                    }
                    m[i] = match;
                }
                return m[i];
            };
            return solve(0);
        }
        bool wordBreak2(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)>
                same = [&](size_t i, const string &w) -> bool
            {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            set<size_t> m;
            queue<size_t> q;
            q.push(0);
            while (!q.empty())
            {
                size_t i = q.front();
                q.pop();
                for (size_t j = 0; j < wordDict.size(); j++)
                {
                    if (same(i, wordDict[j]))
                    {
                        if (i + wordDict[j].size() == s.size())
                            return true;
                        if (m.find(i + wordDict[j].size()) == m.end())
                            q.push(i + wordDict[j].size());
                    }
                }
                m.insert(i);
            }
            return false;
        }
        bool wordBreak3(const string &s, const vector<string> &wordDict)
        {
            if (wordDict.empty())
                return false;
            size_t minLength = wordDict[0].size();
            size_t maxLength = wordDict[0].size();
            for (size_t i = 1; i < wordDict.size(); i++)
            {
                if (wordDict[i].size() < minLength)
                    minLength = wordDict[i].size();
                if (wordDict[i].size() > maxLength)
                    maxLength = wordDict[i].size();
            }
            map<size_t, bool> breakable;
            function<bool(size_t)> solve = [&](size_t i) -> bool
            {
                if (breakable.find(i) != breakable.end())
                    return breakable[i];
                breakable[i] = false;
                if (i == s.size())
                {
                    breakable[i] = true;
                }
                else
                {
                    for (size_t j = minLength; j <= min(maxLength, s.size() - i); j++)
                    {
                        auto it =
                            find(wordDict.begin(), wordDict.end(), s.substr(i, j));
                        if (it != wordDict.end())
                        {
                            if (breakable.find(i + j) == breakable.end())
                                solve(i + j);
                            if (breakable[i + j])
                            {
                                breakable[i] = true;
                                break;
                            }
                        }
                    }
                }
                return breakable[i];
            };
            return solve(0);
        }

        // 140. Word Break II
        // Given a non-empty string s and a dictionary wordDict containing a list of
        // non-empty words, add spaces in s to construct a sentence where each word is
        // a valid dictionary word. Return all such possible sentences. Note: The same
        // word in the dictionary may be reused multiple times in the segmentation. You
        // may assume the dictionary does not contain duplicate words.
        // Example 1:
        // Input:
        // s = "catsanddog"
        // wordDict = ["cat", "cats", "and", "sand", "dog"]
        // Output:
        // [
        //   "cats and dog",
        //   "cat sand dog"
        // ]
        // Example 2:
        // Input:
        // s = "pineapplepenapple"
        // wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
        // Output:
        // [
        //   "pine apple pen apple",
        //   "pineapple pen apple",
        //   "pine applepen apple"
        // ]
        // Explanation: Note that you are allowed to reuse a dictionary word.
        // Example 3:
        // Input:
        // s = "catsandog"
        // wordDict = ["cats", "dog", "sand", "and", "cat"]
        // Output:
        // []
        vector<string> wordBreakII(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)>
                same = [&](size_t i, const string &w) -> bool
            {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            map<size_t, vector<string>> m;
            function<void(size_t)> solve = [&](size_t i)
            {
                if (i > s.size() || m.find(i) != m.end())
                    return;
                m[i] = {};
                if (i == s.size())
                    return;
                for (size_t j = 0; j < wordDict.size(); j++)
                {
                    if (same(i, wordDict[j]))
                    {
                        size_t k = i + wordDict[j].size();
                        if (k == s.size())
                        {
                            m[i].push_back(wordDict[j]);
                        }
                        else
                        {
                            solve(k);
                            for_each(m[k].begin(), m[k].end(), [&](string &r)
                                     {
                                         string r1 = wordDict[j];
                                         r1.append(1, ' ');
                                         r1.append(r);
                                         m[i].push_back(r1);
                                     });
                        }
                    }
                }
            };
            solve(0);
            return m[0];
        }
        vector<string> wordBreakII2(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)>
                same = [&](size_t i, const string &w) -> bool
            {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            vector<string> results;
            queue<pair<size_t, string>> q;
            q.push(make_pair(0, string()));
            while (!q.empty())
            {
                pair<size_t, string> p = q.front();
                q.pop();
                for (size_t i = 0; i < wordDict.size(); i++)
                {
                    if (same(p.first, wordDict[i]))
                    {
                        size_t k = p.first + wordDict[i].size();
                        string r = p.second;
                        if (!r.empty())
                            r.append(1, ' ');
                        r.append(wordDict[i]);
                        if (k == s.size())
                            results.push_back(r);
                        else
                            q.push(make_pair(k, r));
                    }
                }
            }
            return results;
        }

        // 141. Linked List Cycle
        // Given a linked list, determine if it has a cycle in it. To represent a cycle
        // in the given linked list, we use an integer pos which represents the position
        // (0-indexed) in the linked list where tail connects to. If pos is -1, then
        // there is no cycle in the linked list. Example 1: Input: head = [3,2,0,-4],
        // pos = 1 Output: true Explanation: There is a cycle in the linked list, where
        // tail connects to the second node. Example 2: Input: head = [1,2], pos = 0
        // Output: true
        // Explanation: There is a cycle in the linked list, where tail connects to the
        // first node. Example 3: Input: head = [1], pos = -1 Output: false Explanation:
        // There is no cycle in the linked list. Follow up: Can you solve it using O(1)
        // (i.e. constant) memory?
        bool hasCycle(ListNode *head)
        {
            if (head == nullptr)
                return false;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    return true;
            }
            return false;
        }
        bool hasCycle2(ListNode *head)
        {
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                p = p->next;
                q = q->next;
                q = q->next;
                if (p == q)
                    return true;
            }
            return false;
        }

        // 142. Linked List Cycle II
        // Given a linked list, return the node where the cycle begins. If there is no
        // cycle, return null. To represent a cycle in the given linked list, we use an
        // integer pos which represents the position (0-indexed) in the linked list
        // where tail connects to. If pos is -1, then there is no cycle in the linked
        // list. Note: Do not modify the linked list. Example 1: Input: head =
        // [3,2,0,-4], pos = 1 Output: tail connects to node index 1 Explanation: There
        // is a cycle in the linked list, where tail connects to the second node.
        // Example 2:
        // Input: head = [1,2], pos = 0
        // Output: tail connects to node index 0
        // Explanation: There is a cycle in the linked list, where tail connects to the
        // first node. Example 3: Input: head = [1], pos = -1 Output: no cycle
        // Explanation: There is no cycle in the linked list.
        // Follow-up: Can you solve it without using extra space?
        ListNode *detectCycle(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    break;
            }
            if (q->next == nullptr || q->next->next == nullptr)
                return nullptr;
            q = head;
            while (q != p)
            {
                p = p->next;
                q = q->next;
            }
            return q;
        }
        ListNode *detectCycle2(ListNode *head)
        {
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    break;
            }
            if (q == nullptr || q->next == nullptr)
                return nullptr;
            p = head;
            while (p != q)
            {
                p = p->next;
                q = q->next;
            }
            return p;
        }

        // 143. Reorder List
        // Given a singly linked list L: L0->L1->......->Ln-1->Ln,
        // reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->......
        // You may not modify the values in the list's nodes, only nodes itself may be
        // changed. Example 1: Given 1->2->3->4, reorder it to 1->4->2->3. Example 2:
        // Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
        void reorderList(ListNode *head)
        {
            if (head == nullptr)
                return;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
            }
            if (p == q)
                return; // List has only one or two nodes
            // Now p is the (1 + k)-th node
            // q is the (1 + 2k)-th node
            // The list has (1 + 2k) nodes or (2 + 2k) nodes
            // Break after p
            q = p->next;
            p->next = nullptr;
            // Reverse list at q
            p = q;
            q = p->next;
            p->next = nullptr;
            while (q != nullptr)
            {
                ListNode *t = q->next;
                q->next = p;
                p = q;
                q = t;
            }
            // Merge the list at head and the list at p
            q = head;
            while (p != nullptr)
            {
                ListNode *t = p->next;
                p->next = q->next;
                q->next = p;
                q = p->next;
                p = t;
            }
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
        vector<int> postorderTraversal5(TreeNode *root)
        {
            vector<int> output;
            if (root == nullptr)
                return output;
            stack<TreeNode *> s;
            TreeNode *last = nullptr;
            s.push(root);
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if (n->right == nullptr)
                {
                    if (n->left == nullptr || n->left == last)
                    {
                        output.push_back(n->val);
                        s.pop();
                        last = n;
                    }
                    else
                    {
                        s.push(n->left);
                    }
                }
                else if (n->right == last)
                {
                    output.push_back(n->val);
                    s.pop();
                    last = n;
                }
                else
                {
                    s.push(n->right);
                    if (n->left != nullptr && n->left != last)
                    {
                        s.push(n->left);
                    }
                }
            }
            return output;
        }
        vector<int> postorderTraversal6(TreeNode *root)
        {
            vector<int> output;
            if (root == nullptr)
                return output;
            stack<TreeNode *> s;
            TreeNode *last = nullptr;
            s.push(root);
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if ((n->right != nullptr && n->right == last) || (n->right == nullptr && (n->left == nullptr || n->left == last)))
                {
                    output.push_back(n->val);
                    last = n;
                    s.pop();
                }
                else
                {
                    if (n->right != nullptr)
                    {
                        s.push(n->right);
                    }
                    if (n->left != nullptr)
                    {
                        s.push(n->left);
                    }
                }
            }
            return output;
        }

        // 146. LRU Cache
        // Design and implement a data structure for Least Recently Used (LRU) cache.
        // It should support the following operations: get and put.
        // get(key) - Get the value (will always be positive) of the key if the key
        // exists in the cache, otherwise return -1.
        // put(key, value) - Set or insert the value if the key is not already present.
        // When the cache reached its capacity, it should invalidate the least recently
        // used item before inserting a new item.
        // The cache is initialized with a positive capacity.
        // Follow up: Could you do both operations in O(1) time complexity?
        // Example:
        // LRUCache cache = new LRUCache( 2 /* capacity */ );
        // cache.put(1, 1);
        // cache.put(2, 2);
        // cache.get(1);       // returns 1
        // cache.put(3, 3);    // evicts key 2
        // cache.get(2);       // returns -1 (not found)
        // cache.put(4, 4);    // evicts key 1
        // cache.get(1);       // returns -1 (not found)
        // cache.get(3);       // returns 3
        // cache.get(4);       // returns 4
        class LRUCache
        {
        private:
            int _capacity;
            struct Item
            {
                int key;
                int value;
                struct Item *prev;
                struct Item *next;
                Item(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
            } * head, *tail;
            map<int, struct Item *> keys;
            void MoveFront(struct Item *p)
            {
                if (p == this->head)
                    return;
                if (p == this->tail)
                {
                    this->tail = p->prev;
                    this->tail->next = nullptr;
                }
                else
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                }
                p->next = this->head;
                this->head->prev = p;
                p->prev = nullptr;
                this->head = p;
            }

        public:
            LRUCache(int capacity)
                : _capacity(capacity), head(nullptr), tail(nullptr) {}
            ~LRUCache(void)
            {
                while (this->head != nullptr)
                {
                    struct Item *p = this->head;
                    this->head = this->head->next;
                    delete p;
                }
            }
            int Get(int key)
            {
                if (this->keys.find(key) == this->keys.end())
                {
                    return -1;
                }
                else
                {
                    struct Item *p = this->keys[key];
                    MoveFront(p);
                    return p->value;
                }
            }
            void Set(int key, int value)
            {
                struct Item *p;
                if (this->keys.find(key) == this->keys.end())
                {
                    if ((int)this->keys.size() == this->_capacity)
                    {
                        int k = this->tail->key;
                        if (this->head == this->tail)
                        {
                            delete this->head;
                            this->head = nullptr;
                            this->tail = nullptr;
                        }
                        else
                        {
                            p = this->tail;
                            this->tail = p->prev;
                            this->tail->next = nullptr;
                            delete p;
                        }
                        this->keys.erase(k);
                    }
                    p = new struct Item(key, value);
                    if (this->head == nullptr)
                    {
                        this->head = p;
                        this->tail = p;
                    }
                    else
                    {
                        p->next = this->head;
                        this->head->prev = p;
                        this->head = p;
                    }
                    this->keys[key] = p;
                }
                else
                {
                    // Whether or not to change the value,
                    // it counts as an access.
                    p = this->keys[key];
                    p->value = value;
                    MoveFront(p);
                }
            }
        };

        // 147. Insertion Sort List
        // Sort a linked list using insertion sort. A graphical example of insertion
        // sort. The partial sorted list (black) initially contains only the first
        // element in the list. With each iteration one element (red) is removed from
        // the input data and inserted in-place into the sorted list. Algorithm of
        // Insertion Sort: Insertion sort iterates, consuming one input element each
        // repetition, and growing a sorted output list. At each iteration, insertion
        // sort removes one element from the input data, finds the location it belongs
        // within the sorted list, and inserts it there. It repeats until no input
        // elements remain. Example 1: Input: 4->2->1->3 Output: 1->2->3->4 Example 2:
        // Input: -1->5->3->4->0
        // Output: -1->0->3->4->5
        ListNode *insertionSortList(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *t = head; // tail of sorted
            ListNode *p = head->next;
            while (p != nullptr)
            {
                ListNode *q = p;
                p = q->next;
                if (q->val < head->val)
                {
                    t->next = p;
                    q->next = head;
                    head = q;
                    continue;
                }
                ListNode *s = head;
                while (s != t && s->next->val <= q->val)
                {
                    s = s->next;
                }
                if (s == t)
                {
                    t = q;
                }
                else
                {
                    t->next = p;
                    q->next = s->next;
                    s->next = q;
                }
            }
            return head;
        }
        ListNode *insertionSortList2(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return head;
            ListNode *p = head;
            while (p->next != nullptr)
            {
                if (p->val <= p->next->val)
                {
                    p = p->next;
                }
                else
                {
                    ListNode *q = p->next;
                    p->next = q->next;
                    q->next = nullptr;
                    if (q->val < head->val)
                    {
                        q->next = head;
                        head = q;
                    }
                    else
                    {
                        ListNode *s = head;
                        while (s != p && s->next != nullptr && s->next->val <= q->val)
                        {
                            s = s->next;
                        }
                        q->next = s->next;
                        s->next = q;
                    }
                }
            }
            return head;
        }

        // 148. Sort List
        // Sort a linked list in O(n log n) time using constant space complexity.
        // Example 1:
        // Input: 4->2->1->3
        // Output: 1->2->3->4
        // Example 2:
        // Input: -1->5->3->4->0
        // Output: -1->0->3->4->5
        ListNode *sortList(ListNode *head)
        {
            function<ListNode *(ListNode *, ListNode *)> merge =
                [&](ListNode *p, ListNode *q) -> ListNode *
            {
                if (p == nullptr)
                    return q;
                if (q == nullptr)
                    return p;
                ListNode *h = nullptr;
                ListNode *t = nullptr;
                while (p != nullptr && q != nullptr)
                {
                    if (p->val <= q->val)
                    {
                        if (h == nullptr)
                            h = p;
                        else
                            t->next = p;
                        t = p;
                        p = p->next;
                    }
                    else
                    {
                        if (h == nullptr)
                            h = q;
                        else
                            t->next = q;
                        t = q;
                        q = q->next;
                    }
                }
                if (p == nullptr)
                    t->next = q;
                else
                    t->next = p;
                return h;
            };
            function<ListNode *(ListNode *)> sort = [&](ListNode *h) -> ListNode *
            {
                if (h == nullptr || h->next == nullptr)
                    return h;
                ListNode *p = h;
                ListNode *q = h;
                while (q->next != nullptr && q->next->next != nullptr)
                {
                    p = p->next;
                    q = q->next->next;
                }
                q = p->next;
                p->next = nullptr;
                h = sort(h);
                q = sort(q);
                return merge(h, q);
            };
            return sort(head);
        }

        // 149. Max Points on a Line
        // Given n points on a 2D plane, find the maximum number of points that lie on
        // the same straight line.
        // Example 1:
        // Input: [[1,1],[2,2],[3,3]]
        // Output: 3
        // Explanation:
        // ^
        // |
        // |        o
        // |     o
        // |  o
        // +------------->
        // 0  1  2  3  4
        // Example 2:
        // Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
        // Output: 4
        // Explanation:
        // ^
        // |
        // |  o
        // |     o        o
        // |        o
        // |  o        o
        // +------------------->
        // 0  1  2  3  4  5  6
        // NOTE: input types have been changed on April 15, 2019. Please reset to
        // default code definition to get new method signature.
        int maxPoints(const vector<vector<int>> &points)
        {
            if (points.size() < 2)
                return (int)points.size();
            function<int(int, int)> gcd = [&](int a, int b) -> int
            {
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
            function<pair<int, int>(const vector<int> &, const vector<int> &)> slope =
                [&](const vector<int> &p, const vector<int> &q) -> pair<int, int>
            {
                if (p[0] == q[0])
                    return make_pair(0, 1);
                if (p[1] == q[1])
                    return make_pair(1, 0);
                int g = gcd(abs(q[0] - p[0]), abs(q[1] - p[1]));
                int x = (q[0] - p[0]) / g;
                int y = (q[1] - p[1]) / g;
                if (y < 0)
                {
                    x = -x;
                    y = -y;
                }
                // cout << "slope((" << p[0] << ", " << p[1] << "), (" << q[0] << ", "
                //      << q[1] << ")) = "
                //      << "(" << x << ", " << y << ")" << endl;
                // cout << "gcd = " << g << endl;
                return make_pair(x, y);
            };
            int mc = 0;
            for (size_t i = 0; i < points.size(); i++)
            {
                // cout << "Start (" << points[i][0] << ", " << points[i][1] << ")"
                //      << endl;
                map<pair<int, int>, int> m;
                int n = 1; // count duplicates of points[i]
                int c = 0; // count other points on the same line as points[i]
                for (size_t j = 0; j < points.size(); j++)
                {
                    if (j == i)
                        continue;
                    if (points[j][0] == points[i][0] && points[j][1] == points[i][1])
                        n++;
                    else
                    {
                        pair<int, int> k = slope(points[i], points[j]);
                        if (m.find(k) == m.end())
                            m[k] = 1;
                        else
                            m[k]++;
                        c = max(c, m[k]);
                    }
                }
                mc = max(mc, c + n);
                // cout << "m = {" << endl;
                // for_each(m.cbegin(), m.cend(), [&](const pair<pair<int, int>, int>
                // &p) {
                //     cout << "(" << p.first.first << ", " << p.first.second
                //          << ") : " << p.second << endl;
                // });
                // cout << "}" << endl;
            }
            return mc;
        }
        int maxPoints2(vector<vector<int>> &points)
        {
            if (points.size() <= 1)
                return points.size();
            function<int(int, int)> gcd = [&](int a, int b) -> int
            {
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
            function<pair<int, int>(const vector<int> &, const vector<int> &)>
                get_slope =
                    [&](const vector<int> &p, const vector<int> &q) -> pair<int, int>
            {
                if (p[0] == q[0])
                    return make_pair(0, 1);
                if (p[1] == q[1])
                    return make_pair(1, 0);
                int g = gcd(abs(q[0] - p[0]), abs(q[1] - p[1]));
                int x = (q[0] - p[0]) / g;
                int y = (q[1] - p[1]) / g;
                if (y < 0)
                {
                    x = -x;
                    y = -y;
                }
                // cout << "slope((" << p[0] << ", " << p[1] << "), (" << q[0] << ", "
                //      << q[1] << ")) = "
                //      << "(" << x << ", " << y << ")" << endl;
                // cout << "gcd = " << g << endl;
                return make_pair(x, y);
            };
            // Group pairs of points by slopes. The points with the same slope
            // are potentially on the same lines.
            // Use comparer of IntPoint
            sort(points.begin(), points.end(),
                 [&](const vector<int> &l, const vector<int> &r)
                 {
                     if (l[0] == r[0])
                         return l[1] < r[1];
                     return l[0] < r[0];
                 });
            map<vector<int>, int> dup;
            map<pair<int, int>, vector<pair<vector<int>, vector<int>>>> slopes;
            for (size_t i = 0; i < points.size(); i++)
            {
                if (dup.find(points[i]) == dup.end())
                    dup[points[i]] = 1;
                else
                    dup[points[i]]++;
                for (size_t j = i + 1; j < points.size(); j++)
                {
                    if (points[i] == points[j])
                    {
                        // Ignore duplication
                        continue;
                    }
                    pair<int, int> slope = get_slope(points[i], points[j]);
                    if (slopes.find(slope) == slopes.end())
                        slopes[slope] = vector<pair<vector<int>, vector<int>>>{};
                    slopes[slope].push_back(make_pair(points[i], points[j]));
                }
            }
            int max = 0;
            for (map<pair<int, int>, vector<pair<vector<int>, vector<int>>>>::iterator
                     slope = slopes.begin();
                 slope != slopes.end(); slope++)
            {
                // lines of the same slope
                vector<set<vector<int>>> lines;
                for_each(slope->second.begin(), slope->second.end(),
                         [&](pair<vector<int>, vector<int>> &s)
                         {
                             // s is a line segament ending with two points.
                             // Check and assign the points into the set of points on
                             // the same line.
                             // first is the line containing the first point of segament
                             // s
                             vector<set<vector<int>>>::iterator first = lines.end();
                             // second is the line containing the second point of
                             // segament s
                             vector<set<vector<int>>>::iterator second = lines.end();
                             for (vector<set<vector<int>>>::iterator it = lines.begin();
                                  it != lines.end(); it++)
                             {
                                 // it refers to the set of points on the same line
                                 if (it->find(s.first) != it->end())
                                     first = it;
                                 if (it->find(s.second) != it->end())
                                     second = it;
                             }
                             if (first == lines.end() && second == lines.end())
                             {
                                 // Segament s is a new line
                                 set<vector<int>> line;
                                 line.insert(s.first);
                                 line.insert(s.second);
                                 lines.push_back(line);
                             }
                             else if (first == lines.end())
                             {
                                 second->insert(s.first);
                             }
                             else if (second == lines.end())
                             {
                                 first->insert(s.second);
                             }
                             else if (first == second)
                             {
                                 ;
                             }
                             else
                             {
                                 set<vector<int>> line;
                                 line.insert(first->begin(), first->end());
                                 line.insert(second->begin(), second->end());
                                 lines.erase(first);
                                 lines.erase(second);
                                 lines.push_back(line);
                             }
                         });
                for_each(lines.begin(), lines.end(), [&](set<vector<int>> &l)
                         {
                             int m = 0;
                             for_each(l.cbegin(), l.cend(),
                                      [&](const vector<int> &v)
                                      { m += dup[v]; });
                             if (m > max)
                                 max = m;
                         });
            }
            return max;
        }

        // 150. Evaluate Reverse Polish Notation
        // Evaluate the value of an arithmetic expression in Reverse Polish Notation.
        // Valid operators are +, -, *, /. Each operand may be an integer or another
        // expression. Note: Division between two integers should truncate toward zero.
        // The given RPN expression is always valid. That means the expression would
        // always evaluate to a result and there won't be any divide by zero operation.
        // Example 1:
        // Input: ["2", "1", "+", "3", "*"]
        // Output: 9
        // Explanation: ((2 + 1) * 3) = 9
        // Example 2:
        // Input: ["4", "13", "5", "/", "+"]
        // Output: 6
        // Explanation: (4 + (13 / 5)) = 6
        // Example 3:
        // Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
        // Output: 22
        // Explanation:
        //   ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
        // = ((10 * (6 / (12 * -11))) + 17) + 5
        // = ((10 * (6 / -132)) + 17) + 5
        // = ((10 * 0) + 17) + 5
        // = (0 + 17) + 5
        // = 17 + 5
        // = 22
        int evalRPN(const vector<string> &tokens)
        {
            stack<int> q;
            for_each(tokens.cbegin(), tokens.cend(), [&](const string &t)
                     {
                         if (t == "+")
                         {
                             int a = q.top();
                             q.pop();
                             int b = q.top();
                             q.pop();
                             q.push(b + a);
                         }
                         else if (t == "-")
                         {
                             int a = q.top();
                             q.pop();
                             int b = q.top();
                             q.pop();
                             q.push(b - a);
                         }
                         else if (t == "*")
                         {
                             int a = q.top();
                             q.pop();
                             int b = q.top();
                             q.pop();
                             q.push(b * a);
                         }
                         else if (t == "/")
                         {
                             int a = q.top();
                             q.pop();
                             int b = q.top();
                             q.pop();
                             q.push(b / a);
                         }
                         else
                         {
                             q.push(stoi(t));
                         }
                     });
            return q.top();
        }
        int evalRPN2(const vector<string> &tokens)
        {
            int n1;
            int n2;
            stack<int> nums;
            function<void(int &, int &)> pop = [&](int &m1, int &m2)
            {
                m2 = nums.top();
                nums.pop();
                m1 = nums.top();
                nums.pop();
            };
            for (size_t i = 0; i < tokens.size(); i++)
            {
                if (tokens[i].compare("+") == 0)
                {
                    pop(n1, n2);
                    nums.push(n1 + n2);
                }
                else if (tokens[i].compare("-") == 0)
                {
                    pop(n1, n2);
                    nums.push(n1 - n2);
                }
                else if (tokens[i].compare("*") == 0)
                {
                    pop(n1, n2);
                    nums.push(n1 * n2);
                }
                else if (tokens[i].compare("/") == 0)
                {
                    pop(n1, n2);
                    nums.push(n1 / n2);
                }
                else
                {
                    nums.push(atoi(tokens[i].c_str()));
                }
            }
            return nums.top();
        }

        // 151. Reverse Words in a String
        // Given an input string, reverse the string word by word.
        // Example 1:
        // Input: "the sky is blue"
        // Output: "blue is sky the"
        // Example 2:
        // Input: "  hello world!  "
        // Output: "world! hello"
        // Explanation: Your reversed string should not contain leading or trailing
        // spaces. Example 3: Input: "a good   example" Output: "example good a"
        // Explanation: You need to reduce multiple spaces between two words to a single
        // space in the reversed string. Note: A word is defined as a sequence of
        // non-space characters. Input string may contain leading or trailing spaces.
        // However, your reversed string should not contain leading or trailing spaces.
        // You need to reduce multiple spaces between two words to a single space in the
        // reversed string. Follow up: For C programmers, try to solve it in-place in
        // O(1) extra space.
        string reverseWords(string s)
        {
            function<void()> compact = [&]()
            {
                int i = -1;
                for (int j = 0; j < (int)s.size(); j++)
                {
                    if (s[j] == ' ' && (i == -1 || s[i] == ' '))
                        continue;
                    if (++i < j)
                        s[i] = s[j];
                }
                if (i == -1 || s[i] != ' ')
                    i++;
                s.resize(i);
            };
            function<void(int, int)> reverse = [&](int i, int j)
            {
                while (i < j)
                    swap(s[i++], s[j--]);
            };
            compact();
            reverse(0, (int)s.size() - 1);
            int i = 0;
            int j = 0;
            while (j <= (int)s.size())
            {
                if (j == (int)s.size() || s[j] == ' ')
                {
                    reverse(i, j - 1);
                    i = j + 1;
                }
                j++;
            }
            return s;
        }
        string reverseWords2(const string &s)
        {
            string r(s);
            int i = -1;
            int j;
            for (j = 0; j < (int)r.size(); j++)
            {
                if (r[j] == ' ' && (i < 0 || r[i] == ' '))
                    continue;
                i++;
                if (i != j)
                    r[i] = r[j];
            }
            if (i >= 0 && r[i] == ' ')
                i--;
            r.resize(i + 1);
            i = 0;
            while (i < (int)r.size())
            {
                if (r[i] != ' ')
                {
                    j = i;
                    while (j < (int)r.size() && r[j] != ' ')
                        j++;
                    int k = j;
                    j--;
                    while (i < j)
                    {
                        swap(r[i], r[j]);
                        i++;
                        j--;
                    }
                    i = k;
                }
                i++;
            }
            i = 0;
            j = (int)r.size() - 1;
            while (i < j)
            {
                swap(r[i], r[j]);
                i++;
                j--;
            }
            return r;
        }
        void reverseWords3(string &s)
        {
            if (s.empty())
                return;
            // step 1: remove extra spaces
            int i = -1;
            size_t j = 0;
            while (j < s.length() && s[j] == ' ')
                j++;
            if (j == s.length())
            {
                s.resize(0);
                return;
            }
            while (j < s.length())
            {
                if (s[j] != ' ' || s[j - 1] != ' ')
                {
                    i++;
                    if (i < (int)j)
                        s[i] = s[j];
                }
                j++;
            }
            if (0 <= i && s[i] == ' ')
                i--;
            s.resize(i + 1);
            // step 2: reverse words
            function<void(int, int)> reverse = [&](int b, int e)
            {
                while (b < e)
                {
                    swap(s[b++], s[e--]);
                }
            };
            reverse(0, s.length() - 1);
            i = 0;
            j = 0;
            while (j <= s.length())
            {
                if (j == s.length() || s[j] == ' ')
                {
                    reverse(i, j - 1);
                    i = j + 1;
                }
                j++;
            }
        }

        // Reverse Words in a String III
        // Given a string, you need to reverse the order of characters in each word
        // within a sentence while still preserving whitespace and initial word order.
        // Example 1:
        // Input: "Let's take LeetCode contest"
        // Output: "s'teL ekat edoCteeL tsetnoc"
        // Note: In the string, each word is separated by single space and there will
        // not be any extra space in the string.
        string reverseWordsIII(string s)
        {
            int i = 0;
            while (i < (int)s.size())
            {
                if (s[i] != ' ')
                {
                    int j = i;
                    while (j < (int)s.size() && s[j] != ' ')
                        j++;
                    int k = j--;
                    while (i < j)
                        swap(s[i++], s[j--]);
                    i = k;
                }
                i++;
            }
            return s;
        }

        // 152. Maximum Product Subarray
        // Given an integer array nums, find the contiguous subarray within an array
        // (containing at least one number) which has the largest product.
        // Example 1:
        // Input: [2,3,-2,4]
        // Output: 6
        // Explanation: [2,3] has the largest product 6.
        // Example 2:
        // Input: [-2,0,-1]
        // Output: 0
        // Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
        int maxProduct(const vector<int> &nums)
        {
            long long maxProd = LLONG_MIN;
            long long maxNeg = LLONG_MIN;
            long long p = 1;
            for (size_t i = 0; i < nums.size(); i++)
            {
                p *= nums[i];
                if (p < 0)
                {
                    if (maxNeg == LLONG_MIN)
                    {
                        maxProd = max(maxProd, p);
                        maxNeg = p;
                    }
                    else
                    {
                        maxProd = max(maxProd, p / maxNeg);
                        maxNeg = max(maxNeg, p);
                    }
                }
                else
                {
                    maxProd = max(maxProd, p);
                    if (p == 0)
                    {
                        p = 1;
                        maxNeg = LLONG_MIN;
                    }
                }
            }
            return maxProd;
        }
        int maxProduct2(const vector<int> &nums)
        {
            long long maxNegative = LLONG_MIN;
            long long maxProd = LLONG_MIN;
            long long prod = 1;
            for (size_t i = 0; i < nums.size(); i++)
            {
                prod *= nums[i];
                if (prod < 0)
                {
                    if (maxNegative == LLONG_MIN)
                    {
                        maxProd = max(maxProd, prod);
                    }
                    else
                    {
                        maxProd = max(maxProd, prod / maxNegative);
                    }
                    maxNegative = max(maxNegative, prod);
                }
                else if (prod > 0)
                {
                    maxProd = max(maxProd, prod);
                }
                else
                {
                    maxProd = max(maxProd, prod);
                    maxNegative = LLONG_MIN;
                    prod = 1;
                }
            }
            return (int)maxProd;
        }
        int maxProduct3(const vector<int> &nums)
        {
            long long maxProd = LLONG_MIN;
            vector<long long> product(nums.begin(), nums.end());
            for (size_t l = 1; l <= nums.size(); l++)
            {
                for (size_t i = 0; i <= nums.size() - l; i++)
                {
                    if (l > 1)
                    {
                        product[i] *= nums[i + l - 1];
                    }
                    // if (product[i] > maxProd) {
                    //     cout << "prod[" << i << ".." << i + l - 1 << "] = " <<
                    //     product[i] << endl;
                    // }
                    maxProd = max(product[i], maxProd);
                }
            }
            return (int)maxProd;
        }

        // 153. Find Minimum in Rotated Sorted Array
        // Suppose an array sorted in ascending order is rotated at some pivot unknown
        // to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
        // Find the minimum element. You may assume no duplicate exists in the array.
        // Example 1:
        // Input: [3,4,5,1,2]
        // Output: 1
        // Example 2:
        // Input: [4,5,6,7,0,1,2]
        // Output: 0
        int findMin(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (m < h)
                {
                    if (nums[m] > e)
                        l = m + 1;
                    else
                        h = m;
                }
                else
                {
                    return nums[m];
                }
            }
            throw runtime_error("not found");
        }
        int findMin2(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > e)
                    l = m + 1;
                else
                    h = m;
            }
            return nums[l];
        }
        int findMin3(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > e)
                    l = m;
                else
                    h = m;
            }
            if (l <= h)
                return min(nums[l], nums[h]);
            throw runtime_error("not found");
        }
        int findMin4(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (nums[m] > nums[h])
                {
                    if (m + 1 == h)
                        m = h;
                    if (m == h)
                        break;
                    l = m;
                }
                else
                {
                    if (l == m)
                        break;
                    h = m;
                }
            }
            return nums[m];
        }
        int findMin5(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (nums[l] < nums[m])
                {
                    if (nums[m] < nums[h])
                        h = m - 1;
                    else
                        l = m + 1;
                }
                else if (nums[l] > nums[m])
                {
                    h = m;
                }
                else
                {
                    if (nums[m] < nums[h])
                        h = m;
                    else if (nums[m] > nums[h])
                        l = m + 1;
                    else
                        break;
                }
            }
            return nums[m];
        }

        // 154. Find Minimum in Rotated Sorted Array II
        // Suppose an array sorted in ascending order is rotated at some pivot unknown
        // to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
        // Find the minimum element. The array may contain duplicates.
        // Example 1:
        // Input: [1,3,5]
        // Output: 1
        // Example 2:
        // Input: [2,2,2,0,1]
        // Output: 0
        // Note: This is a follow up problem to Find Minimum in Rotated Sorted Array.
        // Would allow duplicates affect the run-time complexity? How and why?
        int findMinII(const vector<int> &nums)
        {
            int n = (int)nums.size();
            int e = nums[n - 1];
            function<int(int, int)> find = [&](int l, int h) -> int
            {
                int m;
                while (l < h)
                {
                    m = l + ((h - l) >> 1);
                    if (nums[m] < e)
                        h = m;
                    else if (nums[m] > e)
                        l = m + 1;
                    else
                        break;
                }
                if (l == h)
                    return nums[l];
                else if (l == m) // e.g. [1, 1]
                    return find(m + 1, h);
                else
                    return min(find(l, m - 1), find(m + 1, h));
            };
            return find(0, n - 1);
        }
        int findMinII2(const vector<int> &nums)
        {
            function<int(int, int)> find = [&](int l, int h) -> int
            {
                if (l == h)
                    return nums[l];
                if (l + 1 == h)
                    return min(nums[l], nums[h]);
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[h])
                    return find(m + 1, h);
                if (nums[m] < nums[h])
                    return find(l, m);
                if (nums[l] > nums[m])
                    return find(l, m);
                if (nums[l] < nums[m])
                    return find(l, m);
                return min(find(l, m - 1), find(m + 1, h));
            };
            return find(0, nums.size() - 1);
        }

        // 155. Min Stack
        // Design a stack that supports push, pop, top, and retrieving the minimum
        // element in constant time.
        // push(x) -- Push element x onto stack.
        // pop() -- Removes the element on top of the stack.
        // top() -- Get the top element.
        // getMin() -- Retrieve the minimum element in the stack.
        // Example:
        // MinStack minStack = new MinStack();
        // minStack.push(-2);
        // minStack.push(0);
        // minStack.push(-3);
        // minStack.getMin();   --> Returns -3.
        // minStack.pop();
        // minStack.top();      --> Returns 0.
        // minStack.getMin();   --> Returns -2.
        class MinStack
        {
        private:
            stack<int> q;
            stack<int> m;

        public:
            /** initialize your data structure here. */
            MinStack() {}
            void push(int x)
            {
                q.push(x);
                if (m.empty())
                    m.push(x);
                else
                    m.push(min(m.top(), x));
            }
            void pop()
            {
                q.pop();
                m.pop();
            }
            int top() { return q.top(); }
            int getMin() { return m.top(); }
        };

        // 160. Intersection of Two Linked Lists
        // Write a program to find the node at which the intersection of two singly
        // linked lists begins. For example, the following two linked lists: begin to
        // intersect at node c1.
        // Example 1:
        // Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5],
        // skipA = 2, skipB = 3
        // Output: Reference of the node with value = 8
        // Input Explanation: The intersected node's value is 8 (note that this must not
        // be 0 if the two lists intersect). From the head of A, it reads as
        // [4,1,8,4,5]. From the head of B, it reads as [5,0,1,8,4,5]. There are 2 nodes
        // before the intersected node in A; There are 3 nodes before the intersected
        // node in B. Example 2: Input: intersectVal = 2, listA = [0,9,1,2,4], listB =
        // [3,2,4], skipA = 3, skipB = 1 Output: Reference of the node with value = 2
        // Input Explanation: The intersected node's value is 2 (note that this must not
        // be 0 if the two lists intersect). From the head of A, it reads as
        // [0,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes
        // before the intersected node in A; There are 1 node before the intersected
        // node in B. Example 3: Input: intersectVal = 0, listA = [2,6,4], listB =
        // [1,5], skipA = 3, skipB = 2 Output: null Input Explanation: From the head of
        // A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two
        // lists do not intersect, intersectVal must be 0, while skipA and skipB can be
        // arbitrary values. Explanation: The two lists do not intersect, so return
        // null. Notes: If the two linked lists have no intersection at all, return
        // null. The linked lists must retain their original structure after the
        // function returns. You may assume there are no cycles anywhere in the entire
        // linked structure. Your code should preferably run in O(n) time and use only
        // O(1) memory.
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
        {
            ListNode *a = headA;
            ListNode *b = headB;
            while (a != nullptr && b != nullptr && a != b)
            {
                a = a->next;
                b = b->next;
                if (a == nullptr && b == nullptr)
                    break;
                if (a == nullptr)
                    a = headB;
                if (b == nullptr)
                    b = headA;
            }
            return (a == nullptr || b == nullptr) ? nullptr : a;
        }
        ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB)
        {
            ListNode *a = headA;
            ListNode *b = headB;
            while (a != nullptr && b != nullptr && a != b)
            {
                a = a->next;
                b = b->next;
                if (a == b)
                    return a;
                if (a == nullptr)
                    a = headB;
                if (b == nullptr)
                    b = headA;
            }
            return a == b ? a : nullptr;
        }
        ListNode *getIntersectionNode3(ListNode *headA, ListNode *headB)
        {
            function<int(ListNode *)> getLength = [&](ListNode *h) -> int
            {
                int i = 0;
                while (h != nullptr)
                {
                    i++;
                    h = h->next;
                }
                return i;
            };
            function<ListNode *(ListNode *, int)> advance = [&](ListNode *h,
                                                                int n) -> ListNode *
            {
                while (n > 0)
                {
                    h = h->next;
                    n--;
                }
                return h;
            };
            int la = getLength(headA);
            int lb = getLength(headB);
            ListNode *pa = headA;
            ListNode *pb = headB;
            if (la > lb)
                pa = advance(pa, la - lb);
            else
                pb = advance(pb, lb - la);
            while (pa != pb)
            {
                pa = pa->next;
                pb = pb->next;
            }
            return pa;
        }

        // 162. Find Peak Element
        // A peak element is an element that is greater than its neighbors. Given an
        // input array nums, where nums[i] != nums[i+1], find a peak element and return
        // its index. The array may contain multiple peaks, in that case return the
        // index to any one of the peaks is fine. You may imagine that
        // nums[-1] = nums[n] = -infinity.
        // Example 1:
        // Input: nums = [1,2,3,1]
        // Output: 2
        // Explanation: 3 is a peak element and your function should return the index
        // number 2. Example 2: Input: nums = [1,2,1,3,5,6,4] Output: 1 or 5
        // Explanation: Your function can return either index number 1 where the peak
        // element is 2, or index number 5 where the peak element is 6. Note: Your
        // solution should be in logarithmic complexity.
        int findPeakElement(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (m < h)
                {
                    if (nums[m] > nums[m + 1])
                        h = m;
                    else
                        l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            throw runtime_error("not found");
        }
        int findPeakElement2(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[m + 1])
                    h = m;
                else
                    l = m + 1;
            }
            return l == h ? l : -1;
        }
        int findPeakElement3(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[m + 1])
                    h = m;
                else
                    l = m;
            }
            if (l <= h)
            {
                if (nums[l] <= nums[h])
                    return h;
                else
                    return l;
            }
            throw runtime_error("not found");
        }
        int findPeakElement4(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (m == 0)
                {
                    if (nums[m] >= nums[m + 1])
                        return m;
                    l = m + 1;
                }
                else if (m == (int)nums.size() - 1)
                {
                    if (nums[m - 1] <= nums[m])
                        return m;
                    h = m - 1;
                }
                else if (nums[m - 1] <= nums[m] && nums[m] >= nums[m + 1])
                {
                    return m;
                }
                else if (nums[m - 1] < nums[m + 1])
                {
                    l = m + 1;
                }
                else
                {
                    h = m - 1;
                }
            }
            return l == h ? l : -1;
        }
        int findPeakElement5(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            if (nums.size() == 1)
                return 0;
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (m == 0)
                {
                    if (nums[m] >= nums[m + 1])
                        break;
                    l = m + 1;
                }
                else if (m == (int)nums.size() - 1)
                {
                    if (nums[m - 1] <= nums[m])
                        break;
                    h = m - 1;
                }
                else if (nums[m - 1] <= nums[m] && nums[m] >= nums[m + 1])
                {
                    break;
                }
                else if (nums[m - 1] < nums[m + 1])
                {
                    l = m + 1;
                }
                else
                {
                    h = m - 1;
                }
            }
            return m;
        }
        int findPeakElement6(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (m == h)
                {
                    break;
                }
                else if (l == m)
                {
                    if (nums[m] <= nums[m + 1])
                        l = m + 1;
                    else
                        break;
                }
                else
                {
                    if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1])
                        break;
                    else if (nums[m - 1] <= nums[m + 1])
                        l = m + 1;
                    else
                        h = m - 1;
                }
            }
            return m;
        }

        // 164. Maximum Gap
        // Given an unsorted array, find the maximum difference between the successive
        // elements in its sorted form. Return 0 if the array contains less than 2
        // elements. Example 1: Input: [3,6,9,1] Output: 3 Explanation: The sorted form
        // of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum
        // difference 3. Example 2: Input: [10] Output: 0 Explanation: The array
        // contains less than 2 elements, therefore return 0. Note: You may assume all
        // elements in the array are non-negative integers and fit in the 32-bit signed
        // integer range. Try to solve it in linear time/space. Approach 3: Buckets and
        // The Pigeonhole Principle Intuition Sorting an entire array can be costly. At
        // worst, it requires comparing each element with every other element. What if
        // we didn't need to compare all pairs of elements? That would be possible if we
        // could somehow divide the elements into representative groups, or rather,
        // buckets. Then we would only need to compare these buckets. Digression: The
        // Pigeonhole Principle The Pigeonhole Principle states that if n items are put
        // into m containers, with n > m, then at least one container must contain more
        // than one item. Suppose for each of the n elements in our array, there was a
        // bucket. Then each element would occupy one bucket. Now what if we reduced,
        // the number of buckets? Some buckets would have to accommodate more than one
        // element. Now let's talk about the gaps between the elements. Let's take the
        // best case, where all elements of the array are sorted and have a uniform gap
        // between them. This means every adjacent pair of elements differ by the same
        // constant value. So for n elements of the array, there are n − 1 gaps, each of
        // width, say, t. It is trivial to deduce that t = (max − min) / (n − 1) (where
        // max and min are the minimum and maximum elements of the array). This width is
        // the maximal width/gap between two adjacent elements in the array; precisely
        // the quantity we are looking for! One can safely argue that this value of t,
        // is in fact, the smallest value that t can ever accomplish of any array with
        // the same number of elements (i.e. n) and the same range (i.e. (max - min)).
        // To test this fact, you can start with a uniform width array (as described
        // above) and try to reduce the gap between any two adjacent elements. If you
        // reduce the gap between arr[i − 1] and arr[i] to some value t - p, then you
        // will notice that the gap between arr[i] and arr[i + 1] would have increased
        // to t + p. Hence the maximum attainable gap would have become t + p from t.
        // Thus the value of the maximum gap t can only increase. Buckets! Coming back
        // to our problem, we have already established by application of the Pigeonhole
        // Principle, that if we used buckets instead of individual elements as our base
        // for comparison, the number of comparisons would reduce if we could
        // accommodate more than one element in a single bucket. That does not
        // immediately solve the problem though. What if we had to compare elements
        // within a bucket? We would end up no better. So the current motivation
        // remains: somehow, if we only had to compare among the buckets, and not the
        // elements within the buckets, we would be good. It would also solve our
        // sorting problem: we would just distribute the elements to the right buckets.
        // Since the buckets can be already ordered, and we only compare among buckets,
        // we wouldn't have to compare all elements to sort them! But if we only had
        // buckets to compare, we would have to ensure, that the gap between the buckets
        // itself represent the maximal gap in the input array. How do we go about doing
        // that? We could do that just by setting the buckets to be smaller than t =
        // (max - min) / (n - 1) (as described above). Since the gaps (between elements)
        // within the same bucket would only be <=t, we could deduce that the maximal
        // gap would indeed occur only between two adjacent buckets. Hence by setting
        // bucket size b to be 1 < b <= (max − min) / (n − 1), we can ensure that at
        // least one of the gaps between adjacent buckets would serve as the maximal
        // gap. Clarifications A few clarifications are in order: Would the buckets be
        // of uniform size? Yes. Each of them would be of the same size b. But, then
        // wouldn't the gap between them be uniform/constant as well? Yes it would be.
        // The gap between them would be 1 integer unit wide. That means a two adjacent
        // buckets of size 3 could hold integers with values, say, 3 - 6 and 7 - 9. We
        // avoid overlapping buckets. Then what are you talking about when you say the
        // gap between two adjacent buckets could be the maximal gap? When we are
        // talking about the size of a bucket, we are talking about its holding
        // capacity. That is the range of values the bucket can represent (or hold).
        // However the actual extent of the bucket are determined by the values of the
        // maximum and minimum element a bucket holds. For example a bucket of size 5
        // could have a capacity to hold values between 6 - 10. However, if it only
        // holds the elements 7,8 and 9, then its actual extent is only (9 - 7) + 1 = 3
        // which is not the same as the capacity of the bucket. Then how do you compare
        // adjacent buckets? We do that by comparing their extents. Thus we compare the
        // minimum element of the next bucket to the maximum element of the current
        // bucket. For example: if we have two buckets of size 5 each, holding elements
        // [1, 2, 3] and [9, 10] respectively, then the gap between the buckets would
        // essentially refer to the value 9 - 3 = 6 (which is larger than the size of
        // either bucket).
        // But then aren't we comparing elements again?! We are, yes! But only compare
        // about twice the elements as the number of buckets (i.e. the minimum and
        // maximum elements of each bucket). If you followed the above, you would
        // realize that this amount is certainly less than the actual number of elements
        // in the array, given a suitable bucket size was chosen. Algorithm We choose a
        // bucket size b such that 1 < b <= (max − min) / (n − 1). Let's just choose b
        // = floor((max − min) / (n − 1)). Thus all the n elements would be divided
        // among k = ceil((max − min) / b) buckets. Hence the i-th bucket would hold the
        // range of values: [min + (i − 1) ∗ b, min + i ∗ b) (1-based indexing). It is
        // trivial to calculate the index of the bucket to which a particular element
        // belongs. That is given by floor((num - min) / b) (0-based indexing) where
        // num is the element in question. Once all n elements have been
        // distributed, we compare k − 1 adjacent bucket pairs to find the maximum gap.
        // Complexity Analysis
        // Time complexity: O(n + b) ~= O(n).
        // Distributing the elements of the array takes one linear pass (i.e. O(n)
        // complexity). Finding the maximum gap among the buckets takes a linear pass
        // over the bucket storage (i.e. O(b) complexity). Hence overall process takes
        // linear runtime. Space complexity: O(2 * b) ~= O(b) extra space. Each bucket
        // stores a maximum and a minimum element. Hence extra space linear to the
        // number of buckets is required.
        int maximumGap(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            pair<vector<int>::const_iterator, vector<int>::const_iterator> p =
                minmax_element(nums.cbegin(), nums.cend());
            int l = *p.first;
            int h = *p.second;
            int bucketSize = max(1, (h - l) / ((int)nums.size() - 1));
            int bucketNum = (h - l) / bucketSize + 1;
            vector<pair<int, int>> buckets(bucketNum, make_pair(-1, -1));
            for (int n : nums)
            {
                int i = (n - l) / bucketSize;
                buckets[i].first =
                    buckets[i].first == -1 ? n : min(buckets[i].first, n);
                buckets[i].second =
                    buckets[i].second == -1 ? n : max(buckets[i].second, n);
            }
            int preMax = l;
            int gap = 0;
            for (const auto &p : buckets)
            {
                if (p.first == -1)
                    continue;
                gap = max(gap, p.first - preMax);
                preMax = p.second;
            }
            return gap;
        }
        int maximumGap2(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            vector<int> v(nums);
            sort(v.begin(), v.end());
            int gap = 0;
            for (size_t i = 1; i < v.size(); i++)
            {
                if (v[i - 1] + 1 < v[i])
                    gap = max(gap, v[i] - v[i - 1]);
            }
            return gap;
        }

        // 165. Compare Version Numbers
        // Compare two version numbers version1 and version2. If version1 > version2
        // return 1; if version1 < version2 return -1; otherwise return 0. You may assume
        // that the version strings are non-empty and contain only digits and the .
        // character. The . character does not represent a decimal point and is used to
        // separate number sequences. For instance, 2.5 is not "two and a half" or "half
        // way to version three", it is the fifth second-level revision of the second
        // first-level revision. You may assume the default revision number for each
        // level of a version number to be 0. For example, version number 3.4 has a
        // revision number of 3 and 4 for its first and second level revision number.
        // Its third and fourth level revision number are both 0. Example 1: Input:
        // version1 = "0.1", version2 = "1.1" Output: -1 Example 2: Input: version1 =
        // "1.0.1", version2 = "1" Output: 1 Example 3: Input: version1 = "7.5.2.4",
        // version2 = "7.5.3" Output: -1 Example 4: Input: version1 = "1.01", version2 =
        // "1.001" Output: 0 Explanation: Ignoring leading zeroes, both “01” and “001"
        // represent the same number “1” Example 5: Input: version1 = "1.0", version2 =
        // "1.0.0" Output: 0 Explanation: The first version number does not have a third
        // level revision number, which means its third level revision number is default
        // to "0" Note: Version strings are composed of numeric strings separated by
        // dots . and this numeric strings may have leading zeroes. Version strings do
        // not start or end with dots, and they will not be two consecutive dots.
        int compareVersion(const string &version1, const string &version2)
        {
            function<int(const string &, int)> nextDot = [&](const string &s,
                                                             int i) -> int
            {
                while (i < (int)s.size() && s[i] != '.')
                    i++;
                return i;
            };
            function<int(int, int, int, int)> comp = [&](int i1, int i2, int j1,
                                                         int j2) -> int
            {
                while (i1 < i2 && version1[i1] == '0')
                    i1++;
                while (j1 < j2 && version2[j1] == '0')
                    j1++;
                if (i2 - i1 > j2 - j1)
                    return 1;
                if (i2 - i1 < j2 - j1)
                    return -1;
                while (i1 <= i2 && j1 <= j2)
                {
                    if (version1[i1] > version2[j1])
                        return 1;
                    if (version1[i1] < version2[j1])
                        return -1;
                    i1++;
                    j1++;
                }
                return 0;
            };
            function<bool(const string &, int)> allZeros = [&](const string &s,
                                                               int i) -> bool
            {
                while (i < (int)s.size())
                {
                    if (s[i] != '0' && s[i] != '.')
                        return false;
                    i++;
                }
                return true;
            };
            int i1 = 0;
            int j1 = 0;
            while (i1 < (int)version1.size() && j1 < (int)version2.size())
            {
                int i2 = nextDot(version1, i1);
                int j2 = nextDot(version2, j1);
                int c = comp(i1, i2 - 1, j1, j2 - 1);
                if (c != 0)
                    return c;
                i1 = i2 + 1;
                j1 = j2 + 1;
            }
            if (i1 >= (int)version1.size())
                return allZeros(version2, j1) ? 0 : -1;
            if (j1 >= (int)version2.size())
                return allZeros(version1, i1) ? 0 : 1;
            return 0;
        }
        int compareVersion2(const string &version1, const string &version2)
        {
            function<int(const string &, size_t &)> version = [&](const string &str,
                                                                  size_t &i) -> int
            {
                int val = 0;
                while (i < str.size() && str[i] == '.')
                    i++;
                if (i >= str.size())
                    return val;
                size_t j = str.find_first_of('.', i);
                if (j == string::npos)
                {
                    val = atoi(str.substr(i).c_str());
                    i = str.size();
                }
                else
                {
                    val = atoi(str.substr(i, j - i).c_str());
                    i = j;
                }
                return val;
            };
            size_t i1 = 0;
            size_t i2 = 0;
            int v1;
            int v2;
            while (i1 < version1.size() || i2 < version2.size())
            {
                v1 = version(version1, i1);
                v2 = version(version2, i2);
                if (v1 < v2)
                    return -1;
                else if (v1 > v2)
                    return 1;
            }
            return 0;
        }

        // 166. Fraction to Recurring Decimal
        // Given two integers representing the numerator and denominator of a fraction,
        // return the fraction in string format. If the fractional part is repeating,
        // enclose the repeating part in parentheses.
        // Example 1:
        // Input: numerator = 1, denominator = 2
        // Output: "0.5"
        // Example 2:
        // Input: numerator = 2, denominator = 1
        // Output: "2"
        // Example 3:
        // Input: numerator = 2, denominator = 3
        // Output: "0.(6)"
        string fractionToDecimal(int numerator, int denominator)
        {
            string integer;
            string fraction;
            long long n = numerator;
            long long d = denominator;
            bool negative = false;
            if (n < 0)
            {
                negative = !negative;
                n = -n;
            }
            if (d < 0)
            {
                negative = !negative;
                d = -d;
            }
            long long i = n / d;
            n = n % d;
            if (i == 0)
            {
                integer = "0";
            }
            else
            {
                while (i > 0)
                {
                    long long c = i % 10;
                    i = i / 10;
                    integer.insert(0, 1, '0' + c);
                }
            }
            map<long long, int> visited;
            while (n != 0 && visited.find(n) == visited.end())
            {
                visited[n] = (int)fraction.size();
                n *= 10;
                long long c = n / d;
                n %= d;
                fraction.append(1, '0' + c);
            }
            if (visited.find(n) != visited.end())
            {
                fraction.insert(visited[n], 1, '(');
                fraction.append(1, ')');
            }
            string decimal;
            if (fraction.empty() && integer.compare("0") == 0)
                decimal.append(1, '0');
            else
            {
                if (negative)
                    decimal.append(1, '-');
                decimal.append(integer);
                if (!fraction.empty())
                {
                    decimal.append(1, '.');
                    decimal.append(fraction);
                }
            }
            return decimal;
        }

        // 167. Two Sum II - Input array is sorted
        // Given an array of integers that is already sorted in ascending order, find
        // two numbers such that they add up to a specific target number. The function
        // twoSum should return indices of the two numbers such that they add up to the
        // target, where index1 must be less than index2. Note: Your returned answers
        // (both index1 and index2) are not zero-based. You may assume that each input
        // would have exactly one solution and you may not use the same element twice.
        // Example:
        // Input: numbers = [2,7,11,15], target = 9
        // Output: [1,2]
        // Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
        vector<int> twoSumII(const vector<int> &numbers, int target)
        {
            int i = 0;
            int j = numbers.size() - 1;
            while (i < j)
            {
                int t = numbers[i] + numbers[j];
                if (t < target)
                    i++;
                else if (t > target)
                    j--;
                else
                    break;
            }
            return {i + 1, j + 1};
        }
        static vector<pair<int, int>> twoSumSortedMultiSolutions(vector<int> &nums,
                                                                 int target)
        {
            vector<pair<int, int>> result;
            function<int(int, int, int)> search = [&](int v, int b, int e) -> int
            {
                while (b <= e)
                {
                    int m = b + ((e - b) >> 1);
                    if (v < nums[m])
                        e = m - 1;
                    else if (v > nums[m])
                        b = m + 1;
                    else if (b == m)
                        return m;
                    else
                        e = m;
                }
                return -1;
            };
            for (int i = 0; i < (int)nums.size(); i++)
            {
                int second = target - nums[i];
                int j = search(second, i + 1, nums.size() - 1);
                if (j == -1)
                    continue;
                do
                {
                    result.push_back(make_pair(i, j));
                    j++;
                } while (j < (int)nums.size() && nums[j] == second);
            }
            return result;
        }
        static vector<pair<int, int>> twoSumSortedMultiSolutions2(vector<int> &nums,
                                                                  int target)
        {
            vector<pair<int, int>> result;
            int i = 0;
            int j = nums.size() - 1;
            while (i < j)
            {
                int sum = nums[i] + nums[j];
                if (sum < target)
                    i++;
                else if (sum > target)
                    j--;
                else
                {
                    int p = i;
                    while (p + 1 <= j && nums[p + 1] == nums[p])
                        p++;
                    int q = j;
                    while (i <= q - 1 && nums[q - 1] == nums[q])
                        q--;
                    if (p < q)
                    {
                        for (int r = i; r <= p; r++)
                            for (int s = q; s <= j; s++)
                                result.push_back(make_pair(r, s));
                    }
                    else // p == j && q == i
                    {
                        for (int r = i; r < j; r++)
                            for (int s = r + 1; s <= j; s++)
                                result.push_back(make_pair(r, s));
                    }
                    i = p + 1;
                    j = q - 1;
                }
            }
            return result;
        }

        // 168. Excel Sheet Column Title
        // Given a positive integer, return its corresponding column title as appear in
        // an Excel sheet. For example:
        //     1 -> A
        //     2 -> B
        //     3 -> C
        //     ...
        //     26 -> Z
        //     27 -> AA
        //     28 -> AB
        //     ...
        // Example 1:
        // Input: 1
        // Output: "A"
        // Example 2:
        // Input: 28
        // Output: "AB"
        // Example 3:
        // Input: 701
        // Output: "ZY"
        string convertToTitle(int n)
        {
            string s;
            while (n > 0)
            {
                int c = n % 26;
                n /= 26;
                if (c == 0)
                {
                    c = 26;
                    n--;
                }
                s.insert(0, 1, 'A' + c - 1);
            }
            return s;
        }

        // 169. Majority Element
        // Given an array of size n, find the majority element. The majority element is
        // the element that appears more than floor(n/2) times. You may assume that the
        // array is non-empty and the majority element always exist in the array.
        // Example 1:
        // Input: [3,2,3]
        // Output: 3
        // Example 2:
        // Input: [2,2,1,1,1,2,2]
        // Output: 2
        // Approach 6: Boyer-Moore Voting Algorithm
        // Intuition
        // If we had some way of counting instances of the majority element as +1 and
        // instances of any other element as −1, summing them would make it obvious that
        // the majority element is indeed the majority element.
        // Algorithm
        // Essentially, what Boyer-Moore does is look for a suffix suf of nums where
        // suf[0] is the majority element in that suffix. To do this, we maintain a
        // count, which is incremented whenever we see an instance of our current
        // candidate for majority element and decremented whenever we see anything else.
        // Whenever count equals 0, we effectively forget about everything in nums up to
        // the current index and consider the current number as the candidate for
        // majority element. It is not immediately obvious why we can get away with
        // forgetting prefixes of nums - consider the following examples (pipes are
        // inserted to separate runs of nonzero count). [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5,
        // 7, 7 | 7, 7, 7, 7] Here, the 7 at index 0 is selected to be the first
        // candidate for majority element. count will eventually reach 0 after index 5
        // is processed, so the 5 at index 6 will be the next candidate. In this case, 7
        // is the true majority element, so by disregarding this prefix, we are ignoring
        // an equal number of majority and minority elements - therefore, 7 will still
        // be the majority element in the suffix formed by throwing away the first
        // prefix. [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 5, 5, 5, 5] Now, the majority
        // element is 5 (we changed the last run of the array from 7s to 5s), but our
        // first candidate is still 7. In this case, our candidate is not the true
        // majority element, but we still cannot discard more majority elements than
        // minority elements (this would imply that count could reach -1 before we
        // reassign candidate, which is obviously false). Therefore, given that it is
        // impossible (in both cases) to discard more majority elements than minority
        // elements, we are safe in discarding the prefix and attempting to recursively
        // solve the majority element problem for the suffix. Eventually, a suffix will
        // be found for which count does not hit 0, and the majority element of that
        // suffix will necessarily be the same as the majority element of the overall
        // array. Complexity Analysis Time complexity : O(n) Boyer-Moore performs
        // constant work exactly n times, so the algorithm runs in linear time. Space
        // complexity : O(1) Boyer-Moore allocates only constant additional memory.
        int majorityElement(const vector<int> &nums)
        {
            int m;
            int c = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (c == 0)
                {
                    m = nums[i];
                    c++;
                }
                else if (nums[i] == m)
                {
                    c++;
                }
                else
                {
                    c--;
                }
            }
            return m;
        }
        int majorityElement2(const vector<int> &nums)
        {
            map<int, int> m;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (m.find(nums[i]) == m.end())
                {
                    m[nums[i]] = 1;
                }
                else
                {
                    m[nums[i]]++;
                }
                if (m[nums[i]] > (int)nums.size() / 2)
                {
                    return nums[i];
                }
            }
            throw AssertError("No result");
        }

        // 171. Excel Sheet Column Number
        // Given a column title as appear in an Excel sheet, return its corresponding
        // column number. For example:
        //     A -> 1
        //     B -> 2
        //     C -> 3
        //     ...
        //     Z -> 26
        //     AA -> 27
        //     AB -> 28
        //     ...
        // Example 1:
        // Input: "A"
        // Output: 1
        // Example 2:
        // Input: "AB"
        // Output: 28
        // Example 3:
        // Input: "ZY"
        // Output: 701
        int titleToNumber(const string &s)
        {
            long long r = 0;
            for (size_t i = 0; i < s.size(); i++)
                r = r * 26 + s[i] - 'A' + 1;
            return (int)r;
        }

        // 172. Factorial Trailing Zeroes
        // Given an integer n, return the number of trailing zeroes in n!.
        // Example 1:
        // Input: 3
        // Output: 0
        // Explanation: 3! = 6, no trailing zero.
        // Example 2:
        // Input: 5
        // Output: 1
        // Explanation: 5! = 120, one trailing zero.
        // Note: Your solution should be in logarithmic time complexity.
        // n! = 1 * 2 * 3 * 4 * 5 * ... * 10 * ... * 15 * ... * n
        //    = 2^x * 5^y * z
        // Usually x >= y. So just need to count occurrence of 5.
        //   n:      1, 2, 3, 4, 5, 6, ..., 2*5, ..., 3*5, ..., n1*5, ..., n
        // n/5 = n1:             1,    ..., 2,   ..., 3,   ..., n2*5, ..., n1
        // n1/5 = n2:                                   1, ..., n3*5, ..., n2
        // n2/5 = n3: ...
        // ...
        int trailingZeroes(int n)
        {
            int c = 0;
            while (n >= 5)
            {
                n /= 5;
                c += n;
            }
            return c;
        }

        // 173. Binary Search Tree Iterator
        // Implement an iterator over a binary search tree (BST). Your iterator will be
        // initialized with the root node of a BST.
        // Calling next() will return the next smallest number in the BST.
        // Example:
        // BSTIterator iterator = new BSTIterator(root);
        // iterator.next();    // return 3
        // iterator.next();    // return 7
        // iterator.hasNext(); // return true
        // iterator.next();    // return 9
        // iterator.hasNext(); // return true
        // iterator.next();    // return 15
        // iterator.hasNext(); // return true
        // iterator.next();    // return 20
        // iterator.hasNext(); // return false
        // Note:
        // next() and hasNext() should run in average O(1) time and uses O(h) memory,
        // where h is the height of the tree. You may assume that next() call will
        // always be valid, that is, there will be at least a next smallest number in
        // the BST when next() is called.
        class BSTIterator
        {
        private:
            TreeNode *_node;
            stack<TreeNode *> _s;

        public:
            BSTIterator(TreeNode *root) { _node = root; }
            /** @return the next smallest number */
            int next()
            {
                int v;
                while (!_s.empty() || _node != nullptr)
                {
                    if (_node != nullptr)
                    {
                        _s.push(_node);
                        _node = _node->left;
                    }
                    else
                    {
                        v = _s.top()->val;
                        _node = _s.top()->right;
                        _s.pop();
                        break;
                    }
                }
                return v;
            }
            int next2()
            {
                while (_node != nullptr)
                {
                    _s.push(_node);
                    _node = _node->left;
                }
                TreeNode *t = _s.top();
                _s.pop();
                _node = t->right;
                return t->val;
            }

            /** @return whether we have a next smallest number */
            bool hasNext() { return !_s.empty() || _node != nullptr; }
        };

        // 174. Dungeon Game
        // The demons had captured the princess (P) and imprisoned her in the
        // bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
        // out in a 2D grid. Our valiant knight (K) was initially positioned in the
        // top-left room and must fight his way through the dungeon to rescue the
        // princess. The knight has an initial health point represented by a positive
        // integer. If at any point his health point drops to 0 or below, he dies
        // immediately. Some of the rooms are guarded by demons, so the knight loses
        // health (negative integers) upon entering these rooms; other rooms are either
        // empty (0's) or contain magic orbs that increase the knight's health (positive
        // integers). In order to reach the princess as quickly as possible, the knight
        // decides to move only rightward or downward in each step. Write a function to
        // determine the knight's minimum initial health so that he is able to rescue
        // the princess. For example, given the dungeon below, the initial health of the
        // knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT ->
        // DOWN -> DOWN. -2 (K) 	-3 	3 -5 	-10 	1 10 	30 	-5 (P)
        // Note: The knight's health has no upper bound. Any room can contain threats or
        // power-ups, even the first room the knight enters and the bottom-right room
        // where the princess is imprisoned.
        int calculateMinimumHP(const vector<vector<int>> &dungeon)
        {
            int m = dungeon.size();
            int n = dungeon[0].size();
            vector<int> health(n, 0);
            for (int i = m - 1; i >= 0; i--)
            {
                for (int j = n - 1; j >= 0; j--)
                {
                    if (i == m - 1)
                    {
                        if (j == n - 1)
                            health[j] = 1 + (dungeon[i][j] >= 0 ? 0 : -dungeon[i][j]);
                        else
                            health[j] = dungeon[i][j] >= health[j + 1]
                                            ? 1
                                            : health[j + 1] - dungeon[i][j];
                    }
                    else
                    {
                        if (j == n - 1)
                            health[j] = dungeon[i][j] >= health[j]
                                            ? 1
                                            : health[j] - dungeon[i][j];
                        else
                        {
                            // min(health[i+1][j],health[i][j+1])
                            int m = min(health[j], health[j + 1]);
                            health[j] = dungeon[i][j] > m ? 1 : m - dungeon[i][j];
                        }
                    }
                }
                // for (int j = 0; j < n; j++) {
                //     cout << "  " << health[j];
                // }
                // cout << endl;
            }
            return health[0];
        }

        // 175. Combine Two Tables
        // SQL Schema
        // Table: Person
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | PersonId    | int     |
        // | FirstName   | varchar |
        // | LastName    | varchar |
        // +-------------+---------+
        // PersonId is the primary key column for this table.
        // Table: Address
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | AddressId   | int     |
        // | PersonId    | int     |
        // | City        | varchar |
        // | State       | varchar |
        // +-------------+---------+
        // AddressId is the primary key column for this table.
        // Write a SQL query for a report that provides the following information for
        // each person in the Person table, regardless if there is an address for each
        // of those people:
        // FirstName, LastName, City, State
        // # Write your MySQL query statement below
        // SELECT FirstName, LastName, City, State
        // FROM Person LEFT JOIN Address ON Person.PersonId = Address.PersonId

        // 179. Largest Number
        // Given a list of non negative integers, arrange them such that they form the
        // largest number. Example 1: Input: [10,2] Output: "210" Example 2: Input:
        // [3,30,34,5,9] Output: "9534330" Note: The result may be very large, so you
        // need to return a string instead of an integer.
        string largestNumber(const vector<int> &nums)
        {
            vector<string> s;
            s.resize(nums.size());
            transform(nums.begin(), nums.end(), s.begin(),
                      [&](int i)
                      { return std::to_string(i); });
            sort(s.begin(), s.end(), [&](const string &a, const string &b) -> bool
                 {
                     string ab = a + b;
                     string ba = b + a;
                     for (size_t i = 0; i < ab.size(); i++)
                     {
                         if (ab[i] > ba[i])
                             return true;
                         else if (ab[i] < ba[i])
                             return false;
                     }
                     return false;
                 });
            if (s[0] == "0")
                return "0";
            ostringstream ss;
            for_each(s.cbegin(), s.cend(), [&](const string &i)
                     { ss << i; });
            return ss.str();
        }
        string largestNumber2(const vector<int> &nums)
        {
            vector<string> strs;
            strs.resize(nums.size());
            transform(nums.begin(), nums.end(), strs.begin(), [&](int i)
                      {
                          ostringstream oss;
                          oss << i;
                          return oss.str();
                      });
            sort(strs.begin(), strs.end(), [&](const string &str1, const string &str2)
                 {
                     string str12(str1);
                     str12.append(str2);
                     string str21(str2);
                     str21.append(str1);
                     return str12.compare(str21) > 0;
                 });
            string result;
            if (strs[0] == "0")
            {
                result = "0";
            }
            else
            {
                for_each(strs.begin(), strs.end(),
                         [&](const string &str)
                         { result.append(str); });
            }
            return result;
        }

        // 187. Repeated DNA Sequences
        // All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
        // for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
        // identify repeated sequences within the DNA. Write a function to find all the
        // 10-letter-long sequences (substrings) that occur more than once in a DNA
        // molecule. Example: Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT" Output:
        // ["AAAAACCCCC", "CCCCCAAAAA"]
        // A is 0x41 = 01000001,
        // C is 0x43 = 01000011,
        // G is 0x47 = 01000111,
        // T is 0x54 = 01000100.
        // Using bit 3 and 2 to encode each one
        vector<string> findRepeatedDnaSequences(const string &s)
        {
            vector<string> result;
            map<int, int> m;
            int t = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                t = ((t << 2) | (s[i] >> 1 & 0x3)) & 0xFFFFF;
                if (i >= 9)
                {
                    if (m.find(t) == m.end())
                        m[t] = 1;
                    else
                    {
                        if (m[t] == 1)
                            result.push_back(s.substr(i - 9, 10));
                        m[t]++;
                    }
                }
            }
            return result;
        }
        vector<string> findRepeatedDnaSequences2(const string &s)
        {
            vector<string> result;
            for (size_t i = 0; i + 10 < s.size(); i++)
            {
                string t = s.substr(i, 10);
                if (find(result.cbegin(), result.cend(), t) == result.cend())
                {
                    size_t j = i + 1;
                    int stop = false;
                    while (!stop && j + 10 <= s.size())
                    {
                        if (s[i] == s[j])
                        {
                            size_t k = 1;
                            while (k < 10 && s[i + k] == s[j + k])
                                k++;
                            if (k == 10)
                            {
                                result.push_back(s.substr(i, k));
                                stop = true;
                            }
                        }
                        j++;
                    }
                }
            }
            return result;
        }

        // 188. Best Time to Buy and Sell Stock IV
        // Say you have an array for which the i-th element is the price of a given
        // stock on day i. Design an algorithm to find the maximum profit. You may
        // complete at most k transactions. Note: You may not engage in multiple
        // transactions at the same time (ie, you must sell the stock before you buy
        // again). Example 1: Input: [2,4,1], k = 2 Output: 2 Explanation: Buy on day 1
        // (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2. Example 2:
        // Input: [3,2,6,5,0,3], k = 2
        // Output: 7
        // Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit =
        // 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit
        // = 3-0 = 3. Let p[i] be the price on day i Let P(i,k) be the max profit with k
        // transactions on day i
        //            k               1                         2                   3
        //            ......      k-1                          k
        // i     p[i]
        // 0     p[0]     -p[0]
        // 1     p[1]     -p[1]   P(1,1)     -p[1]+P(1,1)
        // 2     p[2]     -p[2]   P(2,1)     -p[2]+P(2,1)   P(2,2) -p[2]+P(2,2)
        // 3     p[3]     -p[3]   P(3,1)     -p[3]+P(3,1)   P(3,2) -p[3]+P(3,2) P(3,3)
        // 4     p[4]     -p[4]   P(4,1)     -p[4]+P(4,1)   P(4,2) -p[4]+P(4,2) P(4,3)
        // ......
        // k-1 p[k-1]   -p[k-1] P(k-1,1) -p[k-1]+P(k-1,1) P(k-1,2) ......
        // -p[k-1]+P(k-1,k-2) P(k-1,k-1) -p[k-1]+P(k-1,k-1) k     p[k]     -p[k] P(k,1)
        // -p[k]+P(k,1)   P(k,2) ......     -p[k]+P(k,k-2)   P(k,k-1)     -p[k]+P(k,k-1)
        // P(k,k) k+1 p[k+1]   -p[k+1] P(k+1,1) -p[k+1]+P[k+1,1] P(k+1,2) ......
        // -p[k+1]+P(k+1,k-2) P(k+1,k-1) -p[k+1]+P(k+1,k-1) P(k+1,k)
        // ......
        // i-1 p[i-1]   -p[i-1] P(i-1,1) -p[i-1]+P(i-1,1) P(i-1,2) ......
        // -p[i-1]+P(i-1,k-2) P(i-1,k-1) -p[i-1]+P(i-1,k-1) P(i-1,k) i     p[i] P(i,1)
        // P(i,2) ......                      P(i,k-1)                      P(i,k)

        // P(i,1) = max(P(i-1,1),
        //              p[i] + max{-p[i-1],
        //                         -p[i-2],
        //                         ......
        //                         -p[2],
        //                         -p[1],
        //                         -p[0]}
        // P(i,2) = max{P(i-1, 2),
        //              p[i] + max{-p[i-1] + P(i-1, 1),
        //                         -p[i-2] + P(i-2, 1),
        //                         ......
        //                         -p[2] + P(2, 1),
        //                         -p[1] + P(1, 1)}}
        // P(i,3) = max{P(i-1, 3),
        //              p[i] + max{-p[i-1] + P(i-1, 2),
        //                         -p[i-2] + P(i-2, 2),
        //                         ......
        //                         -p[3] + P(3, 2),
        //                         -p[2] + P(2, 2)}}
        // ......
        // P(i,k-1) = max{P(i-1, k-1),
        //              p[i] + max{-p[i-1] + P(i-1, k-2),
        //                         -p[i-2] + P(i-2, k-2),
        //                         ......
        //                         -p[k-1] + P(k-1, k-2),
        //                         -p[k-2] + P(k-2, k-2)}}
        // P(i,k) = max{P(i-1, k),
        //              p[i] + max{-p[i-1] + P(i-1, k-1),
        //                         -p[i-2] + P(i-2, k-1),
        //                         ......
        //                         -p[k] + P(k, k-1),
        //                         -p[k-1] + P(k-1, k-1)}}
        int maxProfit(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == i)
                    {
                        if (j == 1)
                            c[j - 1] = -prices[i - 1];
                        else
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                        p[j - 1] = prices[i] + c[j - 1];
                    }
                    else
                    {
                        if (j == 1)
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                        else
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                        p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }
        int maxProfit2(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == 1)
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                    else
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }
        int maxProfit3(int k, const vector<int> &prices)
        {
            int m = 0;
            function<void(size_t, int, int)> solve = [&](size_t i, int p, int c)
            {
                if (c == 0)
                {
                    m = max(m, p);
                    return;
                }
                if (i >= prices.size())
                    return;
                for (size_t j = i + 1; j < prices.size(); j++)
                {
                    if (prices[i] < prices[j])
                    {
                        solve(j + 1, p + prices[j] - prices[i], c - 1);
                    }
                }
                solve(i + 1, p, c);
            };
            for (int i = 1; i <= k; i++)
            {
                solve(0, 0, i);
            }
            return m;
        }

        // 189. Rotate Array
        // Given an array, rotate the array to the right by k steps, where k is
        // non-negative. Example 1: Input: [1,2,3,4,5,6,7] and k = 3 Output:
        // [5,6,7,1,2,3,4] Explanation: rotate 1 steps to the right: [7,1,2,3,4,5,6]
        // rotate 2 steps to the right: [6,7,1,2,3,4,5]
        // rotate 3 steps to the right: [5,6,7,1,2,3,4]
        // Example 2:
        // Input: [-1,-100,3,99] and k = 2
        // Output: [3,99,-1,-100]
        // Explanation:
        // rotate 1 steps to the right: [99,-1,-100,3]
        // rotate 2 steps to the right: [3,99,-1,-100]
        // Note: Try to come up as many solutions as you can, there are at least 3
        // different ways to solve this problem. Could you do it in-place with O(1)
        // extra space?
        void rotate(vector<int> &nums, int k)
        {
            k = k % nums.size();
            if (k == 0)
                return;
            function<void(int, int)> Swap = [&](int i, int j)
            {
                while (i < j)
                {
                    swap(nums[i], nums[j]);
                    i++;
                    j--;
                }
            };
            Swap(0, (int)nums.size() - 1);
            Swap(0, k - 1);
            Swap(k, (int)nums.size() - 1);
        }
        void rotate2(vector<int> &nums, int k)
        {
            k %= nums.size();
            if (k == 0)
                return;
            function<void(int, int, int)> Swap = [&](int p, int q, int n)
            {
                for (int m = 0; m < n; m++)
                    swap(nums[p + m], nums[q + m]);
            };
            int i = 0;
            int j = nums.size() - 1;
            int t = j - k + 1;
            // input[i..t-1] and input[t..j];
            while (i < t && t <= j)
            {
                if (t - i < j - t + 1)
                {
                    // Left range is shorter. Swap it to the right, and
                    // repeat with the rest on its left.
                    // input[i..t-1], input[t..j-(t-i)], input[j-(t-i)+1..j]
                    Swap(i, j - (t - i) + 1, t - i);
                    j = j - (t - i);
                }
                else if (t - i > j - t + 1)
                {
                    // Right range is shorter. Swap it to the left, and
                    // repeat with the rest on its right.
                    // input[i..i+(j-t)], input(i+(j-t)+1..t-1], input[t..j]
                    Swap(i, t, j - t + 1);
                    i = i + (j - t) + 1;
                }
                else
                {
                    // Both ranges have the same length
                    Swap(i, t, t - i);
                    break;
                }
            }
        }
        void rotate3(vector<int> &nums, int k)
        {
            if (nums.empty())
                return;
            int n = (int)nums.size();
            k %= n;
            if (k == 0)
                return;
            vector<int> b(k, 0);
            for (int i = 0; i < k; i++)
            {
                if (b[i] == 1)
                    continue;
                int j = i;
                int x = nums[j];
                while (true)
                {
                    int t = j + k;
                    while (t < n)
                    {
                        swap(x, nums[t]);
                        t += k;
                    }
                    t %= n;
                    swap(x, nums[t]);
                    b[t] = 1;
                    if (j == t || t == i)
                        break;
                    j = t;
                }
            }
        }
        // This one works only if n and k are co-prime
        // 0, k, 2k, 3k, ..., (n-1)k, nk
        // 0, k % n, 2k % n, 3k % n, ..., (n-1)k % n, nk % n = 0
        void rotate4(vector<int> &nums, int k)
        {
            if (nums.empty())
                return;
            k %= nums.size();
            if (k == 0)
                return;
            size_t i = 0;
            do
            {
                i = (i + k) % nums.size();
                swap(nums[0], nums[i]);
            } while (i != 0);
        }

        // 190. Reverse Bits
        // Reverse bits of a given 32 bits unsigned integer.
        // Example 1:
        // Input: 00000010100101000001111010011100
        // Output: 00111001011110000010100101000000
        // Explanation: The input binary string 00000010100101000001111010011100
        // represents the unsigned integer 43261596, so return 964176192 which its
        // binary representation is 00111001011110000010100101000000.
        // Example 2:
        // Input: 11111111111111111111111111111101
        // Output: 10111111111111111111111111111111
        // Explanation: The input binary string 11111111111111111111111111111101
        // represents the unsigned integer 4294967293, so return 3221225471 which
        // its binary representation is 10111111111111111111111111111111.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, both input and output will be given as signed integer
        // type and should not affect your implementation, as the internal binary
        // representation of the integer is the same whether it is signed or unsigned.
        // In Java, the compiler represents the signed integers using 2's complement
        // notation. Therefore, in Example 2 above the input represents the signed
        // integer -3 and the output represents the signed integer -1073741825.
        // Follow up: If this function is called many times, how would you optimize it?
        uint32_t reverseBits(uint32_t n)
        {
            n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
            n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
            n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
            n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
            n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
            return n;
        }

        // 191. Number of 1 Bits
        // Write a function that takes an unsigned integer and return the number of '1'
        // bits it has (also known as the Hamming weight).
        // Example 1:
        // Input: 00000000000000000000000000001011
        // Output: 3
        // Explanation: The input binary string 00000000000000000000000000001011 has a
        // total of three '1' bits.
        // Example 2:
        // Input: 00000000000000000000000010000000
        // Output: 1
        // Explanation: The input binary string 00000000000000000000000010000000 has a
        // total of one '1' bit.
        // Example 3:
        // Input: 11111111111111111111111111111101
        // Output: 31
        // Explanation: The input binary string 11111111111111111111111111111101 has a
        // total of thirty one '1' bits.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, the input will be given as signed integer type and should
        // not affect your implementation, as the internal binary representation of the
        // integer is the same whether it is signed or unsigned. In Java, the compiler
        // represents the signed integers using 2's complement notation. Therefore, in
        // Example 3 above the input represents the signed integer -3.
        // Follow up: If this function is called many times, how would you optimize it?
        int hammingWeight(uint32_t n)
        {
            int c = 0;
            while (n > 0)
            {
                n &= (n - 1);
                c++;
            }
            return c;
        }

        // 198. House Robber
        // You are a professional robber planning to rob houses along a street. Each
        // house has a certain amount of money stashed, the only constraint stopping you
        // from robbing each of them is that adjacent houses have security system
        // connected and it will automatically contact the police if two adjacent houses
        // were broken into on the same night. Given a list of non-negative integers
        // representing the amount of money of each house, determine the maximum amount
        // of money you can rob tonight without alerting the police. Example 1: Input:
        // [1,2,3,1] Output: 4 Explanation: Rob house 1 (money = 1) and then rob house 3
        // (money = 3). Total amount you can rob = 1 + 3 = 4. Example 2: Input:
        // [2,7,9,3,1] Output: 12 Explanation: Rob house 1 (money = 2), rob house 3
        // (money = 9) and rob house 5 (money = 1). Total amount you can rob = 2 + 9 + 1
        // = 12.
        // Let m[i] be the max amount for p[0..i]
        // Let s[i] = max(m[i], m[i-1], ..., m[2], m[1], m[0])
        //          = max(m[i], s[i-1])
        // m[0] = p[0]
        // m[1] = max(m[0], p[1])
        // m[2] = max(m[1], p[2] + m[0])
        //      = max(m[1], p[2] + s[0])
        // m[3] = max(m[2], p[3] + max(m[1], m[0]))
        //      = max(m[2], p[3] + s[1])
        // m[4] = max(m[3], p[4] + max(m[2], m[1], m[0]))
        //      = max(m[3], p[4] + s[2])
        // ......
        // m[i] = max{m[i - 1],
        //            p[i] + max{m[i - 2],
        //                       m[i - 1],
        //                       ......
        //                       m[2],
        //                       m[1] = max{p[1], p[0]},
        //                       m[0] = p[0]}}
        //      = max(m[i - 1], p[i] + s[i - 2])
        int rob(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            if (nums.size() == 1)
                return nums[0];
            int s = nums[0];               // m[i-2] at i-2 = 0
            int m = max(nums[0], nums[1]); // m[i-1] at i-1 = 1
            for (size_t i = 2; i < nums.size(); i++)
            {
                int t = m;               // m[i-1]
                m = max(m, nums[i] + s); // m[i] = max(m[i-1], n[i] + m[i-2])
                s = max(s, t);           // max(m[i-1], m[i-2], ..., m[1], m[0])
            }
            return m;
        }
        int rob2(const vector<int> &nums)
        {
            int a = 0; // max at i - 2
            int b = 0; // max at i - 1
            int c;     // max at i
            for (size_t i = 0; i < nums.size(); i++)
            {
                c = max(a + nums[i], b);
                a = b;
                b = c;
            }
            return b;
        }

        // 199. Binary Tree Right Side View
        // Given a binary tree, imagine yourself standing on the right side of it,
        // return the values of the nodes you can see ordered from top to bottom.
        // Example:
        // Input: [1,2,3,null,5,null,4]
        // Output: [1, 3, 4]
        // Explanation:
        //    1            <---
        //  /   \
        // 2     3         <---
        //  \     \
        //   5     4       <---
        vector<int> rightSideView(TreeNode *root)
        {
            vector<int> v;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int d = 1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (d > (int)v.size())
                        v.push_back(n->val);
                    s.push(make_pair(n, d));
                    d++;
                    n = n->right;
                }
                else
                {
                    n = s.top().first->left;
                    d = s.top().second + 1;
                    s.pop();
                }
            }
            return v;
        }
        vector<int> rightSideView2(TreeNode *root)
        {
            vector<int> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int level = 0;
            int current = 0;
            int next = 0;
            TreeNode *p;
            while (!q[0].empty() || !q[1].empty())
            {
                current = level % 2;
                next = (level + 1) % 2;
                p = q[current].front();
                result.push_back(p->val);
                while (!q[current].empty())
                {
                    p = q[current].front();
                    q[current].pop();
                    if (p->right != nullptr)
                        q[next].push(p->right);
                    if (p->left != nullptr)
                        q[next].push(p->left);
                }
                level++;
            }
            return result;
        }

    }
}

#endif