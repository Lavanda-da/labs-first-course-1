#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
