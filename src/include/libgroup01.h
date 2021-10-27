typedef struct node {
int info;
struct node *left;
struct node *right;
} BinaryTree;
BinaryTree createTree(BinaryTree *root);
void showTree(BinaryTree *root);
void freeBinaryTree(BinaryTree *root);