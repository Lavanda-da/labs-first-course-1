#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
