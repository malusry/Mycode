#define N 6
#define INF 99999

typedef struct
{
    int node;
    int dist;
} Entry;
int dist[N];
int selected[N]; // 是否已被选择确认
int graph[N][N] = {
    {0, 4, 2, 0, 0, 0}, // A
    {0, 0, 0, 5, 8, 0}, // B
    {0, 0, 0, 1, 3, 0}, // C
    {0, 0, 0, 0, 0, 2}, // D
    {0, 0, 0, 0, 0, 6}, // E
    {0, 0, 0, 0, 0, 0}, // F
};

void sift_up(Entry heap[], int i)
{
    // i 是新插入元素的下标
    // 当 i 还有父节点，且比父节点小，就交换
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[i].dist < heap[parent].dist)
        {
            // 交换，然后继续往上
            Entry temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        }
        else
        {
            break;
        }
    }
}

void sift_down(Entry heap[], int i, int size)
{
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i; // 假设当前节点最小

        // 如果左子节点存在且更小，更新 smallest
        if (left < size && heap[left].dist < heap[smallest].dist)
        {
            smallest = left;
        }

        // 如果右子节点存在且更小，更新 smallest
        if (right < size && heap[right].dist < heap[smallest].dist)
        {
            smallest = right;
        }
        // 如果 smallest 还是 i，说明不需要交换，结束
        if (smallest == i)
            break;

        // 否则交换，继续往下
        Entry temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
}

void push(Entry heap[], int *size, Entry val)
{
    heap[*size] = val;
    sift_up(heap, *size); // 向上调整堆
    (*size)++;
}

Entry pop(Entry heap[], int *size)
{
    Entry min = heap[0];

    // 把最后一个元素移到堆顶
    heap[0] = heap[*size - 1];

    // size 减一
    (*size)--;

    // 往下调整
    sift_down(heap, 0, *size);

    return min;
}

void init(int start)
{
    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;   // 除起点外，其余初始化为？
        selected[i] = 0; // 初始都未被选择
    }
    dist[start] = 0; // 起点自己到自己是0
}

void dijkstra(int start)
{
    init(start);

    Entry heap[N * N];
    int size = 0;

    // 把起点压入堆
    Entry e;
    e.node = start;
    e.dist = 0;
    push(heap, &size, e);

    while (size > 0)
    {
        // 取出距离最小的节点
        Entry cur = pop(heap, &size);
        int u = cur.node;

        // 如果已经被选择过，跳过
        if (selected[u])
            continue;
        selected[u] = 1;

        // 松弛邻居
        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] != 0 && !selected[v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];

                // 把更新后的邻居压入堆
                Entry next;
                next.node = v;
                next.dist = dist[v];
                push(heap, &size, next);
            }
        }
    }
}