/*
 * AcWing - 3 - Complete Knapsack Problem
 * https://www.acwing.com/problem/content/3/
 *
 * 时间：2026-02-25
 * 作者：ma1us
 *
 * 题目描述：
 *   有 N 种物品和一个容量为 V 的背包。
 *   第 i 种物品的体积是 vi，价值是 wi。
 *   每种物品可以选任意多个（无限次），求最大价值。
 *
 * 输入：
 *   第一行：两个整数 N V，用空格隔开。
 *   接下来 N 行：每行两个整数 vi wi，用空格隔开。
 *
 * 输出：
 *   一个整数，表示最大价值。
 *
 * 样例输入：
 * 4 5
 * 1 2
 * 2 4
 * 3 4
 * 4 5
 *
 * 样例输出：
 * 10
 *
 * 思路：
 *   经典完全背包动态规划
 *   dp[j] 表示容量为 j 的背包能获得的最大价值
 *   状态转移：dp[j] = max(dp[j], dp[j - v[i]] + w[i])  (正序枚举 j)
 *   时间复杂度：O(N*V)
 *
 * 注意点 / 坑：
 *   - 与 01 背包区别：完全背包物品可无限使用 → 正序枚举容量 j
 *   - 数据范围：N <= 1000, V <= 1000
 *   - 初始化：dp[0..V] = 0
 *   - 边界：j < v[i] 时跳过
 */

#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    // 你的代码从这里开始
    int N, V;
    scanf("%d %d", &N, &V);

    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    // 输入物品
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &v[i], &w[i]);
    }

    // 初始化 dp
    for (int j = 0; j <= V; j++)
    {
        dp[j] = 0;
    }

    // 核心 DP
    for (int i = 0; i < N; i++)
    {
        for (int j = v[i]; j <= V; j++) // 从 v[i] 开始
        {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }

    printf("%d\n", dp[V]); // 加个换行，更规范

    // 释放内存（好习惯）
    free(v);
    free(w);
    free(dp);

    return 0;
}