#include <curses.h>
#include "head.h"

int player_dir = CHAR_RIGHT;

void player_move(P_list p_l);
int player_check(Point p, Point e_p);

void player_move(P_list p_l) {
	int chk;
	Point pP = p_l.p_p;
	Point p = p_l.p_p;

	switch (player_dir) {
		case CHAR_LEFT:
			pP.x--;
			break;
		case CHAR_RIGHT:
			pP.x++;
			break;
		case CHAR_DOWN:
			pP.y++;
			break;
		case CHAR_UP:
			pP.y--;
			break;
		default:
			error(6);
	}

	chk = player_check(pP, p_l.e_p);

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

int player_check(Point p, Point e_p) {
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
			if (item_time) if_item_death(2, e_p);
			else g_over_flag = true;
		default:
			return 3;
	}

	error(5);
}