#include <stdio.h>
#include <SingleList.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // 1.插入测试
    LinkList list = NewNode();  // 0
    ListInsert(&list,2,1);      // 0 1
    ListInsert(&list,2,3);      // 0 3 1
    ListInsert(&list,3,4);      // 0 3 4 1
    ListInsert(&list,5,6);      // 0 3 4 1 6
    ListInsert(&list,5,6);      // 0 3 4 1 6
    ListInsert(&list,1,7);      // 7 0 3 4 1 6
    ListInsert(&list,1,8);      // 8 7 0 3 4 1 6
    ListInsert(&list,4,9);      // 8 7 0 9 3 4 1 6
    //ListInfo(list);

    // 2.删除测试
    LinkList list2 = NewNode();  // 0
    ElemType re;
    ListInsert(&list2,1,3);      // 3 0
    ListInsert(&list2,1,2);      // 2 3 0
    ListInsert(&list2,1,1);      // 1 2 3 0
    ListDelete(&list2,1,&re);    // 2 3 0
    ListDelete(&list2,3,&re);    // 2 3
    ListDelete(&list2,1,&re);    // 3
    //ListInfo(list2);

    // 3.整表创建,删除测试.
    LinkList list3 = ListCreate(5);
    ListInfo(list3);
    Listfree(&list3);

    // 4.测试寻找中间节点
    LinkList list4 = ListCreate(1);  // 1
    LinkList list5 = ListCreate(2);  // 1
    LinkList list6 = ListCreate(3);  // 2
    LinkList list7 = ListCreate(4);  // 2
    LinkList list8 = ListCreate(5);  // 3
//    printf("midpos=%d\n",ListMidNode(list4));
//    printf("midpos=%d\n",ListMidNode(list5));
//    printf("midpos=%d\n",ListMidNode(list6));
//    printf("midpos=%d\n",ListMidNode(list7));
//    printf("midpos=%d\n",ListMidNode(list8));

    // 链表逆序测试
    LinkList list9 = ListCreate(6);
    ListInfo(list9);
    ListReverse(&list9);
    ListInfo(list9);
    return 0;
}
