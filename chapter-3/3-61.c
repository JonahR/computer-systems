int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
	int j;
	int result = 0;

	for (j = n-1; j >=0; j--)
		result += A[i][j] * B[j][k];

	return result;
}
