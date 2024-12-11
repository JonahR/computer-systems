// e1.p: 0
// e1.y: 4
// e2.x: 0
// e2.next: 4

// The struct would require 8 total bytes

union ele {
	struct {
		int *p;
		int y;
	} e1;
	struct {
		int x;
		union ele *next;
	} e2;
};

void proc (union ele *up)
{
	up->next->y = *(up->next->p) - up->x;
}
