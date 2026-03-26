#include <stdio.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

int *printListReversingly(struct ListNode *head)
{
    struct ListNode *p = head;
    int len = 0;
    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    if (len == 0)
        return NULL;
    int *result = (int *)malloc(len * sizeof(int));
    int j = 0;
    p = head;
    while (p != NULL)
    {
        int index = len - 1 - j++;
        result[index] = p->val;
        p = p->next;
    }
    return result;
}