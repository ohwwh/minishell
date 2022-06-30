#include "minishell.h"

int	nflag(int i, char *argv[])
{
	static int	end;
	int			n;
	int			j;

	if (!end && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j ++] != 'n')
			{
				end = 1;
				return (0);
			}
			else
				n ++;
		}
		return (n);
	}
	return (0);
}

int	echo(int argc, char *argv[])
{
	int	i;
	int	n;
	int	isflag;

	i = 1;
	n = 0;
	while (i < argc)
	{
		isflag = nflag(i, argv);
		n += isflag;
		if (!isflag)
		{
			ft_putstr_fd(argv[i], 1);
			if (i != argc - 1)
				write(1, " ", 1);
		}
		i ++;
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}