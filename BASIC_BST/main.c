#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

void dfs(struct node *root)
{
    if (root != NULL)
    {
        dfs(root->left);
        struct node *par = root->parent;
        if (par != NULL)
            printf("%d:", par->key);
        printf("%d:%d ", root->key, root->value);
        dfs(root->right);
    }
}

void inorder(struct node *root)
{
    dfs(root);
    printf("\n");
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

struct node *insert(struct node *node, int key, int value, struct node *pre)
{
    if (node == NULL) return newNode(key, value, pre);

    if (key < node->key)
        node->left = insert(node->left, key, value, node);
    else
        node->right = insert(node->right, key, value, node);

    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

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
int maxKey;

void newTree() {
    maxKey = -1e9;
    root = NULL;
}

struct node *getBeginNode() {
    return minValueNode(root);
};

bool isEnd(struct node *node) {
    if ((node->key) == maxKey)
        return true;
    return false;
}

void addNode(int key, int val) {
    root = insert(root, key, val, NULL);
    if (key > maxKey)
        maxKey = key;
}

void delNode(int key) {
    root = deleteNode(root, key);
}

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
    inorder(root);

    delNode(6);
    inorder(root);

    delNode(3);
    inorder(root);

}
