#include <stdio.h>
#include <stdlib.h>

typedef enum {
    cat,
    dog,
    wolf,
    tiger,
    lion
} animal;

animal ConvertStringToAnimal(char symbol[]) {
    switch(symbol[0]){
        case 'c':
            return 0;
        case 'd':
            return 1;
        case 'w':
            return 2;
        case 't':
            return 3;
        case 'l':
            return 4;
    }
}

void ConvertAnimalToString(animal value, char* symbol[10]) {
    
}

typedef struct node {
    animal value;
    struct node* next;
} node;

node* Create() {
    node* root = (node*)malloc(sizeof(node));
    node* terminate = (node*)malloc(sizeof(node));
    terminate = NULL;
    root->next = terminate;
    return root;
}

void Insert(node* root, int index, animal value) {
    for (int i = 0; i < index; ++i) {
        if (root->next == NULL) {
            printf("Index out of range");
            exit(1);
        }
        root = root->next;
    }
    node* tmp = (node*)malloc(sizeof(node));
    tmp->next = NULL;
    tmp->value = value;
    root->next = tmp;
    return;
}

void Erase(node* root, int index) {
    for (int i = 0; i < index; ++i) {
        if (root == NULL) {
            printf("Index out of range");
            exit(1);
        }
        root = root->next;
    }
    root->next = root->next->next;
    return;
}

int Size(node* root) {
    int count = 0;
    while (root != NULL) {
        root = root->next;
        ++count;
    }
    return count - 1;
}

void Print(node* root) {
    root = root->next;
    while (root != NULL) {
        printf("%d ", root->value);
        root = root->next;
    }
    printf("\n");
}

void PrintAnimal(node* root) {
    root = root->next;
    while (root != NULL) {
        switch(root->value){
            case 0:
                printf("cat ");
                break;
            case 1:
                printf("dog ");
                break;
            case 2:
                printf("wolf ");
                break;
            case 3:
                printf("tiger ");
                break;
            case 4:
                printf("lion ");
        }
        root = root->next;
    }
    printf("\n");
}

void Solve(node* root, animal value) {
    while (root->next != NULL) {
        if (root->next->value != value) {
            Erase(root, 0);
        } else {
            root = root->next;
        }
    }
}

int main() {
    node* list = Create();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        char symbol[10];
        scanf("%s", symbol);
        animal value = ConvertStringToAnimal(symbol);
        Insert(list, i, value);
    }
    Print(list);
    PrintAnimal(list);
    printf("%d\n", Size(list));
    char notDeleteSymbol[10];
    scanf("%s", notDeleteSymbol);
    animal notDeleteValue = ConvertStringToAnimal(notDeleteSymbol);
    Solve(list, notDeleteValue);
    Print(list);
    PrintAnimal(list);
    printf("%d\n", Size(list));
    return 0;
}
