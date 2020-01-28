/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:07:42 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/28 18:48:16 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

int main(int argc, char **argv)
{

//	ft_printf("%-2lc", 134);
//
//	ft_printf("% +012.Lf\n", (long double)2314.123456789);
//	ft_printf("%012.Lf\n", (long double)0.);

//	ft_printf("%d\n", INT_MAX);

	ft_printf("%.2f, %.100f\n", 155.645, 155.645);

	ft_printf("%.350f|%.350f|%.350f|%.350f|%.350f", 1.e-1, 1.e-2, 1.e-18, 1.e-57, 1.e-201);
//
	ft_printf("%.2147483649f|%2147483649f\n", 1.0, 1.0);

	ft_printf("this %f float\n", 1.5);

}
