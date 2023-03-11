#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int Max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

struct tree {
    int field;
    struct tree* left;
    struct tree* right;
};

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

void Order(struct tree* tree, int count, int* maxCount) {
    if (!tree) {
        return;
    } 
    ++count;
    *maxCount = Max(count, *maxCount);
    Order(tree -> left, count, maxCount);
    --count;
    *maxCount = Max(count, *maxCount);
    Order(tree -> right, count, maxCount);
}

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

int main(void) {
    struct tree* root;
    root = NULL;
    int count;
    scanf("%d", &count);
    int father, son;
    scanf("%d %d", &father, &son);
    int fatherFound = 1;
    root = AddTree(root, father, son, &fatherFound);
    for (int i = 0; i < count - 1; ++i) {
        scanf("%d %d", &father, &son);
        fatherFound = 0;
        root = AddTree(root, father, son, &fatherFound);
    }
    TreePrint(root, 0);
    int maxCount = 0;
    Order(root, 0, &maxCount);
    printf("%d\n", maxCount - 1);
    return 0;
} 
