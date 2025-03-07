void psum1(float a[], float p[], long int n)
{
	long int i;
	float prev, curr = a[0];
	p[0] = prev;
	for (i = 1; i < n; i++) {
		curr = prev + a[i];
		p[i] = curr;
		prev = curr;
	}
}
