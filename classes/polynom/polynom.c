#include "polynom.h"

void reduct_sorted_polynom(List* polynom) {
    SDL_bool do_increment = SDL_TRUE;
    for (Node *prepreprev = NULL, *preprev = NULL, *prev = polynom->left; prev->next != NULL;) {
        Node* cur = prev->next;

        if (prev->data.power == cur->data.power) {
            prev->data.coef += cur->data.coef;
            erase(polynom, prev);

            if (prev->data.coef == 0) {
                if (preprev == NULL) {
                    pop_front(polynom);
                } else {
                    erase(polynom, preprev);
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

void print_polynom(List* polynom, const char* const hi_message) {
    printf("%s: ", hi_message);
    for (Node* it = polynom->left; it != polynom->right->next; it = it->next) {
        if (it->data.power == 0) {
            if (it->data.coef > 0) {
                if (it->data.coef == 1) {
                    if (it == polynom->left) {
                    } else {
                        printf("+ 1 ");
                    }
                } else {
                    if (it == polynom->left) {
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
                    if (it == polynom->left) {
                        printf("x ");
                    } else {
                        printf("+ x ");
                    }
                } else {
                    if (it == polynom->left) {
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
                    if (it == polynom->left) {
                        printf("x^%d ", it->data.power);
                    } else {
                        printf("+ x^%d ", it->data.power);
                    }
                } else {
                    if (it == polynom->left) {
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
