#include <stdio.h>

/**
 * 希尔排序函数
 * @param arr 待排序数组
 * @param n   数组长度
 */
void shell_sort(int arr[], int n)
{
    // 初始增量 gap，并不断缩小
    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        // 对每个分组进行插入排序
        // 逻辑上是多个组交叉进行，实质上是从 gap 索引开始遍历
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            // 组内的插入排序逻辑
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
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
    int data[] = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    int n = sizeof(data) / sizeof(data[0]);

    shell_sort(data, n);

    printf("希尔排序后的数组: ");
    print_array(data, n);

    return 0;
}