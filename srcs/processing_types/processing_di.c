/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:12:20 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:25:59 by rgalyeon         ###   ########.fr       */
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
	return (value);
}

/*
** Function disable conflicting placeholder's parameters for d, i types
** Flag 0 ignored if precision or flag '-' given
** If value is negative, ' ' and '+' flags ignored
** Flag '+' is given, ' ' ignored
** @param placeholder
** @param value
*/

static void		override_placeholder(t_ph *placeholder, __int128 value)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 ||
									(placeholder->flag & g_flag[MINUS].code))
		placeholder->flag &= ~(g_flag[ZERO].code);
	if (value < 0)
		placeholder->flag &= ~(g_flag[SPACE].code | g_flag[PLUS].code);
	else if (placeholder->flag & g_flag[PLUS].code)
		placeholder->flag &= ~(g_flag[SPACE].code);
}

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @param placeholder
** @value - value from va_list
** @has_sign
*/

static void		get_alignment_params(int align_params[3], t_ph *placeholder,
												__int128 value, t_bool has_sign)
{
	int len;

	len = ft_uint_len(value);
	if (!(value) && (placeholder->precision >= 0))
		len = 0;
	align_params[ZERO_PAD] = (int)placeholder->precision - len;
	align_params[PAD] = (int)placeholder->width -
				(max2(placeholder->precision, len) + has_sign);
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param ph - placeholder
** @param align_params - array with padding params
** @param value - value from va_list
*/

static void		fill_string(t_vec **vec, t_ph *ph, int *align_params,
		__int128 value)
{
	char		*ascii_value;

	if (!(ascii_value = ft_itoa_base(value < 0 ? -value : value, 10)))
		return ;
	if (!(ph->flag & g_flag[MINUS].code) && !(ph->flag & g_flag[ZERO].code))
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
	if (value < 0)
		*vec = ft_vec_push(vec, '-');
	else if (ph->flag & g_flag[PLUS].code || ph->flag & g_flag[SPACE].code)
		*vec = ft_vec_push(vec, ph->flag & g_flag[PLUS].code ?
								g_flag[PLUS].symbol : g_flag[SPACE].symbol);
	if (ph->flag & g_flag[ZERO].code)
	{
		align_params[ZERO_PAD] = align_params[ZERO_PAD] < 0 ?
				align_params[PAD] : align_params[ZERO_PAD] + align_params[PAD];
		align_params[PAD] = 0;
	}
	while (align_params[ZERO_PAD] > 0 && align_params[ZERO_PAD]--)
		*vec = ft_vec_push(vec, '0');
	*vec = ft_vec_string_push(vec,
			(!(value) && (ph->precision >= 0)) ? "" : ascii_value);
	while (align_params[PAD] > 0 && align_params[PAD]--)
		*vec = ft_vec_push(vec, ' ');
	free(ascii_value);
}

void			processing_di(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	__int128	value;
	int			align_params[3];
	t_bool		has_sign;

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	override_placeholder(placeholder, value);
	has_sign = ((value < 0) || (placeholder->flag & g_flag[PLUS].code) ||
			(placeholder->flag & g_flag[SPACE].code));
	get_alignment_params(align_params, placeholder, value,
			has_sign);
	fill_string(vec, placeholder, (int *)align_params, value);
}
