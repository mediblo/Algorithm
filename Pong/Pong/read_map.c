#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "head.h"

int map[Y_MAX][X_MAX];
int temp[Y_MAX][X_MAX];

void orig_read();
void read_b();
void make_b();

void start_map();
void restart_map();

/* 저장되는 파일 내부 프리뷰
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0
0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 1 0
0 5 0 2 0 1 0 2 0 1 0 1 0 2 0 1 0 2 0 5 0
0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 1 0
0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0
0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 1 0 0 0 1 0
0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 1 0 0 0 1 0
0 1 1 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 1 1 0
0 0 0 0 0 1 0 0 0 2 0 2 0 0 0 1 0 0 0 0 0
2 2 2 2 0 1 0 2 2 2 2 2 2 2 0 1 0 2 2 2 2
2 2 2 2 0 1 0 2 0 0 7 0 0 2 0 1 0 2 2 2 2
0 0 0 0 0 1 0 2 0 0 2 0 0 2 0 1 0 0 0 0 0
4 2 2 2 2 1 2 2 0 0 8 0 0 2 2 1 2 2 2 2 4
0 0 0 0 0 1 0 2 0 0 0 0 0 2 0 1 0 0 0 0 0
2 2 2 2 0 1 0 2 2 2 2 2 2 2 0 1 0 2 2 2 2
2 2 2 2 0 1 0 2 0 0 0 0 0 2 0 1 0 2 2 2 2
0 0 0 0 0 1 0 2 0 0 0 0 0 2 0 1 0 0 0 0 0
0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0
0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 1 0
0 5 1 1 0 1 1 1 1 1 9 1 1 1 1 1 0 1 1 5 0
0 0 0 1 0 1 0 1 0 0 0 0 0 1 0 1 0 1 0 0 0
0 0 0 1 0 1 0 1 0 0 0 0 0 1 0 1 0 1 0 0 0
0 1 1 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 1 1 0
0 1 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 1 0
0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
*/

void orig_read() {
	FILE* fp = NULL;
	
	if ((fp = fopen("orig_map.txt", "r")) == NULL) error(2);
	else {
		for (int y = 0; y < Y_MAX; y++) {
			for (int x = 0; x < X_MAX; x++) {
				fscanf(fp, "%d", &map[y][x]);
			}
		}
		fclose(fp);
	}
}

void make_b() {
	FILE* fp = NULL;

	if ((fp = fopen("orig_map.bin", "wb")) == NULL) error(3);
	else {
		orig_read();
		fwrite(&map, sizeof(map), 1, fp);
		fclose(fp);
	}
}

void read_b() {
	FILE* fp = NULL;
	
	if ((fp = fopen("orig_map.bin", "rb")) == NULL) {
		make_b();
		error(4);
	}
	else {
		fread(&map, sizeof(map), 1, fp);
		fclose(fp);
	}
}

void start_map() {
	for (int y = 0; y < Y_MAX; y++)
		for (int x = 0; x < X_MAX; x++)
			temp[y][x] = map[y][x];
}

void restart_map() {
	for (int y = 0; y < Y_MAX; y++)
		for (int x = 0; x < X_MAX; x++)
			map[y][x] = temp[y][x];
}