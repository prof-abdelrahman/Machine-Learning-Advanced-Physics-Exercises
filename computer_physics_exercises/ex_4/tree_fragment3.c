#include <stdio.h>
#include <stdlib.h>
# include <time.h>
/* data structures for tree elements */
struct node_struct
{
    int                  info;                  /* holds ``information'' */
    struct node_struct  *left;  /* points to left subtree (NULL if none) */
    struct node_struct *right;  /* points to left subtree (NULL if none) */
};

typedef struct node_struct node_t;       /* define new type for nodes */

/* function commentary header (empty): */

/*******************  *****************/
/**  **/
/** PARAMETERS: (*)= return-paramter         **/
/**  **/
/** RETURNS:                               **/
/**  **/
/******************************************/


/* function commentary header (empty): */

/******************* create_node() ********************/
/** Creates an tree node and initializes info        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        value: of info                            **/
/** RETURNS:                                         **/
/**     pointer to new node                          **/
/******************************************************/
node_t *create_node(int value)
{
  node_t *node;

  node = (node_t *) malloc (sizeof(node_t));
  node->info = value;
  node->right = NULL;
  node->left = NULL;
  return(node);
}

/********************* delete_node() ******************/
/** Deletes a single tree node (i.e. only if it      **/
/** is not linked to other nodes)                    **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**    0: OK, 1: error                               **/
/******************************************************/
int delete_node(node_t *node)
{
  if(node == NULL)
  {
    fprintf(stderr, "attempt to delete `nothing`\n");
    return(1);
  }
  else if( (node->left != NULL)||(node->right != NULL))
  {
    fprintf(stderr, "attempt to delete linked node!\n");
    return(1);
  }
  else
  {
    free(node);
    return(0);
  }
}

/********************* insert_node() ******************/
/** Inserts 'node' into the 'tree' such that the     **/
/** increasing order is preserved                    **/
/** if node exists already, nothing happens          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**   (new) pointer to root of tree                  **/
/******************************************************/
node_t *insert_node(node_t *tree, node_t *node)
{
  node_t *current;

  if(tree==NULL)
    return(node);
  current = tree;
  while( current != NULL)                  /* run through tree */
  {
    if(current->info==node->info)  /* node already contained ? */
      return(tree);
    if( node->info < current->info)            /* left subtree */  
    {
      if(current->left == NULL)
      {             
	current->left = node;                      /* add node */
	return(tree);
      }
      else
	current = current->left;         /* continue searching */
    }
    else                                      /* right subtree */
    {
      if(current->right == NULL)             
      {
	current->right = node;                     /* add node */
	return(tree);
      }
      else
	current = current->right;         /* continue searching */
    }
  }
  return(tree);
}

/********************* print_tree() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree(node_t *tree)
{
  if(tree != NULL)
  {
    print_tree(tree->left);
    printf("%d ", tree->info);
    print_tree(tree->right);
  }
}

/************** print_tree_indent() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree_indent(node_t *tree, int level)
{
  int t;
  if(tree != NULL)
  {
    print_tree_indent(tree->left, level+1);
    for(t=0; t<level; t++)
      printf("  ");
    printf("%d\n", tree->info);
    print_tree_indent(tree->right, level+1);
  }
}
/********************* count_leaves() *****************/
/** Caluclates number of leaves recursively.         **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   number of leaves                               **/
/******************************************************/
int count_leaves(node_t *tree)
{
  if(tree == NULL)
    return(0);                  /* empty tree -> no leaves */
  if( (tree->left == NULL)&&(tree->right == NULL) )
    return(1);                  /* single node -> one leaf */
  return( count_leaves(tree->left) + count_leaves(tree->right) );
  // printf("TO BE COMPLETED\n");
  // return(0);
}

/*count number of nodes */
int count_nodes(node_t *tree)
{
  if(tree == NULL)
    return(0);                  /* empty tree -> no leaves */
  
  
  return(1 + count_nodes(tree->left) + count_nodes(tree->right));
}/* Therfore the difference will be to make 1+ and count every node without caring to count only if it has no successor*/

/******************** remove_value() ******************/
/** Removes node containung the 'value' from  the    **/
/** tree.                                            **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         value: to be removed                     **/
/**    (*) node_p: address of ptr to removed node    **/
/** RETURNS:                                         **/
/** (new) pointer to the root                        **/
/******************************************************/

