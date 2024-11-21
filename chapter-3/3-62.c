// A. 13
// B. edi = i; ecx = j
// C. 

void transponse(int M, int A[M][M]) {
	int i, j;
	for (i = 0; i < M; i++) {
		int *Arow = A[i];
		int *Acol = &A[0][i];
		for (j = 0; j < i; j++) {
			int t = *Acol;
			int u = Arow[j];
			Arow[j] = t;
			*Acol = u;
			Acol += M;
		}
	}
}
