/*
 * ============================================================
 * 文件名：tsp.c
 * 问题：旅行商问题 (Traveling Salesman Problem)
 * 算法：状态压缩 DP (Bitmask DP)
 * 时间复杂度：O(2^n * n^2)
 * 空间复杂度：O(2^n * n)
 * ============================================================
 *
 * 【核心思想】
 * 用一个整数 S 的二进制位表示"哪些城市已经被访问过"
 * 例如 n=4 时：
 *   S = 0101 (5)  → 城市0和城市2已访问
 *   S = 1111 (15) → 4个城市全部访问完毕
 *
 * 状态定义：
 *   dp[S][i] = 从城市0出发，已访问城市集合为S，
 *              当前停在城市i时的最小总花费
 *
 * 转移方程：
 *   dp[S | (1<<j)][j] = min(dp[S][i] + dist[i][j])
 *   含义：从城市i走到未访问的城市j，把j加入已访问集合
 *
 * 初始状态：
 *   dp[1][0] = 0
 *   含义：城市0已访问(S=0001=1)，当前在城市0，花费为0
 *
 * 最终答案：
 *   ans = min(dp[(1<<n)-1][i] + dist[i][0])，i遍历所有城市
 *   含义：所有城市访问完后，从最后停留的城市i回到城市0
 *
 * 【位运算套路】
 *   (1 << n) - 1       → n位全为1，表示n个城市全部访问
 *   S | (1 << j)       → 将城市j加入集合S
 *   S & (1 << j)       → 判断城市j是否在集合S中（非0则在）
 *   !(S & (1 << j))    → 城市j不在集合S中
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f // 用作"无穷大"，memset友好，且两个INF相加不会溢出int
#define MAXN 20        // 城市数量上限

int n;                   // 城市数量
int dist[MAXN][MAXN];    // dist[i][j]：城市i到城市j的距离，INF表示不可达
int dp[1 << MAXN][MAXN]; // dp[S][i]：已访问集合为S，当前在城市i的最小花费
                         // 第一维大小为2^n，枚举所有可能的访问状态

int min(int a, int b)
{
    return a < b ? a : b;
}

/*
 * tsp()
 * 核心DP函数，返回最小旅行花费
 * 若无解（存在不可达情况导致无法完成回路）返回INF
 */
int tsp()
{
    // 初始化所有状态为INF（不可达）
    memset(dp, 0x3f, sizeof(dp));

    // 起点：已访问{城市0}，当前在城市0，花费为0
    // S=1 即二进制0001，表示只有城市0被访问
    dp[1][0] = 0;

    for (int S = 0; S < (1 << n); S++)
    { // 枚举所有已访问城市的集合S
        for (int i = 0; i < n; i++)
        { // 枚举当前所在城市i
            if (dp[S][i] == INF)
                continue; // 此状态不可达，跳过
            if (!(S & (1 << i)))
                continue; // 城市i不在集合S中，非法状态，跳过

            for (int j = 0; j < n; j++)
            { // 枚举下一个要去的城市j
                if (S & (1 << j))
                    continue; // 城市j已访问过，跳过
                if (dist[i][j] == INF)
                    continue; // 城市i到j不可达，跳过

                // 将城市j加入访问集合，更新到达j的最小花费
                int newS = S | (1 << j); // newS：在S基础上加入城市j
                dp[newS][j] = min(dp[newS][j], dp[S][i] + dist[i][j]);
            }
        }
    }

    // 所有城市访问完毕后，从最后的城市i回到出发城市0
    int full = (1 << n) - 1; // full：n位全1，表示所有城市都已访问
    int ans = INF;
    for (int i = 1; i < n; i++)
    { // 枚举最后停在哪个城市i（i=0无需枚举）
        if (dp[full][i] != INF && dist[i][0] != INF)
        {
            ans = min(ans, dp[full][i] + dist[i][0]);
        }
    }

    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    int ans = tsp();

    if (ans == INF)
        printf("No solution\n");
    else
        printf("%d\n", ans);

    return 0;
}