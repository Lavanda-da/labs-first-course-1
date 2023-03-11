#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void TreePrint(struct tree* tree, int count) {
    if (tree != NULL) { 
        for (int i = 0; i < count; ++i) {
            printf(" ");
        }
        ++count;
        printf("%d\n", tree -> field);
        TreePrint(tree -> left, count);
        --count;
        TreePrint(tree -> right, count);
    }
}
