#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main()
{

    newTree();
    addNode(8, 3);
    addNode(3, 2);
    addNode(1, 3);
    addNode(6, 2);
    addNode(7, 1);
    addNode(10, 9);
    addNode(14, 4);
    addNode(4, 6);
    printf("%d\n", getSize());
    inorder();

    delNode(6);
    printf("%d\n", getSize());
    inorder();

    delNode(3);
    printf("%d\n", getSize());
    inorder();

    struct node *tmp = searchNode(14);
    printf((tmp != NULL ? "YES\n" : "NO\n"));
    tmp = searchNode(13);
    printf((tmp != NULL ? "YES\n" : "NO\n"));

    delNode(14);
    printf("%d\n", getSize());
    inorder();

}
