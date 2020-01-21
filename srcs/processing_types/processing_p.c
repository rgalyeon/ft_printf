/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 21:37:02 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:44:46 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function disable conflicting placeholder's parameters for p type
** @param placeholder
*/

static void	override_placeholder(t_ph *placeholder)
{
	placeholder->flag |= g_flag[HASH].code;
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 ||
									(placeholder->flag & g_flag[MINUS].code))
		placeholder->flag &= ~(g_flag[ZERO].code);
	placeholder->flag &= ~(g_flag[PLUS].code | g_flag[SPACE].code);
}

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @value - int value from va_list
** @converted_value - string hex value
** @param placeholder
*/

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
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
		align_params[PAD] -= 2;
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param placeholder
** @param align_params - array with padding params
** @param converted_value - string hex value
*/

static void	fill_string(t_vec **vec, t_ph *placeholder, int *align_params,
		char *converted_value)
{
	if (!(placeholder->flag & g_flag[MINUS].code) &&
									!(placeholder->flag & g_flag[ZERO].code))
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
	if (placeholder->flag & g_flag[HASH].code)
		*vec = ft_vec_string_push(vec, "0x");
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

void		processing_p(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	__uint128_t	value;
	char		*converted_value;
	int			align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	value = (size_t)va_arg(arg_ptr, void *);
	if (!(converted_value = ft_itoa_base(value, 16)))
		return ;
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder, value, converted_value);
	fill_string(vec, placeholder, align_params, converted_value);
	free(converted_value);
}
