#ifndef SqList_H
#define SqList_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int ElemType;
#define MAXSIZE 20
typedef enum{
    OK=0,
    ERROR=-1,
}Status;

typedef struct {
    ElemType data[MAXSIZE];
    int length;
}SqList;

void ListInit(SqList *L)
{
   memset(L,0,sizeof(*L)) ;
}
// 打印线性表的长度及元素
void ListInfo(SqList *L)
{
    // 前提：L已经存在
    printf("SqList's length is: %d\n", L->length);
    for(int i=0; i <=L->length-1; i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

// 在线性表的第i个位置之前插入元e，i从1开始。
Status ListInsert(SqList *L,int i,ElemType e)
{
    // 前提：L已经存在
    /*元素:        1 2 3
      下标:        0 1 2
      length:     1 2 3 4
      下标范围:	  0~MAXSIZE-1
      i范围:    	  1~MAXSIZE
      可插入的i范围: 1~length+1
    */
    if (i > MAXSIZE+1)
        return ERROR;
    if (L->length == MAXSIZE)   // 线性表满了
        return ERROR;
    if (i<1 || i>(L->length+1)) // 插入位置不在线性表范围中
        return ERROR;
    /* 1 2   // length=2
     * 1 3 2 // 比如在i=2的位置插入3
     */
    // 最后一个位置前面插入，需要先往后移动元素
    int index;
    if (i <= L->length+1)  {
        // 元素线性表中需要往后移的下标
        for(index=L->length-1; index >= i-1;index--){
            L->data[index+1] =  L->data[index]; // 数据往后移
        }
    }
    L->data[i-1] = e; // 在插入位置写入新元素
    L->length++;
    return OK;
}

// 删除第i个元素，并将其值返回为e
Status ListDelete(SqList *L,int i,ElemType *e)
{
    if (!L || i<1 || i>MAXSIZE || !e || i>L->length)
        return ERROR;
    /* 1 2 3 length=3， i=2
       1 3
     */
    *e = L->data[i-1];
    if (i < L->length) {    // 删除非最后一个元素，需要向前移动
        // 需要往前移动
        for(int k=i; k<=L->length-1; k++){
            L->data[k-1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

// 如果L中存在e地址中存储的值,就返回true
bool LocateElem(SqList *L, ElemType *e)
{
    for (int k = 0; k <= L->length; k++){
        if (L->data[k] == *e)
            return true;
    }
    return false;
}
// 合并链表：L1 = L1 U L2,
Status ListUnion(SqList *L1,SqList *L2)
{
    // 思路：将在L2中且不在L1中的元素加入到L1中。
    if (!L1 || !L2)
        return ERROR;
    // L1: 1 2 length=2
    // L2: 3 4
    for (int k=0; k <= L2->length-1; k++){
        if (!LocateElem(L1, &L2->data[k])){ // L1中存在值L2->data[k],返回true
            ListInsert(L1, L1->length+1, L2->data[k]);
            printf("k=%d\n", k);
        }
    }
    return OK;
}

#endif  // SqList_H
