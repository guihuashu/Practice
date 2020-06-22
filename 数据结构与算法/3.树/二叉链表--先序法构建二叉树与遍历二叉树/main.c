#include <stdio.h>
#include <BiTree.h>
int main()
{
    printf("please input preOder for a BiTree:\n");
    BTree tree;
    CreateBiTree(&tree);

    printf("BiTree is:\n");
    PreOderTraverse(&tree);
    printf("\n");
    return 0;
}
