/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/21 00:22:02 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <math.h>
#include <limits.h>

void	out_double(double num)
{
	t_conv		un;
	uint64_t	bits;
	int			i;

	i = 63;
	un.d = num;
	printf("Number: %f\n", num);
	printf("%u %u %llu\n", un.u.sign, un.u.exponent, un.u.mantissa);
	ft_memcpy(&bits, &num, sizeof(double));
	while (i >= 0)
	{
		printf("%d", (int)(bits >> i) & 1);
		if (i == 63)
			printf(" ");
		else if (i == 52)
			printf(" ");
		i--;
	}
	printf("\n");
}

char	*ftoa(double val)
{
	char *d_str;

	return (d_str);
}

//int main()
//{
//	out_double(M_PI);
//	out_double(0.3 - 0.000001);
//	return (0);
//}
