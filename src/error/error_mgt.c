/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:19:36 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/09 08:31:18 by dwianni          ###   ########.fr       */
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

/******************************************************************************
ecrit une string dans la sortie d'erreur
******************************************************************************/
void	ft_perror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}