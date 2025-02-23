#include <stdio.h>

void bubble_a(int *data, int count) {
	int i, last;
	for (last = count-1; last > 0; last--) {
		for (i = 0; i < last; i++)
			if(data[i+1] < data [i]) {
				int t = data[i+1];
				data[i+1] = data[i];
				data[i] = t;
		}
	}
}

void bubble_p(int *data, int count) {
	int i, last;
	for (last = count-1; last > 0; last--) {
		for(i = 0; i < last; i++)
			// incremented
			if (*(data + i + 1) < *(data + i)) {
				int t = *(data + i + 1);
				*(data + i + 1) = *(data + i);
				*(data + i) = t;
			}
	}
}


int main() {
	int array[] = {5,4,3,2,1};
	int i;
	for (i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	bubble_p(array, 5);
	for (i = 0; i < 5; i++)
		printf("%d ", array[i]);
}	

