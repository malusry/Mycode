#include <stdio.h>
#include <string.h>

int findLongestSubstr(char *str, int n, char c)
{
    int dp[100] = {0};

    // 处理第一个字符
    if (str[0] == c)
        dp[0] = 1;

    // 从第2个字符开始遍历
    for (int i = 1; i < n; i++)
    {
        if (str[i] != c)
            dp[i] = 0;
        else if (str[i - 1] == c)
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 1;
    }

    // 找最大值
    int max = dp[0];
    for (int i = 1; i < n; i++)
        if (dp[i] > max)
            max = dp[i];

    return max;
}

int main()
{
    char str[100];
    char c;
    int n = 0;

    // 逐个读入字符，直到遇到空格停止
    while ((str[n++] = getchar()) != ' ')
        ;

    // 读入目标字符c（注意前面有换行符，用空格格式消除）
    scanf(" %c", &c);

    // 调用函数并输出结果
    printf("%d", findLongestSubstr(str, n, c));

    return 0;
}
