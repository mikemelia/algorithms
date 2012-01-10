/* section 1.4 of Gusfield */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list {
    int value;
};

int called = 0;
char *string = "ACGCCGACGCAGGAACTACGCCGACGCAGGAACTAC";

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

void zValuesFor(char *reference, int zvalues[], int length) {
	int k;
	int r = 0; 
	int l = 0;
	zvalues[0] = 0;
	zvalues[1] = bruteForceZValue((reference + 1), reference, length - 1);
	if (zvalues[1] > 0) {
		r = zvalues[1];
		l = 1;
	}
	for (k = 2; k < length; k++) {
		if (k >= r) {
			printf("r = %d", r);
			zvalues[k] = bruteForceZValue((reference + k), reference, length - k);
		} else {
			int kprime = k - l;
			if (zvalues[kprime] < (r - k)) {
				zvalues[k] = zvalues[kprime];
			} else {
				int q = bruteForceZValue((reference + r), reference + zvalues[kprime], length - r);
				zvalues[k] = r + q - k;
				r = r + q;
				l = k;
			}
			printf("k= %d, r = %d", k, r);
		}
	}
}

int main() {
	int *zvalues;
	int length = strlen(string);
	int counter;
	zvalues = malloc(sizeof(int) * length);
	zValuesFor(string, zvalues, length);
    printf("Called %d times.\n", called);
	for (counter = 0; counter < length; counter++) {
	    printf("%d %d\n", counter, *(zvalues + counter));
	}
	return 0;
}