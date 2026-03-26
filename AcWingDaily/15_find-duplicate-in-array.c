/*
 * AcWing - 15 - 找出数组中重复的数
 * https://www.acwing.com/problem/content/15/
 * 时间：2026-03-09
 * 作者：ma1us
 * 题目描述：长度为n+1的数组，所有数在1~n范围内，找出任意一个重复的数，不能修改数组。
 * 输入：数组nums，长度numsSize
 * 输出：任意一个重复的数
 * 样例输入：[2, 3, 5, 4, 3, 2, 6, 7]
 * 样例输出：2 或 3
 * 思路：
 *   对值域[1,n]进行二分，而非对数组下标二分。
 *   每次取mid，统计数组中值落在[low,mid]内的元素个数count。
 *   该范围正常应有mid-low+1个不同的数。
 *   若count > mid-low+1，重复数字在左半段，令high=mid；
 *   否则重复数字在右半段，令low=mid+1。
 *   当low==high时，该值即为重复数字。
 * 注意点 / 坑：
 *   1. 二分的是值域，不是下标，low/high代表值而非数组位置
 *   2. 重复在左边时high=mid（不是mid-1），因为mid本身是候选答案
 *   3. C语言整数除法向下取整，mid=(low+high)/2始终偏向low，不会死循环
 *   4. 最终返回low而非nums[low]
 *   5. 时间复杂度O(nlogn)，空间复杂度O(1)
 */
#include <stdio.h>

// 暴力求解
int duplicateInArray(int *nums, int numsSize)
{

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] < 1 || nums[i] >= numsSize)
        {
            return -1;
        }
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] == nums[j])
            {
                return nums[i];
            }
        }
    }
    return -1;
}

// 二分：对值域进行二分[1,n]
int duplicateInArray(int *nums, int numsSize)
{
    int low = 1;
    int high = numsSize - 1;
    while (low < high)
    {
        int mid = (low + high) / 2; // 向下取整
        int count = 0;

        for (int i = 0; i < numsSize; i++)
        {
            if (nums[i] >= low && nums[i] <= mid)
            {
                count++;
            }
        }
        // 出现重复数字
        if (count > (mid - low + 1))
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    return low;
}

int main()
{
    return 0;
}