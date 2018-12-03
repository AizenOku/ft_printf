/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 10:37:06 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/02 19:41:47 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_f(t_flags *flags, va_list list)
{
	long double	nbr;
	double		frac_part;
	char		*int_str;
	char		*frac_str;
	char		prepend;

	prepend = 0;
	check_stars(flags, list);
	nbr = get_doublenbr(flags, list);
	frac_part = get_intstr_and_frac(nbr, &int_str, (nbr < 0));
	if (get_fracstr_and_carryover(frac_part, &frac_str, &int_str, flags->prec))
		increment_str(&int_str, 'i');
	get_prepend_double(&int_str, &prepend, flags);
	join_int_frac_strings(&int_str, &frac_str);
	if (is_infinity(nbr))
		return (print_weird(int_str, flags));
	return (print_intstr(prepend, int_str, flags));
}

double	get_intstr_and_frac(long double nbr, char **int_str, int isneg)
{
	long double	temp;
	long double	divider;
	int			digits;
	char		*ptr;

	if (is_infinity(nbr))
		return (set_infinity(nbr, int_str));
	digits = 1;
	digits += (isneg) ? 1 : 0;
	nbr = isneg ? -nbr : nbr;
	temp = nbr;
	while ((temp = temp / 10.0) >= 1.0)
		digits++;
	divider = double_pow(10, digits - isneg - 1);
	*int_str = ft_strnew(digits);
	ptr = *int_str;
	isneg ? *ptr++ = '-' : 0;
	while ((digits--) - isneg > 0)
	{
		*ptr++ = (int)(nbr / divider) + '0';
		nbr = nbr - divider * (int)(nbr / divider);
		divider /= 10.0;
	}
	return (nbr);
}

/*
** Convert "frac_part" into a string
** get_fracstr has to consider precision and rounding
** takes in frac_part, frac_str, and precision
** returns 1 if carry-over to int_str needed
** else, returns 0
*/

int		get_fracstr_and_carryover(double frac_part, \
		char **frac_str, char **int_str, int prec)
{
	int		carry_over;
	int		i;

	if (is_infinity(frac_part))
	{
		*frac_str = ft_strdup("");
		return (0);
	}
	carry_over = 0;
	i = 0;
	prec = (prec == -1) ? 6 : prec;
	*frac_str = (char*)ft_strnew(prec);
	while (i < prec)
	{
		*(*frac_str + i) = (int)(frac_part * 10.0) + '0';
		frac_part = frac_part * 10.0 - (int)(frac_part * 10.0);
		i++;
	}
	*(*frac_str + i) = '\0';
	frac_part = frac_part * 10.0;
	if (frac_part == 5)
		carry_over = tie_to_even(int_str, frac_str);
	if (frac_part > 5)
		carry_over = increment_str(frac_str, 'f');
	return (carry_over);
}

int		print_weird(char *int_str, t_flags *flags)
{
	int		slen;
	int		spaces;

	slen = (ft_strstr(int_str, "-inf")) ? 4 : 3;
	spaces = flags->width - slen;
	if (!flags->minus)
		write_padding(spaces, ' ');
	write(1, int_str, slen);
	if (flags->minus)
		write_padding(spaces, ' ');
	free(int_str);
	return (MAX(flags->width, slen));
}

int		print_intstr(char prepend, char *int_str, t_flags *flags)
{
	int		slen;
	int		spaces;

	slen = ft_strlen(int_str);
	if (flags->prec == 0 && !flags->hash)
		slen--;
	spaces = flags->width - MAX(flags->prec, slen) - (prepend != 0);
	if (!flags->minus && !(flags->zero))
		write_padding(spaces, ' ');
	if (prepend)
		write(1, &prepend, 1);
	if (flags->zero && !flags->minus)
		write_padding(spaces, '0');
	else if (flags->prec - slen > 0)
		write_padding(flags->prec - slen, '0');
	write(1, int_str, slen);
	if (flags->minus)
		write_padding(spaces, ' ');
	free(int_str);
	return (MAX(flags->width, MAX(flags->prec, slen) + (prepend != 0)));
}
