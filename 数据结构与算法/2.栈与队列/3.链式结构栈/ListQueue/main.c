#include <stdio.h>
#include <listqueue.h>
int main()
{
    LinkQueue q;
    ElemType e;

    InitQueue(&q);
    EnQueue(&q,1);
    PrintQueue(&q);
    EnQueue(&q,2);
    PrintQueue(&q);
    EnQueue(&q,3);
    PrintQueue(&q);

    DeQueue(&q,&e);
    PrintQueue(&q);
    DeQueue(&q,&e);
    PrintQueue(&q);
    DeQueue(&q,&e);
    PrintQueue(&q);


    return 0;
}
