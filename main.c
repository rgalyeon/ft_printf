/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:50:12 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/19 19:01:08 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
//	ft_printf("he %-5.3d");
//	ft_printf("%2.*3**oXx", 10, -15, 2);
//	ft_printf("%2.*3**llu", 10, -15, 2);
//	ft_printf("%2.*3**lhlp", 10, -15, 2);
//	ft_printf("%2.*3**lhlhlLhhsd", 10, -15, 2);
//	ft_printf("%2.*3**hhhhhhhlllllsd", 10, -15, 2);

	ft_printf("% +-#0.10d$\n", -605555);
	printf("% +-#0.10d$\n\n", -605555);

	ft_printf("% +-#20.10d$\n", 65555);
	printf("% +-#20.10d$\n\n", 65555);

	ft_printf("% d$\n", 65555);
	printf("% d$\n\n", 65555);

	ft_printf("%+-010d$\n", 65555);
	printf("%+-010d$\n\n", 65555);

	ft_printf("%010d$\n", -20);
	printf("%010d$\n\n", -20);

	ft_printf("% 010d$\n", 20);
	printf("% 010d$\n\n", 20);

	ft_printf("%+10.6d$\n", 4254);
	printf("%+10.6d$\n\n", 4254);

	ft_printf("%-0+10.6d$\n", 4254);
	printf("%-0+10.6d$\n\n", 4254);


	ft_printf("%-5.0d$\n", 0);
	printf("%-5.0d$\n\n", 0);

	ft_printf("%-8.5d$\n", 0);
	printf("%-8.5d$\n\n", 0);

	ft_printf("hello, %s$\n", "gavin");
	printf("hello, %s$\n\n", "gavin");

	ft_printf("hello, %.2s$\n", "gavin");
	printf("hello, %.2s$\n\n", "gavin");

	ft_printf("%.09s$\n", NULL);
	printf("%.09s$\n\n", NULL);

	ft_printf("hello, %04s$\n", "ga");
	printf("hello, %04s$\n\n", "ga");

	ft_printf("%c top$\n", 1);
	printf("%c top$\n\n", 1);

	ft_printf("%-5c top$\n", 'd');
	printf("%-5c top$\n\n", 'd');

	ft_printf("%-5c top$\n", 0);
	printf("%-5c top$\n\n", 0);
	char str[] = "string";

	printf("size: %zu\n", sizeof(str));

	printf("%.20f\n", 0.3);
//	printf("%d\n", ft_atoi("09"));
//	printf("%2.*3**d\n", 10, -15, 2, -24242);
//	printf("%lld\n", UINT64_MAX);
//	printf("%zu\n", sizeof(__int128_t));

}