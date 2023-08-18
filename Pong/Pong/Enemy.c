#include <curses.h>
#include <stdlib.h>
#include "head.h"

int enemy_dir = ENEMY_UP;

void enemy_move(Point p);
int enemy_check(Point p);
void enemy_change_dir(Point p);

void normal_enemy_move(P_list p_l);
int normal_enemy_check(int e_dir, Point e_p);
void normal_if_item(P_list* p);

void normal_right_chk(P_list p, Point* e_p, int* chk);
void normal_left_chk(P_list p, Point* e_p, int* chk);
void normal_down_chk(P_list p, Point* e_p, int* chk);
void normal_up_chk(P_list p, Point* e_p, int* chk);

///////////////////////// EASY /////////////////////////

void enemy_move(Point p) {
	int chk;
	int temp;
	static int before_data = 2;

	Point pP = p;

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

	if (chk == 1 || chk == 2 || chk == 5 || chk == 7) {
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
	else if (chk == 9) {
		before_data = 2;
		g_over_flag = true;
	}
}

int enemy_check(Point p) {
	switch (map[p.y][p.x]) {
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	case 4:
		return 4;
	case 5:
		return 5;
	case 7:
		return 7;
	case 9:
		return 9;
	}

	error(9);
}

void enemy_change_dir(Point p) {
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
///////////////////////// EASY /////////////////////////

//////////////////////// NORMAL ////////////////////////

void normal_enemy_move(P_list p) {
	int chk = 0;
	int temp;
	static int start_go = 3;
	static int before_data = 2;

	Point e_p = p.e_p;

	normal_if_item(&p);

	if (start_go <= 0) {
		if (p.e_p.x <= p.p_p.x && p.e_p.y <= p.p_p.y) { // 남동
			normal_down_chk(p, &e_p, &chk);
			normal_right_chk(p, &e_p, &chk);
			normal_left_chk(p, &e_p, &chk);
			normal_up_chk(p, &e_p, &chk);
		}
		else if (p.e_p.x <= p.p_p.x && p.e_p.y >= p.p_p.y) { // 복동
			normal_up_chk(p, &e_p, &chk);
			normal_right_chk(p, &e_p, &chk);
			normal_left_chk(p, &e_p, &chk);
			normal_down_chk(p, &e_p, &chk);
		}
		else if (p.e_p.x >= p.p_p.x && p.e_p.y >= p.p_p.y) { // 북서
			normal_up_chk(p, &e_p, &chk);
			normal_left_chk(p, &e_p, &chk);
			normal_right_chk(p, &e_p, &chk);
			normal_down_chk(p, &e_p, &chk);
		}
		else if (p.e_p.x >= p.p_p.x && p.e_p.y <= p.p_p.y) { // 남서
			normal_down_chk(p, &e_p, &chk);
			normal_left_chk(p, &e_p, &chk);
			normal_right_chk(p, &e_p, &chk);
			normal_up_chk(p, &e_p, &chk);
		}
	}
	else {
		start_go--;
		chk = normal_enemy_check(ENEMY_UP, p.e_p);
		e_p.y--;
	}


	if (chk == 1 || chk == 2 || chk == 5 || chk == 7) {
		temp = map[e_p.y][e_p.x];
		map[e_p.y][e_p.x] = 8;
		map[p.e_p.y][p.e_p.x] = before_data;
		before_data = temp == 7 ? 0 : temp;
	}
	else if (chk == 4) {
		if (p.e_p.x == 1) {
			temp = map[e_p.y][e_p.x];
			map[p.e_p.y][X_MAX - 2] = 8;
			map[p.e_p.y][p.e_p.x] = before_data;
			before_data = temp;
		}
		else {
			temp = map[e_p.y][e_p.x];
			map[p.e_p.y][1] = 8;
			map[p.e_p.y][p.e_p.x] = before_data;
			before_data = temp;
		}
	}
	else if (chk == 9) {
		start_go = 3;
		before_data = 2;
		g_over_flag = true;
	}
}

void normal_right_chk(P_list p, Point* e_p, int* chk) { // 동
	if (p.e_p.x != p.p_p.x && *chk == 0) {
		*chk = normal_enemy_check(ENEMY_RIGHT, p.e_p);
		if (*chk != 0) e_p->x++;
	}
}

void normal_left_chk(P_list p, Point* e_p, int* chk) { // 서
	if (p.e_p.x != p.p_p.x && *chk == 0) {
		*chk = normal_enemy_check(ENEMY_LEFT, p.e_p);
		if (*chk != 0) e_p->x--;
	}
}

void normal_down_chk(P_list p, Point* e_p, int* chk) { // 남
	if (p.e_p.y != p.p_p.y && *chk == 0) {
		*chk = normal_enemy_check(ENEMY_DOWN, p.e_p);
		if (*chk != 0) e_p->y++;
	}
}

void normal_up_chk(P_list p, Point* e_p, int* chk) { // 북
	if (p.e_p.y != p.p_p.y && *chk == 0) {
		*chk = normal_enemy_check(ENEMY_UP, p.e_p);
		if (*chk != 0) e_p->y--;
	}
}

int normal_enemy_check(int e_dir, Point e_p) {
	switch (e_dir) {
		case ENEMY_DOWN:
			return map[e_p.y + 1][e_p.x];
		case ENEMY_UP:
			return map[e_p.y - 1][e_p.x];
		case ENEMY_LEFT:
			return map[e_p.y][e_p.x - 1];
		case ENEMY_RIGHT:
			return map[e_p.y][e_p.x + 1];
	}
}

void normal_if_item(P_list* p) {
	if (item_time) {
		if (p->e_p.x < p->p_p.x) p->p_p.x = 0;
		else p->p_p.x = X_MAX;
		if (p->e_p.y < p->p_p.y) p->p_p.y = 0;
		else p->p_p.y = Y_MAX;
	}
}

//////////////////////// NORMAL ////////////////////////