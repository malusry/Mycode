/*
 * AcWing - 31 - 二叉树中序遍历的下一个节点
 * https://www.acwing.com/problem/content/31/
 * 时间：2025-03-14
 * 作者：ma1us
 * 题目描述：给定二叉树中的一个节点，找出中序遍历序列的下一个节点
 * 输入：一个带有father指针的二叉树节点
 * 输出：中序遍历的后继节点，若不存在则返回NULL
 * 样例输入：二叉树[2,1,3]，给定节点2
 * 样例输出：节点3
 * 思路：
 *   分两种情况：
 *   情况一：当前节点有右子树
 *     → 后继节点是右子树中最左边的节点
 *     → 做法：p = p->right，然后一直往左走直到left为NULL
 *   情况二：当前节点无右子树
 *     → 一直往上走，直到找到某个祖先节点p，
 *       使得p是其父节点的左孩子，则p->father就是后继
 *     → 若一直走到根仍未找到，说明当前节点是中序最后一个，返回NULL
 *     → while循环条件：p->father != NULL && p->father->left != p
 *     → 循环结束后 p = p->father 即为答案（NULL或目标节点）
 * 注意点 / 坑：
 *   1. while条件中判空(p->father != NULL)必须写在左边，利用短路求值
 *      防止father为NULL时再访问father->left导致空指针崩溃
 *   2. 情况二中不要在循环前多走一步，否则会多跳一层
 */

#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *father;
};

struct TreeNode *inorderSuccessor(struct TreeNode *p)
{
    if (p->right != NULL)
    {
        p = p->right;
        while (p->left != NULL)
        {
            p = p->left;
        }
    }
    else
    {
        while (p->father != NULL && p->father->left != p)
        {
            p = p->father;
        }
        p = p->father;
    }

    return p;
}
