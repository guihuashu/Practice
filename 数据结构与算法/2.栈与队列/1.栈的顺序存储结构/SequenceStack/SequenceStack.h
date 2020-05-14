#ifndef SEQUENCESTACK_H
#define SEQUENCESTACK_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 栈的顺序存储结构
#define MAXSIZE 5
typedef int StackElemType;
typedef struct SqStack{
    StackElemType data[MAXSIZE];
    int top;    // 栈顶位置在数组中的下标
}SqStack;

void SqStackInfo(SqStack *s)
{
    printf("SqStack: ");
    if (s->top == -1)  {    // 空栈
        printf("empty\n");
    }
    else {
        for(int i=0; i <= s->top;i++){
            printf("%d, ",s->data[i]);
        }
        printf("\n");
    }
}
int InitSqStack(SqStack *s)
{
    if (!s)
        return -1;
    memset(s, 0, sizeof(SqStack));
    s->top = -1;        // 栈顶被初始化为-1
    return 0;
}

// 压栈
int SqStackPush(SqStack *s, StackElemType e)
{
    if (!s) {
        printf("SqStack is non-existent\n");
        return -1;
    }
    if (s->top == (MAXSIZE -1)){
        printf("SqStack is filled\n");
        return -1;
    }
    s->data[(s->top)+1] = e;
    s->top++;
    return 0;
}

// 出栈,e用于存储被删除元素的值
int SqStackPop(SqStack *s, StackElemType *e)
{
    if (!s) {
        printf("SqStack is non-existent\n");
        return -1;
    }
    if (s->top == -1)  {    // 空栈
        printf("SqStack is empty\n");
        return -1;
    }
    *e = s->data[s->top];
    s->top--;
    return 0;
}



#endif // SEQUENCESTACK_H
