/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:19:36 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/21 16:01:23 by dwianni          ###   ########.fr       */
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
