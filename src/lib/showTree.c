#include<stdio.h>
#include<stdlib.h>

int getHeight(BinaryTree *root);
int saveTree(BinaryTree *root, int is_left, int offset, int depth, char **s);
void showTree(BinaryTree *root);

int main() {
    
    showTree(root);

    return 0;
}

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