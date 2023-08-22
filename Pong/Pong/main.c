#include <stdlib.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#include "head.h"

int main() {
	P_list p;
	int sel;
	int item_cnt = 0;
	bool flag = true;
	srand(time(NULL));

	read_b();
	read_r();
	start_map();
	init_scene();

	do{
		if(flag) sel = select_title();
		flag = false;
		g_over_flag = false;
		score = 0;

		clear();
		start_scene();
		switch(sel){
			case 0:
				while(1){
					player_change_dir();
					p = start_scene();
					// p = debug_scene();

					refresh();
					switch (difficulty) {
						case 0:
							enemy_move(p.e_p);
							break;
						case 1:
							normal_enemy_move(p);
							break;
						default:
							enemy_move(p.e_p);
					}
					player_move(p.p_p);
					refresh();
					Sleep(G_TIME);
					if (item_time) {
						item_cnt+=G_TIME;
						if (item_cnt >= 1000) {
							item_time--;
							item_cnt = 0;
						}
					}

					clear();
					if (g_over_flag) {
						is_ranker();
						rank_name();
						break;
					}
				}
				break;
			case 1:
				rank_name();
				flag = true;
				break;
			case 3:
				printf("GAME EXIT");
				endwin();
				return 0;
		}

		sel = game_over_scene();
		switch (sel) {
			case 0:
				restart_map();
				break;
			case 1:
				flag = true;
				restart_map();
				break;
			case 2:
				sel = 3;
				break;
		}
	} while (1);
	
	return 0;
}