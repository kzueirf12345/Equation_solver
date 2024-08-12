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

void erase(List* list, Node* prev_erase) {
    assert(!(prev_erase == list->right || list->size < 2 || prev_erase == NULL) && "Invalid erase");
    
    Node* erase = prev_erase->next;
    prev_erase->next = erase->next;
    free(erase);
    --list->size;
    if (prev_erase->next == NULL)
    {
        list->right = prev_erase;
    }
}

List merge_msort(List* const llist, List* const rlist) {
    List list = create_List(NULL, NULL, 0);
    Node *itl = llist->left, *itr = rlist->left;
    for (; itl != llist->right->next && itr != rlist->right->next;) {
        if (itl->data.power >= itr->data.power) {
            push_back(&list, itl->data);
            itl = itl->next;
        } else {
            push_back(&list, itr->data);
            itr = itr->next;
        }
    }
    while (itl != llist->right->next) {
        push_back(&list, itl->data);
        itl = itl->next;
    }
    while (itr != rlist->right->next) {
        push_back(&list, itr->data);
        itr = itr->next;
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

void reduct_sorted_eq(List* eq) {
    SDL_bool do_increment = SDL_TRUE;
    for (Node *prepreprev = NULL, *preprev = NULL, *prev = eq->left; prev->next != NULL;) {
        Node* cur = prev->next;

        if (prev->data.power == cur->data.power) {
            prev->data.coef += cur->data.coef;
            erase(eq, prev);

            if (prev->data.coef == 0) {
                if (preprev == NULL) {
                    pop_front(eq);
                } else {
                    erase(eq, preprev);
                }
                prev = preprev;
                preprev = prepreprev;
            }
            do_increment = SDL_FALSE;
        }
        if (do_increment) {
            prepreprev = preprev;
            preprev = prev;
            prev = prev->next;
        } else {
            do_increment = SDL_TRUE;
        }
    }
}

void print_eq(List* eq, const char* const hi_message) {
    printf("%s: ", hi_message);
    for (Node* it = eq->left; it != eq->right->next; it = it->next) {
        if (it->data.power == 0) {
            if (it->data.coef > 0) {
                if (it->data.coef == 1) {
                    if (it == eq->left) {
                    } else {
                        printf("+ 1 ");
                    }
                } else {
                    if (it == eq->left) {
                        printf("%d ", it->data.coef);
                    } else {
                        printf("+ %d ", it->data.coef);
                    }
                }
            } else {
                printf("%d ", it->data.coef);
            }
        } else if (it->data.power == 1) {
            if (it->data.coef > 0) {
                if (it->data.coef == 1) {
                    if (it == eq->left) {
                        printf("x ");
                    } else {
                        printf("+ x ");
                    }
                } else {
                    if (it == eq->left) {
                        printf("%dx ", it->data.coef);
                    } else {
                        printf("+ %dx ", it->data.coef);
                    }
                }
            } else {
                printf("%dx ", it->data.coef);
            }
        } else {
            if (it->data.coef > 0) {
                if (it->data.coef == 1) {
                    if (it == eq->left) {
                        printf("x^%d ", it->data.power);
                    } else {
                        printf("+ x^%d ", it->data.power);
                    }
                } else {
                    if (it == eq->left) {
                        printf("%dx^%d ", it->data.coef, it->data.power);
                    } else {
                        printf("+ %dx^%d ", it->data.coef, it->data.power);
                    }
                }
            } else {
                printf("%dx^%d ", it->data.coef, it->data.power);
            }
        }
    }
    printf("\n");
}
