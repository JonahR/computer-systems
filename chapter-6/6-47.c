#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void undirected_graph_orig(int *G, int dim) {
	int i, j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			G[dim*j + i] = G[dim*j + i] || G[dim*i + j];
		}
	}
}

// Loop unrolling reduced the runtime from 3.5 seconds to 3.0 seconds. This saves some time
// but there are a lot of cache writes and reads not in a stride-1 access pattern. I am sure
// there are more ways to reduce the runtime, but this example shows how simple loop unrolling
// can reduce runtime.
void undirected_graph_perf(int *G, int dim) {
	int i, j;

	for (i = 0; i < dim; i++) {
		for (j = 0; j <= dim-8; j+=8) {
			G[dim*(j+0) + i] = G[dim*(j+0) + i] || G[dim*i + (j+0)];
			G[dim*(j+1) + i] = G[dim*(j+1) + i] || G[dim*i + (j+1)];
			G[dim*(j+2) + i] = G[dim*(j+2) + i] || G[dim*i + (j+2)];
			G[dim*(j+3) + i] = G[dim*(j+3) + i] || G[dim*i + (j+3)];
			G[dim*(j+4) + i] = G[dim*(j+4) + i] || G[dim*i + (j+4)];
			G[dim*(j+5) + i] = G[dim*(j+5) + i] || G[dim*i + (j+5)];
			G[dim*(j+6) + i] = G[dim*(j+6) + i] || G[dim*i + (j+6)];
			G[dim*(j+7) + i] = G[dim*(j+7) + i] || G[dim*i + (j+7)];
		}
	}

	for (; i < dim; i++) {
		for (; j < dim; j++) {
			G[dim*j + i] = G[dim*j + i] || G[dim*i + j];
		}
	}
}

int performance() {
	clock_t start, end;
	double total_cpu_time;

	int (*G)[30000] = malloc(30000 * sizeof(*G));
	if (G == 0) { return 1; }

	start = clock();
	undirected_graph_perf((int*)G, 30000);
	end = clock();
	
	total_cpu_time = ((double) end - start) / CLOCKS_PER_SEC;
	printf("Total CPU time: %f", total_cpu_time);

	free(G);

	return 0;
}

int main() {
	performance();
}

