/*
 * AcWing - 12 - 背包问题求具体方案
 * https://www.acwing.com/problem/content/12/
 * 时间：2026-03-06
 * 作者：ma1us
 * 题目描述：给定N件物品和容量为V的背包，每件物品有体积v[i]和价值w[i]，
 *           求装入背包达到最大价值的方案中，字典序最小的选法。
 * 输入：第一行N和V，接下来N行每行两个整数v[i]和w[i]
 * 输出：字典序最小的方案，输出选中物品的编号
 * 样例输入：4 5 / 1 2 / 2 4 / 3 4 / 4 6
 * 样例输出：1 4
 * 思路：
 *   1. 建后缀DP：g[i][j]表示第i件到第N件物品在容量j下的最大价值。
 *      转移方程：g[i][j] = max(g[i+1][j], g[i+1][j-v[i]]+w[i])
 *      从i=N往i=1推，边界g[N+1][j]=0。
 *   2. 正向贪心：从i=1开始，维护剩余容量vol和剩余目标价值target。
 *      若 g[i+1][vol-v[i]]+w[i] == target，则选物品i，
 *      更新vol和target，否则跳过。
 *      从编号小的开始贪心，保证字典序最小。
 * 注意点 / 坑：
 *   1. 一维滚动数组无法回溯，必须用二维DP保留历史状态
 *   2. 前缀DP无法回答"第i到N件能凑多少价值"，需要专门建后缀DP
 *   3. 贪心时vol和target必须定义在循环外，在迭代间传递状态
 *   4. g数组大小要分配到N+2，因为转移会访问g[N+1]
 */

#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int N, V;
    scanf("%d %d", &N, &V);
    int *v = (int *)malloc((N + 1) * sizeof(int));
    int *w = (int *)malloc((N + 1) * sizeof(int));
    int *selected = (int *)malloc((N + 1) * sizeof(int));
    int **g = malloc((N + 2) * sizeof(int *)); // 边界g[N+1][j]=0

    for (int i = 0; i < N + 2; i++)
    {
        g[i] = (int *)malloc((V + 1) * sizeof(int));
        for (int j = 0; j <= V; j++)
        {
            g[i][j] = 0;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        selected[i] = 0;
        scanf("%d %d", &v[i], &w[i]);
    }

    // 计算第i件到第N件物品在容量j下的最大价值 g[i][j]
    for (int i = N; i >= 1; i--)
    {
        for (int j = V; j >= 0; j--)
        {
            if (j >= v[i])
            {
                g[i][j] = max(g[i + 1][j], g[i + 1][j - v[i]] + w[i]);
            }
            else
            {
                g[i][j] = g[i + 1][j];
            }
        }
    }
    int vol = V;
    int target = g[1][V];
    // 正向贪心找字典序最小方案
    for (int i = 1; i <= N; i++)
    {
        if (vol >= v[i] && g[i + 1][vol - v[i]] + w[i] == target)
        {
            selected[i] = i;
            vol -= v[i];
            target -= w[i];
        }
    }
    for (int i = 1; i <= N; i++)
    {
        if (selected[i] != 0)
        {
            printf("%d ", selected[i]);
        }
    }

    return 0;
}