#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key, value;
    struct node *left, *right;
};

struct node *newNode(int nkey, int nval)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = nkey;
    temp->value = nval;
    temp->left = temp->right = NULL;
    return temp;
}

void dfs(struct node *root)
{
    if (root != NULL)
    {
        dfs(root->left);
        printf("%d:%d ", root->key, root->value);
        dfs(root->right);
    }
}

void inorder(struct node *root)
{
    dfs(root);
}

struct node *insert(struct node *node, int key, int value)
{
    if (node == NULL) return newNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else
        node->right = insert(node->right, key, value);

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
    root = insert(root, 8, 3);
    root = insert(root, 3, 2);
    root = insert(root, 1, 3);
    root = insert(root, 6, 2);
    root = insert(root, 7, 1);
    root = insert(root, 10, 9);
    root = insert(root, 14, 4);
    root = insert(root, 4, 6);

    inorder(root);
    /*
    for (int i = 0; i < n; i++)
        printf("%d:%d ", arr[i].key, arr[i].value);
    */

}
