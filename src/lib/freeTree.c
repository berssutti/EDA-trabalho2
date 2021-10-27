#include<stdio.h>
#include<stdlib.h>
#include "../include/libgroup01.h"

void freeBinaryTree(BinaryTree *root);

void freeBinaryTree(BinaryTree *node) {
  if(node == NULL) { // verifica se a alocacao deu certo
    return;
  }
  freeBinaryTree(node->left); // vai a esquerda e libera
  freeBinaryTree(node->right); // vai a direita e libera
  free(node); // libera o node apos liberar tudo a direita e a esquerda
  node = NULL;
}