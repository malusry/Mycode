#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char val;
    struct Node *left, *right;
} Node;

char seq[100][10];
int idx = 0;

Node *build()
{
    char *val = seq[idx++];
    if (val[0] == '#')
        return NULL; // ① 终止条件

    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val[0];
    node->left = build();  // ② 递归建左子树
    node->right = build(); // ③ 递归建右子树
    return node;
}

void inorder(Node *root)
{
    if (root == NULL)
        return;
    inorder(root->right); // ④ 先遍历哪边？
    printf("%c ", root->val);
    inorder(root->left); // ⑤ 再遍历哪边？
}

#include <stdio.h>

char val[100];
int left_child[100];
int right_child[100];
int cnt = 0;

int build()
{
    char ch;
    scanf(" %c", &ch);
    if (ch == '#')
        return -1;

    int node = cnt++;
    val[node] = ch;
    left_child[node] = build();
    right_child[node] = build();
    return node;
}

void inorder(int node)
{
    if (node == -1)
        return;
    inorder(right_child[node]);
    printf("%c ", val[node]);
    inorder(left_child[node]);
}

int main()
{
    int root = build();
    inorder(root);
    return 0;
}