/*
 * AcWing - 6 - 多重背包问题 III
 * https://www.acwing.com/problem/content/6/
 *
 * 时间：2026-02-27
 * 作者：ma1us
 *
 * 题目描述：
 *   有 N 种物品和容量为 V 的背包，第 i 种物品最多有 s_i 件，
 *   每件体积 v_i，价值 w_i，求装入背包的最大价值。
 *
 * 输入：
 *   第一行两个整数 N, V（物品种数和背包容积）
 *   接下来 N 行，每行三个整数 v_i, w_i, s_i（体积、价值、数量）
 *
 * 输出：
 *   一个整数，表示最大价值
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
 *   单调队列优化多重背包，时间复杂度从 O(N*V*S) 降至 O(N*V)
 *
 *   【为什么能用单调队列】
 *   对于某件物品（体积v，价值w，数量s），原始转移：
 *     dp[j] = max( dp[j-k*v] + k*w )  k=0,1,...,s
 *   发现 dp[j] 只依赖与 j 同余于 v 的那些位置，
 *   因此按余数 r = j % v 把 dp 数组分成 v 组，每组独立计算。
 *   组内序列为 r, r+v, r+2v, ...，每个位置只从左边最多 s 个位置转移，
 *   这正是滑动窗口求最大值的结构，可用单调队列解决。
 *
 *   【p 和 q 的含义】
 *   p：当前要更新的位置编号，实际下标 j = r + p*v
 *   q：转移来源的位置编号，实际下标 = r + q*v
 *   p - q：从 q 跳到 p 放了几件物品，要求 0 <= p-q <= s
 *
 *   【状态转移公式推导】
 *   原始：dp[r+p*v] = max{ dp[r+q*v] + (p-q)*w }
 *   展开：= max{ dp[r+q*v] - q*w } + p*w
 *   定义：g[q] = dp[r+q*v] - q*w  （消除随距离变化的偏移量p*w）
 *   最终：dp[r+p*v] = max{ g[q] } + p*w
 *   其中 max{g[q]} 用单调队列在窗口大小 s 内维护
 *
 *   【每个位置 j 的四步操作】
 *   1. 清理过期队头：若 p - q_head > s，队头出队（超出数量限制）
 *   2. 用队头更新答案：dp[j] = g[队头] + p*w
 *   3. 维护队尾单调性：队尾 g 值 <= g[p] 时踢掉队尾（保持队列单调递减）
 *   4. 当前 p 入队
 *
 *   【为什么需要滚动数组】
 *   计算当前物品时，g[q] 依赖的是上一轮的旧 dp 值。
 *   若原地修改 dp，旧值会被新值覆盖导致计算错误。
 *   因此用 g[] 数组保存上一轮 dp，f[]（即dp[]）写入本轮新值。
 *
 *   时间复杂度：O(N * V)
 *
 * 注意点 / 坑：
 *   - 必须用滚动数组，g[] 保存旧值，不可原地修改 dp[]
 *   - 每次枚举新的余数 r 时，队列的 head 和 tail 必须重置
 *   - 数据范围 N, V <= 20000，数组开到 20001 即可
 *   - 队列存的是实际下标 j（或位置编号 p），注意统一用一种
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{

    int N, V;
    scanf("%d %d", &N, &V);

    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *s = (int *)malloc(N * sizeof(int));
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    int *g = (int *)malloc((V + 1) * sizeof(int));
    int q[20001]; // 队列数组，存的是实际下标 j

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

        memcpy(g, dp, (V + 1) * sizeof(int)); // 保存旧dp
        // 对第 i 件物品（体积v[i]，价值w[i]，数量s[i]）
        for (int r = 0; r < v[i]; r++)
        {
            // 每组重置队列
            int head = 0, tail = -1;
            for (int j = r; j <= V; j += v[i])
            {
                // 清理过期队头
                while (head <= tail && (j - q[head]) / v[i] > s[i])
                {
                    head++;
                }
                // 用队头更新 dp[j]
                if (head <= tail)
                {
                    dp[j] = max(g[j], g[q[head]] + (j - q[head]) / v[i] * w[i]);
                }

                // 维护队尾单调性
                while (head <= tail && g[q[tail]] - (q[tail] - r) / v[i] * w[i] <= g[j] - (j - r) / v[i] * w[i])
                {
                    tail--;
                }
                // 入队
                q[++tail] = j;
            }
        }
    }
    printf("%d", dp[V]);
    free(v);
    free(w);
    free(s);
    free(dp);
    free(g);
    return 0;
}