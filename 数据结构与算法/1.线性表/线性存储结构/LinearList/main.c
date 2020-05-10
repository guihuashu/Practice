#include <stdio.h>
#include <SqList.h>
// 线性表项目
int main()
{
    SqList L1;
    // 插入元素
    ListInit(&L1);
    ListInsert(&L1, 1,1); // 1
    ListInsert(&L1, 2,3); // 1 3
    ListInsert(&L1, 2,2); // 1 2 3
    ListInsert(&L1, 4,4); // 1 2 3 4
//    ListInfo(&L1);

    // 删除元素
    int e;
    ListDelete(&L1, 1, &e); // 2 3 4
    ListDelete(&L1, 2, &e); // 3 4

//    printf("e=%d\n",e);
//    ListInfo(&L1);

    // 合并线性表
    SqList L2;
    SqList L3;
    ListInit(&L2);
    ListInit(&L3);
    ListInsert(&L2, 1,1); // 1
    ListInsert(&L2, 2,2); // 1 3
    ListInsert(&L2, 3,3); // 1 3
    ListInsert(&L3, 1,2); // 1
    ListInsert(&L3, 2,3); // 1 3
    ListInsert(&L3, 3,4); // 1 3
    ListInsert(&L3, 4,5); // 1 3
    ListInfo(&L2);
    ListInfo(&L3);

    ListUnion(&L2, &L3);
    ListInfo(&L2);
    ListInfo(&L3);
    printf("hello world\n");
    return 0;
}





