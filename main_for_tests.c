/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:42:05 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/16 23:46:46 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
//	printf("~~~~~ TEST WIDTH ~~~~~\n");
//	write(1, "printf(\"%10*d$\\n\", 2, 5);\n",
//			strlen("printf(\"%10*d$\\n\", 2, 5);\n"));
//	printf("%10*d$\n", 2, 5);
//	write(1, "printf(\"%10*15d$\\n\", 2, 5);\n",
//			strlen("printf(\"%10*15d$\\n\", 2, 5);\n"));
//	printf("%10*15d$\n", 2, 5);

//	printf("~~~~~ TEST WIDTH ~~~~~\n");
//	printf("%***d$\n", 2, -4, 6, 5);
//	printf("%2*5d$\n", 2, 5);
//
//	printf("~~~~~ TEST PRECISION ~~~~~\n");
//	printf("%3.2*s$\n", -10, "abcde");
//	printf("%10.2s$\n", "abcde");
//	printf("%.***4s$\n", 2, 10, 3, "abcde");
//	printf("%.10s$\n", "abcde");
//	printf("%.*s$\n", -2, "abcde");
//	printf("%-2s$\n", "abcde");
////	printf("%.*.*s$\n", 2, 3, 10, "abcde");
//	printf("%10.2*10s$\n", 0, "abcde");

//	printf("~~~~~ TEST LENGTH ~~~~~\n");
//	printf("%d %d\n", 10000000.232, 10, 20, 30);
//	char test = 'a';
//	printf("%Lllu %d\n", );
//	long double t = 10000000.232;
////	int d = t | INT32_MAX;
////	printf("%d\n", d);

//	printf("%Lf\n", t);
//	printf("%d\n", 1097011920);
//	printf("%zu\n", sizeof(double));
//	printf("%zu\n", sizeof(long double));
//	printf("%zu\n", sizeof(long long int));
////	printf("%zu\n", sizeof());
//	printf("%d\n", printf("%k\n", "str"));
//	int c = 'c';
//	printf("%c\n", c);

	printf("~~~~~ TEST D TYPE ~~~~~\n");
	printf("%s - %d$\n", "%d$", 3000);
	printf("%d$\n", -3000);
	printf("%-d$\n", 3000);
	printf("%+d$\n", 3000);
	printf("%+d$\n", 3000);
	printf("%X$\n", 2);
	printf("%#10.10d$\n", 3000);
	printf("%-11.0d$\n", 3000);
	printf("%llu\n", (unsigned long long)(0-242));
	printf("% -01.2d$\n", -60);
	printf("% +-#0.10d$\n", -605555);
	printf("% +-#12.7d$\n", -605555); ///full size = 13; 0 = 1; padd 4;
}