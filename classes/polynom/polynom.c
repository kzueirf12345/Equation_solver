#include "polynom.h"
#include "../stack/stack.h"
#include <SDL_stdinc.h>
#include <ctype.h>
#include <string.h>

void reduct_sorted_polynom(List* polynom)
{
    SDL_bool do_increment = SDL_TRUE;
    for (Node *prepreprev = NULL, *preprev = NULL, *prev = polynom->left; prev->next != NULL;) {
        Node* cur = prev->next;

        if (prev->data.power == cur->data.power) {
            prev->data.coef += cur->data.coef;
            List_erase(polynom, prev);

            if (prev->data.coef == 0) {
                if (preprev == NULL) {
                    List_pop_front(polynom);
                } else {
                    List_erase(polynom, preprev);
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

void print_polynom(List* polynom, const char* const hi_message)
{
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

SDL_bool is_op(char sym)
{
    return sym == '+' || sym == '-' || sym == '*' || sym == '(';
}

Data monome_parse(const String* const monome)
{
    Data result = Data_create(0, 0);
    String coef = String_create(NULL, 0);
    String pow = String_create(NULL, 0);
    int idx = 0;

    while (monome->data[idx] != 'x' && monome->data[idx] != '*' && idx < monome->size) {
        String_push_back_char(&coef, monome->data[idx]);
        ++idx;
    }

    if (coef.size == 0) {
        String_push_back_char(&coef, '1');
    }

    if (idx == monome->size - 1) {
        result.power = 0;
    }

    while (monome->data[idx] != '^' && idx < monome->size) {
        ++idx;
    }
    ++idx; // skip ^ or skip borders

    while (idx < monome->size) {
        String_push_back_char(&pow, monome->data[idx]);
        ++idx;
    }

    if (pow.size == 0) {
        String_push_back_char(&pow, '1');
    }

    result.coef = String_to_int(&coef);
    result.power = String_to_int(&pow);
    return result;
}

SDL_bool is_op_str(const char* buf)
{
    return (strcmp(buf, "+") || strcmp(buf, "*")) ? SDL_TRUE : SDL_FALSE;
}

Data times(Data left, Data right)
{
    return (Data) { left.coef * right.coef, left.power + right.power };
}

const List pol_nat_upd(const String* equation)
{
    Stack op_stack = Stack_create(sizeof(String), 50);
    Stack token_stack = Stack_create(sizeof(String), 50);
    String token = String_create("", 0);
    for (int i = 0; i < equation->size; ++i) {
        const char sym = equation->data[i];
        if (is_op(sym)) {
            Stack_push(&token_stack, &token); // push token to token_stack
            String_clear(&token); // start another token
            String oper = String_char_to_string(sym); // create operator token
            Stack_push(&op_stack, &oper); // push operator to op_stack
        } else if (sym == ')') {
            while (strcmp(((String*)Stack_back(&op_stack))->data, "(")) {
                Stack_push(&token_stack, Stack_back(&op_stack));
                Stack_pop(&op_stack);
            }
            Stack_pop(&op_stack); // pop last (
        } else {
            String_push_back_char(&token, sym);
        }
    }
    if (token.size != 0) {
        Stack_push(&token_stack, &token);
    }
    while (op_stack.size) {
        Stack_push(&token_stack, Stack_back(&op_stack));
        Stack_pop(&op_stack);
    }

    Stack_clear(&op_stack, 0);

    Stack monomes_stack = Stack_create(sizeof(List), 100);
    int token_idx = 0;
    while (token_idx < token_stack.size) {
        const char* sym = ((String*)token_stack.data[token_idx])->data;
        // if (is_op_str(sym)) {
        if (sym[0] == '+' || sym[0] == '*') {
            List left = *(List*)Stack_back(&monomes_stack);
            Stack_pop(&monomes_stack);
            List right = *(List*)Stack_back(&monomes_stack);
            Stack_pop(&monomes_stack);

            if (strcmp(sym, "+")) {
                List_glue(&left, &right);
                // check if func is working
                // probably
            } else if (strcmp(sym, "*")) {
                // decart product and then push resulting list
                List result = List_create(NULL, NULL, 0);

                for (Node* ptr_l = left.left; ptr_l != left.right;) {
                    for (Node* ptr_r = right.left; ptr_r != right.right;) {
                        List_push_back(&result, times(ptr_l->data, ptr_r->data));
                        
                        assert(ptr_r->next && "index out of range");
                        ptr_r = ptr_r->next;
                    }
                    assert(ptr_l->next && "index out of range");
                    ptr_l = ptr_l->next;
                }

                Stack_push(&monomes_stack, &result);
            }
        } else {
            List operand = List_create(NULL, NULL, 0);
            List_push_back(&operand, monome_parse((String*)token_stack.data[token_idx]));
            Stack_push(&monomes_stack, ((void*)&operand));
        }
        ++token_idx;
    }

    return *(List*)Stack_back(&monomes_stack);
}