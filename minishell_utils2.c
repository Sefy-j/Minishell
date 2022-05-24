/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:48:27 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/24 19:26:20 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long int	ft_atouli(char const *str)
{
	unsigned long long int	ans;
	int						sign;
	int						flag;

	ans = 0;
	sign = 1;
	flag = 0;
	if (ft_strncmp("-9223372036854775808", str, 30) == 0)
		exit(0);
	if (*str == 45)
	{
		sign = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	if (ans > 9223372036854775807 && sign < 0)
		flag = 1;
	else if (ans > 9223372036854775807 && sign > 0)
		flag = 1;
	if (flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	return ((long long int)(ans * sign));
}

int	atoexit(char const *str)
{
	unsigned long long int	nbr;

	if (ft_strlen(str) == 20 && str[0] != '-')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	nbr = ft_atouli(str);
	if (nbr >= 0)
		return (nbr % 256);
	else
	{
		while (nbr < 0)
			nbr += 256;
		return (nbr);
	}
}
