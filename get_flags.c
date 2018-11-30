/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:47:33 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/19 11:52:44 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void	initiate_flags(t_flags **flags)
{
	if (*flags)
		free(*flags);
	*flags = (t_flags*)malloc(sizeof(t_flags));
	(*flags)->minus = 0;
	(*flags)->plus = 0;
	(*flags)->space = 0;
	(*flags)->zero = 0;
	(*flags)->hash = 0;
	(*flags)->star_width = 0;
	(*flags)->width = 0;
	(*flags)->star_prec = 0;
	(*flags)->prec = -1;
	(*flags)->ll = 0;
	(*flags)->l = 0;
	(*flags)->hh = 0;
	(*flags)->h = 0;
	(*flags)->L = 0;
	(*flags)->type = -1; 
}

void		get_flags(const char **fmt, t_flags *flags)
{
	set_flag(fmt, flags);
	set_width_and_prec(fmt, flags);
	set_len(fmt, flags);
	flags->type = ft_strindex("cspdiouxXfb%", **fmt);
	if (flags->type != -1)
		(*fmt)++;
}

inline void	set_flag(const char **fmt, t_flags *flags)
{
	while (**fmt && ft_strchr("- #0+", **fmt))
	{
		SET_IF((**fmt == '-'), flags->minus);
		SET_IF((**fmt == '+'), flags->plus);
		SET_IF((**fmt == ' '), flags->space);
		SET_IF((**fmt == '#'), flags->hash);
		SET_IF((**fmt == '0'), flags->zero);
		(*fmt)++;
	}
}

inline void	set_width_and_prec(const char **fmt, t_flags *flags)
{
	flags->width = ft_atoi(*fmt);
	while (**fmt && ft_isdigit(**fmt))
		(*fmt)++;
	if (**fmt == '*')
		flags->star_width = *((*fmt)++);
	if (**fmt == '.')
	{
		(*fmt)++;
		if (**fmt == '*')
			flags->star_prec = *((*fmt)++);
		else
			flags->prec = ft_atoi(*fmt);
		while (**fmt && ft_isdigit(**fmt))
			(*fmt)++;
	}
}

inline void	set_len(const char **fmt, t_flags *flags)
{
	if (**fmt == 'l')
	{
		(*fmt)++;
		if (**fmt == 'l')
			flags->ll = 1;
		else
			flags->l = 1;
		(*fmt) += (flags->ll) ? 1 : 0;
	}
	else if (**fmt == 'h')
	{
		(*fmt)++;
		if (**fmt == 'h')
			flags->hh = 1;
		else
			flags->h = 1;
		(*fmt) += (flags->hh) ? 1 : 0;
	}
	else if (**fmt == 'L')
	{
		flags->L = 1;
		(*fmt)++;
	}
}

#include <stdio.h>
void	print_flags(t_flags *flags)
{
	char	*types;

	types = ft_strdup("cspdiouxXfb%");
	ft_putstr("flags: ");
	(flags->minus) ? ft_putchar('-') : 0;
	(flags->plus) ? ft_putchar('+') : 0;
	(flags->space) ? ft_putstr("space") : 0;
	(flags->zero) ? ft_putchar('0') : 0;
	(flags->hash) ? ft_putchar('#') : 0;
	ft_putstr("\nwidth: ");
	(flags->star_width) ? ft_putstr("* width") : 0;
	(flags->width) ? ft_putnbr(flags->width) : 0;
	ft_putstr("\nprecision: ");
	(flags->star_prec) ? ft_putstr("* prec") : 0;
	(flags->prec) ? ft_putnbr(flags->prec) : 0;
	ft_putstr("\nlength: ");
	(flags->ll) ? ft_putstr("ll") : 0;
	(flags->l) ? ft_putstr("l") : 0;
	(flags->hh) ? ft_putstr("hh") : 0;
	(flags->h) ? ft_putstr("h") : 0;
	(flags->L) ? ft_putstr("L") : 0;
	ft_putstr("\ntype: ");
	(flags->type) != -1 ? ft_putchar(types[flags->type]) : 0;
	write(1, "\n", 1);
	free(types);
}