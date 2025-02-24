/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:58:15 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/08 10:31:02 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <bsd/string.h>
# include <ctype.h>
# include <stdint.h>
# include <stdarg.h>

int		ft_printf(const char *input, ...);
/*ft_printf_sc */
int		ft_printf_c(int c);
int		ft_printf_s(char *str);

/*ft_printf_pxux */
int		ft_printf_x(unsigned int n);
int		ft_printf_ux(unsigned int n);
int		ft_printf_p(unsigned long ad);

/*ft_printf_diu */
int		ft_printf_d(int n);
int		ft_printf_u(unsigned int n);

/* utils */
size_t	ftp_strlen(const char *s);
void	ft_putchar(char c);
void	ft_putnbr(int n);

#endif