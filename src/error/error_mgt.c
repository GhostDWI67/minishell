/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:19:36 by dwianni           #+#    #+#             */
/*   Updated: 2025/07/03 15:07:15 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Print a message (parameter) and 
Return an int = error number
******************************************************************************/
int	msg_error(char *err_msg, int err_nb)
{
	perror(err_msg);
	return (err_nb);
}

/******************************************************************************
Print a message (parameter) and 
Return an int = error number
******************************************************************************/
int	msg_inf(char *err_msg, int err_nb)
{
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	return (err_nb);
}

void	ft_perror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}

void	mod_error(char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
}
