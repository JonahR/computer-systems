typedef struct ELE *tree_ptr;

struct ELE {
	long val;
	tree_prt left;
	tree_prt right;
};

long trace(tree_ptr tp) {
	if (tp == NULL) {
		return 0;
	}
	tree_ptr node = tp;
	while (node.left != NULL) {
		node = node.left;	
	}
	return node.val;
}

// B. Find the val in the deepest left most node
