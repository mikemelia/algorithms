#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char *text = "abcbdbebdebjkhldshhuhiasdauggdgywegasbjdbhajsdcsadlcgasldclasdclasbdclasbdlcguyggadslblasdlsadgofqoppqsd";

typedef struct node {
  char *edge;
  int length;
  struct node *child;
  struct node *nextSibling;
} Node;

typedef struct tree {
  Node *firstChild;
} Tree;

void *allocate(size_t amount) {
  void *location = malloc(amount);
  check_mem(location);
  return location;
 error:
  exit(1);
}

#ifndef NDEBUG
char *edge_text_from(Node *node) {
  char *label = allocate(sizeof(node->edge) * (node->length + 1));
  memcpy(label, node->edge, node->length);
  memset(label + node->length, 0, 1);
  return label;
}

void print_node(Node *node, int counter) {
  while (node != 0) {
    debug("%d: %s %d \n", counter++, edge_text_from(node), node->length);
    if (node->child != 0) {
      print_node(node->child, counter);
    }
    debug("New Sibling for %s\n", edge_text_from(node));
    node = node->nextSibling;
  }
}

void print_tree(Tree *tree) {
  Node *child = tree->firstChild;
  int i = 0;
  print_node(child, i);
}
#endif

int compare_chars(char *first, char *second) {
  return *first == *second;
}

int has_next_sibling(Node *node) {
  return node->nextSibling != 0;
}

void extend_all_nodes(Tree *tree, int offset) {
  Node *node = tree->firstChild;
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

void add_next_char(Node *child, int counter) {
  debug("child %c compared with %c\n", *(child->edge), *(text + counter));
  while (!compare_chars(child->edge, (text + counter)) && has_next_sibling(child)) {
    child = child->nextSibling;
  }

  if (compare_chars(child->edge, (text + counter))) {
    debug("Creating a child for %s\n", child->edge);
    Node *firstChild = malloc(sizeof(Node));
    firstChild->edge = child->edge + 1;
    firstChild->length = child->length - 1;
    child->child = firstChild;
    child->length = 1;
    Node *sibling = malloc(sizeof(Node));
    sibling->length = 0;
    firstChild->nextSibling = sibling;
  } else {
    Node *nextSibling = malloc(sizeof(Node));
    nextSibling->edge = (text + counter);
    nextSibling->length = 1;
    child->nextSibling = nextSibling;
  }
}

void add_next_tree(Tree *tree, int counter, int length) {
  debug("Processing %s\n", text + counter);
  extend_all_nodes(tree, counter);
  Node *child = tree->firstChild;
  add_next_char(child, counter);
}

int main (int argc, char const *argv[]) {
  int length = strlen(text);
  Tree suffixTree;
  suffixTree.firstChild = allocate(sizeof(Node));
  suffixTree.firstChild->edge = text;
  suffixTree.firstChild->length = 1;
  int i;
  for (i = 1; i < length; i++) {
    add_next_tree(&suffixTree, i, length);
  }

#ifndef NDEBUG
  print_tree(&suffixTree);
#endif
}
