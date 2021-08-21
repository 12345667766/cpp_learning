#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    unordered_map<int, int> mp;
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int preorderStart, int preorderEnd, int inorderStart, int inorderEnd) {
        if (preorderStart > preorderEnd) {
            return nullptr;
        }
        int preRootValue = preorder[preorderStart];
        int inorderRootIndex = mp[preRootValue];
        TreeNode *root = new TreeNode(preRootValue);
        int leftTreeSize = inorderRootIndex - inorderStart;
        int rightTreeStart = preorderStart + leftTreeSize + 1;
        int rightTreeEnd = preorderEnd;
        root->left = dfs(preorder, inorder, preorderStart + 1, preorderStart + leftTreeSize, inorderStart, inorderStart + leftTreeSize - 1);
        root->right = dfs(preorder, inorder, rightTreeStart, rightTreeEnd, inorderRootIndex + 1, inorderEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preorderLen = preorder.size();
        int inorderLen = inorder.size();        
        for (int i = 0; i < inorderLen; i++) {
            mp[inorder[i]] = i;
        }
        return dfs(preorder, inorder, 0, preorderLen - 1, 0, inorderLen - 1);
    }
};
