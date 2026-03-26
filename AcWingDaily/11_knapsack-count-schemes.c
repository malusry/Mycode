/*
 * AcWing - 11 - 背包问题求方案数
 * https://www.acwing.com/problem/content/11/
 * 时间：2026-03-06
 * 作者：ma1us
 * 题目描述：给定N件物品和容量为V的背包，每件物品有体积v[i]和价值w[i]，
 *           求装入背包的最大价值，以及达到最大价值的方案总数。
 * 输入：第一行N和V，接下来N行每行两个整数v[i]和w[i]
 * 输出：一个整数，方案数对1000000007取模
 * 样例输入：3 5 / 1 2 / 2 4 / 3 4
 * 样例输出：2
 * 思路：
 *   在01背包基础上新增cnt[j]数组，表示达到dp[j]这个最大价值的方案数。
 *   初始化：dp[j]=0，cnt[j]=1（什么都不选也是一种方案）。
 *   转移分三种情况：
 *   1. dp[j-v]+w > dp[j]：选当前物品更优，cnt[j] = cnt[j-v]
 *   2. dp[j-v]+w < dp[j]：不选更优，cnt[j]不变
 *   3. dp[j-v]+w == dp[j]：两条路打平，cnt[j] = (cnt[j] + cnt[j-v]) % MOD
 * 注意点 / 坑：
 *   1. 内层循环下界是v[i]不是0，否则j-v[i]为负数导致非法访问
 *   2. cnt累加过程中就要取模，不能只在最后取模
 *   3. 输入用v[i]和w[i]，不能用&v和&w
 */
#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
int main()
{
    int N, V;
    scanf("%d %d", &N, &V);
    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    int *cnt = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        dp[i] = 0;
        cnt[i] = 1;
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &v[i], &w[i]);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = V; j >= v[i]; j--)
        {
            if (dp[j - v[i]] + w[i] > dp[j])
            {
                dp[j] = dp[j - v[i]] + w[i];
                cnt[j] = cnt[j - v[i]];
            }
            else if (dp[j - v[i]] + w[i] == dp[j])
            {
                cnt[j] = (cnt[j] + cnt[j - v[i]]) % MOD;
            }
        }
    }
    printf("%d", cnt[V]);
    return 0;
}