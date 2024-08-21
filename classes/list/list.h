#pragma once

#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    int coef;
    int power;
} Data;

Data Data_create(int coef, int power);

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

Node* Node_create(Data value);

typedef struct List {
    Node* left;
    Node* right;
    size_t size;
} List;

List List_create(Node* left, Node* right, size_t size);

void List_push_front(List* list, Data value);
void List_pop_front(List* list);
void List_push_back(List* list, Data value);
void List_pop_back(List* list);
void List_erase(List* list, Node* prev_erase);
void List_glue(List* const dest, List* glued);

List merge_msort(List* const llist, List* const rlist);
List msort(List* const list);