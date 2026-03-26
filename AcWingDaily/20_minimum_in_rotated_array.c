/*
 * AcWing - 20 - 旋转数组的最小数字
 * https://www.acwing.com/problem/content/20/
 * 时间：2026-03-15
 * 作者：ma1us
 * 题目描述：输入一个升序数组的旋转，输出旋转数组的最小元素。数组可能含重复项。
 * 输入：旋转后的数组 nums，数组长度 numsSize
 * 输出：数组中的最小元素，若数组为空返回 -1
 * 样例输入：nums = [2,2,2,0,1]
 * 样例输出：0
 * 思路：
 *   旋转数组由两段升序子数组构成，最小值是右段的最左侧元素。
 *   用二分查找，每次拿 nums[mid] 和 nums[right] 比较：
 *   1. nums[mid] > nums[right]：mid 在左段，最小值在右侧，left = mid + 1
 *   2. nums[mid] < nums[right]：mid 到 right 单调递增，最小值在左侧（含mid），right = mid
 *   3. nums[mid] == nums[right]：无法判断方向，但 right 可以安全去掉
 *      （因为 nums[mid] 和 nums[right] 相等，去掉 right 不会丢失答案），right--
 *   循环终止条件 left == right，答案为 nums[left]
 *
 * 注意点 / 坑：
 *   1. 数组为空（numsSize < 1）时直接返回 -1
 *   2. nums[mid] < nums[right] 时 right = mid 而不是 mid-1，因为 mid 本身可能是答案
 *   3. 有重复元素时不能简单地和 nums[left] 比较，和 nums[right] 比较才是正确做法
 */

int findMin(int *nums, int numsSize)
{
    if (numsSize < 1)
    {
        return -1;
    }
    int left = 0;
    int right = numsSize - 1;

    while (left < right)
    {
        int mid = (left + right) / 2;
        // mid 比 right大，mid 左侧是一个更大的升序序列，最小值只可能在右边
        if (nums[mid] > nums[right])
        {
            left = mid + 1;
        }
        // mid 到 right 是一个升序序列，那代表只可能在mid的左边（包括mid）
        else if (nums[mid] < nums[right])
        {
            right = mid;
        }
        // 相等时可以去掉right，因为不影响最后结果（mid和right值相等）
        else
        {
            right--;
        }
    }
    return nums[left];
}