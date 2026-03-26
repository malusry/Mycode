/*
 * AcWing - 14 - 不修改数组找重复数
 * https://www.acwing.com/problem/content/14/
 * 时间：2026-03-08
 * 作者：ma1us
 * 题目描述：长度为n的数组，数字范围0~n-1，找出任意一个重复数字
 * 输入：int数组nums，数组长度numsSize
 * 输出：任意一个重复数字，无重复或有越界数字则返回-1
 * 样例输入：nums = [2, 3, 5, 4, 3, 2, 6, 7]
 * 样例输出：2 或 3
 * 思路：
 *   若无重复，n个数字(0~n-1)可以做到下标i处恰好存放数字i。
 *   利用这个性质，对每个位置i，用while不断将nums[i]交换到它"应在"的位置x=nums[i]：
 *   - 若nums[x]==x，说明x同时出现在i和x两处，重复，返回x
 *   - 否则交换nums[i]与nums[x]，把x送回家，继续处理位置i
 *   - 直到nums[i]==i，当前位置处理完毕，外层for推进到下一个i
 * 注意点 / 坑：
 *   1. 必须先检查x是否越界，再用x做下标访问
 *   2. 交换后要继续处理当前位置i（用while而不是if）
 *   3. nums[i]==i只说明当前位置ok，不能直接返回-1，要继续遍历
 */

#include <stdio.h>

int duplicateInArray(int *nums, int numsSize)
{

    for (int i = 0; i < numsSize; i++)
    {
        int x = nums[i];
        if (x >= numsSize || x < 0)
            return -1;
    }

    for (int i = 0; i < numsSize; i++)
    {
        while (nums[i] != i)
        {
            int x = nums[i];

            if (nums[x] == x)
            {
                return x;
            }
            else
            {
                nums[i] = nums[x];
                nums[x] = x;
            }
        }
    }
    return -1;
}

int main()
{
    return 0;
}