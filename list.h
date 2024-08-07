#pragma once

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    int power;
    float coef;
} Data;

Data create_Data(int power, float coef);

typedef struct Node {
    Data data;
    struct Node *next;
} Node;

Node *create_Node(Data value);
void push_front(Data value);
void pop_front(void);
void push_back(Data value);
void pop_back(void);