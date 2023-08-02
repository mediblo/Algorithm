#include <curses.h>
#include "head.h"

int player_dir = PLAYER_RIGHT;

void player_move(point p);
int player_check(point p);

void player_move(point p) {
	int chk;
	point pP = p;

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

	if (chk == 1) map[pP.y][pP.x] = 9;
	else if (chk == 2) {
		if (p.x == 1) map[p.y][X_MAX-2] = 9;
		else map[p.y][1] = 9;
	}
	else return;
	map[p.y][p.x] = 2;
}

int player_check(point p) {
	switch (map[p.y][p.x]) {
		case 0:
		case 7:
			return 0;
		case 4:
			return 2;
		default:
			return 1;
	}

	error(5);
}