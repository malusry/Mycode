#include <stdio.h>

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i]; // 当前要插入的“牌”
        int j = i - 1;

        // 将比 key 大的元素向后移动
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // 插入到正确位置
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
    int data[] = {12, 11, 13, 5, 6};
    int n = sizeof(data) / sizeof(data[0]);
    insertion_sort(data, n);
    printf("直接插入排序结果: ");
    print_array(data, n);
    return 0;
}