#ifndef SQQUEUE_H
#define SQQUEUE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int ElemType;
#define MAXSIZE 5
typedef struct {
    ElemType data[MAXSIZE];
    int front;  // 队头元素的下标
    int rear;   // 队尾的下一个元素的下标
}SqQueue;

// 初始化顺序循环队列
void InitSqQueue(SqQueue *q)
{
    memset(q,0,sizeof(*q));
    q->rear =0;
    q->front =0;
}
void DestroySqQueue(SqQueue *q)
{
    free(q);
}
void ClearSqQueue(SqQueue *q)
{
    InitSqQueue(q);
}
bool QueueEmpty(SqQueue *q)
{
    return (q->front == q->rear);
}
// 队列是满的
bool QueueFull(SqQueue *q)
{
    return (q->rear +1)%MAXSIZE == q->front;
}
void PrintSqQueue(SqQueue *q)
{
    printf("front=%d, rear=%d\n", q->front, q->rear);
    if (q->front <= q->rear) {
        for(int i=0; i < q->front; i++){
            printf("* ");
        }
        for(int j=q->front; j < q->rear; j++){
            printf("%d ", q->data[j]);
        }
        for(int k=q->rear; k < MAXSIZE; k++){
            printf("* ");
        }
    }
    else {
        for(int i=0; i < q->rear; i++){
            printf("%d ", q->data[i]);
        }
        for(int j=q->rear; j < q->front; j++){
            printf("* ", q->data[j]);
        }
        for(int k=q->front; k < MAXSIZE; k++){
            printf("%d ", q->data[k]);
        }
    }
    printf("\n");
}

// front向后移一个单位长度，或者掉转到开头
void FrontBackward(int *front)
{
    *front = (*front+1)%MAXSIZE;
}
// rear向后移一个单位长度，或者掉转到开头
void RearBackward(int *rear)
{
    *rear = (*rear+1)%MAXSIZE;
}
// 返回队列头元素给e
void GetHead(SqQueue *q, ElemType *e)
{
    *e = q->data[q->front];
}
// 队尾插入元素
int EnQueue(SqQueue *q, ElemType e)
{
    if (QueueFull(q))
        return -1;
    q->data[q->rear] = e;
    RearBackward(&q->rear);
    return 0;
}
// 队头取出元素
int DeQueue(SqQueue *q, ElemType *e)
{
    if (QueueEmpty(q))
        return -1;
    *e = q->data[q->front];
    q->data[q->front] = 0;
    FrontBackward(&q->front);
    return 0;
}
// 队列中已经有的元素个数
int QueueLength(SqQueue *q)
{
    return (q->rear - q->front + MAXSIZE)%MAXSIZE;
}
#endif // SQQUEUE_H
