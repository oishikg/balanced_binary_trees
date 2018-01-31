/* ******** Inclusion ******** */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* ******** User defined types ******** */

/* the tree is a recursive data structure containing data, a left subtree, and a 
 * right subtree; thus, the tree should be a node, so that a tree pointer is 
 * a node pointer; this enables recursive traversal of trees */

typedef struct m_tree
{
  int* data;
  int print_index; /* this is useful for printing */
  struct m_tree* left_subtree_pointer;
  struct m_tree* right_subtree_pointer;
} tree;

typedef struct
{
  tree* current_tree;
} tree_wrapper;

