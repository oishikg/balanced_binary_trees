#include "binary_tree.h"


/* ******** standard functions associated with BSTs ******** */

/* function to sort an array */
void bubble_sort_array (int* arr, int len)
{
  int i,j,temp;
  for (i=0 ; i<len ; i++)
    {
      for (j=0 ; j<len-i-1 ; j++)
	{
	  temp = 0;
	  if (arr[j] > arr[j+1])
	    {
	      temp = arr[j];
	      arr[j] = arr[j+1];
	      arr[j+1] = temp;
	    }
	}
    }

}

/* function to check for repetitions in an array */
int check_repetitions (int* array, int size)
{
  int i,j;
  int temp_val;
  int flag;

  flag = 0;

  for (i=0 ; i<size-1 ; i++)
    {
      temp_val = array [i];
      for (j=i+1 ; j<size ; j++)
	{
	  if (temp_val == array [j])
	    {
	      flag = 1;
	      break;
	    }
	  
	}
      if (flag)
	break;
    }

  return (flag);
}










/* to compute the maximum value given two numbers */
int max (int a , int b)
{
  if (a > b)
    return a;
  else
    return b;
}

/* height of tree */
int compute_height (tree* t)
{
  if (t[0].data == NULL)
    return (1);
  else
    {
      /* printf ("The data value is %d \n", t[0].data[0]);*/
	return (
	    max
	    (compute_height (t[0].left_subtree_pointer), 
	     compute_height (t[0].right_subtree_pointer)) + 1
	    );
    }
}

/* number of nodes in a tree */
int count_nodes (tree* t)
{
  if (t[0].data == NULL)
    return (0);
  else
    {
      return (1 + count_nodes (t[0].left_subtree_pointer) +
	      count_nodes (t[0].right_subtree_pointer) );
    }
}

/* check if trees is balanced; return 0 if balanced, -1 otherwise */
int check_balance (tree* t)
{
  int height_lst, height_rst, rv_lst, rv_rst;

  if (t[0].data == NULL)
    return 0;
  else
    {
      /* make recursive calls to subtrees to check if they are balanced */
      rv_lst = check_balance (t[0].left_subtree_pointer);
      rv_rst = check_balance (t[0].right_subtree_pointer);

      /* if any of the subtrees are unbalanced, the entire tree is unbalanced */
      if (rv_lst == -1 || rv_rst == -1)
	return (-1);
      /* if not,  check the difference between the heights of the subtrees */
      else
	{
	  height_lst = count_nodes (t[0].left_subtree_pointer);
	  height_rst = count_nodes (t[0].right_subtree_pointer);

	  if (abs (height_lst - height_rst) > 1)
	    return (-1);
	  else
	    return (0);
	}
    }
}


/* check if a given node value exists in a tree */
int check_node_exists (tree* t, int val)
{
  int lst_rv, rst_rv;
  
  if (t[0].data == NULL)
    return 0;
  else
    {
      if (t[0].data[0] == val)
	return 1;
      else
	{
	  /* if the data does not match, check the subtrees */
	  lst_rv = check_node_exists (t[0].left_subtree_pointer, val);
	  rst_rv = check_node_exists (t[0].right_subtree_pointer, val);

	  if (lst_rv == 1 || rst_rv == 1)
	    return 1;
	  else
	    return 0;
	}
    }
}

/* ******** ******** */

/* ******** create_new_tree () ******** */

/* allocates space for the tree and returns pointer to it */


tree* create_new_tree_aux ()
{
  /* declarations */
  tree* new_tree;
  
  /* allocate memory */
  new_tree = (tree*) malloc (sizeof (tree));

  /* set the root node value to NULL */
  new_tree[0].data = NULL;

  /* set print index for the root node */
  new_tree[0].print_index = 0;
  
  /* return tree */
  return (new_tree);
}

