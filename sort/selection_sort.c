#include <stdio.h>

void selection_sort(int arr[], int n)
{
    int min_idx;

    // 移动未排序子数组的边界
    for (int i = 0; i < n - 1; i++)
    {
        // 寻找 [i, n-1] 区间内的最小元素索引
        min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        // 将找到的最小元素与当前边界位置 i 交换
        if (min_idx != i)
        {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int data[] = {64, 25, 12, 22, 11};
    int n = sizeof(data) / sizeof(data[0]);

    selection_sort(data, n);

    printf("排序后的数组: ");
    print_array(data, n);
    return 0;
}