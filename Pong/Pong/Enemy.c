#include <curses.h>
#include <stdlib.h>
#include <Windows.h>
#include "head.h"

#define MAX_QUEUE_SIZE 100

Point h_data[MAX_QUEUE_SIZE];
int front;
int rear;

int enemy_dir = ENEMY_UP;

void enemy_move(Point p);
int enemy_check(Point p);
void enemy_change_dir(Point p);

void normal_enemy_move(P_list p_l);
int normal_enemy_check(int e_dir, Point e_p);
void if_item(P_list* p);

void normal_right_chk(P_list p, Point* e_p, int* chk);
void normal_left_chk(P_list p, Point* e_p, int* chk);
void normal_down_chk(P_list p, Point* e_p, int* chk);
void normal_up_chk(P_list p, Point* e_p, int* chk);

void enqueue(Point val);
Point dequeue();
Point peek();
void add_front(Point val);
Point delete_rear();
Point get_rear();

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }
void init_deque() { init_queue(); }
void add_rear(Point val) { enqueue(val); }
Point delete_front() { return dequeue(); }
Point get_front() { peek(); }

Point get_point(int x, int y);
int is_valid(int x, int y, int chk);
void BFS(P_list p);
void backtracking(Point* poly, Point here, Point ep);
void hard_enemy_move(Point pP, Point p);

///////////////////////// EASY ///////////////////////// All Random

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

//////////////////////// NORMAL //////////////////////// Similarity BFS/DFS

void normal_enemy_move(P_list p) {
	int chk = 0;
	int temp;
	static int start_go = 3;
	static int before_data = 2;

	Point e_p = p.e_p;

	if_item(&p);

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

void if_item(P_list* p) {
	if (item_time) {
		if (p->e_p.x <= p->p_p.x) p->p_p.x = 1;
		else p->p_p.x = X_MAX-2;
		if (p->e_p.y <= p->p_p.y) p->p_p.y = 1;
		else p->p_p.y = Y_MAX-2;
	}
}

//////////////////////// NORMAL ////////////////////////

///////////////////////// HARD ///////////////////////// Real BFS

void enqueue(Point val) {
	if (is_full()) error(20);
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	h_data[rear] = val;
}

Point dequeue() {
	if (is_empty()) error(21);
	front = (front + 1) % MAX_QUEUE_SIZE;
	return h_data[front];
}

Point peek() {
	if (is_empty()) error(21);
	return h_data[(front + 1) % MAX_QUEUE_SIZE];
}

void add_front(Point val) {
	if (is_full()) error(20);
	h_data[front] = val;
	front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Point delete_rear() {
	int prev = rear;
	if (is_empty()) error(21);
	rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return h_data[prev];
}

Point get_rear() {
	if (is_empty()) error(21);
	return h_data[rear];
}

Point get_point(int x, int y) {
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

int is_valid(int x, int y, int chk) {
	if (x < 0 || y < 0 || x >= X_MAX || y >= Y_MAX) return 0;
	else if (chk == 0) return 0;
	return 1;
}

void BFS(P_list p) {
	int temp[Y_MAX][X_MAX];

	for (int y = 0; y < Y_MAX; y++)
		for (int x = 0; x < X_MAX; x++)
			temp[y][x] = map[y][x];

	Point polymorph[Y_MAX][X_MAX];
	if_item(&p);

	int x, y;
	Point here;
	init_deque();
	add_rear(get_point(p.e_p.x, p.e_p.y));
	while (is_empty() == 0) {
		here = delete_front();
		x = here.x;
		y = here.y;
		if (y == p.p_p.y && x == p.p_p.x) {
			backtracking(polymorph, here, p.e_p);
			return;
		}
		else {
			temp[y][x] = 0;
			if (is_valid(x - 1, y, temp[y][x-1])) { add_rear(get_point(x - 1, y)); polymorph[y][x - 1] = here; }
			if (is_valid(x + 1, y, temp[y][x+1])) { add_rear(get_point(x + 1, y)); polymorph[y][x + 1] = here; }
			if (is_valid(x, y - 1, temp[y-1][x])) { add_rear(get_point(x, y - 1)); polymorph[y - 1][x] = here; }
			if (is_valid(x, y + 1, temp[y+1][x])) { add_rear(get_point(x, y + 1)); polymorph[y + 1][x] = here; }
		}
	}
	error(22);
}

void backtracking(Point* poly, Point here, Point ep) {
	Point temp[Y_MAX * X_MAX];
	Point p;
	int stack_len = 0;
	temp[stack_len].x = here.x;
	temp[stack_len].y = here.y;

	for(; temp[stack_len].x != ep.x || temp[stack_len].y != ep.y; stack_len++) {
		temp[stack_len+1].x = poly[temp[stack_len].y * X_MAX + temp[stack_len].x].x;
		temp[stack_len+1].y = poly[temp[stack_len].y * X_MAX + temp[stack_len].x].y;
	}
	if (item_time && stack_len == 0) return;

	Point reversedTemp[Y_MAX * X_MAX];
	for (int i = 0; i <= stack_len; i++) {
		reversedTemp[i] = temp[stack_len - i];
	}

	/* 디버깅 코드
	for (int i = 0; i < stack_len; i++) {
		map[reversedTemp[i].y][reversedTemp[i].x] = 6;
		start_scene();
		refresh();
		Sleep(G_TIME);
	}
	*/

	hard_enemy_move(reversedTemp[1], ep);
}

void hard_enemy_move(Point pP, Point p) {
	int chk = map[pP.y][pP.x];
	static int before_data = 2;
	int temp;

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