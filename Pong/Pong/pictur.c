#include <curses.h>
#include <Windows.h>
#include "head.h"

void init_scene();
p_list start_scene();

p_list debug_scene();

void init_scene() {
	// PDcurses 초기화
	initscr();
	cbreak(); // 입력 스트림 버퍼링 해제
	noecho(); // 사용자 입력 화면에 안뜸
	keypad(stdscr, TRUE); // 특수키 사용 여부 ( 화살표 키 )
	nodelay(stdscr, TRUE); // 비동기적 설정
}

p_list start_scene() {
	p_list p;
	for (int x = 0; x < X_MAX; x++) {
		for (int y = 0; y < Y_MAX; y++) {
			if (map[y][x] == 0) mvprintw(y, x + 30, "@"); // 벽
			else if (map[y][x] == 1) mvprintw(y, x + 30, "."); // 점수
			else if (map[y][x] == 8) {
				mvprintw(y, x + 30, "E"); // 적
				p.e_p.x = x;
				p.e_p.y = y;
			}
			else if (map[y][x] == 9) {
				mvprintw(y, x + 30, "O"); // 플레이어
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