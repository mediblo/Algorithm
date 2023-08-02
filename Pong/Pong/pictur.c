#include <curses.h>
#include <Windows.h>
#include "head.h"

void init_scene();
p_list start_scene();

p_list debug_scene();

void init_scene() {
	// PDcurses �ʱ�ȭ
	initscr();
	cbreak(); // �Է� ��Ʈ�� ���۸� ����
	noecho(); // ����� �Է� ȭ�鿡 �ȶ�
	keypad(stdscr, TRUE); // Ư��Ű ��� ���� ( ȭ��ǥ Ű )
	nodelay(stdscr, TRUE); // �񵿱��� ����
}

p_list start_scene() {
	p_list p;
	for (int x = 0; x < X_MAX; x++) {
		for (int y = 0; y < Y_MAX; y++) {
			if (map[y][x] == 0) mvprintw(y, x + 30, "@"); // ��
			else if (map[y][x] == 1) mvprintw(y, x + 30, "."); // ����
			else if (map[y][x] == 8) {
				mvprintw(y, x + 30, "E"); // ��
				p.e_p.x = x;
				p.e_p.y = y;
			}
			else if (map[y][x] == 9) {
				mvprintw(y, x + 30, "O"); // �÷��̾�
				p.p_p.x = x;
				p.p_p.y = y;
			}
		}
	}
	refresh();
	return p;
}

p_list debug_scene() {
	p_list p;
	for (int x = 0; x < X_MAX; x++) {
		for (int y = 0; y < Y_MAX; y++) {
			if (map[y][x] == 0) continue;
			else if (map[y][x] == 8) {
				p.e_p.x = x;
				p.e_p.y = y;
			}
			else if (map[y][x] == 9) {
				p.p_p.x = x;
				p.p_p.y = y;
			}
			mvprintw(y, x + 30, "%d", map[y][x]);
		}
	}
	return p;
}