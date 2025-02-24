/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:32:53 by dwianni           #+#    #+#             */
/*   Updated: 2024/12/02 11:15:34 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_not_in_type(char c)
{
	write (1, &"%", 1);
	write (1, &c, 1);
	return (2);
}

static int	ft_printf_type(va_list ap, char c)
{
	if (c == '%')
		return (write(1, &"%", 1));
	if (c == 'c')
		return (ft_printf_c(va_arg(ap, int)));
	else if (c == 's')
		return (ft_printf_s(va_arg(ap, char *)));
	else if (c == 'x')
		return (ft_printf_x(va_arg(ap, unsigned int)));
	else if (c == 'X')
		return (ft_printf_ux(va_arg(ap, unsigned int)));
	else if (c == 'p')
		return (ft_printf_p(va_arg(ap, unsigned long)));
	else if (c == 'd')
		return (ft_printf_d(va_arg(ap, int)));
	else if (c == 'i')
		return (ft_printf_d(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_printf_u(va_arg(ap, unsigned int)));
	else
		return (ft_print_not_in_type(c));
	return (-1);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (input == NULL)
		return (-1);
	va_start(ap, input);
	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != '%')
			count = count + write (1, &input[i], 1);
		else
		{
			count = count + ft_printf_type (ap, input[i + 1]);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
