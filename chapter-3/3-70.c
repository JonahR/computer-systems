#include <limits.h>

typedef struct ELE *tree_ptr;

struct ELE {
	long val;
	tree_ptr left;
	tree_ptr right;
};

long traverse(tree_ptr tp) {
	long ret = LONG_MIN;
	if (tp == 0) {
		return ret;
	}

	ret = tp->val;
	long left_max = traverse(tp->left);	
	if (left_max > ret) {
		ret = left_max;
	}
	long right_max = traverse(tp->right);
	if (right_max > ret) {
		ret = right_max;
	}

	return ret;
}
// B. This function computes the greatest val in the tree recursively