node_t *remove_value(node_t *tree, int value, node_t **node_p)
{
  if (tree == NULL) {
    return NULL;  // Empty tree, nothing to remove
  }

  if (value < tree->info) {
    tree->left = remove_value(tree->left, value, node_p);  // Recursively remove from the left subtree
  } else if (value > tree->info) {
    tree->right = remove_value(tree->right, value, node_p);  // Recursively remove from the right subtree
  } else {
    // Found the node to remove
    *node_p = tree;  // Set the address of the removed node

    // Case 1: No child or only one child
    if (tree->left == NULL) {
      node_t *temp = tree->right;
      free(tree);
      return temp;
    } else if (tree->right == NULL) {
      node_t *temp = tree->left;
      free(tree);
      return temp;
    }

    // Case 2: Two children
    node_t *successor = NULL;  // Initialize successor as NULL
    if (tree->right != NULL) {
      node_t *find_min(node_t *tree);  // Function prototype for find_min

      // ...

      successor = find_min(tree->right);  // Find the minimum value in the right subtree
    }
    tree->info = successor->info;  // Replace the value of the node with the successor
    tree->right = remove_value(tree->right, successor->info, node_p);  // Recursively remove the successor from the right subtree
  }

  return tree;
}

/* implementaion of find_min*/
node_t *find_min(node_t *tree)
{
  while (tree->left != NULL) {
    tree = tree->left;
  }
  return tree;
}

/* a complete function (no frame is provided now!) which estimates the number of leaves
of a tree by a random algorithm (Knuth’s algorithm):

algorithm knuth(tree)
begin
b := 1
while tree has successor do
if tree has one successorr then
tree := tree − > succesort (left or right)
else
begin
b := 2 ∗ b
tree := left/right successor with same probability
end
return (b)
end
*/
double knuth(node_t *tree)
{
  double b = 1.0;
  while (tree != NULL) {
    if (tree->left != NULL && tree->right != NULL) { // tree has two successors
      b *= 2.0;
      if (rand() % 2 == 0) {                        // Randomly choose left or right successor
        tree = tree->left;
      } else {
        tree = tree->right;
      }
    } else if (tree->left != NULL) {              // tree has one successor
      tree = tree->left;
    } else if (tree->right != NULL) {            // tree has one successor    
      tree = tree->right;
    } else {                                    // tree has no successor
      tree = NULL;
    }
  }
  return b;
}

// int random_number(int min_num, int max_num)
//     {
//         int result = 0, low_num = 0, hi_num = 0;

//         if (min_num < max_num)
//         {
//             low_num = min_num;
//             hi_num = max_num + 1; // include max_num in output
//         } else {
//             low_num = max_num + 1; // include max_num in output
//             hi_num = min_num;
//         }

//         srand(time(NULL));
//         result = (rand() % (hi_num - low_num)) + low_num;
//         return result;
//     }



