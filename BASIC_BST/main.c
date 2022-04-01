#include <stdio.h>
#include <stdlib.h>

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



int main()
{
    struct node *root = NULL;
    root = insert(root, 8, 3, NULL);
    root = insert(root, 3, 2, NULL);
    root = insert(root, 1, 3, NULL);
    root = insert(root, 6, 2, NULL);
    root = insert(root, 7, 1, NULL);
    root = insert(root, 10, 9, NULL);
    root = insert(root, 14, 4, NULL);
    root = insert(root, 4, 6, NULL);
    inorder(root);

    root = deleteNode(root, 6);
    inorder(root);

    root = deleteNode(root, 3);
    inorder(root);

}
