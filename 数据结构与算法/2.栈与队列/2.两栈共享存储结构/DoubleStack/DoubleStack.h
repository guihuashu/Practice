#ifndef DOUBLESTACK_H
#define DOUBLESTACK_H
/*
    （1）引入
        1.如果需要两个相同类型的栈(顺序结构), 分别为了两个栈开辟存储空间。
          极有可能出现的情况是栈1已经满了，而栈2还有很多空闲区域。这样就不合理。
        2.解决方法是使用一个数组来同时存储两个这两个栈，这样可以让两个顺序结构栈动态获得存储空间
        3.两栈共享存储空间的好处是：节省存储空间，降低上溢的可能性。
        4.适用场景:两个栈的空间需求有相反关系（一个需求增加会导致另一个需求下降）时使用。

    （2）存储结构
        数组[bottom1,1,2,3,top1,...,top2,4,9,6,bottom2]		// 数组长度为MAXSIZE
        说明:
            1.栈1在左边,栈2在右边
            2.栈1向右增长,栈2向左增长。
    （3）栈的判定条件
        1.栈1为空
            top1 == 0
        2.栈2为空
            top2 == MAXSIZE
        3.存储空间已满
            top1 +1 == top2
    (4)压栈
        1.存储空间已满就退出
        2.如果压入栈1
            top1的下项存储新元素,top1+1
        2.如果压入栈2
            top2的前项存储新元素,top1-1

    (5)弹栈
        2.如果弹栈1
            如果栈为空,退出。
            删除top1的那一项，top1-1.
        2.如果弹栈2
            如果栈为空,退出。
            删除top2的那一项，top1+1.

 */
#define MAXSIZE 8   // 数组的最大长度
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DElemType;
typedef enum StackNum{
    STACK1 = 1,
    STACK2,
}StackNum;
typedef struct DoubleStack{
    DElemType data[MAXSIZE];
    int top1;   // 栈1的栈顶在数组中的下标
    int top2;   // 栈2的栈顶在数组中的下标
}DoubleStack;

// 初始化双栈
int Init_DoubleStack(DoubleStack *s)
{
    if (!s)
        return -1;
    memset(s, 0, sizeof(DoubleStack));
    s->top1 = -1;            // 栈1的栈顶从数组最左端开始,往右增长.
    s->top2 = MAXSIZE;    // 栈2的栈顶从数组最右端开始,往左增长.
}


// 栈1是空的
int Stack1Empty(DoubleStack *s)
{
    return (s->top1 == -1);
}
// 栈2是空的
int Stack2Empty(DoubleStack *s)
{
    return (s->top2 == MAXSIZE);
}
// 数组满了,不可再压入元素
int StackFull(DoubleStack *s)
{
    return ((s->top1+1) == s->top2);
}
int StackEmpty(DoubleStack *s)
{
    return (Stack1Empty(s) && Stack2Empty(s));
}
void DoubleStackInfo(DoubleStack *s)
{
    if (s->top1 != -1) {
        printf("stack1:");
        for(int i=0; i<= s->top1;i++){
            printf("%d, ", s->data[i]);
        }
    }
    if (s->top2 != MAXSIZE) {
        printf("stack2:");
        for(int i=MAXSIZE-1; i>= s->top2;i--){
            printf("%d, ", s->data[i]);
        }
    }
    if (StackEmpty(s))
        printf("stack is empty");
    printf("\n");
}


// 新元素e放入栈num
int DoubleStackPush(DoubleStack *s,StackNum num, DElemType e)
{
    if (StackFull(s) || !s)
        return -1;
    if (num == STACK1) {
        s->data[++s->top1] = e;
    }
    else if (num == STACK2){
        s->data[--s->top2] = e;
    }
    return 0;
}
// 从栈num中弹出一个元素,而用于返回其值
int DoubleStackPop(DoubleStack *s,StackNum num, DElemType *e)
{
    if (!s || !e)
        return -1;
    if (num == STACK1) {
        if (Stack1Empty(s))
            return -1;
        *e = s->data[s->top1--];
    }
    else if (num == STACK2){
        if (Stack2Empty(s))
            return -1;
        *e = s->data[s->top2++];
    }
    return 0;
}
#endif // DOUBLESTACK_H
