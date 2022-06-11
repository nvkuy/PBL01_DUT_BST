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

struct node *insert(struct node *node, int key, int value, struct node *pre)
{

    if (node == NULL) {
        return newNode(key, value, pre);
    }

    if (key < node->key)
        node->left = insert(node->left, key, value, node);
    else if (key > node->key)
        node->right = insert(node->right, key, value, node);
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
int maxKey, treeSize;

void newTree() {
    maxKey = -1e9;
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

bool isEnd(struct node *node) {
    if ((node->key) == maxKey)
        return true;
    return false;
}

struct node *nextNode(struct node *curNode) {
    if (curNode == NULL)
        return curNode;
    if (curNode->right != NULL)
        return minValueNode(curNode->right);
    if (isEnd(curNode))
        return NULL;
    struct node *par = curNode->parent, *tmp = curNode;
    if (par->left->key == curNode->key)
        return par;
    while (par->right->key == tmp->key) {
        tmp = par;
        par = tmp->parent;
    }
    return par;
}

void inorder() {
    struct node *it = getBeginNode();
    while (it != NULL) {
        //if (it->parent != NULL)
        //    printf("%d:", it->parent->key);
        printf("%d:%d ", it->key, it->value);
        it = nextNode(it);
    }
    printf("\n");
}

void addNode(int key, int val) {
    if (searchNode(key) == NULL)
        treeSize++;
    root = insert(root, key, val, NULL);
    struct node *tmp = maxValueNode(root);
    maxKey = tmp->key;
}

void delNode(int key) {
    if (searchNode(key) != NULL)
        treeSize--;
    root = deleteNode(root, key);
    struct node *tmp = maxValueNode(root);
    maxKey = tmp->key;
}

int getSize() {
    return treeSize;
}

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int a[200002];

int main()
{

    newTree();
    int n;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    shuffle(a, n);
    for (int i = 0; i < n; i++)
        addNode(a[i], 0);

    printf("%d", getSize());

}
