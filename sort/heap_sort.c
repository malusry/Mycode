#include <stdio.h>
void sift_up(int heap[], int i)
{
    // i 是新插入元素的下标
    // 当 i 还有父节点，且比父节点小，就交换
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[i] < heap[parent])
        {
            // 交换，然后继续往上
            int temp = heap[i];
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

void sift_down(int heap[], int i, int size)
{
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i; // 假设当前节点最小

        // 如果左子节点存在且更小，更新 smallest
        if (left < size && heap[left] < heap[smallest])
        {
            smallest = left;
        }

        // 如果右子节点存在且更小，更新 smallest
        if (right < size && heap[right] < heap[smallest])
        {
            smallest = right;
        }
        // 如果 smallest 还是 i，说明不需要交换，结束
        if (smallest == i)
            break;

        // 否则交换，继续往下
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
}

void push(int heap[], int *size, int val)
{
    heap[*size] = val;
    sift_up(heap, *size); // 向上调整堆
    (*size)++;
}

int pop(int heap[], int *size)
{
    int min = heap[0];

    // 把最后一个元素移到堆顶
    heap[0] = heap[*size - 1];

    // size 减一
    (*size)--;

    // 往下调整
    sift_down(heap, 0, *size);

    return min;
}
void heap_sort(int arr[], int n)
{
    int heap[n];
    int size = 0;

    // 第一步：全部压入堆
    for (int i = 0; i < n; i++)
    {
        push(heap, &size, arr[i]);
    }

    // 第二步：依次取出，写回原数组
    for (int i = 0; i < n; i++)
    {
        arr[i] = pop(heap, &size);
    }
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int data[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(data) / sizeof(data[0]);

    heap_sort(data, n);

    printf("堆排序后的数组: ");
    print_array(data, n);
    return 0;
}