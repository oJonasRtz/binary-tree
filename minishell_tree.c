#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_ast
{
	char			*cmd;
	int				index;

	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*ast_create(char *args, int index, t_ast *right, t_ast *left)
{
	t_ast	*new;

	if (!args)
		return (NULL);
	new = calloc(1, sizeof(t_ast));
	if (!new)
		return (NULL);
	new->cmd = args;
	new->index = index;
	new->left = left;
	new->right = right;
	return (new);
}

int	is_operator(char *str)
{
	return (strcmp(str, "|") == 0 || strcmp(str, ">") == 0 || strcmp(str, "<") == 0);
}

t_ast	*ast_add(t_ast *root, char *args, int index)
{
	if (!root)
		return (ast_create(args, index, NULL, NULL));
	if (strcmp(args, "|") == 0 && strcmp(root->cmd, "|") != 0)
	{
		if (index > root->index)
			return (ast_create(args, index, NULL, root));
		else
			return (ast_create(args, index, root, NULL));
	}
	if (index > root->index)
		root->right = ast_add(root->right, args, index);
	else
		root->left = ast_add(root->left, args, index);
	return (root);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ast_free(t_ast *root)
{
	if (!root)
		return ;
	ast_free(root->left);
	ast_free(root->right);
	free(root);
}

/*
	excluir futuramente
*/
void ast_print(t_ast *root, int level){
    if (!root)
        return ;
	ast_print(root->left, level + 1);
	for (int i = 0; i < level; i++)
		printf("     ");
	printf("%s (%d)\n", root->cmd, root->index);
	ast_print(root->right, level + 1);
}

int	main(int argc, char **argv)
{
	int		i = 0;
	t_ast	*new = NULL;

	if (argc == 1)
		return (0);
	while (argv[++i])
		new = ast_add(new, argv[i], argc - i - 1);
	ast_print(new, 0);
	ast_free(new);
	return (0);
}

	// 	|
	// 			>
	// ls		grep	text
