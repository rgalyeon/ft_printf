/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:10:47 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:44:46 by rgalyeon         ###   ########.fr       */
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
	return (value);
}

/*
** Function disable conflicting placeholder's parameters for x, X  or o type
** @param placeholder
** @param value - value from va_list
*/

static void			override_placeholder(t_ph *placeholder, __uint128_t value)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 || (placeholder->flag &
														g_flag[MINUS].code))
		placeholder->flag &= ~(g_flag[ZERO].code);
	placeholder->flag &= ~(g_flag[PLUS].code | g_flag[SPACE].code);
	if ((placeholder->flag & g_flag[HASH].code) && !value &&
						!placeholder->precision && placeholder->type == 'o')
		placeholder->precision = 1;
	if (!value)
		placeholder->flag &= ~(g_flag[HASH].code);
}

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @value - int value from va_list
** @converted_value - string hex/oct value
** @param placeholder
*/

static void			get_alignment_params(int align_params[3], t_ph *placeholder,
		__uint128_t value, char *converted_value)
{
	int len;

	len = ft_strlen(converted_value);
	if (!(value) && (placeholder->precision >= 0))
		len = 0;
	align_params[ZERO_PAD] = (int)placeholder->precision - len;
	align_params[PAD] = (int)(placeholder->width -
										(max2(placeholder->precision, len)));
	if (placeholder->flag & g_flag[HASH].code)
	{
		if (placeholder->type != 'o')
			align_params[PAD] -= 2;
		else if (align_params[ZERO_PAD] <= 0)
			align_params[PAD] -= 1;
	}
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param placeholder
** @param align_params - array with padding params
** @param converted_value - string hex/oct value
*/

static void			fill_string(t_vec **vec, t_ph *placeholder,
									int *align_params, char *converted_value)
{
	if (!(placeholder->flag & g_flag[MINUS].code) &&
									!(placeholder->flag & g_flag[ZERO].code))
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
	if (placeholder->flag & g_flag[HASH].code)
	{
		if (placeholder->type == 'o')
			(*vec = ft_vec_push(vec, '0')) && align_params[ZERO_PAD]--;
		else
			*vec = ft_vec_string_push(vec, placeholder->type == 'X' ? "0X" :
			"0x");
	}
	if (placeholder->flag & g_flag[ZERO].code)
	{
		align_params[ZERO_PAD] = align_params[ZERO_PAD] < 0 ?
				align_params[PAD] : align_params[ZERO_PAD] + align_params[PAD];
		align_params[PAD] = 0;
	}
	while (align_params[ZERO_PAD] > 0 && align_params[ZERO_PAD]--)
		*vec = ft_vec_push(vec, '0');
	*vec = ft_vec_string_push(vec, (!ft_strcmp(converted_value, "0") &&
		placeholder->precision >= 0) ? "" : converted_value);
	while (align_params[PAD] > 0 && align_params[PAD]--)
		*vec = ft_vec_push(vec, ' ');
}

/*
** Function handle 'x', 'X' and 'o' types
** @param vec - output string (vector0
** @param placeholder
** @param arg_ptr - va_list
** @return
*/

void				processing_x(t_vec **vec, t_ph *placeholder,
															va_list arg_ptr)
{
	const int	base = placeholder->type == 'o' ? 8 : 16;
	__uint128_t	value;
	char		*converted_value;
	int			align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	if (!(converted_value = ft_itoa_base(value, base)))
		return ;
	placeholder->type == 'X' ? ft_str_upper(converted_value) : converted_value;
	override_placeholder(placeholder, value);
	get_alignment_params(align_params, placeholder, value, converted_value);
	fill_string(vec, placeholder, align_params, converted_value);
	free(converted_value);
}
