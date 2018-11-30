/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:17:11 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/30 10:18:49 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./ft_printf.h"
#include "./libft/libft.h"
#include "./libft/get_next_line.h"
#include <fcntl.h>
#include <math.h>
#include "limits.h"
#define TEST_RET(a, b) (a == b) ? printf("SAME: %d\n\n", a) \
: printf("DIFF: a %d b %d\n\n", a, b);

int		main(void)
{
	char	*s;
	int		a;
	int		b;
	
	a = 5;
	b = 5;
	s = NULL;
	double	nbr = 0.0 / 0.0;
	int		prec = 3;
	double	frac_part;
	char	*int_str;
	char	*frac_str;

	frac_part = get_intstr_and_frac(nbr, &int_str, (nbr < 0));
	if (get_fracstr_and_carryover(frac_part, &frac_str, prec))
		increment_str(&int_str, 'i');
	printf("mine: %s.%s\n", int_str, frac_str);
	printf("real: %.*f\n", prec, nbr);

	/*
	printf("-----TEST-----\n");
	printf("%f\n", 0.99);
	printf("%.0f\n", 0.99);
	printf("%.1f\n", 0.99);
	printf("%.2f\n", 0.99);
	printf("%.3f\n", 0.99);
	printf("%.23f\n", 0.99);
	printf("%.40f\n\n", 0.99);

	printf("%f\n", 0.15);
	printf("%.0f\n", 0.15);
	printf("%.1f\n", 0.15);
	printf("%.2f\n", 0.15);
	printf("%.3f\n", 0.15);
	printf("%.16f\n", 0.15);
	printf("%.17f\n", 0.15);
	printf("%.25f\n", 0.15);
	*/

	/*
	printf("-----TEST----\n");
	printf("\n%.0f\n", -5.5);
	printf("%.0f\n", -4.5);
	printf("%.0f\n", -3.5);
	printf("%.0f\n", -2.5);
	printf("%.0f\n", -1.5);
	printf("%.0f\n", -0.5);
	printf("%.0f\n", 0.5);
	printf("%.0f\n", 1.5);
	printf("%.0f\n", 2.5);
	printf("%.0f\n", 3.5);
	printf("%.0f\n", 4.5);
	printf("%.0f\n", 4.5);
	printf("%.0f\n", 5.5);
	*/
	/*
	a = printf("%lld\n", -9223372036854775808);
	b = ft_printf("%lld\n", -9223372036854775808);
	TEST_RET(a, b);
	a = printf("--[%030.20lf]--\n", -99.99);
	b = ft_printf("--[%030.20lf]--\n", -99.99);
	TEST_RET(a, b);
	a = printf("[%.25f]\n", (int)0 / 0);
	b = ft_printf("[%.25f]\n", (int)0 / 0);	
	TEST_RET(a, b);
	*/
	printf("\n-----ROUNDING-----\n\n");
	a = printf("%.2f\n", 0.125);
	a = printf("%.20f\n", 0.1251);
	b = ft_printf("%.20f\n", 0.1251);
	TEST_RET(a, b);
	a = printf("%.f\n", 0.5);
	b = ft_printf("%.f\n", 0.5);
	TEST_RET(a, b);
	a = printf("%.f\n", 1.5);
	b = ft_printf("%.f\n", 1.5);
	TEST_RET(a, b);
	printf("--------TEST---------\n\n");
	a = printf("%f\n", 0.0);
	b = ft_printf("%f\n", 0.0);
	TEST_RET(a, b);
	a = printf("[%20.f]\n", 0.0 / 0.0);
	b = ft_printf("[%20.f]\n", 0.0 / 0.0);
	TEST_RET(a, b);
	a = printf("[%-*.*f]\n", -20, 0, -1.0 / 0.0);
	b = ft_printf("[%-*.*f]\n", -20, 0, -1.0 / 0.0);
	TEST_RET(a, b);
	// printf("[%20.10f]\n", 0.0);
	a = ft_printf("[%050.20f]\n", 0.15);
	b = printf("[%050.20f]\n", 0.15);
	TEST_RET(a, b);
	return (0);
}
