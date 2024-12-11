typedef struct {
	int left;
	a_struct a[8];
	int right;
} b_struct;

typedef struct {
	int idx;
	int x[4];
} a_struct;

void test(int i, b_struct *bp)
{
	int n = bp->left + bp->right;
	a_struct *ap = &bp->a[i];
	ap->x[ap->idx] = n;
}

