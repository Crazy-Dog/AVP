#ifdef __INTELLISENSE__
void __syncthreads();
#endif
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#define SIZEA 2048
#define SIZEB ((SIZEA+1)/2)

using namespace std;

void cudaFunc(const int* a, int* b);
void cpuFunc(const int* a, int* b);
//2.Ѕикубическа€ интерпол€ци€
//фильтраци€ изображени€
__global__ void addKernel(const int *a, int *b)
{
	__shared__ int tmp[1024];
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < SIZEB) {
		tmp[threadIdx.x] = a[i];
		tmp[threadIdx.x + 512] = a[SIZEA - 1 - i];
	}	

	__syncthreads();

	if (i < SIZEB) {
		b[i] = tmp[threadIdx.x] + tmp[threadIdx.x + 512];
	}
}

int main() {
	int *a = new int[SIZEA];
	int *resCuda = new int[SIZEB];
	int *resCPU = new int[SIZEB];

	for (int i = 0; i < SIZEA; i++) {
		a[i] = rand();
	}

	cudaFunc(a, resCuda);
	cpuFunc(a, resCPU);

	system("pause");
	return 0;
}

void cudaFunc(const int* a, int* b)
{
	int *dev_a = 0;
	int *dev_b = 0;

	float time;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	//random array values
	

	// Allocate GPU buffers for three vectors (two input, one output)
	cudaMalloc((void**)&dev_a, SIZEA * sizeof(int));
	cudaMalloc((void**)&dev_b, SIZEB * sizeof(int));

	// Copy input vectors from host memory to GPU buffers.
	cudaMemcpy(dev_a, a, SIZEA * sizeof(int), cudaMemcpyHostToDevice);

	dim3 threads(512);
	dim3 blocks((SIZEB + 511) / 512);

	cudaEventRecord(start, 0);
	// Launch a kernel on the GPU with one thread for each element.
	addKernel << <blocks, threads >> >(dev_a, dev_b);
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
	cout << time << endl;

	cudaFree(dev_a);
	cudaFree(dev_b);
}

void cpuFunc(const int* a, int* b)
{
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
	res /= tmp.QuadPart / 1000;

	/*for (int i = 0; i < SIZEA; i++) {
	cout << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < SIZEB; i++) {
	cout << b[i] << " ";
	}*/

	cout << res << endl;
}