#pragma once

typedef struct _Data {
    int power;
    float coef;
} Data;

typedef struct _Node {
    Data data;
    struct Node* next;
} Node;

typedef struct _List {
    Node* root;
    unsigned long long size;
    void (*push_front)(Data value);       // check for constness here
    void (*pop_front)();                  // check for constness here
    void (*push_back)(Data value);        // check for constness here
    void (*pop_back)();                   // check for constness here
    Data (*get)(unsigned long long idx);  // check for constness here
} List;

void push_front(Data value);
void pop_front();
void push_back(Data value);
void pop_back();