#include <stdlib.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#include "head.h"

int main() {
	p_list p;
	srand(time(NULL));

	read_b();
	
	init_scene();
	start_scene();
	while(1){
		func_a();
		p = start_scene();
		// p = debug_scene();

		refresh();
		enemy_move(p.e_p);
		player_move(p.p_p);
		refresh();
		Sleep(G_TIME);
		clear();
	}

	endwin();
	
	return 0;
}