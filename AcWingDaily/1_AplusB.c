/*
 * AcWing - 1 - A + B
 * https://www.acwing.com/problem/content/1/
 *
 * 时间：2026-02-25  14:28
 * 作者：ma1us
 *
 * 题目描述：
 *   输入两个整数，求这两个整数的和是多少。
 *
 * 输入：
 *   输入两个整数A,B，用空格隔开
 *
 * 输出：
 *   输出一个整数，表示这两个数的和
 * 数据范围:
 *   0 ≤ A,B ≤ 10^8
 * 样例输入：
 * 3 4
 *
 * 样例输出：
 * 7
 *
 * 思路：
 *   你的思路：——————————
 *   时间复杂度：O(1)
 *
 * 注意点 / 坑：
 *   -对输入的a，b值的范围进行一下判断
 *   -要注意a+b的值是否超过int最大表示范围
 */

#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    if ((a < 0 || b < 0) || (a > 100000000 || b > 100000000))
    {
        printf("Invalid Value!\n");
    }
    else
        printf("%d", a + b);
    return 0;
}
