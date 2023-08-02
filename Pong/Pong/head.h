#pragma once

#define X_MAX 21 // ���� �� X �ִ� ��ǥ
#define Y_MAX 27 // ���� �� Y �ִ� ��ǥ
#define G_TIME 250 // ���� �� �̵� �ӵ�

// Ű���� ȭ��ǥ
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_UP 72
#define KB_DOWN 80

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point e_p;
	point p_p;
} p_list;

// �÷��̾� ����
enum player_direction {
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

// �� ����
enum enemy_direction {
	ENEMY_LEFT,
	ENEMY_RIGHT,
	ENEMY_UP,
	ENEMY_DOWN
};

extern int player_dir;
extern int enemy_dir;

// 0 �� / 1 ���� / 2 �� �� / 4 �Ѿ�� ���� / 7 ���� �Ұ� / 8 �� �������� / 9 �÷��̾�

extern int map[Y_MAX][X_MAX];

// status_error.c
void error(int status_code); // ���� ���� �Լ�

// pictur.c
void init_scene(); // PDC �ʱ� ����
p_list start_scene(); // ���� ȭ�� �׸���

p_list debug_scene(); // ����׿�

// read_map.c
void orig_read(); // ���� ������ ���� �� ����
void make_b(); // ���� ���� ����
void read_b(); // ���� ���� �ҷ�����

// player.c
void player_move(point p); // �÷��̾� ������
int player_check(point p); // �÷��̾� üũ

// Enemy.c
void enemy_move(point p); // �� ������
int enemy_check(point p); // �� �� üũ
void enemy_change_dir(point p); // �� ���� �ٲٱ� [ Easy ]

// process_func.c
void func_a(); // �񵿱� �Լ� [ Ű���� �Է� ]