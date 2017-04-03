#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <intrin.h>

using namespace std;

#define N 100

int main(int argc, char const *argv[])
{
	__int64 start, result;
	double**** xmass = (double****)calloc(N, sizeof(double***));
	for (int i = 0; i < N; i++) {
		xmass[i] = (double***)calloc(N, sizeof(double**));
		for (int j = 0; j < N; j++) {
			xmass[i][j] = (double**)calloc(4, sizeof(double*));
			for (int k = 0; k < 4; k++) {
				xmass[i][j][k] = (double*)calloc(4, sizeof(double));
				for (int l = 0; l < 4; l++) {
					srand(time(NULL));
					xmass[i][j][k][l] = rand();
				}
			}
		}
	}


	double**** ymass = (double****)calloc(N, sizeof(double***));
	for (int i = 0; i < N; i++) {
		ymass[i] = (double***)calloc(N, sizeof(double**));
		for (int j = 0; j < N; j++) {
			ymass[i][j] = (double**)calloc(4, sizeof(double*));
			for (int k = 0; k < 4; k++) {
				ymass[i][j][k] = (double*)calloc(4, sizeof(double));
				for (int l = 0; l < 4; l++) {
					srand(time(NULL));
					ymass[i][j][k][l] = rand();
				}
			}
		}
	}

	double**** zmass = (double****)calloc(N, sizeof(double***));
	for (int i = 0; i < N; i++) {
		zmass[i] = (double***)calloc(N, sizeof(double**));
		for (int j = 0; j < N; j++) {
			zmass[i][j] = (double**)calloc(4, sizeof(double*));
			for (int k = 0; k < 4; k++) {
				zmass[i][j][k] = (double*)calloc(4, sizeof(double));
			}
		}
	}
	start = __rdtsc();
	for (int a = 0; a < N; a++) {
		for (int b = 0; b < N; b++) {
			for (int x1 = 0; x1 < 4; x1++) {
				double *z = zmass[a][b][x1];
				//продолжение дерьма
				for (int x2 = 0; x2 < 4; x2++) {
					double x = xmass[a][b][x1][x2];
					double *y = ymass[a][b][x2];
					__m128d t1 = _mm_set1_pd(x);
					//тута следующий цикл
					for (int k = 0; k < 2; k += 2) {
						__m128d t0 = _mm_load_pd(zmass[a][b][x1] + k);
						__m128d t2 = _mm_load_pd(y + k);
						t0 = _mm_add_pd(t0, _mm_mul_pd(t1, t2));
						_mm_store_pd(z + k, t0);
					}
				}
			}
		}
	}
	result = __rdtsc() - start;

	cout << "ticks: " << result << endl;
	system("pause");
	return 0;
}