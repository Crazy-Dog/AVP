#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#define SIZEA 50000
#define SIZEB ((SIZEA+1)/2)

using namespace std;
//1.Перенсти код
//2.Профайлер
//3.Добавить разделяемую память
__global__ void addKernel(const int *a, int *b)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < SIZEB) {
		b[i] = a[i] + a[SIZEA - 1 - i];
	}
}

int main()
{
    int *a = new int[SIZEA];
    int *b = new int[SIZEB];
	int *dev_a = 0;
	int *dev_b = 0;

	float time;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	//random array values
	for (int i = 0; i < SIZEA; i++) {
		//srand(time(NULL));
		a[i] = rand();
	}

	// Allocate GPU buffers for three vectors (two input, one output)
	cudaMalloc((void**)&dev_a, SIZEA * sizeof(int));
	cudaMalloc((void**)&dev_b, SIZEB * sizeof(int));

	// Copy input vectors from host memory to GPU buffers.
	cudaMemcpy(dev_a, a, SIZEA * sizeof(int), cudaMemcpyHostToDevice);

	dim3 threads(512);
	dim3 blocks((SIZEB + 511) / 512);

	cudaEventRecord(start, 0);
	// Launch a kernel on the GPU with one thread for each element.
	addKernel <<<blocks, threads>>>(dev_a, dev_b);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);

	cudaMemcpy(b, dev_b, SIZEB * sizeof(int), cudaMemcpyDeviceToHost);

	/*for (int i = 0; i < SIZEA; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < SIZEB; i++) {
		cout << b[i] << " ";
	}*/

	cudaEventElapsedTime(&time, start, stop);
	cout << endl << time << endl;

	system("pause");

	cudaFree(dev_a);
	cudaFree(dev_b);

    return 0;
}
