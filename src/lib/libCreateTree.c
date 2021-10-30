#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
int info;
struct node *left;
struct node *right;
int FatBal;
} BinaryTree;
/////////////////////////////////////////////////
// Essa parte é a de gerar a ABP
BinaryTree *createBinaryTree();
BinaryTree *insertBinaryTree(BinaryTree *root, int value);
BinaryTree *loadTreeFromFile();
/////////////////////////////////////////////////
// Essa parte é a show tree
int getHeight(BinaryTree *root);
int saveTree(BinaryTree *root, int is_left, int offset, int depth, char **s);
void showTree(BinaryTree *root);
////////////////////////////////////////////////////////////////////
// Essa parte é para calcular o fator de balanceamento
int verifyBalancedTree(BinaryTree *root);
////////////////////////////////////////////////
// Essa parte é a parte de desalocar a arvore binaria
void freeBinaryTree(BinaryTree *root);

int main() {
    BinaryTree *root;
    
    root = createBinaryTree();
    root = loadTreeFromFile("../testC.txt");
    
    showTree(root);

    freeBinaryTree(root);
    return 0;
}

BinaryTree *createBinaryTree() {
    BinaryTree *root;
    root = (BinaryTree *) malloc(sizeof(BinaryTree));

    if(root != NULL) {
        root = NULL;
    }
    return root; 
}
BinaryTree *loadTreeFromFile(char *nameOfFile) {
    FILE *fp;
    int number;

    BinaryTree *root = createBinaryTree();

    fp = fopen(nameOfFile, "r");

    if (fp == NULL) {
        printf("Was not found!\n");
    }

    // Temos que encontrar um método para ler o txt com virgulas
    while(!feof(fp)) {
        fscanf(fp, "%d", &number);
        printf("%d\n", number);
        root = insertBinaryTree(root, number);
    }

    fclose(fp);

    return root;
}

BinaryTree *insertBinaryTree(BinaryTree *root, int value) {
    BinaryTree *new;
    new = (BinaryTree *) malloc(sizeof(BinaryTree));
    if(new == NULL) { // confere a alocacao
        exit(1);
    }

    new->info = value;
    new->right = NULL;
    new->left = NULL;

    // onde inserir:
    if(root == NULL) {
        root = new;
    }
    else {
        BinaryTree *current = root;
        BinaryTree *previous = NULL;

        while(current != NULL) { // quando tiver achado aonde ira ser inserido, para o while
            previous = current; // salva o atual pois o atual se tornara um dos filhos
            if(value == current->info) {
                free(new);
                printf("Element already exists in the tree.\n");
                exit(2);// elemento ja existe
            }
            if(value > current->info) { // vai percorrer ate que um seja nulo e o anterior eh a folha que vai ficar em cima do elemento a ser inserido
                current = current->right;
            } else {
                current = current->left;
            }
        }
        // ve se vai ser inserido na direita ou na esquerda da folha encontrada acima
        if(value > previous->info) {
        previous->right = new;
        } else {
        previous->left = new;
        }
    }
    return root;
}
///////////////////////////////////////
// Essa parte é a show tree
int getHeight(BinaryTree *root) {
  if(root == NULL) {
    return 0;
  }
  int leftHeight = getHeight(root->left); // endereco do no da esquerda
  int rightHeight = getHeight(root->right); // endereco do no da direita
  if(leftHeight > rightHeight) {
    return (leftHeight + 1);
  } else {
    return (rightHeight + 1);
  }
}

int saveTree(BinaryTree *root, int is_left, int offset, int depth, char **s) {
    char b[20];
    int width = 5;

    if (!root) return 0;

    sprintf(b, " %3d ", root->info);

    int left  = saveTree(root->left,  1, offset, depth + 1, s);
    int right = saveTree(root->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '*';

        s[2 * depth - 1][offset + left + width/2] = '/';
        s[2 * depth - 1][offset + left + width + right + width/2] = ':';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '*';

        s[2 * depth - 1][offset + left + width/2] = 92;
        s[2 * depth - 1][offset - width/2 - 1] = ':';
    }

    return left + width + right;
}

void showTree(BinaryTree *root) {
  int height = getHeight(root);
  int tam = ((height * 2) + 1);

  char **show = (char **)malloc( tam * sizeof(char *));
	for (int i = 0; i < tam; i++) {
		show[i] = (char *)malloc(255 * sizeof(char));
		sprintf(show[i], "%80s", " ");
	}

	saveTree(root, 0, 0, 0, show);

	for (int i = 0; i < tam; i++) {
    int tamStr = strlen(show[i]);
    for(int j = 0; j < tamStr; j++){
        printf("%c", show[i][j]);
    }
    printf("\n");
  }

    for (int i = 0; i < tam; i++)
        free(show[i]);
    free(show);
}
////////////////////////////////////////////////////////////////////
// Essa parte é para calcular o fator de balanceamento
int verifyBalancedTree(BinaryTree *root) {

    /* if((root != NULL && root->left == NULL && root->right == NULL) || root == NULL) {
        return 1;
    } */

    int hLeftTree = getHeight(root->left);
    int hRightTree = getHeight(root->right);
    int balanceFactor = hRightTree - hLeftTree;

    root->FatBal = balanceFactor;

    return verifyBalancedTree(root->right) && verifyBalancedTree(root->left);
}
////////////////////////////////////////////////////////////////////
// Essa parte é a parte de desalocar a arvore binaria
void freeBinaryTree(BinaryTree *node) {
  if(node == NULL) { // verifica se a alocacao deu certo
    return;
  }
  freeBinaryTree(node->left); // vai a esquerda e libera
  freeBinaryTree(node->right); // vai a direita e libera
  free(node); // libera o node apos liberar tudo a direita e a esquerda
  node = NULL;
}
