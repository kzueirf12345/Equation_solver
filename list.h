#pragma once

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int power;
    float coef;
} Data;

Data create_Data(int power, float coef);

typedef struct {
    Data data;
    struct Node* next;
} Node;

Node* create_Node(Data value);
void push_front(Data value);
void pop_front();
void push_back(Data value);
void pop_back();