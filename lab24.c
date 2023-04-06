#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>

typedef struct _Node {
    char value;
    struct _Node* next;
    struct _Node* prev; 
} Node;

typedef struct _Stack {
    int size;
    Node* head;
    Node* tail;
} Stack;

Stack* Stack_create() {
    Stack* tmp = (Stack*) malloc(sizeof(Stack));
    tmp -> size = 0;
    tmp -> head = tmp -> tail = NULL;
    return tmp;
}

int Stack_size(Stack* stack) {
    return stack -> size;
}

int Stack_is_empty(Stack* stack) {
    return (Stack_size(stack) > 0 ? 1 : 0);
}

void Stack_push(Stack* stack, char value) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp -> value = value;
    tmp -> next = NULL;
    tmp -> prev = stack -> tail;
    if (stack -> tail) {
        stack -> tail -> next = tmp;
    }
    stack -> tail = tmp;
 
    if (stack -> head == NULL) {
        stack -> head = tmp;
    }
    ++stack -> size;
}
 
char Stack_pop(Stack* stack) {
    Node* next;
    char tmp;
    if (stack -> tail == NULL) {
        exit(4);
    }
 
    next = stack -> tail;
    stack -> tail = stack -> tail -> prev;
    if (stack -> tail) {
        stack -> tail -> next = NULL;
    }
    if (next == stack -> head) {
        stack -> head = NULL;
    }
    tmp = next -> value;
    free(next);
 
    --stack -> size;
    return tmp;
}

void Stack_print(Stack* stack) {
    Node* tmp = stack -> head;
    while (tmp) {
        printf("%c ", tmp -> value);
        tmp = tmp -> next;
    }
    printf("\n");
}

char *convertInNotation(Stack* stack, char *phrase, char *phraseInNotation, int *index, int *countOfBracket, int *countOfUnarMinus, int n) {
    for (int i = 0; i < n; ++i) {
        if (phrase[i] == '-' && (phrase[i - 1] == '(' || i == 0)) {
            Stack_push(stack, phrase[i]);
            phraseInNotation[*index] = '|';
            ++*index;
            ++*countOfUnarMinus;
        } else if (Stack_is_empty(stack) == 0) {
            if (phrase[i] == '+' || phrase[i] == '-' || phrase[i] == '*' || phrase[i] == '/' || phrase[i] == '(') {
                if (phrase[i] == '(') {
                    ++*countOfBracket;
                }
                Stack_push(stack, phrase[i]);
            } else {
                phraseInNotation[*index] = phrase[i];
                ++*index;
            }
        } else if (phrase[i] == '*' || phrase[i] == '/') {
            Stack_push(stack, phrase[i]);
        } else if (phrase[i] == '+' || phrase[i] == '-') {
            char elem = Stack_pop(stack);
            if (elem == '*' || elem == '/') {
                phraseInNotation[*index] = elem;
                ++*index;
                char elem2;
                while (Stack_is_empty(stack) == 1) {
                    elem2 = Stack_pop(stack);
                    if (elem2 == '(') {
                        Stack_push(stack, elem2);
                        break;
                    }
                    phraseInNotation[*index] = elem2;
                    ++*index;
                }
                Stack_push(stack, phrase[i]);
            } else {
                Stack_push(stack, elem);
                Stack_push(stack, phrase[i]);
            }
        } else if (phrase[i] == '(') {
            ++*countOfBracket;
            Stack_push(stack, phrase[i]);
        } else if (phrase[i] == ')') {
            ++*countOfBracket;
            char elem2;
            while (Stack_is_empty(stack) == 1) {
                elem2 = Stack_pop(stack);
                if (elem2 == '(') {
                    break;
                }
                phraseInNotation[*index] = elem2;
                ++*index;
            }
        } else {
            phraseInNotation[*index] = phrase[i];
            ++*index;
        }
    }
    char elem2;
    while (Stack_is_empty(stack) == 1) {
        elem2 = Stack_pop(stack);
        phraseInNotation[*index] = elem2;
        ++*index;
    }
    return phraseInNotation;
}

