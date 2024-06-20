#include "list.h"

Node *front = NULL, *back = NULL;
size_t list_size = 0;

Data create_Data(int power, float coef) {
    return (Data){power, coef};
}

Node *create_Node(Data data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push_front(Data data) {
    Node *new_node = create_Node(data);

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

void pop_front(void) {
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

void push_back(Data data) {
    Node *new_node = create_Node(data);

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

void pop_back(void) {
    assert(front && "list is empty");

    Node *del = front;
    if (list_size == 1) {
        front = NULL;
        back = NULL;
    } else {
        Node *cur = front;
        while (cur->next->next) {
            cur = cur->next;
        }

        del = cur->next; 
        back = cur;
    }
    --list_size;
    free(del);
}