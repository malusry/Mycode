/*
 * AcWing - 4 - Multiple Knapsack Problem
 * https://www.acwing.com/problem/content/4/
 *
 * 时间：2026-02-26  xx:xx
 * 作者：ma1us
 *
 * 题目描述：
 *   有 N 种物品和一个容量为 V 的背包。
 *   第 i 种物品最多有 si 件可用，每件体积 vi，价值 wi。
 *   求解将哪些物品装入背包可使这些物品的总体积不超过背包容量，且总价值最大。
 *
 * 输入：
 *   第一行：两个整数 N V，用空格隔开。
 *   接下来 N 行：每行三个整数 vi wi si，用空格隔开。
 *
 * 输出：
 *   一个整数，表示最大价值。
 *
 * 样例输入：
 * 4 5
 * 1 2 3
 * 2 4 1
 * 3 4 3
 * 4 5 2
 *
 * 样例输出：
 * 10
 *
 * 思路：
 *   多重背包问题（每种物品有限次数 si）
 *   标准做法：二进制优化（将 si 拆成 1,2,4,...,2^k + 余数，每组当成一个 01 物品）
 *   或者直接三重循环：for i, for j=V downto vi, for k=1 to si (if j>=k*vi)
 *   时间复杂度：二进制优化 O(N*V*log S)，直接三重 O(N*V*S)，S<=100
 *   推荐用二进制优化，更稳
 *
 * 注意点 / 坑：
 *   - si 可以达到 100~1000，N<=100, V<=1000
 *   - 二进制优化后物品数变为 O(N log S)，仍可接受
 *   - 拆分时注意余数处理：如 si=13 → 1,2,4,6
 *   - dp 初始化为 0
 *   - 容量枚举倒序（01背包风格）
 */

#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int N, V;
    scanf("%d %d", &N, &V);

    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *s = (int *)malloc(N * sizeof(int));
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        dp[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &v[i], &w[i], &s[i]);
    }

    for (int i = 0; i < N; i++)
    {
        int vol = v[i], val = w[i], cnt = s[i]; // 数量
        // 二进制拆分 + 立即更新
        for (int k = 1; k <= cnt; k *= 2)
        {
            int pack_vol = k * v[i];
            int pack_val = k * w[i];

            // 把这个“打包物品”当成一个 01 物品更新 dp
            for (int j = V; j >= pack_vol; j--)
            {
                dp[j] = max(dp[j], dp[j - pack_vol] + pack_val);
            }
            cnt -= k;
        }
        // 处理余数
        if (cnt > 0)
        {
            int pack_vol = cnt * v[i];
            int pack_val = cnt * w[i];
            for (int j = V; j >= pack_vol; j--)
            {
                dp[j] = max(dp[j], dp[j - pack_vol] + pack_val);
            }
        }
    }

    printf("%d\n", dp[V]);

    free(v);
    free(w);
    free(s);
    free(dp);

    return 0;
}