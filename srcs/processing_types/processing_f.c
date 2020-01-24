/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:10:15 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/24 21:50:41 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	get_value_from_va_stack(u_int8_t length, va_list arg_ptr)
{
	long double	value;

	if (length & LENGTH_LONG_DOUBLE)
		value = va_arg(arg_ptr, long double);
	else
		value = va_arg(arg_ptr, double);
	return (value);
}

static void			override_placeholder(t_ph *placeholder, const char *value)
{
	placeholder->width = placeholder->width <= -1 ? 0 : placeholder->width;
	if (placeholder->flag & g_flag[MINUS].code)
		placeholder->flag &= ~(g_flag[ZERO].code);
	if (value[0] == '-')
		placeholder->flag &= ~(g_flag[SPACE].code | g_flag[PLUS].code);
	else if (placeholder->flag & g_flag[PLUS].code)
		placeholder->flag &= ~(g_flag[SPACE].code);
	if (placeholder->precision > 0)
		placeholder->flag &= ~g_flag[HASH].code;
}

static void			get_alignment_params(int align_params[3], t_ph *placeholder,
		char *value, t_bool has_sign)
{
	int len;

	len = (int)ft_strlen(value) + has_sign + (ft_strchr(value, 'n') ? 1 : 0);
	align_params[PAD] = (int)placeholder->width - len;
}

static void			fill_string(t_vec **vec, t_ph *ph, int *align_params,
		char *value)
{
	if (!(ph->flag & g_flag[MINUS].code) && !(ph->flag & g_flag[ZERO].code))
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
	if (value[0] == '-')
		*vec = ft_vec_push(vec, '-');
	else if (ph->flag & g_flag[PLUS].code || ph->flag & g_flag[SPACE].code)
		*vec = ft_vec_push(vec, ph->flag & g_flag[PLUS].code ?
								g_flag[PLUS].symbol : g_flag[SPACE].symbol);
	if (ph->flag & g_flag[ZERO].code)
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, '0');
	*vec = ft_vec_string_push(vec, value[0] == '-' ? value + 1 : value);
	if (ph->flag & g_flag[HASH].code && !ft_strchr(value, 'n'))
		ft_vec_push(vec, '.');
	while (align_params[PAD] > 0 && align_params[PAD]--)
		*vec = ft_vec_push(vec, ' ');
}

void				processing_f(t_vec **vec, t_ph *placeholder,
														va_list arg_ptr)
{
	long double	value;
	int			align_params[3];
	char		*str_value;
	t_bool		has_sign;

	ft_memset(align_params, 0, sizeof(align_params));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	placeholder->precision = placeholder->precision <= -1 ?
									DEFAULT_PREC : placeholder->precision;
	str_value = ftoa(value, placeholder->precision);
	override_placeholder(placeholder, str_value);
	has_sign = ((placeholder->flag & g_flag[PLUS].code) ||
			(placeholder->flag & g_flag[SPACE].code));
	get_alignment_params(align_params, placeholder, str_value, has_sign);
	fill_string(vec, placeholder, align_params, str_value);
}
