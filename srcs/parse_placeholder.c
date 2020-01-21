/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_placeholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 22:47:47 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/21 16:01:27 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** function parse "#-+ 0" flags
** @param placeholder
** @param format - given string
*/

static void	parse_flags(t_ph *placeholder, char **format)
{
	u_int8_t	i;

	i = 0;
	while (i < 5)
	{
		if (**format == g_flag[i].symbol)
		{
			placeholder->flag |= g_flag[i].code;
			(*format)++;
			i = 0;
		}
		else
			++i;
	}
}

/*
** @param placeholder
** @param format - given string
** @param arg_ptr - va_list
** @return width if value occurs or  -1 if width is not given
*/

static int	parse_width(t_ph *placeholder, char **format, va_list arg_ptr)
{
	int		width;

	width = -1;
	while (ft_isdigit(**format) || (**format == '*'))
	{
		if (ft_isdigit(**format))
		{
			width = ft_atoi(*format);
			*format += ft_int_len(width);
		}
		else
		{
			width = va_arg(arg_ptr, int);
			if (width < 0)
			{
				placeholder->flag |= g_flag[MINUS].code;
				width *= -1;
			}
			(*format)++;
		}
	}
	return (width);
}

/*
** Parse value after '.' and update width if needed
** @param placeholder
** @param format - given string
** @param arg_ptr - va_list
** @return precision
*/

static int	parse_precision(t_ph *placeholder, char **format, va_list arg_ptr)
{
	int	precision;

	if (**format != '.')
		return (-1);
	precision = 0;
	(*format)++;
	if (ft_isdigit(**format))
	{
		precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	else if (**format == '*')
	{
		if ((precision = va_arg(arg_ptr, int)) < 0)
		{
			placeholder->width = (unsigned int)precision * -1;
			placeholder->flag |= g_flag[MINUS].code;
			precision = -1;
		}
		(*format)++;
	}
	placeholder->width = (ft_isdigit(**format) || (**format == '*')) ?
			parse_width(placeholder, format, arg_ptr) : placeholder->width;
	return (precision);
}

/*
** TODO: think about parse something after length
** @param placeholder
** @param format - given string
*/

static void	parse_length(t_ph *placeholder, char **format)
{
	int			i;
	u_int8_t	length;
	char		length_symbol;

	i = 0;
	length = 0;
	while (i < 3)
	{
		length_symbol = g_length[i].symbol;
		if (**format == length_symbol)
		{
			(*format)++;
			if (length_symbol == 'l' && **format == 'l' && ((*format)++))
				length |= LENGTH_LONG_LONG;
			else if (length_symbol == 'h' && **format == 'h' && ((*format)++))
				length |= LENGTH_CHAR;
			else
				length |= g_length[i].code;
			i = 0;
		}
		else
			i++;
	}
	placeholder->length = length;
}

/*
** function parse placeholder's params and handle given type
** @param vec - formatted string (vector)
** @param format - given string
** @param size - pointer to output string size
** @param arg_ptr - va_list
*/

void		parse_placeholder(t_vec **vec, char **format, int *size,
															va_list arg_ptr)
{
	t_ph *placeholder;

	if (!(placeholder = (t_ph *)ft_memalloc(sizeof(t_ph))))
	{
		*size = -1;
		return ;
	}
	parse_flags(placeholder, format);
	placeholder->width = parse_width(placeholder, format, arg_ptr);
	placeholder->precision = parse_precision(placeholder, format, arg_ptr);
	parse_length(placeholder, format);
	placeholder->type = **format;
	(*format) += **format == 0 ? 0 : 1;
	processing_types(vec, placeholder, arg_ptr);
	free(placeholder);
}
