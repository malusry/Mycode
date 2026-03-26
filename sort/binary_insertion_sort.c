#include <stdio.h>

void binary_insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        // 二分查找插入位置
        while (left <= right)
        {
            int mid = left + (right - left) / 2; // 防止溢出
            if (key < arr[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        // 移动 left 及其之后的元素
        for (int j = i - 1; j >= left; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

int main()
{
    int data[] = {37, 23, 0, 17, 12, 72, 31};
    int n = sizeof(data) / sizeof(data[0]);
    binary_insertion_sort(data, n);
    printf("折半插入排序结果: ");
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    return 0;
}