void simplificationExpression(Node* tree) {
    if (tree == NULL) {
        return;
    } 
    if (tree -> prev != NULL && tree -> prev -> next != NULL) {
        if (tree -> value == '*' && tree -> prev -> value == '-' && tree -> prev -> prev == NULL && tree -> prev -> next != NULL) {
            tree -> value = '-';
            tree -> prev -> value = '*';
            tree -> prev -> prev = tree -> next;
            tree -> next = NULL;
            Node* tmp = (Node*) malloc(sizeof(Node));
            tmp = tree -> next;
            tree -> next = tree -> prev;
            tree -> prev = tmp;
        } else {
            simplificationExpression(tree -> prev);
        }
    }
    if (tree -> next != NULL && tree -> next -> next != NULL) {
        if (tree -> value == '*' && tree -> next -> value == '-' && tree -> next -> prev == NULL && tree -> next -> next != NULL) {
            tree -> value = '-';
            tree -> next -> value = '*';
            tree -> next -> prev = tree -> prev;
            tree -> prev = NULL;
        } else {
            simplificationExpression(tree -> next);
        }
    } else {
        return;
    }
}

void TreePrint(Node* tree, int* bracketHasPair) {
    if (tree == NULL) {
        return;
    }
    if (tree -> next == NULL) {
        printf("%c", tree -> value);
        if (*bracketHasPair == 1) {
            printf(")");
            *bracketHasPair = 0;
        }
        return;
    }
    if (tree -> value == '-' && tree -> prev == NULL && tree -> next -> value == '-' && tree -> next -> prev == NULL) {
        tree = tree -> next -> next;
    }
    if ((tree -> value == '*' || tree -> value == '/') && (tree -> prev -> value == '-' || tree -> prev -> value == '+')) {
        printf("(");
    }
    if (tree -> value == '-' && tree -> prev == NULL) {
        printf("(");
        *bracketHasPair = 1;
    }
    TreePrint(tree -> prev, bracketHasPair);
    if ((tree -> value == '*' || tree -> value == '/') && (tree -> prev -> value == '-' || tree -> prev -> value == '+')) {
        printf(")");
    }
    printf("%c", tree -> value);
    if ((tree -> value == '*' || tree -> value == '/') && (tree -> next -> value == '-' || tree -> next -> value == '+')) {
        printf("(");
    }
    TreePrint(tree -> next, bracketHasPair);
    if ((tree -> value == '*' || tree -> value == '/') && (tree -> next -> value == '-' || tree -> next -> value == '+')) {
        printf(")");
    }
}

int main() {
    Stack* stack = Stack_create();
    int n;
    scanf("%d", &n);
    char phrase[n];
    char *phraseInNotation = malloc(2 * n);
    scanf("%s", phrase);
    int index = 0;
    int countOfBracket = 0;
    int countOfUnarMinus = 0;
    phraseInNotation = convertInNotation(stack, phrase, phraseInNotation, &index, &countOfBracket, &countOfUnarMinus, n);
    // printf("%s\n", phraseInNotation);
    Node* matrixOfTrees[n];
    index = 0;
    for(int i = 0; i < n - countOfBracket + countOfUnarMinus; ++i) {
        if (phraseInNotation[i] == '+' || phraseInNotation[i] == '-' || phraseInNotation[i] == '*' || phraseInNotation[i] == '/' || phraseInNotation[i] == '(') {
            --index;
            Node* tree = (Node*) malloc(sizeof(Node));
            tree -> value = phraseInNotation[i];
            tree -> next = matrixOfTrees[index];
            tree -> prev = matrixOfTrees[index - 1];
            --index;
            matrixOfTrees[index] = tree;
            ++index;
        } else {
            if (phraseInNotation[i] == '|') {
                Node* tree = (Node*) malloc(sizeof(Node));
                tree = NULL;
                matrixOfTrees[index] = tree;
                ++index;
            } else {
                Node* tree = (Node*) malloc(sizeof(Node));
                tree -> value = phraseInNotation[i];
                tree -> next = NULL;
                tree -> prev = NULL;
                matrixOfTrees[index] = tree;
                ++index;
            }
        }
    }
    Node* tree = matrixOfTrees[0];
    int isBinaryMinus = 0;
    for (int i = 0; i < n; ++i) {
        simplificationExpression(tree);
    }
    int bracketHasPair = 0;
    TreePrint(tree, &bracketHasPair);
    printf("\n");
    return 0;
}
