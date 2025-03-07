void merge(int src1[], int src2[], int dest[], int n) {
	int i1 = 0;
	int i2 = 0;
	int id = 0;
	while (i1 < n && i2 < n) {
			int val1 = src1[i1];
			int val2 = src2[i2];
			int dest1 = val1 < val2;
			dest[id++] = dest1 ? val1 : val2;
			i1 += dest1;
			i2 += 1 - dest1;
	}
}

