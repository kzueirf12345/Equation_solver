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

Data create_Data(int coef, int power);

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

Node* create_Node(Data value);

typedef struct List {
    Node* left;
    Node* right;
    size_t size;
} List;

List create_List(Node* left, Node* right, size_t size);

void push_front(List* list, Data value);
void pop_front(List* list);
void push_back(List* list, Data value);
void pop_back(List* list);
void erase(List* list, Node* prev_erase);

List merge_msort(List* const llist, List* const rlist);
List msort(List* const list);