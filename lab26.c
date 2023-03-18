#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>

typedef struct _Node {
    int value;
    struct _Node* next;
    struct _Node* prev; 
} Node;

typedef struct _Deque {
    int size;
    Node* head;
    Node* tail;
} Deque;

Deque* Deque_create() {
    Deque* tmp = (Deque*) malloc(sizeof(Deque));
    tmp -> size = 0;
    tmp -> head = tmp -> tail = NULL;
    return tmp;
}

int Deque_size(Deque* deque) {
    return deque -> size;
}

int Deque_is_empty(Deque* deque) {
    return (Deque_size(deque) > 0 ? 1 : 0);
}

void Deque_push_front(Deque* deque, int data) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp -> value = data;
    tmp -> next = deque -> head;
    tmp -> prev = NULL;
    if (deque -> head) {
        deque -> head -> prev = tmp;
    }
    deque -> head = tmp;
    if (deque -> tail == NULL) {
        deque -> tail = tmp;
    }
    ++deque -> size;
}

int Deque_pop_front(Deque* deque) {
    Node* prev;
    int tmp;
    if (deque -> head == NULL) {
        exit(2);
    }
    prev = deque -> head;
    deque -> head = deque -> head -> next;
    if (deque -> head) {
        deque -> head -> prev = NULL;
    }
    if (prev == deque -> tail) {
        deque -> tail = NULL;
    }
    tmp = prev -> value;
    free(prev);
    --deque -> size;
    return tmp;
}

void Deque_push_back(Deque* deque, int value) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp -> value = value;
    tmp -> next = NULL;
    tmp -> prev = deque -> tail;
    if (deque -> tail) {
        deque -> tail -> next = tmp;
    }
    deque -> tail = tmp;
 
    if (deque -> head == NULL) {
        deque -> head = tmp;
    }
    ++deque -> size;
}
 
int Deque_pop_back(Deque* deque) {
    Node* next;
    int tmp;
    if (deque -> tail == NULL) {
        exit(4);
    }
 
    next = deque -> tail;
    deque -> tail = deque -> tail -> prev;
    if (deque -> tail) {
        deque -> tail -> next = NULL;
    }
    if (next == deque -> head) {
        deque -> head = NULL;
    }
    tmp = next -> value;
    free(next);
 
    --deque -> size;
    return tmp;
}

void Deque_print(Deque* deque) {
    Node* tmp = deque -> head;
    while (tmp) {
        printf("%d ", tmp -> value);
        tmp = tmp -> next;
    }
    printf("\n");
}

int main() {
    Deque* deque = Deque_create();
    int number, value;
    scanf("%d", &number);
    for (int i = 0; i < number; ++i) {
        scanf("%d", &value);
        Deque_push_front(deque, value);
    }
    scanf("%d", &number);
    for (int i = 0; i < number; ++i) {
        scanf("%d", &value);
        Deque_push_back(deque, value);
    }
    Deque_print(deque);
    int size = deque -> size;
    int mas[size];
    int i = 0;
    int elem;
    while (i != size) {
        elem = Deque_pop_front(deque);
        mas[i] = elem;
        Deque_push_back(deque, elem);
        ++i;
    }
    int min_index, t;
    for (i = 0; i < size - 1; ++i) {
        min_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (mas[j] < mas[min_index]) {
                min_index = j;
            }
        }
        if (mas[min_index] != mas[i]) {
            t = mas[i];
            mas[i] = mas[min_index];
            mas[min_index] = t;
        }
    }
    printf("%d\n", mas[size - 1]);
    Deque* deque2 = Deque_create();
    elem = Deque_pop_front(deque);
    while (elem != mas[size - 1]) {
        Deque_push_front(deque2, elem);
        elem = Deque_pop_front(deque);
    }
    while (Deque_is_empty(deque2) == 1) {
        Deque_push_front(deque, Deque_pop_front(deque2));
    }
    Deque_print(deque);
    return 0;
}
