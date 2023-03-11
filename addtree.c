#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tree* AddTree(struct tree* tree, int father, int son, int* fatherFound) {
    if (tree == NULL) {
            if (*fatherFound == 1) {
            tree = (struct tree*) malloc (sizeof(struct tree));
            tree -> field = son;
            tree -> left =  NULL;
            tree -> right = NULL;
            *fatherFound = 2;
        }
    } else if ((father == tree -> field) && (*fatherFound == 0)) {
        *fatherFound = 1;
        tree -> left = AddTree(tree -> left, father, son, fatherFound);
    } else if (*fatherFound == 1) {
        tree -> right = AddTree(tree -> right, father, son, fatherFound);
    } else if (*fatherFound == 0) {
        tree -> left = AddTree(tree -> left, father, son, fatherFound);
        tree -> right = AddTree(tree -> right, father, son, fatherFound);
    }
    return (tree);
}
