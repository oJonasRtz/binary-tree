#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_ast
{
	char			*cmd;

	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*ast_create(char *args)
{
	t_ast	*new;

	if (!args)
		return (NULL);
	new = calloc(1, sizeof(t_ast));
	if (!new)
		return (NULL);
	new->cmd = args;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int	is_operator(char *str)
{
	return (strcmp(str, "|") == 0 || strcmp(str, ">") == 0 || strcmp(str, "<") == 0);
}

t_ast	*ast_add(t_ast *root, char *args)
{
	if (!root)
		return (ast_create(args));
	if (strcmp(root->cmd, "|") == 0)
	{
		if (!root->left)
			root->left = ast_add(root->left, args);
		else
			root->right = ast_add(root->right, args);
	}
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
	printf("%s \n", root->cmd);
	ast_print(root->right, level + 1);
}

int	main(void)
{
	t_ast	*new;

	new = ast_create("|");
	new = ast_add(new, "ls -l");
	new = ast_add(new, "|");
	new = ast_add(new, "grep Makefile");
	new = ast_add(new, "wc -w");
	ast_print(new, 0);
	ast_free(new);
	return (0);
}
