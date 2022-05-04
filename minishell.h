/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:09:47 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/04 15:02:34 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct	s_data {
	char			**cmds;
	char			**files;
	char			*dir;
	struct s_data	*next;
}				t_data;

enum {
	LEFT = 49,
	RIGHT = 50,
	LEFTLEFT = 51,
	RIGHTRIGHT = 52
};

char	**ft_free(char **result);
char	*check_those_quotes(char *read);
t_data	*parse_machine(char **cmds);
char	**ft_split_cmds(char const *s1, char c);

#endif
