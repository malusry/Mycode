/*
 * AcWing - 9 - 分组背包问题
 * https://www.acwing.com/problem/content/9/
 *
 * 时间：2026-03-01
 * 作者：ma1us
 *
 * 题目描述：
 *   有 N 组物品和容量为 V 的背包，每组物品最多选一件，
 *   每件物品有体积 v 和价值 w，求装入背包的最大价值。
 *
 * 输入：
 *   第一行两个整数 N, V（组数和背包容积）
 *   接下来每组第一行一个整数 s_i（该组物品数量）
 *   该组接下来 s_i 行，每行两个整数 v_ij, w_ij（体积、价值）
 *
 * 输出：
 *   一个整数，表示最大价值
 *
 * 样例输入：
 * 3 5
 * 2
 * 1 2
 * 2 4
 * 1
 * 3 4
 * 1
 * 4 5
 *
 * 样例输出：
 * 8
 *
 * 思路：
 *   分组背包是01背包的扩展，区别在于每组物品只能选一件。
 *
 *   【为什么不能贪心选最大价值】
 *   直接选每组价值最大的物品会忽略体积限制，
 *   可能导致体积超出背包容量，错过更优的组合。
 *   必须综合考虑体积和价值，用动态规划求解。
 *
 *   【状态转移方程】
 *   dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k])
 *   其中 i 是组号，k 是组内物品编号，j 是当前背包容量。
 *   对每个容量 j，枚举组内所有物品找最优的那一件。
 *
 *   【循环顺序的关键】
 *   正确顺序：for 组i → for 容量j（倒序）→ for 组内物品k
 *   错误顺序：for 组i → for 组内物品k → for 容量j（倒序）
 *
 *   错误顺序会导致同一组内多件物品被重复选择：
 *   k=0时物品A更新了dp，k=1时物品B又在A更新后的dp上继续更新，
 *   相当于A和B都被选了，违反"每组只能选一件"的规则。
 *
 *   正确顺序保证对每个容量j，只从组内选一件最优物品更新dp。
 *
 *   【与01背包的对比】
 *   01背包：每件物品选或不选，内层直接更新
 *   分组背包：每组选一件或不选，内层枚举组内所有物品取最优
 *   本质都是保证每个"选择单元"只被选一次。
 *
 *   时间复杂度：O(N * V * S)，S 为每组最大物品数
 *
 * 注意点 / 坑：
 *   - 循环顺序必须是 组→容量→组内物品，不能把容量和组内物品交换
 *   - 容量 j 从 V 倒序到 0，避免同组物品重复选择
 *   - 内层用 if (j >= v[i][k]) 判断容量是否足够，替代循环下界
 *   - v 和 w 都是二维动态数组，按组动态分配
 */

#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int main()
{

    int N, V;
    scanf("%d %d", &N, &V);
    int *s = (int *)malloc(N * sizeof(int));
    int **v = malloc(N * sizeof(int *));
    int **w = malloc(N * sizeof(int *));
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        dp[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &s[i]);
        v[i] = (int *)malloc(s[i] * sizeof(int));
        w[i] = (int *)malloc(s[i] * sizeof(int));
        for (int j = 0; j < s[i]; j++)
        {
            scanf("%d %d", &v[i][j], &w[i][j]);
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = V; j >= 0; j--)
        {
            for (int k = 0; k < s[i]; k++)
            {
                if (j >= v[i][k])
                {
                    dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k]);
                }
            }
        }
    }

    printf("%d\n", dp[V]);

    free(s);
    free(dp);
    for (int i = 0; i < N; i++)
    {
        free(v[i]);
        free(w[i]);
    }
    free(v);
    free(w);

    return 0;
}