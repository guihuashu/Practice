#include <stdio.h>
#include <SequenceStack.h>
int main()
{
    printf("Hello World!\n");
    SqStack s1;
    // 压栈测试
    InitSqStack(&s1);
    SqStackInfo(&s1);
    SqStackPush(&s1,1);
    SqStackInfo(&s1);
    SqStackPush(&s1,2);
    SqStackInfo(&s1);
    SqStackPush(&s1,3);
    SqStackInfo(&s1);
    SqStackPush(&s1,4);
    SqStackInfo(&s1);
    SqStackPush(&s1,5);
    SqStackInfo(&s1);
    SqStackPush(&s1,6);

    // 弹栈测试
    printf("------------------------------\n");
    StackElemType e;
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    SqStackInfo(&s1);
    SqStackPop(&s1,&e);
    return 0;
}
