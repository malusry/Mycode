/*
 * AcWing - 16 - 在二维数组中查找数
 * https://www.acwing.com/problem/content/16/
 * 时间：2026-03-09
 * 作者：ma1us
 * 题目描述：在一个行列均递增的二维数组中，判断是否含有某个整数
 * 输入：二维数组指针、行数、列数、目标值
 * 输出：true 或 false
 * 样例输入：array = [[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]], target = 7
 * 样例输出：true
 * 思路：
 *   从右上角出发，该位置特殊性：行内最大、列内最小
 *   当前值 > target → 整列可排除，col--（左移）
 *   当前值 < target → 整行可排除，row++（下移）
 *   每次移动必然排除一行或一列，最多移动 rows+cols 次
 *   时间复杂度 O(rows+cols)
 * 注意点 / 坑：
 *   1. rows或cols为0时直接返回false，防止越界
 *   2. 不能从左上角或右下角出发，两个方向都可走，无法确定唯一方向
 */
#include <stdio.h>
#include <stdbool.h>

bool searchArray(int **array, int arrayRowSize, int arrayColSize, int target)
{
    if (arrayRowSize == 0 || arrayColSize == 0)
    {
        return false;
    }
    // 定义行列下标, 作为位置, 从右上角出发
    int row = 0;
    int col = arrayColSize - 1;
    while (row < arrayRowSize && col >= 0)
    {
        if (array[row][col] == target)
        {
            return true;
        }

        if (array[row][col] < target)
        {
            row++;
        }
        else
        {
            col--;
        }
    }
    return false;
}
