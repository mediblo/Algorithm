#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "head.h"

int item_time = 0;
int score = 0; // √— 187∞≥ ¿÷¿Ω

void item_get() { item_time = 7; }
int score_add(bool is_score) { return is_score ? ++score : score; }
void init_score() { score = 0; }

void check_all_score() {
	if (score == 187) {
		g_over_flag = true;
	}
}