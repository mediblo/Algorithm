#include <conio.h>
#include <stdio.h>
#include "head.h"

void player_change_dir() {
	if (_kbhit()) {
		int key = _getch();

		switch (key) {
		case 'a':
		case 'A':
			player_dir = CHAR_LEFT;
			break;
		case 'd':
		case 'D':
			player_dir = CHAR_RIGHT;
			break;
		case 'w':
		case 'W':
			player_dir = CHAR_UP;
			break;
		case 's':
		case 'S':
			player_dir = CHAR_DOWN;
			break;
		default:
			error(5);
		}
	}
}