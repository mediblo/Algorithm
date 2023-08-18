#include <curses.h>
#include "head.h"

int player_dir = PLAYER_RIGHT;

void player_move(Point p);
int player_check(Point p);

void player_move(Point p) {
	int chk;
	Point pP = p;

	switch (player_dir) {
		case PLAYER_LEFT:
			pP.x--;
			break;
		case PLAYER_RIGHT:
			pP.x++;
			break;
		case PLAYER_DOWN:
			pP.y++;
			break;
		case PLAYER_UP:
			pP.y--;
			break;
		default:
			error(6);
	}

	chk = player_check(pP);

	if (chk == 3) map[pP.y][pP.x] = 9;
	else if (chk == 1) {
		map[pP.y][pP.x] = 9;
		score_add(TRUE);
	}
	else if (chk == 2) {
		if (p.x == 1) map[p.y][X_MAX-2] = 9;
		else map[p.y][1] = 9;
	}
	else if (chk == 4) {
		map[pP.y][pP.x] = 9;
		item_get();
	}
	else return;
	map[p.y][p.x] = 2;
}

int player_check(Point p) {
	switch (map[p.y][p.x]) {
		case 0:
		case 7:
			return 0;
		case 4:
			return 2;
		case 5:
			return 4;
		case 1:
			return 1;
		case 8:
			g_over_flag = true;
		default:
			return 3;
	}

	error(5);
}