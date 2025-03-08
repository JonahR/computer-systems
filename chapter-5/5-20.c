double poly(double a[], double x, int degree) {
	long int i;
	double result = a[0];
	double xpwr1 = x;
	double xpwr2 = xpwr1 * xpwr1;
	double xpwr3 = xpwr2 * xpwr1;
	double xpwr4 = xpwr3 * xpwr1;
	double xpwr5 = xpwr4 * xpwr1;
	int result1, result2, result3, result4, result5 = 0;

	for (i = 1; i <= degree - 4; i+=5) {
		result1 += a[i] * xpwr1;
		result2 += a[i+1] * xpwr2;
		result3 += a[i+2] * xpwr3;
		result4 += a[i+3] * xpwr4;
		result5 += a[i+4] * xpwr5;

		xpwr1 = xpwr1 * xpwr5;
		xpwr2 = xpwr2 * xpwr5;
		xpwr3 = xpwr3 * xpwr5;
		xpwr4 = xpwr4 * xpwr5;
		xpwr5 = xpwr5 * xpwr5;
	}

	for (; i <= degree; i++) {
		result1 += a[i] * xpwr1;
		xpwr1 *= xpwr1;
	}

	result = result1 + result2 + result3 + result4 + result5;

	return result;
}
