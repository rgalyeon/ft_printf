/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:12:20 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/17 22:58:05 by rgalyeon         ###   ########.fr       */
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
	FULL_SIZE = (int)max3(placeholder->width,
			placeholder->precision + has_sign,
			len + has_sign);
	ZERO_COUNT = (int)placeholder->precision - len;
	PADDING = (int)placeholder->width -
				(max2(placeholder->precision, len) + has_sign);
}

static void	fill_string(char *str, t_ph *placeholder, int *align_params,
		__int128 value)
{
	int 		idx;
	char		*ascii_value;

	if (!(ascii_value = ft_itoa(value < 0 ? -value : value)))
		exit(MALLOC_ERR);
	idx = 0;
	if (!(placeholder->flag & MINUS.code) && !(placeholder->flag & ZERO.code))
		while (PADDING > 0 && PADDING--)
			str[idx++] = ' ';
	if (value < 0)
		str[idx++] = '-';
	else if (placeholder->flag & PLUS.code || placeholder->flag & SPACE.code)
		str[idx++] = placeholder->flag & PLUS.code ? PLUS.symbol : SPACE.symbol;
	if (placeholder->flag & ZERO.code) //TODO объединить if'ы
		ZERO_COUNT = ZERO_COUNT < 0 ? PADDING : ZERO_COUNT + PADDING;
	if (placeholder->flag & ZERO.code)
		PADDING = 0;
	while (ZERO_COUNT > 0 && ZERO_COUNT--)
		str[idx++] = '0';

	ascii_value = (!(value) && (placeholder->precision >= 0)) ? "" :
			ascii_value; //TODO NEED FIX
	ft_strcpy(&str[idx], ascii_value);
	idx += ft_strlen(ascii_value);
	while (PADDING > 0 && PADDING--)
		str[idx++] = ' ';
//	free(ascii_value);
}

char		*processing_di(t_ph *placeholder, va_list arg_ptr)
{
	__int128	value;
	int 		align_params[3];
	t_bool		has_sign;
	char 		*processed_string;

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	override_placeholder(placeholder, value);
	has_sign = ((value < 0) || (placeholder->flag & PLUS.code) ||
			(placeholder->flag & SPACE.code));
	get_alignment_params(align_params, placeholder, value,
			has_sign);
	if (!(processed_string = ft_memalloc(FULL_SIZE + 1)))
		exit(MALLOC_ERR);
	fill_string(processed_string, placeholder, (int *)align_params, value);
	return (processed_string);
}