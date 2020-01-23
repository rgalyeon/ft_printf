/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:07:42 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/23 22:11:04 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

int *foo(int x)
{
	int array[x];

	array[0] = 5;
	return (&array);
}

int main(int argc, char **argv)
{
	int x = 0;
	int	*ptr;

	x += argc == 1 ? 2 : 10;
	ptr = foo(x);
	ptr[0] = 21;
	printf("ptr %d\t%p\n", ptr[0], ptr);

	for (int i = 0; i < 20; i++)
	{
		int *ptrs = foo(1);
		printf("%p\n", ptrs);
		printf("%d %d\n", ptrs[0], ptrs);
	}
	printf("ptr %d\t%p\n", ptr[0], ptr);

	int *p = foo(x);
	printf("ptr %p\t%p\n", ptr, p);
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
//	ft_printf("this %f float\n", 1.5);
//	printf("this %f float\n\n", 1.5);

}
