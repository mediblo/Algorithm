#include <curses.h>
#include <Windows.h>
#include "head.h"

void init_scene();
P_list start_scene();
void title_scene();
int select_title();
void game_over_scene();

P_list debug_scene();

void init_scene() {
	// PDcurses 초기화
	initscr();
	cbreak(); // 입력 스트림 버퍼링 해제
	noecho(); // 사용자 입력 화면에 안뜸
	keypad(stdscr, TRUE); // 특수키 사용 여부 ( 화살표 키 )
	// nodelay(stdscr, TRUE); // 비동기적 설정 [ 타이틀 때는 FALSE로 해야함 ]
}

P_list start_scene() {
	P_list p = {0,0};
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
	mvprintw(4, 70, "SCORE : %d", score_add(FALSE));
	refresh();
	return p;
}

P_list debug_scene() {
	P_list p = { 0,0 };
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


//
// @@@@@    @    @@@@@         @   @    @    @   @
// @   @   @ @   @             @@ @@   @ @   @@  @
// @@@@@  @@@@@  @      @@@@@  @ @ @  @@@@@  @ @ @
// @      @   @  @             @   @  @   @  @  @@
// @      @   @  @@@@@         @   @  @   @  @   @
//

void title_scene() {
	char p_title[5][50] = { "@@@@@    @    @@@@@         @   @    @    @   @",
							"@   @   @ @   @             @@ @@   @ @   @@  @",
							"@@@@@  @@@@@  @      @@@@@  @ @ @  @@@@@  @ @ @",
							"@      @   @  @             @   @  @   @  @  @@",
							"@      @   @  @@@@@         @   @  @   @  @   @" };

	for (int y = 0; y < 5; y++) mvprintw(y + 4, 20, p_title[y]);
}

int select_title() {
	int sel = 0;
	int key = 0;

	char* game_scene[4] = {"START", " RANKING", "KEY SETTING", "EXIT"};
	char* game_diff[3] = { "EASY", "NORMAL", "HARD" };

	while (1) {
		clear();
		title_scene();

		for (int i = 0; i < 4; i++) {
			if (sel == i) {
				attron(A_REVERSE);
				mvprintw(15, 20 + (i * 15), "%s", game_scene[i]);
				attroff(A_REVERSE);
			}
			else mvprintw(15, 20 + (i * 15), "%s", game_scene[i]);
		};

		refresh();
		key = getch();

		switch (key) {
		case 'a':
		case 'A':
			sel--;
			if (sel == -1) sel = 0;
			break;
		case 'd':
		case 'D':
			sel++;
			if (sel == 4) sel = 3;
			break;
		}

		if (key == 10) {
			if (sel == 0) {
				int game_sel = 0;
				int game_key = 0;
				while (1) {
					bool flag = false;
					for (int j = 0; j < 3; j++) {
						if (game_sel == j) {
							attron(A_REVERSE);
							mvprintw(19, 26 + (j * 10), "%s", game_diff[j]);
							attroff(A_REVERSE);
						}
						else mvprintw(19, 26 + (j * 10), "%s", game_diff[j]);
					}
					mvprintw(21, 27, "Enter Q to go back.");

					refresh();
					game_key = getch();
					switch (game_key) {
						case 'a':
						case 'A':
							game_sel--;
							if (game_sel == -1) game_sel = 0;
							break;
						case 'd':
						case 'D':
							game_sel++;
							if (game_sel == 3) game_sel = 2;
							break;
						case 'q':
						case 'Q':
							flag = true;
							break;
						case 10:
							return 0;
					}
					if (flag) break;
				}
			}
			else break;
		}
	}

	return sel;
}


//    GGG
//  GGG GGG
// GG     GG
//GG
//G     GGGG
//GG       G
// GG     GG
//  GGG GGGG
//    GGG  G

void game_over_scene() {
	static bool g_over_flag = false;
	if (!g_over_flag) return;

	char g_over[9][12] = {	"     GGG",
							"   GGG GGG",
							"  GG     GG",
							" GG",
							" G     GGGG",
							" GG       G",
							"  GG     GG",
							"   GGG GGGG",
							"     GGG  G"};

	char* g_over_sel[4] = { "TRY AGAIN", "CHANGE DIFF", "TITLE", "QUIT"};
	int sel = 0;
	int key = 0;

	clear();
	for (int y = 0; y < 9; y++) mvprintw(y + 4, 20, g_over[y]);
	for (int y = 0; y < 9; y++) mvprintw(y + 4, 40, g_over[y]);
	refresh();

	while (1) {
		for (int i = 0; i < 4; i++) {
			if (sel == i) {
				attron(A_REVERSE);
				mvprintw(15 + i * 2, 16, g_over_sel[i]);
				attroff(A_REVERSE);
			}
			else mvprintw(15 + i * 2, 16, g_over_sel[i]);
		}
		refresh();
		key = getch();
		switch (key) {
			case 'w':
			case 'W':
				sel--;
				if (sel == -1) sel = 0;
				break;
			case 's':
			case 'S':
				sel++;
				if (sel == 4) sel = 3;
				break;
			case 10:
				return sel;
		}
	}
}