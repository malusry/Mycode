/*
 * AcWing - 19 - 斐波那契数列
 * https://www.acwing.com/problem/content/19/
 * 时间：2026-03-15
 * 作者：ma1us
 * 题目描述：输入整数 n，求斐波那契数列的第 n 项，从第 0 项开始，F(0) = 0
 * 输入：整数 n（0 ≤ n ≤ 39）
 * 输出：斐波那契数列第 n 项的值
 * 样例输入：n = 5
 * 样例输出：5
 * 思路：
 *   方法一（递归）：
 *     直接按定义递归：F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
 *     存在大量重复计算，但 n ≤ 39 数据范围小，不会超时，可以通过
 *
 *   方法二（迭代 + 数组）：
 *     用数组 f[n+1] 存储每一项，f[0]=0, f[1]=1
 *     从 f[2] 开始逐项推导，每项只计算一次，无重复
 *     注意 malloc 申请的堆内存必须在函数内 free，
 *     因为返回值是 int 值而非指针，调用者无法释放该内存
 *
 * 注意点 / 坑：
 *   1. n=0 时需单独处理，否则 malloc(1个int) 后访问 f[1] 越界
 *   2. 用 malloc 动态分配时，必须先存结果再 free，最后 return 结果
 */
#include <stdlib.h>
// 递归方式
int Fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}
// 非递归方式
int Fibonacci(int n)
{
    if (n < 1)
    {
        return 0;
    }
    int *f = (int *)malloc((n + 1) * sizeof(int));
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
    }
    int result = f[n];
    free(f);
    return result;
}