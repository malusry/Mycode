#include <stdio.h>

void flipHorizontal(int a[][100], int n, int m)
{
    // 每行左右交换
    for (int i = 0; i < n; i++)
    {
        for (int j = 0, k = m - 1; j < k; j++, k--)
        {
            int temp = a[i][j];
            a[i][j] = a[i][k];
            a[i][k] = temp;
        }
    }
}

void flipVertical(int a[][100], int n, int m)
{
    // 每列上下交换
    for (int i = 0; i < m; i++)
    {
        for (int j = 0, k = n - 1; j < k; j++, k--)
        {
            int temp = a[j][i];
            a[j][i] = a[k][i];
            a[k][i] = temp;
        }
    }
}

int main()
{
    int n, m, t, a[100][100];

    // 读入 n, m, t
    scanf("%d %d %d", &n, &m, &t);

    // 读入矩阵
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    // 根据t调用对应函数
    if (t == 0)
        flipHorizontal(a, n, m);
    if (t == 1)
        flipVertical(a, n, m);

    // 输出矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    return 0;
}