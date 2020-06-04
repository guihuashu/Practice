#ifndef LISTQUEUE_H
#define LISTQUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int ElemType;
typedef struct Node_{
    ElemType e;
    struct Node_ *next;
}Node,*NodePtr;

typedef struct {
    NodePtr head;   // 头结点,队列头的前一个元素
    NodePtr rear;   // 队尾节点
    int len;        // 队列长度
}LinkQueue;

NodePtr MallocNode()
{
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    p->next = NULL;
    return p;
}

void InitQueue(LinkQueue *q)
{
   q->head = MallocNode();
   q->rear =  q->head;
   q->len = 0;
}
void PrintQueue(LinkQueue *q)
{
    NodePtr p = q->head->next;
    while(p){
        printf("%d ",p->e);
        p = p->next;
    }
    printf("\n");
}
// 入队操作
int EnQueue(LinkQueue *q, ElemType e)
{
   NodePtr new = MallocNode();
   new->e = e;
   new->next = NULL;
   q->rear->next = new;
   q->rear = new;
   q->len++;
   return 0;
}
// 出队操作
int DeQueue(LinkQueue *q, ElemType *e)
{
    if (q->len == 0) // 队列是空的
        return -1;
    NodePtr del = q->head->next;    // 队列头
    *e = del->e;
    q->head->next = del->next;
    q->len--;
    free(del);
    if (q->len == 0)
       q->rear = q->head;
    return 0;
}


#endif // LISTQUEUE_H
