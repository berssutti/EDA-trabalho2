#include<stdio.h>
#include<stdlib.h>

typedef struct node {
int info;
struct node *left;
struct node *right;
} BinaryTree;


int main(){
    int option;
    BinaryTree *root;
    //char getFileLenght[20];
   // char *fileName;
    do{
        printf("*** MENU ***\n"
        "1- Gerar ABP\n"
        "2- Calcular Fator de Balanceamento\n"
        "3- Imprimir ABP\n"
        "4- Sair\n"
        "O que deseja fazer:\n"
        );
        scanf("%d",&option);
        switch (option){
        case 1:
            printf("Digite o nome do arquiavo: \n");
           // scanf("%s", getFileLenght);
           // fileName = (char *) malloc(sizeof(getFileLenght));
           // fileName = getFileLenght;
           createTree(root);
            break;  
        case 2:
            /* code */
            break;
        case 3:
            showTree(root);
            break;
        case 4:
            freeBinaryTree(root);      
            break;
        default:
        printf("Digite novamente!\n");
        }
    }while(option != 4);

    return 0;
}