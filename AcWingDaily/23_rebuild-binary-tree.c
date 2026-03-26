/*
 * AcWing - 23 - 重建二叉树
 * https://www.acwing.com/problem/content/23/
 * 时间：2025-03-10
 * 作者：ma1us
 * 题目描述：输入一棵二叉树的前序遍历和中序遍历结果，重建该二叉树
 * 输入：前序遍历数组、中序遍历数组及各自长度
 * 输出：重建后的二叉树根节点指针
 * 样例输入：preorder=[3,9,20,15,7], inorder=[9,3,15,20,7]
 * 样例输出：[3,9,20,null,null,15,7]
 * 思路：
 *   前序数组的第一个元素一定是当前子树的根节点。
 *   在中序数组中找到根节点的下标k，k左边是左子树，k右边是右子树。
 *   左子树节点数为 k-in_left，据此可以切分前序数组的左右子树范围。
 *   递归对左右子树做同样的操作，直到范围为空（pre_left > pre_right）返回NULL。
 *   范围为空的本质是节点数为0，用下标表示就是左边界大于右边界。
 * 注意点 / 坑：
 *   1. 找k时循环范围是 in_left ~ in_right，不能从0开始
 *   2. malloc使用 sizeof(struct TreeNode)，C语言不能省略struct关键字
 *   3. buildTree必须return build(...)的结果
 */

#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *build(int *pre, int pre_left, int pre_right,
                       int *in, int in_left, int in_right)
{
    if (pre_left > pre_right)
    {
        return NULL;
    }
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = pre[pre_left];
    int k = -1;
    for (int i = in_left; i <= in_right; i++)
    {
        if (in[i] == root->val)
        {
            k = i;
        }
    }

    root->left = build(pre, pre_left + 1, pre_left + k - in_left, in, in_left, k - 1);
    root->right = build(pre, pre_left + k - in_left + 1, pre_right, in, k + 1, in_right);
    return root;
}

struct TreeNode *buildTree(int *preorder, int preorder_size, int *inorder, int inorder_size)
{
    return build(preorder, 0, preorder_size - 1, inorder, 0, inorder_size - 1);
}