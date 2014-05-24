#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

enum BOOLEAN {
	false,
	true
};

typedef struct edge {
	char *label;
	struct node *nextSibling;
} edge;

typedef struct node {
		struct node *firstChild;
		enum BOOLEAN isRoot;
		int order;
		edge edge;	
	} node_t;

typedef struct tree {
		node_t *root;
	} tree_t;

enum SEARCHSTATUS {
	notFound,
	found
};

typedef struct nodeSearch {
	node_t *node;
	enum SEARCHSTATUS status;
} nodeSearch;

char *text = "bananas";
tree_t suffixTree;

enum BOOLEAN compareChars(char *first, char *second) {
	return *first == *second;
}

void printNodeDetails(node_t *node) {
	printf("Label %c\n", *(node->edge.label));
}

void printNode(node_t *node) {
	node_t *sibling = node;
	while (sibling != 0) {
		printNodeDetails(sibling);
		node_t *child = sibling->firstChild;
		if (child != 0) {
			printNode(child);
		}
		sibling = sibling->edge.nextSibling;
	}
}
void printTree() {
	node_t *node = suffixTree.root->firstChild;
	printNode(node);
}

nodeSearch *findNode(node_t *previous, node_t *node, char *label, int depth) {
	while (node != 0 && depth > 0) {
		if (compareChars(node->edge.label, label)) {
			node_t *child = node->firstChild;
			return findNode(node, child, label + 1, depth - 1);
		} else {
			return findNode(previous, node->edge.nextSibling, label, depth);
		}
	}
	nodeSearch *searchResult = malloc(sizeof(nodeSearch));
	if (depth == 0) {
		searchResult->status = found;
	} else {
		searchResult->status = notFound;
		searchResult->node = previous;
	}
	return searchResult;
}
	
void addSiblingTo(node_t *node, node_t *newNode) {
	if (node->edge.nextSibling == 0) {
		node->edge.nextSibling = newNode;
	} else {
		addSiblingTo(node->edge.nextSibling, newNode);
	}
}

void addChildTo(node_t *node, char *label) {
	node_t *newNode = malloc(sizeof(node_t));
	newNode->edge.label = label;
	if (node->firstChild == 0) {
		node->firstChild = newNode;
	} else {
		addSiblingTo(node->firstChild, newNode);
	}
}

void addToPath(char *label, char *addition, int labelLength) {
	nodeSearch *searchResult = findNode(suffixTree.root, suffixTree.root->firstChild, label, labelLength);
	if (searchResult->status == notFound) {
		addChildTo(searchResult->node, addition);
	}
}

void addNextTree(int i) {
	int j;
	for (j = 1; j <= i + 1; j++) {
		addToPath((text + j - 1), text + i, i + 2 - j);	
	}
}

int main (int argc, char const *argv[]) {
	int length = strlen(text);
	node_t *root = malloc(sizeof(node_t));
	suffixTree.root = root;
	root->isRoot = true;
	addChildTo(root, text);
	int i;
	for (i = 1; i < length; i++) {
		addNextTree(i);
	}
	printTree();
	
}

