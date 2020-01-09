/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:08:32 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/09 17:09:51 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int printf (const char *format, ...)
{
	va_list arg;
	int done;
	va_start (arg, format);
//	done = vfprintf_internal (stdout, format, arg, 0);
	done = 2;
	va_end (arg);
	return (done);
}