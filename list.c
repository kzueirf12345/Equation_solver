#include "list.h"

Data create_Data(int coef, int power) { return (Data){coef, power}; }

Node* create_Node(Data data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List create_List(Node* left, Node* right, size_t size) { return (List){left, right, size}; }

void push_front(List* list, Data data) {
    Node* new_node = create_Node(data);

    assert(new_node && "bad alloc");

    if (list->left == NULL && list->right == NULL) {
        list->left = new_node;
        list->right = new_node;
    } else {
        new_node->next = list->left;
        list->left = new_node;
    }
    ++list->size;
}

void pop_front(List* list) {
    assert(list->left && "List is empty");

    Node* del = list->left;
    if (list->size == 1) {
        list->left = NULL;
        list->right = NULL;
    } else {
        list->left = del->next;
    }
    --list->size;
    free(del);
}

void push_back(List* list, Data data) {
    Node* new_node = create_Node(data);

    assert(new_node && "bad alloc");

    if (list->left == NULL && list->right == NULL) {
        list->left = new_node;
        list->right = new_node;
    } else {
        list->right->next = new_node;
        list->right = new_node;
    }
    ++list->size;
}

void pop_back(List* list) {
    assert(list->left && "List is empty");

    Node* del = list->left;
    if (list->size == 1) {
        list->left = NULL;
        list->right = NULL;
    } else {
        Node* cur = list->left;
        while (cur->next->next) {
            cur = cur->next;
        }

        del = cur->next;
        list->right = cur;
    }
    --list->size;
    free(del);
}

List merge_msort(List* const llist, List* const rlist) {
    List list = create_List(NULL, NULL, 0);
    Node *itl = llist->left, *itr = rlist->left;
    size_t cntl = 0, cntr = 0;
    for (; cntl < llist->size && cntr < rlist->size;) {
        if (itl->data.power >= itr->data.power) {
            push_back(&list, itl->data);
            itl = itl->next;
            ++cntl;
        } else {
            push_back(&list, itr->data);
            itr = itr->next;
            ++cntr;
        }
    }
    while (cntl < llist->size) {
        push_back(&list, itl->data);
        itl = itl->next;
        ++cntl;
    }
    while (cntr < rlist->size) {
        push_back(&list, itr->data);
        itr = itr->next;
        ++cntr;
    }
    return list;
}

List msort(List* const list) {
    if (list == NULL || list->size == 0) {
        return create_List(NULL, NULL, 0);
    }
    if (list->size == 1) {
        List temp = create_List(NULL, NULL, 0);
        push_back(&temp, list->left->data);
        return temp;
    }

    Node* mid = list->left;
    const size_t halfmid = list->size / 2 - (size_t)(list->size % 2 == 0);
    for (size_t i = 0; i < halfmid; ++i, mid = mid->next);

    List left = create_List(list->left, mid, 1 + halfmid);
    List right = create_List(mid->next, list->right, list->size - halfmid - 1);
    left = msort(&left);
    right = msort(&right);
    return merge_msort(&left, &right);
}
