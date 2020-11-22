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
    TreeNode* dfs(vector<int>& inorder, vector<int>& postorder, int inorderLeft, int inorderRight, int postorderLeft, int postorderRight) {
        if (inorderLeft > inorderRight) {
            return nullptr;
        }
        TreeNode *root = new TreeNode(postorder[postorderRight]);
        int inRootIndex = mp[postorder[postorderRight]];
        int inLeftTreeLeft = inorderLeft;
        int inLeftTreeRight = inRootIndex - 1;
        int inLeftTreeSize = inRootIndex - inorderLeft;
        int postLeftTreeLeft = postorderLeft;
        int postLeftTreeRight = postorderLeft + inLeftTreeSize - 1;
        int inRightTreeLeft = inRootIndex + 1;
        int inRightTreeRight = inorderRight;
        int postRightTreeLeft = postLeftTreeRight + 1;
        int postRightTreeRight = postorderRight - 1;
        root->left = dfs(inorder, postorder, inLeftTreeLeft, inLeftTreeRight, postLeftTreeLeft, postLeftTreeRight);
        root->right = dfs(inorder, postorder, inRightTreeLeft, inRightTreeRight, postRightTreeLeft, postRightTreeRight);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int postorderLen = postorder.size();
        int inorderLen = inorder.size();        
        for (int i = 0; i < inorderLen; i++) {
            mp[inorder[i]] = i;
        }
        return dfs(inorder, postorder, 0, inorderLen - 1, 0, postorderLen - 1);
    }
};
