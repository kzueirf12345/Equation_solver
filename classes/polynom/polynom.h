#pragma once

#include "../list/list.h"
#include "../my_string/my_string.h"
#include <SDL_stdinc.h>

const string pol_nat(const string* equation);
void reduct_sorted_polynom(List* polynom);
void print_polynom(List* polynom, const char* const hi_message);