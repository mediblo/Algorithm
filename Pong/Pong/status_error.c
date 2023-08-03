#include <stdio.h>
#include <curses.h>

// 1:5 �� ���� ����, 5: ���� ���� ���� ����
void error(int status_code) {
	if(status_code > 4) endwin();
	switch (status_code) {
		case 1:
			printf("���� ���� ���� [ ������ ȣ�� �ٶ� ]\n");
			printf("Error Code : 1");
			break;
		case 2:
			printf("���� �ҷ����� ���� [ ������ ȣ�� �ٶ� ]\n");
			printf("Error Code : 2");
			break;
		case 3:
			printf("���� ���� ���� ���� [ ������ ȣ�� �ٶ� ]\n");
			printf("Error Code : 3");
			break;
		case 4:
			printf("���� ���� ������... �ٽ� ��������ֽñ� �ٶ��ϴ�.\n");
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