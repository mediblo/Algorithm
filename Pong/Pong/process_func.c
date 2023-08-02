#include <conio.h>
#include <stdio.h>
#include "head.h"

void func_a() {
	if (_kbhit()) {

		int key = _getch();

		switch (key) {
		case KB_LEFT:
		case 'a':
		case 'A':
			player_dir = PLAYER_LEFT;
			break;
		case KB_RIGHT:
		case 'd':
		case 'D':
			player_dir = PLAYER_RIGHT;
			break;
		case KB_DOWN:
		case 'w':
		case 'W':
			player_dir = PLAYER_UP;
			break;
		case KB_UP:
		case 's':
		case 'S':
			player_dir = PLAYER_DOWN;
			break;
		default:
			error(5);
		}
	}
}