/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:12:20 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/18 16:59:49 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static __int128	get_value_from_va_stack(u_int8_t length, va_list arg_ptr)
{
	__int128	value;

	if (length & LENGTH_LONG_LONG)
		value = va_arg(arg_ptr, long long int);
	else if (length & LENGTH_LONG)
		value = va_arg(arg_ptr, long int);
	else if (length & LENGTH_SHORT)
		value = (short int)va_arg(arg_ptr, int);
	else if (length & LENGTH_CHAR)
		value = (char)va_arg(arg_ptr, int);
	else
		value = va_arg(arg_ptr, int);
	return value;
}

/**
** Function disable conflicting placeholder's parameters for d, i types
** Flag 0 ignored if precision or flag '-' given
** If value is negative, ' ' and '+' flags ignored
** Flag '+' is given, ' ' ignored
** @param placeholder
** @param value
*/

static void override_placeholder(t_ph *placeholder, __int128 value)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 || (placeholder->flag & MINUS.code))
		placeholder->flag &= ~ZERO.code;
	if (value < 0)
		placeholder->flag &= ~(SPACE.code | PLUS.code);
	else if (placeholder->flag & PLUS.code)
		placeholder->flag &= ~SPACE.code;
}

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
												__int128 value, t_bool has_sign)
{
	int len;

	len = ft_uint_len(value);
	if (!(value) && (placeholder->precision >= 0))
		len = 0;
	ZERO_COUNT = (int)placeholder->precision - len;
	PADDING = (int)placeholder->width -
				(max2(placeholder->precision, len) + has_sign);
}

static void	fill_string(t_vec **vec, t_ph *placeholder, int *align_params,
		__int128 value)
{
	char		*ascii_value;

	if (!(ascii_value = ft_itoa_base(value < 0 ? -value : value, 10)))
		exit(MALLOC_ERR);
	if (!(placeholder->flag & MINUS.code) && !(placeholder->flag & ZERO.code))
		while (PADDING > 0 && PADDING--)
			ft_vec_push(vec, ' ');
	if (value < 0)
		ft_vec_push(vec, '-');
	else if (placeholder->flag & PLUS.code || placeholder->flag & SPACE.code)
		ft_vec_push(vec, placeholder->flag & PLUS.code ? PLUS.symbol :
																SPACE.symbol);
	if (placeholder->flag & ZERO.code) //TODO объединить if'ы
		ZERO_COUNT = ZERO_COUNT < 0 ? PADDING : ZERO_COUNT + PADDING;
	if (placeholder->flag & ZERO.code)
		PADDING = 0;
	while (ZERO_COUNT > 0 && ZERO_COUNT--)
		ft_vec_push(vec, '0');
	ft_vec_string_push(vec,
			(!(value) && (placeholder->precision >= 0)) ? "" : ascii_value);
	while (PADDING > 0 && PADDING--)
		ft_vec_push(vec, ' ');
	free(ascii_value);
}

char		*processing_di(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	__int128	value;
	int 		align_params[3];
	t_bool		has_sign;

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	override_placeholder(placeholder, value);
	has_sign = ((value < 0) || (placeholder->flag & PLUS.code) ||
			(placeholder->flag & SPACE.code));
	get_alignment_params(align_params, placeholder, value,
			has_sign);
	fill_string(vec, placeholder, (int *)align_params, value);
	return (NULL);
}