int main(int argc, char *argv[])
{
  node_t *tree, *node;
  int value;
  
  // tree = NULL;
  /* Basic Tree done by the prof */
  // node = create_node(20);
  // tree = insert_node(tree, node);
  // node = create_node(10);
  // tree = insert_node(tree, node);
  // node = create_node(30);
  // tree = insert_node(tree, node);
  // node = create_node(5);
  // tree = insert_node(tree, node);
  // node = create_node(15);
  // tree = insert_node(tree, node);
  // node = create_node(25);
  // tree = insert_node(tree, node);
  // node = create_node(35);
  // tree = insert_node(tree, node);
  // node = create_node(3);
  // tree = insert_node(tree, node);
  // node = create_node(12);
  // tree = insert_node(tree, node);
  // node = create_node(27);
  // tree = insert_node(tree, node);
  // node = create_node(40);
  // tree = insert_node(tree, node);
  // node = create_node(40);
  // tree = insert_node(tree, node);

  /* Tree with n number of nodes */
  // a tree with n nodes randomly

  // Use current time as 
  // seed for random generator 

  // srand(time(0));

  // int n = rand() % (41 + 1 - 31) + 31; // Random number of nodes between 30 and 40
  // // printf("n: %d\n", n);
  // tree = NULL;
  // for (int i = 0; i < n; i++) {
  //   node = create_node(drand48() * 1000);
  //   tree = insert_node(tree, node);
  // }

  // /* print the tree */
  // // printf("tree: ");
  // // print_tree(tree); printf("\n");
  // // print_tree_indent(tree,0); printf("\n");

  // /* print number of leaves */
  // double no_leaves = (double) count_leaves(tree);
  // // printf("%d leaves\n", count_leaves(tree));
  // // printf("%f",no_leaves);

  // /* print number of nodes */
  // // printf("%d nodes\n", count_nodes(tree));

  // /* One can show (easily by recursion): the expectation value hbi is equal to the number of leaves. */
  // /* iterate until the 10**7 and stop before if the no of leaves == Knuth */
  // int i = 1;
  // double avg = 0; // average number of knuth leaves
  // double knuth_leaves = 0;
  // double sum_knuth = 0;
  // FILE *f = fopen("avg.txt", "w");
  // if (f == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }

  // FILE *f2 = fopen("no_of_leaves.txt", "w");
  //   if (f2 == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }
  // while (i < (10000000+1)) {
  //   knuth_leaves = knuth(tree);
  //   sum_knuth += knuth_leaves;
  //   avg = sum_knuth/i;
    
  //   f = fopen("avg.txt", "a");
  //   f2 = fopen("no_of_leaves.txt", "a");
  //   fprintf(f, "%d %f\n", i, avg);
  //   fprintf(f2, "%d %f\n", i, no_leaves);
  //   // avg += knuth_leaves/i;
  //   // if (count_leaves(tree) == avg){
  //   //   printf("Average number of Knuth: %f\n", knuth(tree));
  //   //   printf("Average number of knuth is equal to the real number of leaves in: %d iterations\n", i);
  //   //   break;
  //   // }
  //   // else if (count_leaves(tree) == knuth_leaves) {
  //   //   printf("Knuth: %f\n", knuth(tree));
  //   //   printf("Knuth algorithm value is equal to the real number of leaves in: %d iterations\n", i);
  //   //   break;
  //   // }
  //   // printf("Knuth: %f, ", knuth_leaves);
  //   // printf("Average number of knuth: %f\n", avg);
  //   // printf("\n");
  //   i++;
  //   fclose(f);
  //   fclose(f2);
  // }

  // // make a file with the number of leaves 

  // /* First tree */
  // printf("First tree\n");
  // /* print number of leaves */
  // printf("%d leaves\n", count_leaves(tree));

  // /* print number of nodes */
  // printf("%d nodes\n", count_nodes(tree));

  // /* print avg */
  // printf("Average number of knuth: %f\n", avg);

  // /* A tree for which the algorithm “converges” quickly. */
  // printf("Second tree\n");
  // tree = NULL;
  // node = create_node(1);
  // tree = insert_node(tree, node);
  // node = create_node(2);
  // tree = insert_node(tree, node);
  // node = create_node(3);
  // tree = insert_node(tree, node);
  // node = create_node(4);
  // tree = insert_node(tree, node);
  // node = create_node(5);
  // tree = insert_node(tree, node);
  // node = create_node(6);
  // tree = insert_node(tree, node);
  // node = create_node(7);
  // tree = insert_node(tree, node);
  // node = create_node(8);
  // tree = insert_node(tree, node);
  // node = create_node(9);
  // tree = insert_node(tree, node);
  // node = create_node(10);
  // tree = insert_node(tree, node);

  // /* One can show (easily by recursion): the expectation value hbi is equal to the number of leaves. */
  // /* iterate until the 10**7 and stop before if the no of leaves == Knuth */
  // int i = 1;
  // double avg = 0; // average number of knuth leaves
  // double knuth_leaves = 0;
  // double sum_knuth = 0;
  // double no_leaves = (double) count_leaves(tree);
  // FILE *f = fopen("avg2.txt", "w");
  // if (f == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }

  // FILE *f2 = fopen("no_of_leaves2.txt", "w");
  //   if (f2 == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }
  // while (i < (10000000+1)) {
  //   knuth_leaves = knuth(tree);
  //   sum_knuth += knuth_leaves;
  //   avg = sum_knuth/i;
    
  //   f = fopen("avg2.txt", "a");
  //   f2 = fopen("no_of_leaves2.txt", "a");
  //   fprintf(f, "%d %f\n", i, avg);
  //   fprintf(f2, "%d %f\n", i, no_leaves);
  //   i++;
  //   fclose(f);
  //   fclose(f2);
  // }

  // /* A tree for which the algorithm “converges” quickly. */
  // printf("Third tree\n");
  // tree = NULL;
  // node = create_node(40);
  // tree = insert_node(tree, node);
  // node = create_node(20);
  // tree = insert_node(tree, node);
  // node = create_node(60);
  // tree = insert_node(tree, node);
  // node = create_node(10);
  // tree = insert_node(tree, node);
  // node = create_node(30);
  // tree = insert_node(tree, node);
  // node = create_node(50);
  // tree = insert_node(tree, node);
  // node = create_node(70);
  // tree = insert_node(tree, node);
  // node = create_node(5);
  // tree = insert_node(tree, node);
  // node = create_node(15);
  // tree = insert_node(tree, node);
  // node = create_node(27);
  // tree = insert_node(tree, node);

  // /* One can show (easily by recursion): the expectation value hbi is equal to the number of leaves. */
  // /* iterate until the 10**7 and stop before if the no of leaves == Knuth */
  // i = 1;
  // avg = 0; // average number of knuth leaves
  // knuth_leaves = 0;
  // sum_knuth = 0;
  // no_leaves = (double) count_leaves(tree);
  // FILE *f3 = fopen("avg3.txt", "w");
  // if (f == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }

  // FILE *f4 = fopen("no_of_leaves3.txt", "w");
  //   if (f2 == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }
  // while (i < (10000000+1)) {
  //   knuth_leaves = knuth(tree);
  //   sum_knuth += knuth_leaves;
  //   avg = sum_knuth/i;
    
  //   f3 = fopen("avg3.txt", "a");
  //   f4 = fopen("no_of_leaves3.txt", "a");
  //   fprintf(f3, "%d %f\n", i, avg);
  //   fprintf(f4, "%d %f\n", i, no_leaves);
  //   i++;
  //   fclose(f3);
  //   fclose(f4);
  // }

  /* A tree for which the algorithm “converges” slowly. */
  // printf("Hardest tree\n");
  // tree = NULL;
  // node = create_node(20);
  // tree = insert_node(tree, node);
  // node = create_node(10);
  // tree = insert_node(tree, node);
  // node = create_node(30);
  // tree = insert_node(tree, node);
  // node = create_node(25);
  // tree = insert_node(tree, node);
  // node = create_node(35);
  // tree = insert_node(tree, node);
  // node = create_node(18);
  // tree = insert_node(tree, node);
  // node = create_node(80);
  // tree = insert_node(tree, node);
  // node = create_node(69);
  // tree = insert_node(tree, node);
  // node = create_node(10);
  // tree = insert_node(tree, node);
  // node = create_node(48);
  // tree = insert_node(tree, node);
  // node = create_node(47);
  // tree = insert_node(tree, node);
  // node = create_node(46);
  // tree = insert_node(tree, node);
  // node = create_node(45);
  // tree = insert_node(tree, node);

  // /* One can show (easily by recursion): the expectation value hbi is equal to the number of leaves. */
  // /* iterate until the 10**7 and stop before if the no of leaves == Knuth */
  // int i = 1;
  // double avg = 0; // average number of knuth leaves
  // double knuth_leaves = 0;
  // double sum_knuth = 0;
  // double no_leaves = (double) count_leaves(tree);
  // FILE *f5 = fopen("avg4.txt", "w");
  // if (f5 == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }

  // FILE *f6 = fopen("no_of_leaves4.txt", "w");
  //   if (f6 == NULL)
  // {
  //   printf("Error opening file!\n");
  //   return 1;
  // }
  // while (i < (10000000+1)) {
  //   knuth_leaves = knuth(tree);
  //   sum_knuth += knuth_leaves;
  //   avg = sum_knuth/i;
    
  //   f5 = fopen("avg4.txt", "a");
  //   f6 = fopen("no_of_leaves4.txt", "a");
  //   fprintf(f5, "%d %f\n", i, avg);
  //   fprintf(f6, "%d %f\n", i, no_leaves);
  //   i++;
  //   fclose(f5);
  //   fclose(f6);
  // }
  
  



  


  // value = 25;
  // printf("rem: %d\n", value);
  // tree = remove_value(tree, value, &node);
  // print_tree(tree); printf("\n");
  // // print_tree_indent(tree,0); printf("\n");

  // value = 20;
  // printf("rem: %d\n", value);
  // tree = remove_value(tree, value, &node);
  // print_tree(tree); printf("\n");
  // print_tree_indent(tree,0); printf("\n");

  // value = 10;
  // printf("remove node: %d\n", value);
  // tree = remove_value(tree, value, &node);      /* remove 10 */

  // /* print the tree */
  // printf("tree: ");
  // print_tree(tree); printf("\n");

  return(0);
}
