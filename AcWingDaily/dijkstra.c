#define N 6
#define INF 99999

int dist[N];     // 从起点到各节点的当前最短距离
int selected[N]; // 是否已被选择确认
int graph[N][N] = {
    {0, 4, 2, 0, 0, 0}, // A
    {0, 0, 0, 5, 8, 0}, // B
    {0, 0, 0, 1, 3, 0}, // C
    {0, 0, 0, 0, 0, 2}, // D
    {0, 0, 0, 0, 0, 6}, // E
    {0, 0, 0, 0, 0, 0}, // F
};

void init(int start)
{
    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;   // 除起点外，其余初始化为？
        selected[i] = 0; // 初始都未被选择
    }
    dist[start] = 0; // 起点自己到自己是0
}

int find_min()
{
    int min_index = -1;
    for (int i = 0; i < N; i++)
    {
        if (!selected[i] && (min_index == -1 || dist[i] < dist[min_index]))
        {
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int start)
{
    init(start);

    for (int i = 0; i < N; i++)
    {
        // 第一步：找最小
        int u = find_min();

        // 如果找不到可用节点，提前结束
        if (u == -1)
            break;

        // 第二步：标记为已选择
        selected[u] = 1;

        // 第三步：松弛（暂时留空）
        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] != 0 && !selected[v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}