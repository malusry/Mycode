/*
 * AcWing - 36 - 用栈实现队列
 * https://www.acwing.com/problem/content/36/
 * 时间：2025-03
 * 作者：ma1us
 * 题目描述：用栈的标准操作模拟队列，支持 push/pop/peek/empty
 * 输入：操作序列
 * 输出：pop 和 peek 返回对应元素，empty 返回布尔值
 * 样例输入：
 *   push(1), push(2), peek(), pop(), empty()
 * 样例输出：
 *   1, 1, false
 * 思路：
 *   用两个栈 s1 和 s2 模拟队列：
 *   - push：永远只往 s1 push，与 s2 无关
 *   - pop/peek：若 s2 不为空，直接从 s2 操作；
 *              若 s2 为空，先把 s1 的所有元素一次性倒进 s2，再从 s2 操作
 *   - 倒元素的时机：只在需要出队且 s2 为空时触发，是一次性动作
 *   - empty：s1 和 s2 同时为空才算队列为空
 * 注意点 / 坑：
 *   1. push 条件是 top1 < maxSize - 1，保证 ++top1 后不越界
 *   2. top 初始值为 -1，表示空栈
 *   3. myQueueFree 需要依次 free s1、s2、结构体本身，顺序不能反
 *   4. maxSize 需要存入结构体，否则 push 无法判断栈满
 */

#include <stdlib.h>
#include <stdbool.h>
typedef struct
{
    int *s1, *s2;
    int top1, top2;
    int maxSize;
} MyQueue;

/** Initialize your data structure here. */
MyQueue *myQueueCreate(int maxSize)
{
    MyQueue *q = (MyQueue *)malloc(sizeof(MyQueue));
    q->maxSize = maxSize;
    q->s1 = (int *)malloc(maxSize * sizeof(int));
    q->top1 = -1;
    q->s2 = (int *)malloc(maxSize * sizeof(int));
    q->top2 = -1;
    return q;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue *obj, int x)
{
    if (obj->top1 < obj->maxSize - 1)
    {
        obj->s1[++obj->top1] = x;
    }
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue *obj)
{
    if (obj->top2 != -1)
    {
        return obj->s2[obj->top2--];
    }
    else
    {
        while (obj->top1 >= 0)
        {
            obj->s2[++obj->top2] = obj->s1[obj->top1--];
        }
        return obj->s2[obj->top2--];
    }
}

/** Get the front element. */
int myQueuePeek(MyQueue *obj)
{
    if (obj->top2 != -1)
    {
        return obj->s2[obj->top2];
    }
    else
    {

        while (obj->top1 >= 0)
        {
            obj->s2[++obj->top2] = obj->s1[obj->top1--];
        }
        return obj->s2[obj->top2];
    }
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue *obj)
{
    if (obj->top1 != -1 || obj->top2 != -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void myQueueFree(MyQueue *obj)
{
    free(obj->s1);
    free(obj->s2);
    free(obj);
}