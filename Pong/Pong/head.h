#pragma once
#include <stdbool.h> // bool shit

#define X_MAX 21 // 게임 내 X 최대 좌표
#define Y_MAX 27 // 게임 내 Y 최대 좌표
#define G_TIME 250 // 게임 내 이동 속도

// 좌표 구조체
typedef struct {
	int x;
	int y;
} Point;

// 플레이어와 적 좌표 구조체
typedef struct {
	Point e_p;
	Point p_p;
} P_list;

// 플레이어 방향
enum player_direction {
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

// 적 방향
enum enemy_direction {
	ENEMY_LEFT,
	ENEMY_RIGHT,
	ENEMY_UP,
	ENEMY_DOWN
};

extern int player_dir;

extern bool g_over_flag;

// 0 벽 / 1 점수 / 2 빈 값 / 4 넘어가는 지점 / 7 진입 불가 / 8 적 시작지점 / 9 플레이어

extern int map[Y_MAX][X_MAX];

// status_error.c
void error(int status_code); // 에러 대응 함수

// pictur.c
void init_scene(); // PDC 초기 설정
P_list start_scene(); // 게임 화면 그리기
void title_scene(); // 타이틀 pac-man 그리기
int select_title(); // 타이틀 선택
void game_over_scene(); // 게임오버 화면

P_list debug_scene(); // 디버그용

// read_map.c
void orig_read(); // 이진 파일이 없을 시 제작
void make_b(); // 이진 파일 제작
void read_b(); // 이진 파일 불러오기

// player.c
void player_move(Point p); // 플레이어 움직임
int player_check(Point p); // 플레이어 체크

// Enemy.c
void enemy_move(Point p); // 적 움직임
int enemy_check(Point p); // 적 맵 체크
void enemy_change_dir(Point p); // 적 방향 바꾸기 [ Easy ]

// item.c
int score_add(bool is_score); // 점수 증가

// process_func.c
void player_change_dir(); // 비동기 함수 [ 키보드 입력 ]