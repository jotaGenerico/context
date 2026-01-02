#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_filter(char *line, char *str)
{
	int	len = strlen(str);
	int	i = 0;

	while (line[i])
	{
		int	h = 0;
		while (str[h] && line[i + h] == str[h])
			h++;
		if (h == len)
		{
			for (int j = 0; j < len; j++)
				write(1, "*", 1);
			i += len;
		}
		else
			write(1, &line[i++], 1);
	}
}

int	main(int argc, char **argv)
{
	char	buf[BUFFER_SIZE + 1];
	char	*carry;
	int		len_s, r;

	if (argc != 2 || !argv[1][0])
		return (1);
	len_s = strlen(argv[1]);
	carry = calloc(len_s, 1); // armazena o "resto" do buffer anterior
	if (!carry)
	{
		perror("Error");
		return (1);
	}
	while ((r = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		// junta o final do anterior + atual
		char *joined = malloc(strlen(carry) + r + 1);
		if (!joined)
			return (free(carry), perror("Error"), 1);
		strcpy(joined, carry);
		strcat(joined, buf);

		// deixa no carry apenas o possível início de match parcial
		int keep = len_s - 1;
		if ((int)strlen(joined) < keep)
			keep = strlen(joined);
		int offset = strlen(joined) - keep;

		char *process_part = strndup(joined, offset);
		ft_filter(process_part, argv[1]);
		free(process_part);
		strcpy(carry, joined + offset);
		free(joined);
	}
	if (r < 0)
		return (perror("Error"), free(carry), 1);
	// processa o que sobrou
	ft_filter(carry, argv[1]);
	free(carry);
	return (0);
}
