# Implementation of Balanced Binary Trees in C 

## About
This repository contains a C implementation of a balanced binary tree structure, and functions commonly associated with the data structure. The code contains an interactive loop that accepts user requests to define and apply the above mentioned functions to binary trees. 

## Functions implemented
We first define a data structure `tree`. Then we impelemment the following functions :
- `tree * create_new_tree()`: Allocates enough space for a tree.
- `void balance_tree(tree *t)`: Balances a binary tree.
- `int add_node(tree * t, int val)` : Add a new node storing val to the tree. Returns 0 if
the insertion was done, -1 otherwise (e.g. if val is already a node).
- `int edit_node(tree *t, int oldval, int newval)`: Changes the value of a given
node from oldval to newval. Returns 0 if the edit was succesfull and the tree was not changed (e.g. no
nodes were moved), -1 if oldval could not be found, -2 if the tree had to be rebalanced.
- `int remove_node(tree *t, int val)`: Removes a node with value val. Returns 0 if
successful, -1 if the value could not be found.
- `int shortest_distance (tree *t, int node1, int node2)`: Returns the
minimum distance (in terms of numbers of nodes) between two nodes, -1 if any of the nodes does not
exist.
- `int find_depth(tree *t, int val)`: Finds the depth of a given node. Root has a depth of
0, children to the root have a depth of 1, etc… Returns the depth (> 0) or -1 if the val could not be
found.
- `void print_nodes_at_level (tree *t, int level)`: prints all the node found at
level n. Note: level 0 is the root, level 1 should display the two children of the root, level 2 should
display 4 nodes [grand-children of the node] etc…
- `void print_tree(tree *t)`: prints the tree in a user-friendly way.
- `void delete_tree(tree *t)`: Deletes a tree.
- `tree * generate_random_tree(int size)`: Generates a balanced tree with size nodes,
each node has a random (unique) value. The tree must be balanced.
- `tree * generate_from_array(int *array, int size)`: Generates a balanced tree
with size nodes. The values are stored in array.

## Compilation and Running
To compile this code, use `make`. The `Makefile` was configured to run on my system though, so check whether all the libraries used in the code are present on your system. To view the output, run the executable `bt`. 

## Authors
Oishik Ganguly

## Acknowledgement
This code written as part of Yale-NUS College's AY2017-18 fall semester POSIX course (course code : YSC3217). The above description of the binary tree functions were written by Professor Simon Perrault, who ran the course. 


