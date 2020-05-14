#include <stdio.h>
#include <DoubleStack.h>
int main()
{
    DoubleStack s;
    DElemType e;
    Init_DoubleStack(&s);
    if (StackEmpty(&s))
        printf("s empty\n");

    DoubleStackPush(&s,STACK1,1);
    DoubleStackPush(&s,STACK2,7);
    DoubleStackPush(&s,STACK1,1);
    DoubleStackPush(&s,STACK2,7);
    DoubleStackPush(&s,STACK1,1);
    DoubleStackPush(&s,STACK2,7);
    DoubleStackPush(&s,STACK1,1);
    DoubleStackPush(&s,STACK2,7);
    DoubleStackPush(&s,STACK1,1);
    DoubleStackPush(&s,STACK2,7);
    DoubleStackInfo(&s);

    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    DoubleStackPop(&s, STACK1,&e);
    DoubleStackPop(&s, STACK2,&e);
    DoubleStackInfo(&s);
    return 0;
}
