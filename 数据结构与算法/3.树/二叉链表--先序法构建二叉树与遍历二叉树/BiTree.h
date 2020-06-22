#ifndef BITREE_H
#define BITREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 二叉树的二叉链表节点结构定义 */

typedef char ElemType;
typedef struct BiTreeNode {
    ElemType data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BTNode,*BTree; // 二叉树节点和二叉树的结构形式

/* 按前序输入二叉树中节点的值（一个字符）
   构造二叉链表来表示二叉树T
*/
void CreateBiTree(BTree *T)
{
    ElemType    e;
    //printf("-1\n");
    scanf("%c",&e); // 当前数的根节点的数据
    fflush(stdin);  // 这个必须有
    //printf("0\n");
    if(e == '#')
        *T = NULL;  // 这棵树数空的
    else {          // 建立一颗非空树
        // 1.构建根节点
        *T = (BTree)malloc(sizeof(BTNode));  // 为根节点分配存储空间
        if (!*T)
            exit(-1);
        (*T)->data = e;
       // printf("1\n");
        // 2.创建左子树
        CreateBiTree(&(*T)->lchild);
       // printf("2\n");
        // 3.创建右子树
        CreateBiTree(&(*T)->rchild);
        //printf("end1\n");
    }
   // printf("end2\n");
}
/* 前序遍历二叉树 */
void PreOderTraverse(BTree *T)
{
    //printf("PreOderTraverse\n");
    ElemType e=0;
    if (!*T) { // 这是一颗空数
        printf("#");
    }
    else{
        e = (*T)->data;
        printf("%c",e);   // 构造根节点
        // 分别遍历左子树和右子树
        PreOderTraverse(&(*T)->lchild);
        PreOderTraverse(&(*T)->rchild);
    }

}
#endif // BITREE_H
