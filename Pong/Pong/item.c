#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "head.h"

int score_add(bool is_score) {
	static int score = 0;

	return is_score ? ++score : score;
}