tree_wrapper* create_new_tree ()
{
  tree_wrapper* new_tree_wrapper;

  new_tree_wrapper = (tree_wrapper*) malloc (sizeof (tree_wrapper));
  new_tree_wrapper[0].current_tree = create_new_tree_aux();
  return (new_tree_wrapper);
}

/* ******** ******** */

/* ******** delete_tree () ******** */

/* delete a given tree and free memory */

void delete_tree_aux (tree *t)
{
  /* base case */
  if (t[0].data == NULL)
    return;
  /* inductive case */
  else 
    {
      /* recurse the left and right sub-trees */
      delete_tree_aux (t[0].left_subtree_pointer);
      delete_tree_aux (t[0].right_subtree_pointer);
    
      /* once the left and right subtrees have been recursively traversed, 
       * free the memory allocated to them */

      /* free data */
      free (t[0].data);
      t[0].data = NULL;

      /* free left subtree */
      free (t[0].left_subtree_pointer);
      t[0].left_subtree_pointer = NULL;

      /* free right subtree */
      free (t[0].right_subtree_pointer);
      t[0].right_subtree_pointer = NULL;
      
      return;
    }
}
void delete_tree (tree_wrapper *t)
{
  /* delete_tree_aux() traverses the tree recursively and frees the pointers to the
   * data and subtrees */
  delete_tree_aux (t[0].current_tree);

  /* finally, free pointer to the root node by free the pointer to the tree */
  free (t[0].current_tree);
  t[0].current_tree = NULL;
  free (t);
  t = NULL;
}

/* ******** ******** */


/* ******** balance_tree () ******** */

/* we define some helper functions to balanced the tree */
tree* right_rotate (tree* t)
{
  tree* original_tree;
  if (t[0].data == NULL)
    return t;
  /* case 1: Node (Leaf , val , t2) - continue right rotating on t2 */
  else if (t[0].left_subtree_pointer[0].data == NULL)
    {
      /*printf ("The data value in the current node is %d \n" , t[0].data[0]);*/
     t[0].right_subtree_pointer = right_rotate (t[0].right_subtree_pointer);
     return t;
    }
  /* case 2: Node ( Node( t11 , val , t12) , val' , t2) - perform the left 
   * rotation */
  else
    {
      /* store the details of the original tree in */
      original_tree = t;
      
      /* make the swap */
      t = t[0].left_subtree_pointer;
      original_tree[0].left_subtree_pointer = t[0].right_subtree_pointer;
      t[0].right_subtree_pointer = original_tree;

      /* call the function recursively on the given tree */
      t = right_rotate (t);
      return t;
    }
}

void tree_to_array (tree* t , int* node_array, int index_counter)
{
  if (t[0].data == NULL)
    return;
  else
    {
      node_array[index_counter] = t[0].data[0] ;
      tree_to_array ( t[0].right_subtree_pointer, node_array, (index_counter+1));
    }
}

tree* array_to_tree (int* node_array, int lb, int ub, tree* t)
{
  int mid_point;
  int node_val;
  tree* lst;
  tree* rst;
  /* base case */
  if (lb > ub)
    return t;
  else
    {
      /* add the value to the current tree */
      mid_point = lb + (ub - lb) / 2;
      node_val = node_array [mid_point];

      /* allocate memory for data and store val */
      t[0].data = (int*) malloc (sizeof (int));
      t[0].data[0] = node_val;

      /* allocate memory for left subtree */
      t[0].left_subtree_pointer = (tree*) malloc (sizeof (tree));
      t[0].left_subtree_pointer[0].data = NULL;

      /* allocate memory for right subtree */
      t[0].right_subtree_pointer = (tree*) malloc (sizeof (tree));
      t[0].right_subtree_pointer[0].data = NULL;


      /* construct the left and right sub trees */

      /* construct left tree */
      lst = create_new_tree_aux ();
      lst = array_to_tree (node_array, lb, (mid_point - 1),  lst);

      /* construct right tree */
      rst = create_new_tree_aux ();
      rst = array_to_tree (node_array, (mid_point + 1), ub, rst);

      /* put the tree together and return */
      t[0].left_subtree_pointer = lst;
      t[0].right_subtree_pointer = rst;

      return t;
    }
}


