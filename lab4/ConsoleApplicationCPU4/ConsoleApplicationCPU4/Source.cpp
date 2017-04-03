#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#define SIZEA 50000
#define SIZEB ((SIZEA+1)/2)

void main() {

	int *a = new int[SIZEA];
	int *b = new int[SIZEB];

	//random array values
	for (int i = 0; i < SIZEA; i++) {
		a[i] = rand();
	}

	double res = 0;
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	res = tmp.QuadPart;

	for (int i = 0; i < SIZEB; i++) {
		b[i] = a[i] + a[SIZEA - 1 - i];
	}
	QueryPerformanceCounter(&tmp);
	res = tmp.QuadPart - res;
	QueryPerformanceFrequency(&tmp);
	res /= tmp.QuadPart/1000;

	/*for (int i = 0; i < SIZEA; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < SIZEB; i++) {
		cout << b[i] << " ";
	}*/

	cout << endl << res << endl;

	system("pause");
}