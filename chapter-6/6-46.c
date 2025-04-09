#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transpose(int *dst, int *src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim +j];
}

void transpose_1(int *dst, int *src, int dim)
{
	int i, j;

	// Loop unrolling took the runtime from 3.0 seconds to 1.25 seconds
	// We read with stride-1 access and write with stride-dim access
	// To improve this method, look into optimizing the writes.
	for (i = 0; i < dim; i++) {
		for (j = 0; j <= dim-8; j += 8) {
			dst[j*dim + i] = src[i*dim + j];
			dst[j*dim + (i+1)] = src[(i+1)*dim + j];
			dst[j*dim + (i+2)] = src[(i+2)*dim + j];
			dst[j*dim + (i+3)] = src[(i+3)*dim + j];
			dst[j*dim + (i+4)] = src[(i+4)*dim + j];
			dst[j*dim + (i+5)] = src[(i+5)*dim + j];
			dst[j*dim + (i+6)] = src[(i+6)*dim + j];
			dst[j*dim + (i+7)] = src[(i+7)*dim + j];
		}

		for (; j < dim; j++) {
			dst[j*dim + i] = src[i*dim + j];
		}
	}
}

int original() {
	clock_t start, end;
	double total_cpu_time;

	int (*src)[30000] = malloc(30000 * sizeof(*src));
	if (src == NULL) {
		return 1;
	}

	int (*dst)[30000] = malloc(30000 * sizeof(*dst));
	if (dst == NULL) {
		return 1;
	}
	
	start = clock();
	transpose(dst, src, 30000);
	end = clock();
	
	total_cpu_time = ((double) end - start) / CLOCKS_PER_SEC;
	printf("Total CPU time: %f", total_cpu_time);

	free(src);
	free(dst);

	return 0;
}

int performance() {
	clock_t start, end;
	double total_cpu_time;

	int (*src)[30000] = malloc(30000 * sizeof(*src));
	if (src == NULL) {
		return 1;
	}

	int (*dst)[30000] = malloc(30000 * sizeof(*dst));
	if (dst == NULL) {
		return 1;
	}
	
	start = clock();
	transpose_1(dst, src, 30000);
	end = clock();
	
	total_cpu_time = ((double) end - start) / CLOCKS_PER_SEC;
	printf("Total CPU time: %f", total_cpu_time);

	free(src);
	free(dst);

	return 0;
}

int main() {
	performance();
}
