#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "head.h"

int item_time = 0;
int score = 0;

void item_get() { item_time = 7; }
int score_add(bool is_score) { return is_score ? ++score : score; }
