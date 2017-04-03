#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define N 1024

int main(int argc, char const *argv[])
{
	__int64 start, result1, result2;
	double** xmass = (double**)calloc(N, sizeof(double*));
	for (int i = 0; i < N; i++) {
		xmass[i] = (double*)calloc(N, sizeof(double));
			for (int j = 0; j < N; j++) {
				srand(time(NULL));
				xmass[i][j] = rand();
			}
	}

	double** ymass = (double**)calloc(N, sizeof(double*));
	for (int i = 0; i < N; i++) {
		ymass[i] = (double*)calloc(N, sizeof(double));
		for (int j = 0; j < N; j++) {
			srand(time(NULL));
			ymass[i][j] = rand();
		}
	}

	double** zmass = (double**)calloc(N, sizeof(double*));
	for (int i = 0; i < N; i++) {
		zmass[i] = (double*)calloc(N, sizeof(double));
	}

	start = __rdtsc();
	for (int x1 = 0; x1 < 1024; x1++) {
		for (int x2 = 0; x2 < 1024; x2++) {
			for (int x3 = 0; x3 < 1024; x3++) {
				zmass[x1][x3] += xmass[x1][x2] * ymass[x2][x3];
			}
		}
	}
	result1 = __rdtsc() - start;

	//зануление
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 1024; j++) {
				zmass[i][j] = 0;
		}
	}

	start = __rdtsc();
	for (int l3 = 0; l3 < 1024; l3 += 512) {
		for (int m3 = 0; m3 < 1024; m3 += 512) {
			for (int k3 = 0; k3 < 1024; k3 += 512) {
				//продолжение говнокода с циклами для кэша 2 лвл
				for (int l2 = l3; l2 < l3 + 512; l2+=128) {
					for (int m2 = m3; m2 < m3 + 512; m2+=128) {
						for (int k2 = k3; k2 < k3 + 512; k2+=128) {
							//продолжение говнокода с циклами для кэша 1 лвл
							for (int l1 = l2; l1 < l2 + 128; l1 += 64) {
								for (int m1 = m2; m1 < m2 + 128; m1 += 64) {
									for (int k1 = k2; k1 < k2 + 128; k1 += 64) {
										//что-то
										for (int x1 = l1; x1 < l1 + 64; x1++) {
											for (int x2 = m1; x2 < m1 + 64; x2++) {
												for (int x3 = k1; x3 < k1 + 64; x3++) {
													zmass[x1][x3] += xmass[x1][x2] * ymass[x2][x3];
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	result2 = __rdtsc() - start;
	cout << "first time: " << result1 << endl << "second time: " << result2 << endl;
	system("pause");
	return 0;
}