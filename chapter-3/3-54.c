int decode2(int x, int y, int z)
{
	int val1 = y - z;
	int val2 = val1 << 31;
	val2 >>= 31;
	val1 *= x;
	return val1 | val2;
}
