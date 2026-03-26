/*
 * 江南大学软件工程专硕 - 25年复试真题第1题 - 字符串分割
 * 时间：2026-03-26
 * 作者：ma1us
 * 题目描述：输入两个字符串str1和str2，str2中的字符作为分隔符，
 *           将str1按分隔符切割后逐行输出，连续分隔符只换行一次
 * 输入：第一行str1，第二行str2
 * 输出：被分割的每一段，每段一行
 * 样例输入：
 *   ab.cfs,/ds
 *   .,/
 * 样例输出：
 *   ab
 *   cfs
 *   ds
 * 思路：遍历str1，对每个字符检查是否在str2中（双层循环）。
 *       用found标志判断当前字符是否是分隔符；
 *       用is_delimiter标志记录上一个字符是否是分隔符，避免连续分隔符多次换行；
 *       用index记录当前段的起始位置；
 *       循环结束后单独打印最后一段。
 * 注意点 / 坑：
 *   1. 连续分隔符时else分支也要更新index = i + 1，否则会把分隔符打印出来
 *   2. is_delimiter重置必须在内层循环外，否则str2多个字符时会误重置
 *   3. 循环结束后最后一段需要单独输出
 */

#include <string.h>
void split(char *str1, char *str2)
{
    int is_delimiter = 0;
    int index = 0;
    for (int i = 0; i < strlen(str1); i++)
    {
        int found = 0;
        for (int j = 0; j < strlen(str2); j++)
        {
            if (str1[i] == str2[j])
            {
                found = 1;
                if (is_delimiter != 1)
                {
                    for (int k = index; k < i; k++)
                    {
                        printf("%c", str1[k]);
                    }
                    printf("\n");
                    index = i + 1;
                    is_delimiter = 1;
                }
                else
                {
                    index = i + 1;
                    break;
                }
            }
        }
        if (!found)
        {
            is_delimiter = 0;
        }
    }
    for (int i = index; i < strlen(str1); i++)
    {
        printf("%c", str1[i]);
    }
    printf("\n");
}