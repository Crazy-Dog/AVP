#include <iostream>

#define N 65536
#define str 8

#define K (N + N / 8)
#define strk 9

using namespace std;

void main() {
	int arr[N];
	int arr1[K];

//при условии 8 строк в кэше
	int i = 0;
	while(true){
		arr[i] = i + N / str;
		if (arr[i] > N-1) {
			arr[i] -= N - 1;
		}
		else if (arr[i] == N-1) {
			arr[N-1] = 0;
			break;
		}
		i = arr[i];
	}
	i = 0;
	__int64 start = __rdtsc();
	for (int j = 0; j < 100000; j++) {
		i = arr[i];
	}
	cout << __rdtsc() - start << endl << i <<endl;

//9 строк(появляется больше промахов, а также примерно в 2 раза увеличивается время, т.к. степень ассоциативности 8)
	i = 0;
	while (true) {
		arr1[i] = i + K / strk;
		if (arr1[i] > K - 1) {
			arr1[i] -= K - 1;
		}
		else if (arr1[i] == K - 1) {
			arr1[K - 1] = 0;
			break;
		}
		i = arr1[i];
	}
	i = 0;
	start = __rdtsc();
	for (int j = 0; j < 100000; j++) {
		i = arr1[i];
	}
	cout << __rdtsc() - start << endl << i << endl;
	system("pause");
}