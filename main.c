/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:07:42 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/28 15:24:14 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

void	output_ldbl(long double value)
{
	t_dbl2int	convert;
	uint64_t	mantissa;
	int32_t		exponent;
	uint8_t		sign;
	int			i;

	i = 79;
	convert.dbl = value;
	while (i >= 0)
	{
		ft_printf("%d", (int)(convert.bits >> i) & 1u);
		if (i == 79 || i == 64 || i == 62)
			ft_printf(" ");
		i--;
	}
	ft_printf("\n");
}

int main(int argc, char **argv)
{
//	int *t = foo(1000);
//	*(t + 3984 / 4) = 5;
//	printf("t %d\t%p\n", t[0], t);
//	printf("ptr %d\n", ptr[0]);
//	printf("%02ll4.2d$\n", 5);
//	printf("%10f$\n", 24.678);
//	printf("%#10f$\n", 24.678);
//	printf("%7.1f$\n", 24.678);
//	printf("%7.1f$\n", 24.898);
//	printf("%-7.0f$\n", 24.898);
//	printf("%07.1f$\n", 24.898);
//	printf("%07.1f$\n", 0.);
//	printf("%07.0f$\n", 0.);
//	printf("%+07.0f$\n\n", 0.);

//	ft_printf("%-2lc", 134);

//	printf("% +012.Lf\n", (long double)2314.123456789);
//	printf("%012.Lf\n", (long double)0.);
//
//	printf("%Lf %Lf\n", (long double)1.0, (long double)2.0, (long double)3.0);
//	printf("%Lf %Lf %Lf\n", (long double)4.0, (long double )5.0);


//	printf("%d\n", ft_printf("%*d\n", INT_MAX, 5));

//	printf("%.2f, %.100f\n", 155.645, 155.645); // 155.65
//	printf("%.2f, %.100f\n", 155.675, 155.675); // 155.68
//	printf("%.2f, %.100f\n", 155.665, 155.665); // 155.66
//	printf("%.2f, %.100f\n", 155.655, 155.655); // 155.66
//	printf("%.2f, %.100f\n", 155.635, 155.635); // 155.63
//	printf("%.2f, %.100f\n", 155.625, 155.625); // 155.62
//	printf("%.2f, %.100f\n", 155.615, 155.615); // 155.62
//	printf("%.2f, %.100f\n\n", 155.605, 155.605); //155.60
//	printf("%.2f, %.100f\n", 155.685, 155.685);
//	printf("%.2f, %.100f\n", 155.69500000001, 155.69500000001);
//	int arr[argc];
//
//	arr[0] = 10;
//	printf("%.1f\n", 155.675);
//	printf("%.1f\n", 155.665);
//	printf("%.1f\n", 155.655);
//	printf("%.1f\n", 155.645);
//
//	printf("%.1f\n", 36.45);

	long double		number = LDBL_MAX;
	t_dbl2int		convert;

	convert.dbl = number;
//	output_ldbl(convert.dbl);
	ft_printf("%.100Lf\n\n", number);
	printf("%.100Lf\n", number);

//	ft_printf("%.1150Lf|%.1150Lf|%.1150Lf|%.1150Lf\n", 0x1p-1074, 0x1.ffffffffffffep-1023, 0x1.4e46p-1058, 0x1.59a8b0c3dp-1037);
//	printf("%.1150f|%.1150f|%.1150f|%.1150f", 0x1p-1074, 0x1.ffffffffffffep-1023, 0x1.4e46p-1058, 0x1.59a8b0c3dp-1037);
	return (0);
}
