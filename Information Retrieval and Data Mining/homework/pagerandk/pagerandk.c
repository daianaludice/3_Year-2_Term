/*
PageRank Simulation program.  2017/09/26
by Kang, Seung-Shik
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

// Set out-links for all pages -- random
void set_page(int page[][MAX])
{
	int i, j;

	srand(time(NULL));
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			page[i][j] = (i == j) ? 0 : (rand() % 4) == 1;
		}
	}
}

void put_page(int page[][MAX])
{
	int i, j;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf("  %d", page[i][j]);
		}
		putchar('\n');
	}
}

void pagerank(int page[][MAX], double rank[MAX], double dfactor)
{
	int i, j, k;
        int count =0;
	int nout[MAX] = { 0 };	// number of out-links for page i
	double pr = 0.;

	for (i = 0; i < MAX; i++) rank[i] = 1.0;	// initalize

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (page[i][j]) nout[i]++;
		}
	}
 
	for (k = 0; k < 99; k++) {	// max. iteration is 99
		for (i = 0; i < MAX; i++) {
			// 여기에서 pr (PageRank) 값 계산
                        for(j=0;j<MAX; j++){
                          if(page[j][i]) pr += rank[j] / nout[j];
			rank[i] = (1.0 - dfactor) + dfactor * pr;
		}
		// rank[i] 값에 변동이 없거나 미미할 때 break
		if (rank[i] == rank[i+1]) count++;
                if(count >= MAX) break;
                else countinue;
	}

	for (i = 0; i < MAX; i++)
		printf("%d : %5.2f\n", nout[i], rank[i]);
}

int main() {
	int page[MAX][MAX];
	double rank[MAX] = { 1.0 };

	set_page(page);
	put_page(page);
	pagerank(page, rank, 0.85);
}
