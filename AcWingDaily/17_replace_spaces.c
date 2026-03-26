/*
 * AcWing - 17 - 替换空格
 * https://www.acwing.com/problem/content/17/
 * 时间：2026-03-09
 * 作者：ma1us
 * 题目描述：把字符串中每个空格替换成"%20"
 * 输入：字符串指针
 * 输出：替换后的新字符串指针
 * 样例输入："We are happy."
 * 样例输出："We%20are%20happy."
 * 思路：
 *   先遍历统计空格数，计算新字符串长度 = 原长度 + 空格数×2 + 1
 *   malloc新数组，用双下标 i 遍历原串、j 写入新串
 *   遇到空格写入'%','2','0'三个字符，否则直接复制
 *   最后 new_str[j] = '\0' 终止字符串
 *   时间复杂度 O(n)，空间复杂度 O(n)
 * 注意点 / 坑：
 *   1. 结尾'\0'要用j定位，不能用strlen(new_str)，malloc的内存未初始化
 *   2. 新数组长度是原长度 + 空格数×2 + 1， +1 给'\0'留位置
 *   3. 调用方用完后需要free返回的指针
 */
#include <string.h>
#include <stdlib.h>
char *replaceSpaces(char *str)
{
    int len = strlen(str);
    int count = 0;
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            count++;
        }
    }

    char *new_str = (char *)malloc((len + count * 2 + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            new_str[j++] = '%';
            new_str[j++] = '2';
            new_str[j++] = '0';
        }
        else
        {
            new_str[j++] = str[i];
        }
    }
    new_str[j] = '\0';

    return new_str;
}