void balance_tree (tree_wrapper* t)
{
  /* declarations */
  int i;
  int num_nodes;
  int* node_array;
  
  /* first convert the tree into a right tree */
  t[0].current_tree = right_rotate (t[0].current_tree);

  /* now convert the tree into an array */
  num_nodes = count_nodes (t[0].current_tree);
  node_array = (int*) malloc (sizeof (int) * num_nodes);
  tree_to_array (t[0].current_tree , node_array , 0);

  /* sort the node_array */
  bubble_sort_array (node_array, num_nodes);

  printf ("\n Printing the sorted node array \n");
  for (i=0 ; i<num_nodes ; i++)
    printf ("%d  ", node_array[i]);
  printf ("\n");

  /* finally, convert the array into a balanced tree using the divide-and-pick the 
   * center point method ; to do so, we will delete the old tree and build a new 
   * one */
  delete_tree_aux (t[0].current_tree);
  free (t[0].current_tree);
  t[0].current_tree = create_new_tree_aux ();
  t[0].current_tree =
    array_to_tree (node_array, 0, (num_nodes - 1), t[0].current_tree);

  /* we can check if the tree is balanced or not */
  if (check_balance (t[0].current_tree) == 0)
    printf ("The tree is balanced \n");
  else
    printf ("The tree is not balanced \n");

  free (node_array);
}

/* ******** ******** */

/* ******** add_node () ******** */

/* add node to the tree; return 0 if the node was inserted, -1 otherwise */

int add_node_aux (tree* t, int val)
{
  /* base case: if the root node is a NULL (i.e., a leaf), 
   * then insert the given val; the node must first be created */
  if (t[0].data == NULL)
    {
      /* allocate memory for data and store val */
      t[0].data = (int*) malloc (sizeof (int));
      t[0].data[0] = val;

      /* allocate memory for left subtree */
      t[0].left_subtree_pointer = (tree*) malloc (sizeof (tree));
      t[0].left_subtree_pointer[0].data = NULL;

      /* allocate memory for right subtree */
      t[0].right_subtree_pointer = (tree*) malloc (sizeof (tree));
      t[0].right_subtree_pointer[0].data = NULL;

      /* return 1 to indicated succesful addition of node */
      return (0);
    }

  /* if the value is strictly less than the value at the current node, insert the 
   * data value into the left sub-tree */
  else if (t[0].data[0] > val)
    return (add_node_aux (t[0].left_subtree_pointer , val));
  
  /* if the value is strictly greater than the value at the current node, insert the 
   * data value into the right sub-tree */
  else if (t[0].data[0] < val)
    return (add_node_aux (t[0].right_subtree_pointer , val));

  /* if the value is equal to the value at the current node, then return -1 */
  else
    return (-1);
}

int add_node (tree_wrapper* t, int val)
{
  int rv; 
  rv = add_node_aux (t[0].current_tree, val);

  /* check if the tree is unbalanced; if so, rebalance it */
  if (check_balance (t[0].current_tree) == 0)
    return (rv);
  else
    {
      printf ("The tree is out of balanced and needs to be rebalanced... \n");
      balance_tree (t);
      printf ("The tree has been balanced. \n");
      return (rv);
    }
}

/* ******** ******** */


/* ******** print_tree() ******** */

/* we first define some helper functions */


/* set print_index for every node */
void set_print_index (tree* t, int print_index)
{
  if (t[0].data == NULL)
    return;
  else
    {
      /* set print_index */
      t[0].print_index = print_index;

      /* call the function on the left and right subtrees */
      set_print_index (t[0].left_subtree_pointer , (print_index*2 + 1));
      set_print_index (t[0].right_subtree_pointer , (print_index*2 + 2));
      return;
    }
}


