/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:29:34 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/18 16:18:21 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static __uint128_t	get_value_from_va_stack(u_int8_t length, va_list arg_ptr)
{
	__uint128_t	value;

	if (length & LENGTH_LONG_LONG)
		value = (unsigned long long)va_arg(arg_ptr, long long int);
	else if (length & LENGTH_LONG)
		value = (unsigned long)va_arg(arg_ptr, long int);
	else if (length & LENGTH_SHORT)
		value = (unsigned short)va_arg(arg_ptr, int);
	else if (length & LENGTH_CHAR)
		value = (unsigned char)va_arg(arg_ptr, int);
	else
		value = (unsigned)va_arg(arg_ptr, int);
	return value;
}

/**
** Function disable conflicting placeholder's parameters for u type
** Flag 0 ignored if precision or flag '-' given
** ' ', '+' doesn't work with unsigned conversion
** @param placeholder
** @param value
*/

static void			override_placeholder(t_ph *placeholder, __uint128_t value)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 || (placeholder->flag & MINUS.code))
		placeholder->flag &= ~ZERO.code;
	placeholder->flag &= ~(PLUS.code | SPACE.code);
}

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
		__uint128_t value)
{
	int len;

	len = ft_uint_len(value);
	if (!(value) && (placeholder->precision >= 0))
		len = 0;
	ZERO_COUNT = (int)placeholder->precision - len;
	PADDING = (int)placeholder->width -
			(max2(placeholder->precision, len));
}

static void	fill_string(t_vec **vec, t_ph *placeholder, int *align_params,
		__uint128_t value)
{
	char		*ascii_value;

	if (!(ascii_value = ft_itoa(value)))
		exit(MALLOC_ERR);
	if (!(placeholder->flag & MINUS.code) && !(placeholder->flag & ZERO.code))
		while (PADDING > 0 && PADDING--)
			ft_vec_push(vec, ' ');
	if (placeholder->flag & ZERO.code) //TODO объединить if'ы
		ZERO_COUNT = ZERO_COUNT < 0 ? PADDING : ZERO_COUNT + PADDING;
	if (placeholder->flag & ZERO.code)
		PADDING = 0;
	while (ZERO_COUNT > 0 && ZERO_COUNT--)
		ft_vec_push(vec, '0');
	ascii_value = (!(value) && (placeholder->precision >= 0)) ? "" :
				  ascii_value; //TODO NEED FIX
	ft_vec_string_push(vec, ascii_value);
	while (PADDING > 0 && PADDING--)
		ft_vec_push(vec, ' ');
//	free(ascii_value);
}

char				*processing_u(t_vec **vec, t_ph *placeholder, va_list
arg_ptr)
{
	__uint128_t	value;
	int 		align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	override_placeholder(placeholder, value);
	get_alignment_params(align_params, placeholder, value);
	fill_string(vec, placeholder, align_params, value);

	return (NULL);
}
