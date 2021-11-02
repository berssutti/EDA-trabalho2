#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PARA DEFINIIR O ARQUIVO DE LEITURA
//VÁ NA LINHA 51

typedef struct no {
int chave;
struct no *pEsq;
struct no *pDir;
int fatBal;
} ArvoreBinaria;
/////////////////////////////////////////////////
// Essa parte é a de gerar a ABP
ArvoreBinaria *criarArvoreBinaria();
ArvoreBinaria *plantarArvoreBinaria(ArvoreBinaria *raiz, int valor);
ArvoreBinaria *lerArvoreArquivo();
/////////////////////////////////////////////////
// Essa parte é a mostrar tree
int getAltura(ArvoreBinaria *raiz);
int salvarArvore(ArvoreBinaria *raiz, int is_pEsq, int deslocar, int profundidade, char **s);
void mostrarArvore(ArvoreBinaria *raiz);
////////////////////////////////////////////////////////////////////
// Essa parte é para calcular o fator de balanceamento
void verificarBalanco(ArvoreBinaria *raiz);
void printfatBal(ArvoreBinaria *raiz);
////////////////////////////////////////////////
// Essa parte é a parte de desalocar a arvore binaria
void podarArvoreBinaria(ArvoreBinaria *raiz);
void imprimiCrescente(ArvoreBinaria *raiz);



int main() {

    int opcao;
    ArvoreBinaria *raiz;
    do{
        printf("*** MENU ***\n"
        "1- Gerar ABP\n"
        "2- Calcular Fator de Balanceamento\n"
        "3- Imprimir ABP\n"
        "4- Sair\n"
        "O que deseja fazer:\n"
        );
        scanf("%d",&opcao);
        switch (opcao){
        case 1:
            raiz = criarArvoreBinaria();
            raiz = lerArvoreArquivo("./tests/testA.txt");
            break;  
        case 2:
            verificarBalanco(raiz);
            break;
        case 3:
            mostrarArvore(raiz);
            imprimiCrescente(raiz);
            break;
        case 4:
            podarArvoreBinaria(raiz);   
            break;
        default:
            printf("Digite novamente!\n");
            break;
        }
    }while(opcao != 4);

    return 0;
}

ArvoreBinaria *criarArvoreBinaria() {
    ArvoreBinaria *raiz;
    raiz = (ArvoreBinaria *) malloc(sizeof(ArvoreBinaria));

    if(raiz != NULL) {
        raiz = NULL;
    }
    return raiz; 
}

ArvoreBinaria *lerArvoreArquivo(char *nameOfFile) {
    FILE *fp;
    int numero;

    ArvoreBinaria *raiz = criarArvoreBinaria();

    fp = fopen(nameOfFile, "r");

    if (fp == NULL) {
        printf("Nao foi encontrado!\n");
    }

    // Temos que encontrar um método para ler o txt com virgulas
    while(!feof(fp)) {
        fscanf(fp, "%d,", &numero);
        raiz = plantarArvoreBinaria(raiz, numero);
    }

    fclose(fp);

    return raiz;
}

ArvoreBinaria *plantarArvoreBinaria(ArvoreBinaria *raiz, int valor) {
    ArvoreBinaria *novo;
    novo = (ArvoreBinaria *) malloc(sizeof(ArvoreBinaria));
    if(novo == NULL) { // confere a alocacao
        exit(1);
    }

    novo->chave = valor;
    novo->pDir = NULL;
    novo->pEsq = NULL;

    // onde inserir:
    if(raiz == NULL) {
        raiz = novo;
    }
    else {
        ArvoreBinaria *atual = raiz;
        ArvoreBinaria *anterior = NULL;

        while(atual != NULL) { // quando tiver achado aonde ira ser inserido, para o while
            anterior = atual; // salva o atual pois o atual se tornara um dos filhos
            if(valor == atual->chave) {
                free(novo);
                return raiz;
            }
            if(valor > atual->chave) { // vai percorrer ate que um seja nulo e o anterior eh a folha que vai ficar em cima do elemento a ser inserido
                atual = atual->pDir;
            } else {
                atual = atual->pEsq;
            }
        }
        // ve se vai ser inserido na direita ou na esquerda da folha encontrada acima
        if(valor > anterior->chave) {
        anterior->pDir = novo;
        } else {
        anterior->pEsq = novo;
        }
    }
    return raiz;
}
///////////////////////////////////////
// Essa parte é a mostrar tree
int getAltura(ArvoreBinaria *raiz) {
  if(raiz == NULL) {
    return 0;
  }
  int pEsqHeight = getAltura(raiz->pEsq); // endereco do no da esquerda
  int pDirHeight = getAltura(raiz->pDir); // endereco do no da direita
  if(pEsqHeight > pDirHeight) {
    return (pEsqHeight + 1);
  } else {
    return (pDirHeight + 1);
  }
}

