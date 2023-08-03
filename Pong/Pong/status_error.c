#include <stdio.h>
#include <curses.h>

// 1:5 맵 관련 오류, 5: 게임 실행 관련 오류
void error(int status_code) {
	if(status_code > 4) endwin();
	switch (status_code) {
		case 1:
			printf("파일 제작 실패 [ 관리자 호출 바람 ]\n");
			printf("Error Code : 1");
			break;
		case 2:
			printf("파일 불러오기 실패 [ 관리자 호출 바람 ]\n");
			printf("Error Code : 2");
			break;
		case 3:
			printf("이진 파일 제작 실패 [ 관리자 호출 바람 ]\n");
			printf("Error Code : 3");
			break;
		case 4:
			printf("이진 파일 제작중... 다시 실행시켜주시기 바랍니다.\n");
			printf("Error Code : 4");
			break;
		case 5:
			printf("func_a\n");
			printf("error Code : 5");
			break;
		case 6:
			printf("player_move error\n");
			printf("error code : 6");
			break;
		case 7:
			printf("enemy_move switch error\n");
			printf("error code : 7");
			break;
		case 8:
			printf("player vs enemy\n");
			break;
		case 9:
			printf("enemy_check error\n");
			printf("error code : 9");
			break;
		default:
			printf("OTHER ERROR\n");
			printf("error code : %d", status_code);
	}
	exit(1);
}