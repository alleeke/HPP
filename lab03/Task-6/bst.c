#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tree_node
{
   int              ID;
   char             *name;
   struct tree_node *left;
   struct tree_node *right;
} node_t;


void print_bst(node_t *node)
{
   if(node == NULL) {printf("Tree is empty!\n"); return;}

   if (node != NULL) printf("%d %s: \t", node->ID, node->name);
   if (node->left != NULL) printf("L%d,", node->left->ID);
   if (node->right != NULL) printf("R%d", node->right->ID);
   printf("\n");

   if (node->left != NULL)
      print_bst(node->left);
   if (node->right != NULL)
      print_bst(node->right);
}


void delete_tree(node_t **node)
{
/* 
Implement a function delete tree which recursively deletes all the nodes in the
tree.
Hint. The empty tree is represented by a NULL pointer. After deleting the tree, we
should set the root pointer to NULL inside the delete tree function. In general,
it is a good practice to set a pointer to NULL after calling function free. Since we
want the delete tree function to be able to modify the pointer, the function has
as an input parameter of type node t** (a pointer to a pointer to a node t).

Hint. Do not forget to free memory allocated for names.
 */  

/*
TODO: 
   1. Check if the tree is already empty
   2. Recursively call the delete_tree for non NULL child nodes
   3. free name pointer  
   4. Set the current node = NULL
 */

if(*node == NULL) return; // 1
if((**node).left != NULL) delete_tree(&(**node).left); // 2
if((**node).right != NULL) delete_tree(&(**node).right); // 2
free((**node).name); // 3
*node = NULL; // 4 
}

void insert(node_t **node, int ID, char *name)
{
   /*
   Insert node in correct place.
   1. Check the first one, if the first node = NULL assign then newNode here.
   2. If !NULL check if ID is larger or smaller than node.ID. 
      a) If smaller call the insert function for left node
      b) If larger call the insert function for the right node
   We do not need to free memory for each recursion. We create a node_t not a pointer here
   */

   if(*node == NULL)
   {
      
      


      node_t* newNode;
      newNode = (node_t*)malloc(sizeof(node_t));
      (*newNode).name = strdup(name); // Allocates memore for name newNode.name --> Copies name --> return pointer to copied value of name
      

      /* 
      // Manually, the copy is not done. Loop through and assign each char?  
      newNode.name = (char*)malloc(sizeof(name)); // Allocates memore for name newNode.name
      newNode.name =  // Copy value of name to newNode
      */

      
      (*newNode).ID = ID;
      (*newNode).left = NULL;
      (*newNode).right = NULL; 


      *node = newNode; 
      
   }
   
   if(ID < (**node).ID) insert(&(**node).left, ID,name);
   if(ID > (**node).ID) insert(&(**node).right, ID,name);
}


void search(node_t *node, int ID)
{
/* 
Task 8: Implement a function search which searches the tree to find the name of a plant
with a given ID.
Example:
search(root, 168);
search(root, 467);
Output:
Plant with ID 168 has name banana
Plant with ID 467 does not exist! */

/* 
TODO:
   1. Check if ID is smaller or larger (else you found your NODE)
   2. If smaller && left node != NULL: call search with left node.
   2a. if left node == NULL --> doesn't exist
   3. If larger: && left node != NULL: call serch with right node.
   3a. if right node == NULL --> doesn't exist
 */

   if(ID < node->ID && node->left != NULL) search(node->left, ID); // 2
   else if (ID > node->ID && node->right != NULL) search(node->right, ID); // 3
   else if (node->ID == ID) printf("Plant with ID %d has name %s\n",ID,node->name); // 1 
   else printf("Plant with ID %d does not exists\n",ID);
}


int main(int argc, char const *argv[])
{
   node_t *root = NULL;  // empty tree
   printf("Inserting nodes to the binary tree.\n");

   insert(&root, 445, "sequoia");
   insert(&root, 162, "fir");
   insert(&root, 612, "baobab");
   insert(&root, 845, "spruce");
   insert(&root, 862, "rose");
   insert(&root, 168, "banana");
   insert(&root, 225, "orchid");
   insert(&root, 582, "chamomile");  

   printf("Printing nodes of the tree.\n");
   print_bst(root);


   search(root, 168);
   search(root, 467);

   printf("Deleting tree.\n");
   delete_tree(&root);

   print_bst(root);
   return 0;
}
