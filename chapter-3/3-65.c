typedef struct {
	short x[A][B];
	int y;
} str1;

typedef struct {
	char array[B];
	int t;
	short s[B];
	int u;
} str2;

void setVal(str1 *p, str2 *q) {
	int v1 = q ->t;
	int v2 = q->u;
	p->y = v1+v2;
}
// A = 5 B = 9
