typedef struct {
	int a;
	int *p;
} str1;

typedef struct {
	int sum;
	int diff;
} str2;

str2 word_sum(str1 s1) {
	str2 result;
	result.sum = s1.a + *s1.p;
	result.diff = s1.a - *s1.p;
	return result;
}

int prod(int x, int y)
{
	str1 s1;
	str2 s2;
	s1.a = x;
	s1.p = &y;
	s2 = word_sum(s1);
	return s2.sum * s2.diff;
}

// A. %eax is address of s1 from the caller's frame. %ebx is a. %edx is p.
// B. 0 stores s1.p, 4 stores s1.a, 8 stores the arg s1.p, 12 stores arg s1.a, 16 stores return address
// C. Each field value is passed in and a reference to the struct is passed in.
// D. The values are updated in the callers stack frame instead of passing a new struct back
