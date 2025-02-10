#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_rbtree
{
	int		value;
	char	colour;

	struct s_rbtree	*left;
	struct s_rbtree	*right;
	struct s_rbtree	*parent;
}	t_rbtree;

t_rbtree	*g_null_leaf = NULL;

void	init_leaf(void){
	if (!g_null_leaf){
		g_null_leaf = calloc(1, sizeof(t_rbtree));
		if (!g_null_leaf)
			return ;
		g_null_leaf->value = INT_MIN;
		g_null_leaf->colour = 'b';
		g_null_leaf->parent = NULL;
		g_null_leaf->left = NULL;
		g_null_leaf->right = NULL;
	}
}

static void	set_null(t_rbtree *root){
	root->left = g_null_leaf;
	root->right = g_null_leaf;
}

static void	balance(t_rbtree *root){
	if (!root->parent){
		root->colour = 'b';
		set_null(root);
		return ;
	}
	if (root->parent->colour == 'r')
		root->parent->colour = 'b';
	root->colour = 'r';
	set_null(root);
}

/*
	Create a new node
		but different from a normal binary tree whe balance it
*/
static t_rbtree	*new_node(int value, t_rbtree *parent){
	t_rbtree	*new;

	new = calloc(1, sizeof(t_rbtree));
	if (!new)
		return (NULL);
	new->value = value;
	new->parent = parent;
	balance(new);
	return (new);
}

/*
	Add a new branch to the tree

	if the value is less then the current value it goes to the left
		like a normal binary tree
*/
static t_rbtree	*add_node(t_rbtree *root, int value, t_rbtree *parent){
	if (!root || root == g_null_leaf)
		return (new_node(value, parent));
	if (value < root->value)
		root->left = add_node(root->left, value, root);
	else
		root->right = add_node(root->right, value, root);
	return (root);
}

/*
	Prints at the format:
			13
		12
			11
	10
		9
				8
			7
				6			
*/
static void print_tree(t_rbtree *root, int level){
    if (!root || root == g_null_leaf)
        return ;
	print_tree(root->left, level + 1);
	for (int i = 0; i < level; i++)
		printf("     ");
	printf("%d\n", root->value);
	print_tree(root->right, level + 1);
}

/*
	Prints the sequence of the values

	0 1 2 3 4 5
*/
static void	print_sequence(t_rbtree *root){
	if (!root || root == g_null_leaf)
		return ;
	print_sequence(root->left);
	printf("%d (%s)  ", root->value, root->colour == 'b' ? "Black" : "Red");
	print_sequence(root->right);
}

static int	error_message(char *message, int error_code){
	printf("%s\n", message);
	return (error_code);
}

/*
	free the node to prevent leak
*/
static void	destroy_node(t_rbtree *root){
	if (!root || root == g_null_leaf)
		return ;
	destroy_node(root->left);
	destroy_node(root->right);
	free(root);
}

/*
	free the leaf to prevent leak
*/
static void	destroy_leaf(void){
	free(g_null_leaf);
}

int	main(int argc, char **argv){
	t_rbtree	*node;
	int			i;

	if (argc < 2)
		return (error_message("Too few arguments.", 1));
	init_leaf();
	node = new_node(atoi(argv[1]), NULL);
	i = 2;
	while (argv[i])
		node = add_node(node, atoi(argv[i++]), NULL);
	print_tree(node, 0);
	printf("\n");
	print_sequence(node);
	printf("\n");
	destroy_node(node);
	destroy_leaf();
	return (0);
}
