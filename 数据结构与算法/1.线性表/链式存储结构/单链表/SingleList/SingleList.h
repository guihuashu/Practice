#ifndef SINGLELIST_H
#define SINGLELIST_H

///////////////////////////////////// 这是没有头结点的版本文件 //////////////////////////////
///////////////////////////////////// 有头结点的版本更简单些,也不易出错 //////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node,*LinkList;

// 分配新节点并初始化
LinkList NewNode(void)
{
    LinkList new = (LinkList)malloc(sizeof(struct Node));
    if (new)
        memset(new, 0, sizeof(*new));
    return new;
}
void ListInfo(LinkList list)
{
    LinkList pos = list;
    if (!list){
        printf("ListInfo: NULL\n");
        return;
    }
    printf("ListInfo:\n");
    while(pos){
        printf("%d, ",pos->data);
        pos = pos->next;
    }
    printf("\n");
}
// 在单链表list的第i个节点前插入节点e
int ListInsert(LinkList *list, int i, ElemType e)
{
    /* 前提条件: list已经存在,并且i没有超出链表的范围 */
    LinkList pos = *list;
    LinkList new = NewNode();
    new->data = e;

    // 插入到链表的最前面,头指针改变。
    if (i == 1){
        new->next =  pos;
        *list = new; // 头指针改为新插入的节点
    }
    // 插入到链表头指针后面,头指针不改变
    else{
        // 1 2 4==> 1 2 3 4
        //   i=3
        for(int k=1; k <= i-1-1; k++){
            if(!pos) // 插入位置前面的一个节点不存在,无法插入.
                return -1;
            pos = pos->next;
        }
        new->next = pos->next;
        pos->next = new;
        //printf("pos=%p, pos->next=%p\n",pos,pos->next);
    }
    return 0;
}
// 删除单链表list的第i个节点,并将该节点的数据域返回给e。
int ListDelete(LinkList *list, int i, ElemType *e)
{
    LinkList pos = *list;    // 链表头指针

    if (i == 1){                // 删除头指针
        if (e)
            *e = pos->data;
        if (!pos->next)         // 只有头指针,不允许删除。
            return -1;
        *list = pos->next;   // 链表头指针 = 链表头指针的下一项
        free(pos);
    }
    else{               // 删除非头指针
        // 1 2  => 1, i=2
        for(int k=1; k <= i-1-1; k++){
            if(!pos) // 插入位置前面的一个节点不存在,无法插入.
                return -1;
            pos = pos->next;
        }
        // pos为删除位置的前一项
        if (e)
            *e = pos->next->data;
        LinkList del = pos->next;       // 被删除的元素
        pos->next = del->next;
        free(del);
    }
    return 0;
}

void Listfree(LinkList *list)
{
    LinkList head;
    while(*list) {
        head = *list;   // 头指针
        *list = head->next; // 头指针=头指针的下一项
        free(head);      // 释放头指针
        printf("head=%p\n", head);
    }
    //*list = NULL;
}

// 链表最前面插入新元素,链表没有头结点。
void ListAddHead(LinkList *list, LinkList new)
{
    new->next = *list;
    *list = new;
}

// 创建带有n个节点的链表,没有头结点
LinkList ListCreate(int n)
{
    LinkList list = NewNode();
    if (!list)
        return NULL;
    srand(time(0));
    list->data = rand()%1000+1;    // 1000的随机数
    for (int i=1; i <=n-1; i++){

        LinkList new = NewNode();
        new->data = rand()%1000+1;    // 1000的随机数
        if (!new){
            Listfree(&list);
            return NULL;
        }
        ListAddHead(&list,new);
    }
    return list;
}

// 快速找出链表的中间节点,返回节点的序号
int ListMidNode(LinkList list)
{
    /* // 快慢指针法
    1.设置两个指针 *search，*mid，都指向单链表的头结点。
    2.其中*serch的移动速度是*mid的两倍。
    3.先让*search先走。
      如果*search后面有两个节点以上(节点总数为奇数)，那么*search移动两步，*mid移动一步；
      如果*search后面只有一个节点(节点总数为偶数)，那么*search移动一步，mid不移动；
      如果*search后面没有节点时，那么搜索结束。
    4.当*search指向末尾节点的时候，mid正好就在中间了。
        //////////例子//////////////////
        1  2  3  4  5  6  7	// 链表节点
        ms	 				// 第一次搜索
           m  s				// 第二次搜索
              m 	s
                 m	      s // 第三次搜索
    */
    LinkList mid,search;
    mid = search = list; //指向开始位置
    int midPos=1;
    while(search->next){
        if (search->next->next){
            search = search->next->next;
            mid = mid->next;
            midPos++;
        }
        else{
            search = search->next;
        }
    }
    return midPos;
}

// 不分配新空间,逆序链表。
void ListReverse(LinkList *list)
{
    /* p1(head prePos) p2(pos)          p3     // head = p1, prePos=p1, pos=p2
     * p2(head)        p1(prePos)       p3     // head = p2, prePos=p1, pos=p3
     * p3(head)        p2               p1(prePos)    (NULL)pos      // head = p3, prePos=p1, pos=NULL
        步骤: 1.从第二项开始循环往前挪动元素,pos为NULL时结束。
                 1.从链表中断开pos节点
                 2.将pos节点插入到链表头部
             2.重新赋值链表的头指针
    */
    LinkList head   = *list;
    LinkList pos = head->next;
    LinkList posPre = head;    // pos的前一项
        // pos的前一项
    while (pos){
        posPre->next = pos->next;   /* 1.从链表中断开pos节点 */
        pos->next = head;           /* 2.将pos节点插入到链表头部 */
        head = pos;
        // posPre往后移了一项,所以pos = posPre的下一项
        pos = posPre->next;
    }
    /* 重新赋值链表的头指针 */
    *list = head;
}
#endif // SINGLELIST_H