/* extract data */
void extract_data (tree* t, int** node_array)
{
  if (t[0].data == NULL)
    return;
  else
    {
      /* allocate memory to the the index of the node_array corresponding to the 
       * print_index of the given node */
      node_array [t[0].print_index] = (int*) malloc (sizeof (int));
      node_array [t[0].print_index][0] = t[0].data[0];

      /* call left and right subtrees */
      extract_data (t[0].left_subtree_pointer, node_array);
      extract_data (t[0].right_subtree_pointer, node_array);

      return;
    }
    
}


/* margin_distance ()*/

int margin_distance (int sib, int cous, int level)
{
  int d;
  int fact;

  fact = (int) (pow(2,level)/4);

  d = fact * sib + (int) (fact - 0.5) * cous;
  
  return d;
  
}



void print_tree_aux (tree* t)
{
  /* declarations */
  int height;
  int i,j,k ;
  int sibling_distance;
  int cousin_distance;
  int m_dist;
  int** node_array;
  int node_array_size;
  int temp_dist;

  /* initializations */

  /* determine node array size */
  height = compute_height (t);
  node_array_size = 0;
  for (i=0 ; i< height ; i++)
    node_array_size += (int) pow (2,i);

  /* allocate memory for node array */
  node_array = (int**) malloc (sizeof(int*) * node_array_size);
  for (i=0 ; i<node_array_size ; i++)
    node_array[i] = NULL;

  /* set print indeces for tree */
  set_print_index (t , 0);

  /* extract data from node_array */
  extract_data (t , node_array);

  /* set sibling and cousin distances; ensure they are multiples of 2 */
  sibling_distance = 2;
  cousin_distance = 2;

  /* print the root node */
  m_dist = margin_distance (sibling_distance, cousin_distance,
				(height-1));
  for (k=0 ; k<m_dist ; k++)
    printf (" ");

  if (node_array[0] != NULL)
    printf ("%d \n", node_array[0][0]);

  /* print nodes in middle layers (excluding the last layer */
  for (i=1 ; i<height-2 ; i++)
    {
      
      m_dist = margin_distance (sibling_distance, cousin_distance,
				(height - i-1));
      /* print the required spaces */
      for (k=0 ; k< m_dist ; k++)
	printf (" ");

      /* print nodes */
      for (j= ((int) pow (2,i) - 1 )  ; j<= ((int) pow (2, (i+1)) - 2) ; j++)
	{
	  if (node_array [j] != NULL)
	    printf ("%d", node_array[j][0]);
	  else
	    printf ("L");

	  /* add gap */
	  temp_dist = ((int) pow (2, (height - i - 2))) *
	    (sibling_distance + cousin_distance);
	  for (k=0 ; k< temp_dist ; k++)
	    {
	      if (j%2 !=0)
		printf ("-");
	      else
		printf (" ");
	    }
	}

      /* print newline */
      printf (" \n");
    }

  if (height > 2)
    {
      /* print the second last layer */
      for (j= ((int) pow (2,(height-2)) - 1 )  ;
	   j<= ((int) pow (2, (height - 1)) - 2) ; j++)
	{
	  if (node_array [j] != NULL)
	    printf ("%d", node_array[j][0]);
	  else
	    printf ("L");

	  /* add the gap */
	  if (j%2 == 0)
	    {
	      for (k=0 ; k<cousin_distance*2 ; k++)
		printf (" ");
	    }
	  else /* connect siblings */
	    {
	      for (k=0 ; k<sibling_distance*2 ; k++)
		printf ("-");
	    }
	}
    }

  /* the last layer is always leaves, so we don't need to print it */
  
  printf ("\n");

  /* free node_array */
  for (i=0 ; i<node_array_size ; i++)
    {
      if (node_array[i] == NULL)
	continue;
      else
	{
	  free (node_array[i]);
	  node_array[i] = NULL;
	}
    }
  free (node_array);
  node_array = NULL;
  
}

