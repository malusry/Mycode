/*
 * AcWing - 10 - 有依赖的背包问题
 * https://www.acwing.com/problem/content/10/
 * 时间：2026-03-05
 * 作者：ma1us
 * 题目描述：物品间存在父子依赖关系（树状），选择子节点必须先选父节点。求容量V下的最大价值。
 * 输入：物品数N，容量V；每个物品的体积、价值、父节点ID。
 * 输出：最大价值。
 * 样例输入：
 * 5 7
 * 2 3 -1
 * 2 2 1
 * 3 5 1
 * 4 7 2
 * 3 6 2
 * 样例输出：11
 * 思路：
 * 1. 结构存储：使用链式前向星（head, next_edge）存储树形结构。
 * 2. 递归处理：DFS深度优先遍历。对于每个节点 u，先递归计算其所有子树的 DP 结果。
 * 3. 分组背包合并：将每个子树视为一个“物品组”。
 * dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[child][k])
 * 其中 j 是当前 u 分配的总容量，k 是分配给当前正在处理的这棵子树的容量。
 * 4. 强制选择：因为子节点依赖父节点，处理完所有子树后，必须将 u 放入。
 * 原本容量 j 能达到的价值，现在必须变为 j-v[u] 的价值加上 w[u]。
 * 注意点 / 坑：
 * 1. C语言内存：动态分配 2D 数组时，注意 N+1 和 V+1 的边界。
 * 2. 状态更新顺序：合并子树时，容量 j 必须从大到小遍历（类似 01 背包优化），防止同一子树方案被重复计算。
 * 3. 根节点判定：父节点为 -1 时标记为 root。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int *v, *w, *p, *head, *to, *next_edge;
int **dp;
int cnt = 0;
void dfs(int u, int V)
{
    // 第一步：遍历u的所有子节点，递归处理
    for (int i = head[u]; i != 0; i = next_edge[i])
    {
        int child = to[i];
        dfs(child, V); // 先把子树算完

        // 第二步：把child子树的dp合并到u的dp
        for (int j = V; j >= 0; j--)
        {
            for (int k = 0; k <= j; k++)
            {
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[child][k]);
            }
        }
    }

    // 第三步：加上u自身的价值
    for (int j = V; j >= v[u]; j--)
    {
        dp[u][j] = dp[u][j - v[u]] + w[u];
    }
    // 容量不足以选u，由于依赖关系，u的整棵子树都不能选
    for (int j = 0; j < v[u]; j++)
    {
        dp[u][j] = 0;
    }
}

// 类似头插法
void add(int p, int u)
{
    to[++cnt] = u;
    next_edge[cnt] = head[p];
    head[p] = cnt;
}

int main()
{

    int N, V;
    int root;
    scanf("%d %d", &N, &V);
    w = (int *)malloc((N + 1) * sizeof(int));
    p = (int *)malloc((N + 1) * sizeof(int));
    v = (int *)malloc((N + 1) * sizeof(int));
    head = (int *)malloc((N + 1) * sizeof(int));      // 节点u的第一条边的编号
    to = (int *)malloc((N + 1) * sizeof(int));        // 第i条边指向的节点
    next_edge = (int *)malloc((N + 1) * sizeof(int)); // 第i条边的下一条边的编号（同一个父节点的下一个子节点）
    dp = malloc((N + 1) * sizeof(int *));
    // 初始化dp
    for (int i = 1; i <= N; i++)
    {
        dp[i] = (int *)malloc((V + 1) * sizeof(int));
        for (int j = 0; j <= V; j++)
        {
            dp[i][j] = 0;
        }
    }
    // 初始化head
    memset(head, 0, (N + 1) * sizeof(int));
    for (int i = 1; i <= N; i++)
    {

        scanf("%d %d %d", &v[i], &w[i], &p[i]);
        if (p[i] != -1)
        {
            add(p[i], i);
        }
        else
        {
            root = i; // 记录根结点
        }
    }
    dfs(root, V);
    printf("%d\n", dp[root][V]);

    free(v);
    free(w);
    free(p);
    free(head);
    free(to);
    free(next_edge);
    for (int i = 1; i <= N; i++)
    {
        free(dp[i]);
    }
    free(dp);
    return 0;
}