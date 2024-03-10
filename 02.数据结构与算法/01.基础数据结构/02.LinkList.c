/*************************************************************************
	> File Name: 02.LinkList.c
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Mar 2024 08:42:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int data_type;

typedef struct Node {
    data_type data;
    struct Node *next;
}Node;

typedef struct LinkList {
    Node *head;
    int len;
}LinkList;

Node *getNewNode(data_type val) {
    Node *node = (Node *)calloc(sizeof(node), 1);
    node->data = val;
    node->next = NULL;
    return node;
}

LinkList *getNewLinklist() {
    LinkList *l = (LinkList *)calloc(sizeof(LinkList), 1);
    l->head = getNewNode(-1);//虚拟头结点
    l->len = 0;
    return l;
}


int insert(LinkList *l, int ind, data_type val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->len) return 0;
    Node *p = l->head, *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = getNewNode(val);
    p->next->next = q;
    l->len++;
    return 1;
}

int erase(LinkList *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->len) return 0;
    Node *p = l->head, *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->len--;
    return 1;
}

data_type find(LinkList *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->len) return 0;
    Node *p = l->head->next;
    while (ind--) {
        p = p->next;
    }
    return p->data;
}

int update(LinkList *l, int ind, data_type val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->len) return 0;
    Node *p = l->head->next;
    while (ind--) p = p->next;
    p->data = val;
    return 1;
}


void output(LinkList *l) {
    if (l == NULL) return ;
    Node *p = l->head->next;
    printf("LinkList : [%d] => [", l->len);
    int flag = 0;
    while (p != NULL) {
        flag && printf("->"), flag = 1;
        printf(" %d ", p->data);
        p = p->next;
    }
    printf("-> NULL]\n");
    return ;
}



void clearNode(Node *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clearLink(LinkList *l) {
    if (l == NULL) return ;
    Node *p = l->head, *q = NULL;

    while (p != NULL) {
        q = p;
        p = p->next;
        clearNode(q);
    }
    free(l);

    return ;
}


int main() {
    #define max_op 20
    int op, ind, val;
    LinkList *l = getNewLinklist();
    srand(time(0));
    for (int i = 0; i < max_op; i++) {
        op = rand() % 6;
        ind = rand() % (l->len + 2) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert val[%d] to ind[%d] LinkList %d.\n", val, ind, insert(l, ind, val));
            } break;
            case 3: {
                printf("erase ind[%d] from LinkList %d.\n", ind, erase(l, ind));
            } break;
            case 4: {
                printf("find ind[%d] val[%d] from LinkList. \n", ind, find(l, ind));
            } break;
            case 5: {
                printf("update ind[%d] val[%d] to val[%d] LinkList %d\n", ind, find(l, ind), val, update(l, ind, val) );
            } break;
        }
        output(l);
    }
    #undef max_op
    clearLink(l);
    return 0;
}
