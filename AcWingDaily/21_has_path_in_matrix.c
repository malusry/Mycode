/*
 * AcWing - 21 - 矩阵中的路径
 * https://www.acwing.com/problem/content/21/
 * 时间：2025-03-15
 * 作者：ma1us
 *
 * 题目描述：
 *   判断矩阵中是否存在一条路径，路径上的字符按访问顺序恰好等于给定字符串。
 *   路径可从任意格子出发，每步可上下左右移动，不能重复进入同一格子。
 *
 * 输入：
 *   char **matrix  矩阵
 *   int rows       行数
 *   int cols       列数
 *   char *str      目标字符串
 *
 * 输出：
 *   bool 是否存在满足条件的路径
 *
 * 样例输入：
 *   matrix = [['A','B','C','E'],
 *             ['S','F','C','S'],
 *             ['A','D','E','E']]
 *   str = "BCCE"
 *
 * 样例输出：
 *   true
 *
 * 思路：
 *   DFS + 回溯
 *   1. 外层 hasPath 遍历矩阵每个格子作为起点，调用 DFS
 *   2. DFS 函数参数：matrix, rows, cols, str, visited, i, j, index
 *      - index 表示当前需要匹配 str 的第几个字符
 *   3. 终止条件：
 *      - index == strlen(str)          → 全部匹配成功，return true
 *      - 越界 / 已访问 / 字符不匹配   → return false
 *   4. 进入当前格子前标记 visited[i][j] = 1
 *      向四个方向递归，传入 index+1
 *      若四个方向全部失败，回溯 visited[i][j] = 0，return false
 *
 * 注意点 / 坑：
 *   1. index 和 i、j 一样作为参数传递，不需要手动重置，天然支持回溯
 *   2. break 只能跳出直接包裹它的那一层循环，双层循环需额外处理
 *   3. visited 是动态申请的二维数组，free 时要先逐行 free，再 free 指针数组
 *   4. 回溯必须在四个方向全部失败后才执行，不能在 return true 之前执行
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool DFS(char **matrix, int rows, int cols, char *str, int **visited, int i, int j, int index)
{
    // 匹配成功
    if (index == strlen(str))
    {
        return true;
    }
    // 越界
    if (i < 0 || i >= rows || j < 0 || j >= cols)
    {
        return false;
    }
    // 已访问
    if (visited[i][j] == 1)
    {
        return false;
    }
    // 字符不匹配
    if (str[index] != matrix[i][j])
    {
        return false;
    }

    visited[i][j] = 1;
    // 往四个方向递归，任意一个方向成功就返回true
    if (DFS(matrix, rows, cols, str, visited, i + 1, j, index + 1))
    {
        return true;
    }
    if (DFS(matrix, rows, cols, str, visited, i - 1, j, index + 1))
    {
        return true;
    }
    if (DFS(matrix, rows, cols, str, visited, i, j + 1, index + 1))
    {
        return true;
    }
    if (DFS(matrix, rows, cols, str, visited, i, j - 1, index + 1))
    {
        return true;
    }
    // 回溯
    visited[i][j] = 0;
    return false;
}

bool hasPath(char **matrix, int rows, int cols, char *str)
{
    int index = 0;
    bool res = false;
    int **visited = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        visited[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        if (res)
        {
            break;
        }
        for (int j = 0; j < cols; j++)
        {
            if (DFS(matrix, rows, cols, str, visited, i, j, index))
            {
                res = true;
                break;
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        free(visited[i]);
    }
    free(visited);
    return res;
}