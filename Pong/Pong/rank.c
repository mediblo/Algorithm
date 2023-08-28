#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include "head.h"

RANKER ranker[10];

void init_rank();
void first_make_r();
void make_r();
void read_r();
void is_ranker();

void init_rank() {
	for (int i = 0; i < 10; i++) {
		ranker[i].score = 10 - i;
		strcpy(ranker[i].name, "AAA");
		ranker[i].diff = 0;
	}
}

void first_make_r() {
	FILE* fp = NULL;

	fp = fopen("rank.bin", "wb");
	init_rank();
	fwrite(&ranker, sizeof(ranker), 1, fp);
	fclose(fp);
}

void make_r() {
	FILE* fp = NULL;
	
	if ((fp = fopen("rank.bin", "wb")) == NULL) error(10);
	else {
		fwrite(&ranker, sizeof(ranker), 1, fp);
		fclose(fp);
	}
}

void read_r() {
	FILE* fp = NULL;

	if ((fp = fopen("rank.bin", "rb")) == NULL) first_make_r();
	else {
		fread(&ranker, sizeof(ranker), 1, fp);
		fclose(fp);
	}
}

void is_ranker() {
	int n_score = score_add(false);
	if (ranker[9].score >= n_score) return;
	
	RANKER temp;
	temp.score = n_score;
	strcpy(temp.name, get_your_name());
	temp.diff = difficulty;
	
	for (int i = 9; i >= 0; i--) {
		if (ranker[i].score < n_score || (ranker[i].score == n_score && ranker[i].diff < difficulty)) {
			if (i == 9) ranker[i] = temp;
			else {
				temp = ranker[i];
				ranker[i] = ranker[i+1];
				ranker[i + 1] = temp;
			}
		}
		else break;
	}
	make_r();
}