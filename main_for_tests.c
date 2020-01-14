/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:42:05 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/14 22:18:42 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ft_printf.h"

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
	printf("%***d$\n", 2, -4, 6, 5);
	printf("%2*5d$\n", 2, 5);

	printf("~~~~~ TEST PRECISION ~~~~~\n");
	printf("%3.2*s$\n", -10, "abcde");
	printf("%10.2s$\n", "abcde");
	printf("%.***4s$\n", 2, 10, 3, "abcde");
	printf("%.10s$\n", "abcde");
	printf("%.*s$\n", -2, "abcde");
	printf("%-2s$\n", "abcde");
//	printf("%.*.*s$\n", 2, 3, 10, "abcde");
	printf("%10.2*10s$\n", 0, "abcde");

}