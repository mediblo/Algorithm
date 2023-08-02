#include <curses.h>
#include <stdlib.h>
#include "head.h"

int enemy_dir = ENEMY_UP;

void enemy_move(point p);
int enemy_check(point p);
void enemy_change_dir(point p);

void enemy_move(point p) {
	int chk;
	int temp;
	static int before_data = 2;

	point pP = p;

	switch (enemy_dir) {
	case ENEMY_LEFT:
		if (map[p.y][p.x - 1] == 0) enemy_change_dir(p);
		break;
	case ENEMY_RIGHT:
		if (map[p.y][p.x + 1] == 0) enemy_change_dir(p);
		break;
	case ENEMY_DOWN:
		if (map[p.y + 1][p.x] == 0) enemy_change_dir(p);
		break;
	case ENEMY_UP:
		if (map[p.y - 1][p.x] == 0) enemy_change_dir(p);
		break;
	}

	switch (enemy_dir) {
	case ENEMY_LEFT:
		pP.x--;
		break;
	case ENEMY_RIGHT:
		pP.x++;
		break;
	case ENEMY_DOWN:
		pP.y++;
		break;
	case ENEMY_UP:
		pP.y--;
		break;
	default:
		error(7);
	}

	chk = enemy_check(pP);

	if (chk == 1 || chk == 2 || chk == 7) {
		temp = map[pP.y][pP.x];
		map[pP.y][pP.x] = 8;
		map[p.y][p.x] = before_data;
		before_data = temp;
	}
	else if (chk == 4) {
		if (p.x == 1) {
			temp = map[pP.y][pP.x];
			map[p.y][X_MAX - 2] = 8;
			map[p.y][p.x] = before_data;
			before_data = temp;
		}
		else {
			temp = map[pP.y][pP.x];
			map[p.y][1] = 8;
			map[p.y][p.x] = before_data;
			before_data = temp;
		}
	}
	else if (chk == 9) error(8); // player ¿‚¿Ω
}

int enemy_check(point p) {
	switch (map[p.y][p.x]) {
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	case 4:
		return 4;
	case 7:
		return 7;
	}

	error(9);
}

void enemy_change_dir(point p) {
	bool wall_chk[4] = { FALSE, FALSE, FALSE, FALSE };
	bool escape = TRUE;
	int ran_dir;

	if (map[p.y][p.x - 1] == 0) wall_chk[0] = TRUE; // L
	else if (map[p.y][p.x + 1] == 0) wall_chk[1] = TRUE; // R
	else if (map[p.y - 1][p.x] == 0) wall_chk[2] = TRUE; // U
	else if (map[p.y + 1][p.x] == 0) wall_chk[3] = TRUE; // D

	while (escape) {
		ran_dir = rand() % 4;

		if (wall_chk[ran_dir] == FALSE)
			escape = FALSE;
	}

	enemy_dir = ran_dir;
}