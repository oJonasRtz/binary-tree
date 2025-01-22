#include <stdio.h>
#include <stdlib.h>

/*
	This struct consists of:
		-An value that the node holds(int value);
		-Two pointers, left and right pointing to the child nodes.
			To sort in correct order when adding a new value
*/
typedef struct s_btree{
	
	int             value;

	struct s_btree  *left;
	struct s_btree  *right;
}   t_btree;

/*
	Creates the first node of the tree
*/
static t_btree *new_tree(int value){
	t_btree *new;

	new = calloc(1, sizeof(t_btree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/*
	passes through the node to find the correct position of the value,
	then creates a new node at that position.
*/
static t_btree *add_node(t_btree *root, int value){
	if (!root)
		return (new_tree(value));
	if (value < root->value)
		root->left = add_node(root->left, value);
	else
		root->right = add_node(root->right, value);
	return (root);
}

/*
	Clear all memory allocations to prevent leaks
*/
static void	destroy_tree(t_btree *root){
	if (!root)
		return ;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

/*
	Prints the binary tree in ascending order
*/
static void print_tree(t_btree *root){
	if (!root)
		return ;
	print_tree(root->left);
	printf("%d ", root->value);
	print_tree(root->right);
}

static int	error_message(char *message, int error_code){
	printf("%s\n", message);
	return (error_code);
}

/*
	When you write any number in the execution of the program its added to the list

	How to use:
	
	-No args
		$ ./bin_tree
		$ Too few arguments.
	-Using args
		$ ./bin_tree 30 43 1 15
		$ 1 15 30 43 
*/
int main(int argc, char **argv){
	t_btree	*node;
	int		i;
	
	if (argc != 1){
		i = 2;
		node = new_tree(atoi(argv[1]));
		while (argv[i])
			node = add_node(node, atoi(argv[i++]));	
	}
	else
		return (error_message("Too few arguments.", 1));
	print_tree(node);
	printf("\n");
	destroy_tree(node);
	return (0);
}
