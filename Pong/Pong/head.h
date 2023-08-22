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

// ��Ŀ ������ ����ü
typedef struct {
	int score;
	char name[4];
} RANKER;

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
extern int difficulty;
extern int item_time;
extern int score;
extern RANKER ranker[10];

// 0 �� / 1 ���� / 2 �� �� / 4 �Ѿ�� ���� / 5 ������ / 7 ���� �Ұ� / 8 �� �������� / 9 �÷��̾�

extern int map[Y_MAX][X_MAX];

// status_error.c
void error(int status_code); // ���� ���� �Լ�

// pictur.c
void init_scene(); // PDC �ʱ� ����
P_list start_scene(); // ���� ȭ�� �׸���
void title_scene(); // Ÿ��Ʋ pac-man �׸���
int select_title(); // Ÿ��Ʋ ����
int game_over_scene(); // ���ӿ��� ȭ��
void rank_name(); // ��Ŀ �̸� ���
char* get_your_name(); // ��Ŀ �̸� �Է�

P_list debug_scene(); // ����׿�

// read_map.c
void orig_read(); // ���� ������ ���� �� ����
void make_b(); // ���� ���� ����
void read_b(); // ���� ���� �ҷ�����

void start_map(); // �ʱ� �� ����
void restart_map(); // ����� �� ����

// player.c
void player_move(Point p); // �÷��̾� ������
int player_check(Point p); // �÷��̾� üũ

// Enemy.c
void enemy_move(Point p); // �� ������ [ Easy ]
int enemy_check(Point p); // �� �� üũ [ Easy ]
void enemy_change_dir(Point p); // �� ���� �ٲٱ� [ Easy ]
void normal_enemy_move(P_list p); // �� ������ [ Normal ]
int normal_enemy_check(int e_dir, Point e_p); // �� �� üũ [ Normal ]
void normal_if_item(P_list* p); // �� ������ üũ [ Normal ]

void normal_right_chk(P_list p, Point* e_p, int* chk); // Normal ���� �˰���
void normal_left_chk(P_list p, Point* e_p, int* chk); // Normal ���� �˰���
void normal_down_chk(P_list p, Point* e_p, int* chk); // Normal ���� �˰���
void normal_up_chk(P_list p, Point* e_p, int* chk); // Normal ���� �˰���

// item.c
int score_add(bool is_score); // ���� ����
void item_get(); // ������ ����

// process_func.c
void player_change_dir(); // �񵿱� �Լ� [ Ű���� �Է� ]

// rank.c
void init_rank(); // �� ó�� ��Ŀ �ʱ�ȭ
void first_make_r(); // �� ó�� ��ũ �������� ����
void make_r(); // �������� ����
void read_r(); // �������� �б�
void is_ranker(); // ��Ŀ �߰