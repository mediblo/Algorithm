#pragma once
#include <stdbool.h> // bool shit

#define X_MAX 21 // ���� �� X �ִ� ��ǥ
#define Y_MAX 27 // ���� �� Y �ִ� ��ǥ
#define G_TIME 250 // ���� �� �̵� �ӵ�

// ��ǥ ����ü
typedef struct {
	int x;
	int y;
} Point;

// �÷��̾�� �� ��ǥ ����ü
typedef struct {
	Point e_p;
	Point p_p;
} P_list;

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

extern bool g_over_flag;

// 0 �� / 1 ���� / 2 �� �� / 4 �Ѿ�� ���� / 7 ���� �Ұ� / 8 �� �������� / 9 �÷��̾�

extern int map[Y_MAX][X_MAX];

// status_error.c
void error(int status_code); // ���� ���� �Լ�

// pictur.c
void init_scene(); // PDC �ʱ� ����
P_list start_scene(); // ���� ȭ�� �׸���
void title_scene(); // Ÿ��Ʋ pac-man �׸���
int select_title(); // Ÿ��Ʋ ����
void game_over_scene(); // ���ӿ��� ȭ��

P_list debug_scene(); // ����׿�

// read_map.c
void orig_read(); // ���� ������ ���� �� ����
void make_b(); // ���� ���� ����
void read_b(); // ���� ���� �ҷ�����

// player.c
void player_move(Point p); // �÷��̾� ������
int player_check(Point p); // �÷��̾� üũ

// Enemy.c
void enemy_move(Point p); // �� ������
int enemy_check(Point p); // �� �� üũ
void enemy_change_dir(Point p); // �� ���� �ٲٱ� [ Easy ]

// item.c
int score_add(bool is_score); // ���� ����

// process_func.c
void player_change_dir(); // �񵿱� �Լ� [ Ű���� �Է� ]