#include <stdio.h>
#include <stdlib.h>

/**
 * struct bst_node - A node of a binary search tree
 * @data: The data stored in the node
 * @left: The left child of the node
 * @right: The right child of the node
 */
struct bst_node
{
    int data;
    struct bst_node *left;
    struct bst_node *right;
};

/**
 * bst_insert - Inserts a new node into a binary search tree
 * @root: The root of the tree
 * @data: The data to be inserted
 *
 * Return: The new node, or NULL on failure
 */
struct bst_node *bst_insert(struct bst_node **root, int data)
{
    struct bst_node *new_node;

    if (*root == NULL)
    {
        new_node = malloc(sizeof(struct bst_node));
        if (new_node == NULL)
            return (NULL);
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        *root = new_node;
        return (new_node);
    }
    if (data < (*root)->data)
        return (bst_insert(&(*root)->left, data));
    if (data > (*root)->data)
        return (bst_insert(&(*root)->right, data));
    return (*root);
}

/**
 * bst_inorder - Prints the elements of a binary search tree in order
 * @root: The root of the tree
 */
void bst_inorder(struct bst_node *root)
{
    if (root == NULL)
        return;
    bst_inorder(root->left);
    printf("%d ", root->data);
    bst_inorder(root->right);
}

/**
 * bst_free - Frees a binary search tree
 * @root: The root of the tree
 */
void bst_free(struct bst_node *root)
{
    if (root == NULL)
        return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    struct bst_node *tree = NULL;

    /* Insert some elements into the tree */
    bst_insert(&tree, 50);
    bst_insert(&tree, 30);
    bst_insert(&tree, 70);
    bst_insert(&tree, 20);
    bst_insert(&tree, 40);
    bst_insert(&tree, 60);
    bst_insert(&tree, 80);

    /* Print the elements in order */
    printf("The elements of the tree are: ");
    bst_inorder(tree);
    printf("\n");

    /* Free the tree */
    bst_free(tree);

    return (0);
}
