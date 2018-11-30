/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 19:32:45 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/28 02:22:26 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_c(t_flags *flags, va_list list)
{
	char			c;
	int				spaces;

	check_stars(flags, list);
	c = va_arg(list, int);
	spaces = flags->width - 1;
	if (spaces > 0)
	{
		if (!flags->minus)
			write_padding(spaces, ' ');
		write(1, &c, 1);
		if (flags->minus)
			write_padding(spaces, ' ');
	}
	else
		write(1, &c, 1);
	return (MAX(flags->width, 1));
}

int		handle_percent(t_flags *flags, va_list list)
{
	char			c;
	int				spaces;

	check_stars(flags, list);
	c = '%'; 
	spaces = flags->width - 1;
	if (spaces > 0)
	{
		if (!flags->minus)
			write_padding(spaces, ' ');
		write(1, &c, 1);
		if (flags->minus)
			write_padding(spaces, ' ');
	}
	else
		write(1, &c, 1);
	return (MAX(flags->width, 1));	
}

int		handle_s(t_flags *flags, va_list list)
{
	char			*s;
	int				spaces;
	int				slen;

	check_stars(flags, list);
	s = va_arg(list, char *);
	if (s == 0)
		s = "(null)";
	slen = ft_strlen(s);
	if (flags->prec != -1)
		slen = (slen > flags->prec) ? flags->prec : slen;
	spaces = flags->width - slen;
	if (spaces > 0)
	{
		if (!flags->minus)
			write_padding(spaces, ' ');
		write(1, s, slen);
		if (flags->minus)
			write_padding(spaces, ' ');
	}
	else
		write(1, s, slen);
	return (MAX(flags->width, slen));
}

int		handle_p(t_flags *flags, va_list list)
{
	void			*ptr;
	char			*str;
	int				spaces;
	int				slen;

	check_stars(flags, list);
	str = NULL;
	ptr = va_arg(list, void*);
	str = ft_itoa_base_ptr((unsigned long)ptr, 16);
	slen = ft_strlen(str);
	spaces = flags->width - slen;	
	if (spaces > 0)
	{
		if (!flags->minus)
			write_padding(spaces, ' ');
		write(1, str, slen);
		if (flags->minus)
			write_padding(spaces, ' ');
	}
	else
		write(1, str, slen);
	free(str);
	return (MAX(slen, flags->width));
}

