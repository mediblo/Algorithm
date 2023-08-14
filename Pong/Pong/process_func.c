#include <conio.h>
#include <stdio.h>
#include "head.h"

void player_change_dir() {
	if (_kbhit()) {
		int key = _getch();

		switch (key) {
		case 'a':
		case 'A':
			player_dir = PLAYER_LEFT;
			break;
		case 'd':
		case 'D':
			player_dir = PLAYER_RIGHT;
			break;
		case 'w':
		case 'W':
			player_dir = PLAYER_UP;
			break;
		case 's':
		case 'S':
			player_dir = PLAYER_DOWN;
			break;
		default:
			error(5);
		}
	}
}