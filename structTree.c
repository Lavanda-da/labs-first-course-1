#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tree {
    int field;
    struct tree* left;
    struct tree* right;
};
