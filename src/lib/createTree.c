#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////Create ABP//////
BinaryTree *createBinaryTree();
BinaryTree *insertBinaryTree(BinaryTree *root, int value);
BinaryTree *loadTreeFromFile();

BinaryTree createTree(BinaryTree *root) {
    
    root = createBinaryTree();
    root = loadTreeFromFile("../testC.txt");

    return root;
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