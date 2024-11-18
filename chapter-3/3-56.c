int loop(int x, int n)
{
	int result = -1;
	int mask;
	for (mask = 0; mask != 0; mask = mask << (n &0xFF)) {
		result |= (x & mask);
	}
	return result;
}
