#include <stdio.h>

/**
 * 分区函数（挖坑法）
 * @param arr  待排序数组
 * @param low  左边界
 * @param high 右边界
 * @return     基准值的最终索引
 */
int partition(int arr[], int low, int high)
{
    int pivot = arr[low]; // 选取第一个元素为基准，留下第一个坑位

    while (low < high)
    {
        // 从右向左，找小于 pivot 的元素
        while (low < high && arr[high] >= pivot)
        {
            high--;
        }
        arr[low] = arr[high]; // 填入左侧坑位，high 成为新坑位

        // 从左向右，找大于 pivot 的元素
        while (low < high && arr[low] <= pivot)
        {
            low++;
        }
        arr[high] = arr[low]; // 填入右侧坑位，low 成为新坑位
    }

    arr[low] = pivot; // 基准值填入最终的坑位 (此时 low == high)
    return low;
}

/**
 * 快速排序主函数
 * @param arr  待排序数组
 * @param low  左边界
 * @param high 右边界
 */
void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        // 划分子数组，获取基准位置
        int pivot_index = partition(arr, low, high);

        // 递归对左右子数组进行排序
        quick_sort(arr, low, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, high);
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
    int data[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(data) / sizeof(data[0]);

    quick_sort(data, 0, n - 1);

    printf("快速排序后的数组: ");
    print_array(data, n);

    return 0;
}