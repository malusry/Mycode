#include <stdio.h>
// 返回值为交换的总次数
int get_selection_sort_swaps(int a[], int n)
{
    if (a == NULL || n <= 1)
        return 0; // 边界处理
    int count = 0;
    int min_idx;
    // ... 排序与计数逻辑 ...
    for (int i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
        {
            int temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
            count++;
        }
    }
    return count;
}