int salvarArvore(ArvoreBinaria *raiz, int is_pEsq, int deslocar, int profundidade, char **s) {
    char b[20];
    int largura = 5;

    if (!raiz) return 0;

    sprintf(b, " %3d ", raiz->chave);

    int pEsq  = salvarArvore(raiz->pEsq,  1, deslocar, profundidade + 1, s);
    int pDir = salvarArvore(raiz->pDir, 0, deslocar + pEsq + largura, profundidade + 1, s);

    for (int i = 0; i < largura; i++)
        s[2 * profundidade][deslocar + pEsq + i] = b[i];

    if (profundidade && is_pEsq) {

        for (int i = 0; i < largura + pDir; i++)
            s[2 * profundidade - 1][deslocar + pEsq + largura/2 + i] = '*';

        s[2 * profundidade - 1][deslocar + pEsq + largura/2] = '/';
        s[2 * profundidade - 1][deslocar + pEsq + largura + pDir + largura/2] = ':';

    } else if (profundidade && !is_pEsq) {

        for (int i = 0; i < pEsq + largura; i++)
            s[2 * profundidade - 1][deslocar - largura/2 + i] = '*';

        s[2 * profundidade - 1][deslocar + pEsq + largura/2] = 92;
        s[2 * profundidade - 1][deslocar - largura/2 - 1] = ':';
    }

    return pEsq + largura + pDir;
}

void mostrarArvore(ArvoreBinaria *raiz) {
  int height = getAltura(raiz);
  int tam = ((height * 2) + 1);

  char **mostrar = (char **)malloc( tam * sizeof(char *));
	for (int i = 0; i < tam; i++) {
		mostrar[i] = (char *)malloc(255 * sizeof(char));
		sprintf(mostrar[i], "%80s", " ");
	}

	salvarArvore(raiz, 0, 0, 0, mostrar);

	for (int i = 0; i < tam; i++) {
    int tamStr = strlen(mostrar[i]);
    for(int j = 0; j < tamStr; j++){
        printf("%c", mostrar[i][j]);
    }
    printf("\n");
  }

    for (int i = 0; i < tam; i++)
        free(mostrar[i]);
    free(mostrar);
}
////////////////////////////////////////////////////////////////////
// Essa parte é para calcular o fator de balanceamento
void verificarBalanco(ArvoreBinaria *raiz) {

    if(raiz == NULL) {
        return;
    }         
    if(raiz != NULL){
        int hpEsqArvore = getAltura(raiz->pEsq);
        int hpDirArvore = getAltura(raiz->pDir);
        int balancoFator = hpDirArvore - hpEsqArvore;
        raiz->fatBal = balancoFator;

        verificarBalanco(raiz->pDir);   
        verificarBalanco(raiz->pEsq);
    }
}

void imprimiCrescente(ArvoreBinaria *raiz) {
  if(raiz == NULL) {
    return;
  }
  if(raiz != NULL) {
    imprimiCrescente(raiz->pEsq);
    printf("chave: %d || fatBal: %d\n", raiz->chave, raiz->fatBal); // imprime o ultimo a esquerda, vai pra raiz imprime e vai pra direita e começa do ultimo a esquerda
    imprimiCrescente(raiz->pDir);
  }
}

////////////////////////////////////////////////////////////////////
// Essa parte é a parte de desalocar a arvore binaria
void podarArvoreBinaria(ArvoreBinaria *no) {
  if(no == NULL) { // verifica se a alocacao deu certo   
    return;
  }
  podarArvoreBinaria(no->pEsq); // vai a esquerda e libera
  podarArvoreBinaria(no->pDir); // vai a direita e libera
  free(no); // libera o no apos liberar tudo a direita e a esquerda
  no = NULL;
}
