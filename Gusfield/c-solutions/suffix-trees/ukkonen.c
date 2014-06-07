#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char *text = "abcbdbebdebjkhldshhuhiasdauggdgywegasbjdbhajsdcsadlcgasldclasdclasbdclasbdlcguyggadslblasdlsadgofqoppqsd";

typedef struct Node {
  char *edge;
  int length;
  struct Node *child;
  struct Node *nextSibling;
} node_t;

typedef struct Tree {
  node_t *firstChild;
} tree_t;

int compareChars(char *first, char *second) {
  return *first == *second;
}

char *nodeLabelFrom(node_t *node) {
  char *label = malloc(sizeof(node->edge) * (node->length + 1));
  memcpy(label, node->edge, node->length);
  memset(label + node->length, 0, 1);
  return label;
}

void printNode(node_t *node, int counter) {
  while (node != 0) {
    debug("%d: %s %d \n", counter++, nodeLabelFrom(node), node->length);
    if (node->child != 0) {
      printNode(node->child, counter);
    }
    debug("New Sibling for %s\n", nodeLabelFrom(node));
    node = node->nextSibling;
  }
}

void printTree(tree_t *tree) {
  node_t *child = tree->firstChild;
  int i = 0;
  printNode(child, i);
}

int hasNextSibling(node_t *node) {
  return node->nextSibling != 0;
}

void addToAllNodes(tree_t *tree, int offset) {
  node_t *node = tree->firstChild;
  while (node != 0) {
    if (node->length == 0) {
      node->length = 1;
      node->edge = (text + offset);
    } else {
      node->length += 1;
    }
    node = node->nextSibling;
  }
}

void addNextChar(node_t *child, int counter) {
  debug("child %c compared with %c\n", *(child->edge), *(text + counter));
  while (!compareChars(child->edge, (text + counter)) && hasNextSibling(child)) {
    child = child->nextSibling;
  }

  if (compareChars(child->edge, (text + counter))) {
    debug("Creating a child for %s\n", child->edge);
    node_t *firstChild = malloc(sizeof(node_t));
    firstChild->edge = child->edge + 1;
    firstChild->length = child->length - 1;
    child->child = firstChild;
    child->length = 1;
    node_t *sibling = malloc(sizeof(node_t));
    sibling->length = 0;
    firstChild->nextSibling = sibling;
  } else {
    node_t *nextSibling = malloc(sizeof(node_t));
    nextSibling->edge = (text + counter);
    nextSibling->length = 1;
    child->nextSibling = nextSibling;
  }
}

void addNextTree(tree_t *tree, int counter, int length) {
  debug("Processing %s\n", text + counter);
  addToAllNodes(tree, counter);
  node_t *child = tree->firstChild;
  addNextChar(child, counter);
}


int main (int argc, char const *argv[]) {
  int length = strlen(text);
  tree_t suffixTree;
  suffixTree.firstChild = malloc(sizeof(node_t));
  suffixTree.firstChild->edge = text;
  suffixTree.firstChild->length = 1;
  int i;
  for (i = 1; i < length; i++) {
    addNextTree(&suffixTree, i, length);
  }

#ifndef NDEBUG
  printTree(&suffixTree);
#endif
}
