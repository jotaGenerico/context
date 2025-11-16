#include "minishell.h"

static int	count_non_empty(char **argv);
static void	copy_non_empty(char **argv, char **new_argv);

char	**remove_empty_args(char **argv)
{
	char	**new_argv;
	int		count;

	if (!argv)
		return (NULL);
	count = count_non_empty(argv);
	if (count == 0)
		return (argv);
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return (NULL);
	copy_non_empty(argv, new_argv);
	free(argv);
	return (new_argv);
}

static int	count_non_empty(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	copy_non_empty(char **argv, char **new_argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			new_argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	new_argv[j] = NULL;
}
