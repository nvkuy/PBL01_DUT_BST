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
    inorder();

    delNode(6);
    inorder();

    delNode(3);
    inorder();

    struct node *tmp = searchNode(14);
    printf((tmp != NULL ? "YES\n" : "NO\n"));
    tmp = searchNode(13);
    printf((tmp != NULL ? "YES\n" : "NO\n"));

}
