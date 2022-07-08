#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int key, value;
    struct node *left, *right, *parent;
};

struct node *newNode(int nkey, int nval, struct node *pre)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = nkey;
    temp->value = nval;
    temp->left = temp->right = NULL;
    temp->parent = pre;
    return temp;
}

struct node *find(struct node *node, int key) {
    if (node == NULL)
        return node;
    if (key < node->key)
        return find(node->left, key);
    else if (key > node->key)
        return find(node->right, key);
    else
        return node;
}

struct node *insert(struct node *node, int key, int value, struct node *pre, int isRoot)
{

    if (node == NULL) {
        return newNode(key, value, ((isRoot == 0) ? pre : NULL));
    }

    if (key < node->key)
        node->left = insert(node->left, key, value, node, 0);
    else if (key > node->key)
        node->right = insert(node->right, key, value, node, 0);
    else
        node->value = value;

    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    while (current != NULL && current->left != NULL)
        current = current->left;

    return current;
}

struct node *maxValueNode(struct node *node)
{
    struct node *current = node;

    while (current != NULL && current->right != NULL)
        current = current->right;

    return current;
}

struct node *deleteNode(struct node *root, int key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

//Binary search tree operations
struct node *root;
int treeSize;

void newTree() {
    treeSize = 0;
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

struct node *searchNode(int key) {
    struct node *node = find(root, key);
    return node;
}

struct node *getBeginNode() {
    return minValueNode(root);
};

struct node *nextNode(struct node *curNode) {
    if (curNode->right != NULL)
        return minValueNode(curNode->right);
    struct node *par = curNode->parent;
    while (par != NULL && curNode->key > par->key) {
        curNode = par;
        par = par->parent;
    }
    return par;
}

void inorder() {
    struct node *it = getBeginNode();
    while (it != NULL) {
        printf("%d:%d ", it->key, it->value);
        it = nextNode(it);
    }
    printf("\n");
}

void showTree(struct node *curNode) {
    if (curNode == NULL)
        return;
    printf("%d:%d ", curNode->key, curNode->value);
    showTree(curNode->left);
    showTree(curNode->right);
}

void addNode(int key, int val) {
    if (searchNode(key) == NULL)
        treeSize++;
    root = insert(root, key, val, NULL, 1);
}

void delNode(int key) {
    if (searchNode(key) != NULL)
        treeSize--;
    root = deleteNode(root, key);
}

int getSize() {
    return treeSize;
}
