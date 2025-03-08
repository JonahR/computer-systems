void psum_unroll(float a[], float p[], long int n)
{
	long int i;
	float last_val, a0, a1, a2, p_i, temp1, temp2, p_1i, p_2i;
	last_val = p[0] = a[0];
	for (i = 1; i < n-2; i++) {
		a0 = a[i];
		a1 = a[i+1];
		a2 = a[i+2];

		p_i = last_val + a0;
		temp1 = a0 + a1;
		temp2 = a1 + a2;
		
		p_1i = last_val + temp1;
		p_2i = p_i + temp2;
		
		p[i] = p_i;
		p[i+1] = p_1i;
		p[i+2] = p_2i;

		last_val = p_2i;
	}

	for (; i < n; i++) {
		p_i = last_val + a[i];
		p[i] = p_i;
		last_val = p_i;
	}
		
}
/*
The CPE is ~2.33. This is because last_val is in the critical path. It takes 3 float additions per 3 elements to construct last_val. The final addition relies
on the prevous 2 additions. So it will take a minimum of 4 cycles before the addition begins and another 3 to complete, for a total of 7 cycles per 3
elements. This is a CPE = 7 / 9 * 3 = 2.33 which is lower than the latency of 3 CPE of float addition.
