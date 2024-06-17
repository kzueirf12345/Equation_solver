#include "list.h"

// #define NDEBUG

Node *front = NULL, *back = NULL;
int list_size = 0;

Data create_Data(int power, float coef) {
    Data new_data;
    new_data.power = power;
    new_data.coef = coef;
    return new_data;
}

Node *create_Node(Data data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push_front(Data value) {
    Node *new_node = create_Node(value);

    assert(new_node && "bad alloc");

    if (front == NULL && back == NULL) {
        front = new_node;
        back = new_node;
    } else {
        new_node->next = front;
        front = new_node;
    }
    ++list_size;
    return;
}

void pop_front() {
    assert(front && "list is empty");

    Node *del = front;
    if (list_size == 1) {
        front = NULL;
        back = NULL;
    } else {
        front = del->next;
    }
    --list_size;
    free(del);
}

void push_back(Data value) {
    Node *new_node = create_Node(value);

    assert(new_node && "bad alloc");

    if (front == NULL && back == NULL) {
        front = new_node;
        back = new_node;
    } else {
        back->next = new_node;
        back = new_node;
    }
    ++list_size;
    return;
}

void pop_back() {
    assert(back && "list is empty");

    Node *del = NULL;
    if (list_size == 1) {
        front = NULL;
        back = NULL;
    } else {
        Node *cur = front;
        while (cur->next) {
            cur = cur->next;
        }

        del = cur->next; 
        back = cur;
    }
    --list_size;
    free(del);
}