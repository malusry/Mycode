typedef struct
{
    int i;
    int j;
} Point;

int visited[50][50];

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

int BFS(int m, int n, int k)
{
    // 初始化队列，队头和队尾
    Point queue[50 * 50];
    int head = 0, tail = 0;
    // 记录步数, 从(0,0)开始入队
    int count = 1;
    visited[0][0] = 1;
    queue[tail++] = (Point){0, 0};
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    while (head != tail)
    {
        // 1. 取出队头元素，head++
        Point locate = queue[head++];
        // 2. 用for循环遍历四个方向（用dx dy）
        for (int cnt = 0; cnt < 4; cnt++)
        {
            // 3. 计算新坐标 ni = 当前i + dx[方向], nj = 当前j + dy[方向]
            int i = locate.i + dx[cnt];
            int j = locate.j + dy[cnt];
            // 4. 判断三个条件（越界、数位之和、已访问），不合法就continue
            if (i < 0 || i >= m || j < 0 || j >= n)
            {
                continue;
            }
            if (digitSum(i) + digitSum(j) > k)
            {
                continue;
            }
            if (visited[i][j] == 1)
            {
                continue;
            }
            // 5. 合法就入队，标记visited，count++
            queue[tail++] = (Point){i, j};
            visited[i][j] = 1;
            count++;
        }
    }
    return count;
}

int movingCount(int threshold, int rows, int cols)
{
    if (rows == 0 || cols == 0)
    {
        return 0;
    }
    return BFS(rows, cols, threshold);
}