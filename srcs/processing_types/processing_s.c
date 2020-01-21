/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 11:51:19 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:55:46 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @param placeholder
** @param row_str - string from va_list
*/

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
		const char *row_str)
{
	int len;

	len = ft_strlen(row_str);
	if (placeholder->precision != -1)
		len = (placeholder->precision < len ? placeholder->precision : len);
	align_params[FULL_SIZE] = (int)max2(placeholder->width, len);
	align_params[PAD] = (int)max2(0, (int)placeholder->width - len);
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param ph - placeholder
** @param align_params - array with padding params
** @param row_str - string from va_list
*/

static void	fill_string(t_vec **vec, t_ph *ph,
		int *align_params, const char *row_str)
{
	int				len;
	const t_bool	has_left_padding = (ph->flag & g_flag[MINUS].code);
	const char		fill_char = (ph->flag & g_flag[ZERO].code) ? '0' : ' ';

	len = align_params[FULL_SIZE] - align_params[PAD];
	if (!has_left_padding)
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, fill_char);
	while (len--)
		*vec = ft_vec_push(vec, *row_str++);
	if (has_left_padding)
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
}

/*
** Function disable conflicting placeholder's parameters for s type
** @param placeholder
*/

static void	override_placeholder(t_ph *placeholder)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->flag & g_flag[MINUS].code)
		placeholder->flag &= ~(g_flag[ZERO].code);
}

void		processing_s(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	char		*row_string;
	int			align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	row_string = va_arg(arg_ptr, char *);
	if (row_string == NULL)
		row_string = "(null)";
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder, row_string);
	fill_string(vec, placeholder, align_params, row_string);
}