void print_tree (tree_wrapper* t)
{
  print_tree_aux (t[0].current_tree);
}

/* ******** ******** */

/* ******** edit_node () ******** */

/* we write an auxiliary function make the edit; then the main edit function checks 
 * if the tree is unbalanced, and if so, rebalanced it */

int edit_node_aux (tree* t, int oldval, int newval)
{
  /* declarations */
  int lst_rv, rst_rv;

  /* if we reach the leaves of a subtree, the node is not in that subtree */
  if (t[0].data == NULL)
    return -1;
  else if (t[0].data[0] == oldval)
    {
      t[0].data[0] = newval;
      return 0; /* for succesful edit */
    }
  else
    {
      /* search the left and right subtrees for the value */
      lst_rv = edit_node_aux (t[0].left_subtree_pointer, oldval, newval);
      rst_rv = edit_node_aux (t[0].right_subtree_pointer, oldval, newval);

      /* only if both the return value are -1, return -1 */
      if (lst_rv == -1 && rst_rv == -1)
	return -1;
      else
	return 0;
    }
}


int check_ordering (tree* t)
{
  int rv, lst_rv, rst_rv;
  
  if (t[0].data == NULL)
    return 0;
  else
    {
      /* first check the left and right subtrees */
      lst_rv = check_ordering (t[0].left_subtree_pointer);
      rst_rv = check_ordering (t[0].right_subtree_pointer);

      /* if a disordering is found in either of the subtrees, return -2 */
      if (lst_rv == -2 || rst_rv == -2)
	return (-2);
      
      /* otherwise check the current node for ordering */
      else
	{
	  /* let the default return value be 0 */
	  rv = 0;
      
	  /* check if current data is greater than left subtree data */
	  if (t[0].left_subtree_pointer[0].data != NULL)
	    {
	      if (t[0].data[0] > t[0].left_subtree_pointer[0].data[0])
		rv = 0;
	      else
		rv = -2;
	    }

	  /* check if current data is lesser than the right subtree data */
	  if (t[0].right_subtree_pointer[0].data != NULL)
	    {
	      if (t[0].data[0] < t[0].right_subtree_pointer[0].data[0])
		rv = 0;
	      else
		rv = -2;
	    }

	  /* return rv */
	  return (rv);
	}
    }
}




int edit_node (tree_wrapper* t, int oldval, int newval)
{
  /* declarations */
  int rv;
  
  rv = edit_node_aux (t[0].current_tree, oldval, newval);
  
  if (rv == 0)
    {
      /* now check if the tree ordering is preserved; if not, rebalance and return
       * -2 */
      if (check_ordering (t[0].current_tree) == 0)
	return 0;
      else
	{
	  balance_tree (t);
	  return (-2);
	}
    }
  else
    return -1;
}


/* ******** ******** */


/* ******** remove_node () ******** */

int remove_node (tree_wrapper* t, int val)
{
  /* declarations */
  int  num_nodes;
  int* node_array;
  int* new_node_array;
  int i, index;

  /* if the node exists, it must be deleted, and the tree rearranged with the 
   * remaining nodes */

  if (check_node_exists (t[0].current_tree, val))
    {
      /* first convert the tree into a right tree */
      t[0].current_tree = right_rotate (t[0].current_tree);
      
      /* now convert the tree into an array */
      num_nodes = count_nodes (t[0].current_tree);
      node_array = (int*) malloc (sizeof (int) * num_nodes);
      tree_to_array (t[0].current_tree , node_array , 0);

      /* remove the element to be deleted */
      new_node_array = (int*) malloc (sizeof (int) * (num_nodes - 1));
      index = 0;
      for (i=0 ; i<num_nodes ; i++)
	{
	  if (node_array[i] == val)
	    continue;
	  else
	    new_node_array[index++] = node_array[i];
	}

      /* sort the new array */
      bubble_sort_array (new_node_array, (num_nodes - 1));

      /* reconstruct new rebalanced array without the deleted element */
      delete_tree_aux (t[0].current_tree);
      free (t[0].current_tree);
      t[0].current_tree = create_new_tree_aux ();
      t[0].current_tree =
	array_to_tree (new_node_array, 0, (num_nodes - 2), t[0].current_tree);

      /* return 0 to indicate succesful removal */
      return 0;
    }
  else
    return (-1);
}

