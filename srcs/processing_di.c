/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:12:20 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/16 23:14:15 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
** Flag 0 ignored if precision or flag '-' given
** @param placeholder
*/

static void override_placeholder(t_ph *placeholder, __int128 value)
{
	placeholder-> width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 || (placeholder->flag & MINUS.code))
		placeholder->flag &= ~ZERO.code;
	if (value < 0)
		placeholder->flag &= ~(SPACE.code | PLUS.code);
	else if (placeholder->flag & PLUS.code)
		placeholder->flag &= ~SPACE.code;
}

static int 	get_padding(t_ph *placeholder, __int128 value)
{
	int		padding_size;
	t_bool	has_sign;
	const int len = 5;

	has_sign = ((value < 0) || (placeholder->flag & PLUS.code) ||
			(placeholder->flag & SPACE.code));
	placeholder->precision -= len;


}

char	*processing_di(t_ph *placeholder, va_list arg_ptr)
{
	__int128	value;


	if (placeholder->length & LENGTH_LONG_LONG)
		value = va_arg(arg_ptr, long long int);
	else if (placeholder->length & LENGTH_LONG)
		value = va_arg(arg_ptr, long int);
	else
		value = va_arg(arg_ptr, int);
	override_placeholder(placeholder, value);
	get_padding(placeholder, value);
	char *t = ft_itoa(value);
	int len = ft_strlen(t);
	return NULL;
}