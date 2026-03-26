/*
 * AcWing - 2 - 01 Knapsack Problem
 * https://www.acwing.com/problem/content/2/
 *
 * 时间：2026-02-25  xx:xx
 * 作者：ma1us
 *
 * 题目描述：
 *   有 N 件物品和一个容量为 V 的背包。
 *   第 i 件物品的体积是 V_i，价值是 W_i。
 *   求解将哪些物品装入背包可使这些物品的总体积不超过背包容量，且总价值最大。
 *   输出最大价值。
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
 * 8
 *
 * 思路：
 *   经典 01 背包动态规划
 *   dp[j] 表示容量为 j 的背包能获得的最大价值
 *   状态转移：dp[j] = max(dp[j], dp[j - v[i]] + w[i])  (从后往前枚举 j)
 *   时间复杂度：O(N*V)
 *
 * 注意点 / 坑：
 *   - N <= 1000, V <= 1000（数据范围小，可用一维 dp）
 *   - 体积和价值均为正整数
 *   - 初始化：dp[0..V] = 0（不装任何物品价值为 0）
 *   - 必须逆序枚举容量 j，避免物品被多次使用
 */

#include <stdio.h>
#include <stdlib.h> // 使用malloc必须加这个

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
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
        for (int j = V; j >= v[i]; j--)
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