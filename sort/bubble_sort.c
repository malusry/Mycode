#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false; // 优化：若一趟遍历中没有发生交换，说明已完成排序
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
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
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(data) / sizeof(data[0]);

    bubble_sort(data, n);

    printf("排序后的数组: ");
    print_array(data, n);
    return 0;
}