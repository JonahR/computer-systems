int switch_prob(int x, int n)
{
	int result = x;

	switch(n) {
		case 50:
		case 52:
		result <<= 2;
		break;
		case 51:
		result += 10;
		break;
		case 53:
		result >>= 2;
		break;
		case 54:
		result *= 3;
		case 55:
		result *= result;
		break;
	}

	return result;
}
