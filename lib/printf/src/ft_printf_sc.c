/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:32:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/01/11 15:00:02 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s(char *str)
{
	if (str == NULL)
		return (write(1, &"(null)", 6));
	return (write(1, str, ft_strlenpf(str)));
}

int	ft_printf_c(int c)
{
	return (write(1, &c, 1));
}