/* ******** ******** */

/* ******** shortest_distance ()  ******** */

tree* get_common_ancestor_tree (tree* t, int n1, int n2)
{
  /* determine whether both nodes are in the left or right subtree */

  /* left subtree */
  if (check_node_exists (t[0].left_subtree_pointer, n1) == 1 &&
      check_node_exists (t[0].left_subtree_pointer, n2) == 1)
    return (get_common_ancestor_tree (t[0].left_subtree_pointer, n1, n2));

  /* right subtree */
  else if (check_node_exists (t[0].right_subtree_pointer, n1) == 1 &&
	   check_node_exists (t[0].right_subtree_pointer, n2) == 1)
    return (get_common_ancestor_tree (t[0].right_subtree_pointer, n1, n2));

  /* if neither subtrees are common ancestors, the current node is the closest
   * ancestor */
  else  
    return t;
}


/* this determines the lenght of the path from the root of a tree to a given node */
int compute_root_node_length (tree* t, int node)
{
  if (check_node_exists (t[0].left_subtree_pointer, node) == 1)
    return (1 + compute_root_node_length (t[0].left_subtree_pointer, node));
  else if (check_node_exists (t[0].right_subtree_pointer, node) == 1)
    return (1 + compute_root_node_length (t[0].right_subtree_pointer, node));
  else
    return 0;
}

int compute_shortest_distance (tree* t, int small_node, int big_node) 
{
  tree* ancestor;
  
  /* either big_node is a right descendant of small node, 
   * or small_node is a left descendant of big_node, 
   * or they both have a common ancestor; we need to clarify this */

  ancestor = get_common_ancestor_tree (t, small_node, big_node);

 
  if (ancestor[0].data[0] == small_node ||
      ancestor[0].data[0] == big_node)
    return (compute_root_node_length (ancestor, small_node) +
	    compute_root_node_length (ancestor, big_node));
  else
    return ((compute_root_node_length (ancestor, small_node) +
	    compute_root_node_length (ancestor, big_node)));

}


int shortest_distance (tree_wrapper* t, int node1, int node2)
{
  /* check for existence of nodes */
  if (check_node_exists (t[0].current_tree, node1) == 0 ||
      check_node_exists (t[0].current_tree, node2) == 0 )
    return (-1);
  else
    return (compute_shortest_distance (t[0].current_tree, node1, node2));
}


/* ******** ******** */

/* ******** find_depth ()******** */

int compute_depth_of_node (tree* t, int val)
{
  if (t[0].data[0] == val)
    return 0;
  else
    {
      if (check_node_exists (t[0].left_subtree_pointer, val))
	return (1 + compute_depth_of_node (t[0].left_subtree_pointer, val));
      else
	return (1 + compute_depth_of_node (t[0].right_subtree_pointer, val));
    }
}



int find_depth (tree_wrapper* t, int val)
{
  /* check if node exists */
  if (check_node_exists (t[0].current_tree, val))
    return (compute_depth_of_node (t[0].current_tree, val));
  else
    return (-1);
}


/* ******** ******** */

/* ******** print_nodes_at_level() ******** */

void print_nodes_at_level_aux (tree* t, int level)
{
  if (level == 0)
    {
      if (t[0].data == NULL)
	printf ("L  ");
      else
	printf ("%d  ", t[0].data[0]);
    }
  else
    {
      print_nodes_at_level_aux (t[0].left_subtree_pointer, (level - 1));
      print_nodes_at_level_aux (t[0].right_subtree_pointer, (level - 1));
    }
}

