int cread_alt(int *xp) {
	int zero = 0;
	int *val = xp ? xp : &zero;
	return *val;
}
