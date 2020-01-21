/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/21 23:58:33 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void	out_double(double num)
{
	t_conv		un;
	uint64_t	bits;
	int			i;

	i = 63;
	un.d = num;
	printf("Number: %f\n", num);
	ft_printf("%u %u %llu\n", un.u.sign, un.u.exponent, un.u.mantissa);
	ft_memcpy(&bits, &num, sizeof(double));
	while (i >= 0)
	{
		ft_printf("%d", (int)(bits >> i) & 1);
		if (i == 63)
			ft_printf(" ");
		else if (i == 52)
			ft_printf(" ");
		i--;
	}
	ft_printf("\n");
}

char	*ftoa(double val, int prec)
{
	char *d_str;

	return (d_str);
}

//int main()
//{
//	t_conv	number;
//	t_bignum	*m;
//	t_bignum	*e;
//	t_bignum	*tmp;
//
//	number.d = M_PI * 123123123123123;
//	out_double(number.d);
//	m = int2bignum(number.u.mantissa | (1ull << DBL_MANTISSA_BITS));
//	e = int2bignum(number.u.exponent);
//	int e2 = -DBL_MANTISSA_BITS + number.u.exponent - 1023;
//	printf("e2 = %d\n", e2);
//	print_bignum(bignum_mul(m, bignum_pow(int2bignum(5), -e2)), -e2);
//	printf("%.100f\n", number.d);
//	return (0);
//}