void print_nodes_at_level (tree_wrapper* t, int level)
{
  /* for invalid levels */

  if (level > (compute_height (t[0].current_tree) - 2) || level < 0 )
    {
      printf ("The level you have enetred is invalid \n");
      return;
    }
  else
    {
      print_nodes_at_level_aux (t[0].current_tree, level);
      printf ("\n ");
    }
}

/* ******** ******** */

/* ******** generate_random_tree () ******** */



tree_wrapper* generate_random_tree (int size)
{
  /* declarations */
  tree_wrapper* new_tree_wrapper;
  int* node_array;
  int i;

  /* create pointer to new tree wrapper */
  new_tree_wrapper = create_new_tree ();

  /* allocate memory to a node array */
  node_array = (int*) malloc (sizeof (int) * size);

  /* generate random value to store in the array */
  srand (time (NULL));
  for (i=0 ; i<size ; i++)
    node_array[i] = (rand () % 1000);

  /* sort the array */
  bubble_sort_array (node_array, size);

  /* construct the tree using array_to_tree */
  new_tree_wrapper[0].current_tree = create_new_tree_aux ();
  new_tree_wrapper[0].current_tree =
    array_to_tree (node_array, 0, (size - 1), new_tree_wrapper[0].current_tree);

  /* finally, return the newly constructed tree */
  return (new_tree_wrapper);


  free (node_array);
}

/* ******** ******** */

/* ******** generate_from_array () ******** */

tree_wrapper* generate_from_array (int* array, int size)
{
  /* we simply use the array_to_tree function */
  tree_wrapper* new_tree_wrapper;

  bubble_sort_array (array, size);
  new_tree_wrapper = create_new_tree ();
  new_tree_wrapper[0].current_tree = create_new_tree_aux ();
  new_tree_wrapper[0].current_tree =
    array_to_tree (array, 0, (size - 1), new_tree_wrapper[0].current_tree);

  /* return the pointer */
  return (new_tree_wrapper);
}

/* ******** ******** */



/* ******** unit testing ******** */

