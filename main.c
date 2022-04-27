#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	const char *prompt = "minishell";
	char		*a;
	a = readline(prompt);
	return (0);
}
