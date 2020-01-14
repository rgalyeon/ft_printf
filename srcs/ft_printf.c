/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:08:32 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/09 17:51:31 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	va_list arg;
	int done;
	va_start (arg, format);
	done = ft_vfprintf(STDOUT_FILENO, format, arg);
	va_end (arg);
	return (done);
}