void test_functions()
{
  /* declarations */
  int temp;
  int int_input;
  tree_wrapper* new_tree;
  int val_input;
  int new_input_val;
  int temp2;
  int node_array_size, i;
  int* node_array;

  temp = 1;
  new_tree = create_new_tree ();
  
  while (temp)
    {
	
      printf ("\n \n UNIT TESTING \n \n");
      printf (" Enter the integer coresponding to your choice: \n (1) Create a new tree \n (2) Balance the tree \n (3) Add a node to the tree \n (4) Edit a node \n (5) Remove a node \n (6) Find shortest distance between two nodes \n (7) Find the depth of a given node \n (8) Print the nodes at a given level \n (9) Print the tree \n (10) Delete the tree \n (11) Generate a random BST \n (12) Generate a balanced tree from a given array \n (13) Exit \n \n");
      printf (" \n \n");
	  
      if (scanf ("%d" , &int_input) == 0)
	{
	  while (fgetc(stdin) != '\n');
	  printf ("The input choice was incorrect. Please try again. \n \n");
	  continue;
	}
      /* switch case statement to call desired function */
      switch (int_input)
	{
	case 1:
	  /* delete old tree */
	  delete_tree (new_tree);
	  printf ("Creating new tree ...\n");
	  new_tree = create_new_tree ();
	  printf ("New tree created. \n \n");
	  break;

	case 2:
	  printf ("Balancing tree ... \n");
	  balance_tree (new_tree);
	  printf (" Tree is balanced. \n \n");
	  break;

	case 3:
	  printf ("Enter input value: ");
	  scanf ("%d", &val_input);
	  printf (" \n Adding value to tree...\n");
	  temp2 = add_node (new_tree , val_input);
	  if (temp2 == 0)
	    printf (" New node created. \n \n");
	  else
	    printf (" This value already exists in the tree \n \n");
	  break;
	      
	case 4:
	  printf ("Enter value of node to be changed: \n");
	  scanf ("%d", &val_input);
	  printf ("Enter new value: \n");
	  scanf ("%d", &new_input_val);
	  printf ("Attempting to modify node...\n");
	  switch (edit_node (new_tree, val_input, new_input_val))
	    {
	    case 0:
	      printf ("The edit was succesful \n \n");
	      break;
	    case (-1):
	      printf ("The given node could not be found \n \n");
	      break;
	    case (-2):
	      printf (" The node was added but the tree had to be rebalanced \n \n");
	      break;
	    }
	  break;
	      
	case 5:
	  printf ("Enter value of node to be removed \n \n");
	  scanf ("%d", &val_input);
	  if (remove_node (new_tree, val_input) == 0)
	    printf ("Removal was succesful \n \n");
	  else
	    printf ("The node you entered could not be found \n \n");
	  break;

	case 6:
	  printf ("Enter the first node: \n");
	  scanf ("%d", &val_input);
	  printf ("Enter the second node: \n");
	  scanf ("%d", &new_input_val);
	  if (shortest_distance (new_tree, val_input, new_input_val) == -1)
	    printf ("One of the nodes does not exist \n \n");
	  else
	    printf ("The shortest distance is: %d \n \n",
		    shortest_distance (new_tree, val_input, new_input_val));
	  break; 

	case 7:
	  printf ("Enter the node whose depth you wish to find: \n");
	  scanf ("%d", &val_input);
	  if (find_depth (new_tree, val_input) == -1)
	    printf ("The node does not exist \n \n");
	  else
	    printf ("The depth of the node is : %d \n \n",
		    find_depth (new_tree, val_input));
	  break; 
	      
	case 8:
	  printf ("Enter the level : \n");
	  scanf ("%d" , &val_input);
	  print_nodes_at_level (new_tree, val_input);
	  break; 

	case 9:
	  print_tree (new_tree);
	  break;

	case 10:
	  printf ("Deleting tree... \n");
	  delete_tree (new_tree);
	  printf ("Tree deleted. \n \n");
	  break;

	case 11:
	  if (new_tree != NULL)
	    delete_tree (new_tree);
	  printf ("Enter size of the random BST : \n");
	  scanf ("%d" , &val_input);
	  printf ("Constructing the new tree \n");
	  new_tree = generate_random_tree (val_input);
	  printf ("The new tree is as constructed \n");
	  break;

	case 12:
	  /* ask for the array size */
	  printf ("Enter the size of the array you wish to upload \n");
	  scanf ("%d" , &node_array_size);

	  /* allocate memory to the node array */
	  node_array = (int*) malloc (sizeof (int) * node_array_size);

	  /* loop through the input size and ask the user for the values */
	  printf ("You will now be prompted to enter the array values \n");
	  for (i=0 ; i< node_array_size ; i++)
	    {
	      printf ("Enter the value # %d \n", (i+1));
	      scanf ("%d", &node_array[i]);
	    }

	  if (check_repetitions (node_array, node_array_size))
	      printf ("There are repetitions in your array. Please try again \n");
	  else
	    {
	      printf ("Constructing the BST...\n");
	      if (new_tree != NULL)
		delete_tree (new_tree);
	      new_tree = generate_from_array (node_array, node_array_size);
	      printf ("The construction of the tree is complete \n");
	    }
	  free (node_array);
	  break;
	case 13:
	  if (new_tree != NULL)
	    delete_tree (new_tree);
	  printf ("Exiting the testing... \n \n");
	  temp = 0;
	  break;
	default:
	  if (new_tree != NULL)
	    delete_tree (new_tree);
	  printf ("Exiting the testing... \n \n");
	  temp = 0;
	}
    }
}









/* ******** main () ******** */

int main (void)
{

  test_functions ();
  
  return (0);
}

