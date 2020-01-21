/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:32:32 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:53:24 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @param placeholder
*/

static void	get_alignment_params(int align_params[3], t_ph *placeholder)
{
	const int len = 1;

	align_params[PAD] = (int)max2(0, (int)placeholder->width - len);
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param ph - placeholder
** @param align_params - array with padding params
** @param row_char
*/

static void	fill_string(t_vec **vec, t_ph *ph,
									int *align_params, const char row_char)
{
	const t_bool	has_left_padding = (ph->flag & g_flag[MINUS].code);
	const char		fill_char = (ph->flag & g_flag[ZERO].code) ? '0' : ' ';

	if (!has_left_padding)
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, fill_char);
	*vec = ft_vec_push(vec, row_char);
	if (has_left_padding)
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, ' ');
}

/*
** Function disable conflicting placeholder's parameters for c type
** @param placeholder
** @param value - given value
*/

static void	override_placeholder(t_ph *placeholder)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->flag & g_flag[MINUS].code)
		placeholder->flag &= ~(g_flag[ZERO].code);
}

void		processing_c(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	char	row_char;
	int		align_params[3];

	row_char = (placeholder->type == 'c') ? (char)va_arg(arg_ptr, int) :
														(char)placeholder->type;
	ft_memset(align_params, 0, sizeof(align_params));
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder);
	fill_string(vec, placeholder, align_params, row_char);
}
