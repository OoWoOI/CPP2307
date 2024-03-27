/*************************************************************************
	> File Name: 07.table2tree.c
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Mar 2024 11:40:53 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
}Node;

typedef struct stack {
    Node **data;
    int top;
}stack;

//初始化
Node *getNewNode(int val) {
    Node *root = (Node *)calloc(sizeof(Node), 1);
    root->data = val;
    root->lchild = root->rchild = NULL;
    return root;
}

stack *getNewStack(int size) {
    stack *stk = (stack *)calloc(sizeof(stack), 1);
    stk->data = (Node **)calloc(sizeof(Node *), size);
    stk->top = -1;
    return stk;
}

//栈操作
int empty(stack *stk) {
    return stk->top == -1;
}

void push(stack *stk, Node *root) {
    stk->data[++stk->top] = root;
    return ;
}

void pop(stack *stk) {
    if (empty(stk)) return ;
    stk->top--;
    return ;
}

Node *top(stack *stk) {
    if (empty(stk)) return NULL;
    return stk->data[stk->top];
}

void clearStack(stack *stk);

//树操作
Node *in2tree(char *str, int *cnt) {
    Node *temp = NULL, *p = NULL;
    int flag = 0;//0插左边，1插右边;
    stack *stk = getNewStack(strlen(str));
    while (str[0]) {
        switch(str[0]) {
            case '(': {
                flag = 0;
                push(stk, temp);
                temp = NULL; 
            }
                break;
            case ',': {
                flag = 1;
                temp = NULL;
            }
                break;
            case ')': {
                p = top(stk);
                pop(stk);
            }
                break;
            case ' ':
                
                break;
            default : {
                int val = str[0] - '0';
                while (str[0] <= '9' && str[0] >= '0') {
                    val = val * 10 + (str[0] - '0');
                    printf("%d\n", val);
                    if (*(str + 1) > '9' || *(str + 1) < 0) break;
                    ++str;
                }
                temp = getNewNode(val);
                if (!empty(stk) && flag == 0) {
                    top(stk)->lchild = temp;
                } else if (!empty(stk) && flag == 1) {
                    top(stk)->rchild = temp;
                }
                ++(*cnt);
            }
                break;
        }
        ++str;
    } 
    clearStack(stk);
    if (temp && !p) p = temp;
    return p;
}

//输出树型结构
void __output(Node *root) {
    if (root == NULL) return ;
    printf("%d", root->data);
    printf("(");
    __output(root->lchild);
    printf(",");
    __output(root->rchild);
    printf(")");
    return ;
}
void output(Node *root, int cnt) {
    printf("Tree [%d]: ", cnt);
    __output(root);
    printf("\n");
    return ;
}

//结构回收
void clearNode(Node *root) {
    if (root == NULL) return ;
    clearNode(root->lchild);
    clearNode(root->rchild);
    free(root);
    return ;
}

void clearStack(stack *stk) {
    if (stk == NULL) return ;
    if (stk->top == -1) free(stk);
    else perror("clearStack");
    return ;
}

int main() {
    char str[1024] = {0};
    int cnt = 0;
    scanf("%[^\n]", str);
    Node *root = in2tree(str, &cnt);
    output(root, cnt);
    return 0;
}
