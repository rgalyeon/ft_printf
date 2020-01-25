/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:01:30 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/25 19:13:15 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	processing_n(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	int *dest;

	(void)placeholder;
	dest = va_arg(arg_ptr, int *);
	*dest = (*vec)->total;
}
