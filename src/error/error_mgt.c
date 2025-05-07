/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:19:36 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/06 11:24:24 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Print a message (parameter) and 
Return an int = error number

A faire, integrer un free de tout
On stocke le resultat dans la structure commande ??
******************************************************************************/
int	msg_error(char *err_msg, int err_nb)
{
	perror(err_msg);
	return (err_nb);
}

/******************************************************************************
Print a message (parameter) and 
Return an int = error number

A faire, integrer un free de tout
On stocke le resultat dans la structure commande ??
******************************************************************************/
int	msg_inf(char *err_msg, int err_nb)
{
	printf("%s\n", err_msg);
	return (err_nb);
}

/******************************************************************************
ecrit une string dans la sortie d'erreur

return void;
******************************************************************************/
void	ft_perror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}