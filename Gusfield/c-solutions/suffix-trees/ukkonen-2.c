#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

enum BOOLEAN {
	false,
	true
};

typedef struct node {
		char *label;
		int length;	
	} node_t;

typedef struct tree {
		node_t **children;
	} tree_t;

char *text = "bananas";

node_t *createNode() {
	return malloc(sizeof(node_t));
}

void extendUsing(int latestPosition) {
	node_t *node = createNode();
}

int main (int argc, char const *argv[]) {
	int length = strlen(text);
	int i = 0;
	for (i = 0; i < length; i++) {
		extendUsing(i);
	}	
}

