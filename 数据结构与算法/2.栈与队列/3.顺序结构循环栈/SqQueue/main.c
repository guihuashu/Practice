#include <stdio.h>
#include <SqQueue.h>
int main()
{
    SqQueue q;
    ElemType e;
    InitSqQueue(&q);
    PrintSqQueue(&q);
    EnQueue(&q,1);
    PrintSqQueue(&q);
    EnQueue(&q,2);
    PrintSqQueue(&q);
    EnQueue(&q,3);
    PrintSqQueue(&q);
    EnQueue(&q,4);
    PrintSqQueue(&q);

    DeQueue(&q, &e);
    PrintSqQueue(&q);
    DeQueue(&q, &e);
    PrintSqQueue(&q);
    DeQueue(&q, &e);
    PrintSqQueue(&q);
    DeQueue(&q, &e);
    PrintSqQueue(&q);

    EnQueue(&q,5);
    PrintSqQueue(&q);
    EnQueue(&q,6);
    PrintSqQueue(&q);
    EnQueue(&q,7);
    PrintSqQueue(&q);
    EnQueue(&q,8);
    PrintSqQueue(&q);

    printf("Hello World!\n");
    return 0;
}
