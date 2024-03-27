/*************************************************************************
	> File Name: 06.binary_tree.c
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Mar 2024 11:02:47 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int data;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int val) {
    Node *root = (Node *)calloc(sizeof(Node), 1);
    root->data = val;
    root->lchild = root->rchild = NULL;
    return root;
}

Node *insert(Node *root, int val, int *ret) {
    if (root == NULL) {
        *ret = 1;
        return getNewNode(val);
    }

    if (root->data > val) {
        root->lchild = insert(root->lchild, val, ret);
    } else {
        root->rchild = insert(root->rchild, val, ret);
    }

    return root;
}

void __pre_order(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->data);
    __pre_order(root->lchild);
    __pre_order(root->rchild);
    return ;
}

//前序
void pre_order(Node *root) {
    if (root == NULL) return ;
    printf("前序遍历: ");
    __pre_order(root);
    printf("\n");
    return ;
}

void __mid_order(Node *root) {
    if (root == NULL) return ;
    __mid_order(root->lchild);
    printf(" %d", root->data);
    __mid_order(root->rchild);
    return ;
}

//中序
void mid_order(Node *root) {
    if (root == NULL) return ;
    printf("中序遍历: ");
    __mid_order(root);
    printf("\n");
    return ;
}

void __last_order(Node *root) {
    if (root == NULL) return ;
    __last_order(root->lchild);
    __last_order(root->rchild);
    printf(" %d", root->data);
    return ;
}

//后序
void last_order(Node *root) {
    printf("后序遍历: ");
    __last_order(root);
    printf("\n");
    return ;
}

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
void output(Node *root, int ret) {
    printf("Tree[%d] : ", ret);
    __output(root);
    printf("\n");
    return ;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


int main() {
    #define max_op 10
    Node *root = NULL;
    srand(time(0));
    int opt, val;
    for (int i = 0; i < max_op; i++) {
        int ret = 0;
        val = rand() % 100 + 1;
        root = insert(root, val, &ret);
        output(root, ret);
        pre_order(root);
        mid_order(root);
        last_order(root);
    }
    clear(root);
    #undef max_op
    return 0;
}
