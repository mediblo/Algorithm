#include <stdlib.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#include "head.h"

int main() {
	P_list p;
	int sel;
	srand(time(NULL));

	read_b();
	init_scene();
	sel = select_title();
	clear();
	start_scene();
	switch(sel){
		case 0:
			while(1){
				player_change_dir();
				p = start_scene();
				// p = debug_scene();

				refresh();
				enemy_move(p.e_p);
				player_move(p.p_p);
				refresh();
				Sleep(G_TIME);
				clear();
			}
		case 3:
			printf("GAME EXIT");
		default:
			endwin();
	}
	
	return 0;
}