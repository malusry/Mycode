/*
 * AcWing - 22 - 机器人的运动范围
 * https://www.acwing.com/problem/content/22/
 * 时间：2025-03-16
 * 作者：ma1us
 * 题目描述：地上有一个m行n列的方格，机器人从(0,0)出发，
 *           每次只能上下左右移动一格，不能进入行列坐标数位之和大于k的格子，
 *           求机器人能到达的格子总数。
 * 输入：threshold k, rows m, cols n
 * 输出：可到达的格子总数
 * 样例输入：k=7, m=4, n=5
 * 样例输出：20
 *
 * 思路：DFS从(0,0)出发，递归探索四个方向。
 *       每次进入一个格子前检查三个条件，满足任意一个则return 0：
 *         1. 越界：i<0 || i>=m || j<0 || j>=n
 *         2. 数位之和超限：digitSum(i)+digitSum(j) > k
 *         3. 已访问：visited[i][j]==1
 *       通过检查后标记visited[i][j]=1，
 *       返回值 = 四个方向递归结果之和 + 1（当前格子本身）
 *
 * 注意点 / 坑：
 *   1. digitSum要用while循环通用写法（先%取位再/缩位），不能只处理两位数
 *   2. 动态分配visited时，free顺序必须是先逐行free，再free指针数组
 *   3. DFS返回值必须用变量接住再return，不能忘记return count
 */

int **visited;

int digitSum(int num)
{
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num = num / 10;
    }

    return sum;
}

int DFS(int m, int n, int i, int j, int k)
{
    // 越界
    if (i < 0 || i >= m || j < 0 || j >= n)
    {
        return 0;
    }
    // 数位之和大于k
    if (digitSum(i) + digitSum(j) > k)
    {
        return 0;
    }
    // 已经走过
    if (visited[i][j] == 1)
    {
        return 0;
    }

    visited[i][j] = 1;

    return DFS(m, n, i + 1, j, k) + DFS(m, n, i - 1, j, k) + DFS(m, n, i, j + 1, k) + DFS(m, n, i, j - 1, k) + 1;
}

int movingCount(int threshold, int rows, int cols)
{
    visited = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        visited[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = 0;
        }
    }
    int count = DFS(rows, cols, 0, 0, threshold);
    for (int i = 0; i < rows; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return count;
}