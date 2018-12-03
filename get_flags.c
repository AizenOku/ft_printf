/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:47:33 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/03 10:03:57 by ihuang           ###   ########.fr       */
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
	(*flags)->bigl = 0;
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
		flags->bigl = 1;
		(*fmt)++;
	}
}
