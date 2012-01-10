/* section 1.4 of Gusfield */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list {
    int value;
};

int called = 0;

int bruteForceZValue(char *sub, char *reference, int length) {
	int counter = 0;
	char *position = sub;
	char *refpos = reference;
	while (*position == *refpos) {
		counter += 1;
		position = position + 1;
		refpos = refpos + 1;
		called += 1;
	}
	return counter;
}

int getValueFor(int k, char *reference, int length, int *l, int *r) {
	int value = bruteForceZValue((reference + k), reference, length - k);
	if (value > 0) {
		*r = k - 1 + value;
		*l = k - 1;
	}
	return value;
}

void zValuesFor(char *reference, int zvalues[], int length) {
	int k;
	int r = 0; 
	int l = 0;
	zvalues[0] = 0;
	zvalues[1] = getValueFor(1, reference, length, &l, &r);
	for (k = 2; k < length; k++) {
		if (k >= r) {
			zvalues[k] = getValueFor(k, reference, length, &l, &r);
		} else {
			int kprime = k - l;
			if (zvalues[kprime] < (r - k - 1)) {
				zvalues[k] = zvalues[kprime];
			} else {
				int q = bruteForceZValue((reference + r), reference + zvalues[kprime], length - r);
				zvalues[k] = r + q - k - 1;
				r = r + q;
				l = k;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int *zvalues;
	char *string = argv[1];
	int length = strlen(string);
	int counter;
	zvalues = malloc(sizeof(int) * length);
	zValuesFor(string, zvalues, length);
    printf("Called %d times for a length of %d %s.\n", called, length, string);
	for (counter = 0; counter < length; counter++) {
	    printf("%d %d\n", counter, *(zvalues + counter));
	}
	return 0;
}