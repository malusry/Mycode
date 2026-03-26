#include <stdio.h>
#include <stdlib.h>

/**
 * 合并两个有序子区间 [left, mid] 和 [mid+1, right]
 */
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组回原数组 arr[left...right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        { // 注意这里的 <= 保证了算法的稳定性
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // 拷贝剩余元素
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

/**
 * 归并排序递归函数
 */
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // 递归分解
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // 合并
        merge(arr, left, mid, right);
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
    int data[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(data) / sizeof(data[0]);

    merge_sort(data, 0, n - 1);

    printf("归并排序后的数组: ");
    print_array(data, n);
    return 0;
}