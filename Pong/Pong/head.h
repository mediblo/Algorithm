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

// 랭커 데이터 구조체
typedef struct {
	int score;
	char name[4];
	int diff;
} RANKER;

// 캐릭터 방향
enum Character_direction {
	CHAR_LEFT,
	CHAR_RIGHT,
	CHAR_UP,
	CHAR_DOWN
};

extern int player_dir;

extern bool g_over_flag;
extern int difficulty;
extern int item_time;
extern RANKER ranker[10];

// 0 벽 / 1 점수 / 2 빈 값 / 4 넘어가는 지점 / 5 아이템 / 7 진입 불가 / 8 적 시작지점 / 9 플레이어

extern int map[Y_MAX][X_MAX];

// status_error.c
void error(int status_code); // 에러 대응 함수

// pictur.c
void init_scene(); // PDC 초기 설정
P_list start_scene(); // 게임 화면 그리기
void title_scene(); // 타이틀 pac-man 그리기
int select_title(); // 타이틀 선택
int game_over_scene(); // 게임오버 화면
void rank_name(); // 랭커 이름 출력
char* get_your_name(); // 랭커 이름 입력

P_list debug_scene(); // 디버그용

// read_map.c
void orig_read(); // 이진 파일이 없을 시 제작
void make_b(); // 이진 파일 제작
void read_b(); // 이진 파일 불러오기

void start_map(); // 초기 맵 복사
void restart_map(); // 재시작 맵 복사

// player.c
void player_move(P_list p_l); // 플레이어 움직임
int player_check(Point p, Point e_p); // 플레이어 체크

// Enemy.c
void enemy_move(Point p); // 적 움직임 [ Easy ]
void normal_enemy_move(P_list p); // 적 움직임 [ Normal ]
void BFS(P_list p); // 적 움직임 [ Hard ]
void if_item_death(int* before_data, Point p); // [ 아이템 획득 시 사망 ]

// item.c
int score_add(bool is_score); // 점수 증가
void item_get(); // 아이템 얻음
void init_score(); // 점수 초기화
void check_all_score(); // 점수를 다 먹었는지?

// process_func.c
void player_change_dir(); // 비동기 함수 [ 키보드 입력 ]

// rank.c
void read_r(); // 이진파일 읽기
void is_ranker(); // 랭커 추가