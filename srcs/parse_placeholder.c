/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_placeholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 22:47:47 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/19 22:18:40 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void parse_flags(t_ph *placeholder, char **format)
{
	u_int8_t	i;

	i = 0;
	while (i < 5)
	{
		if (**format == FLAGS(i).symbol)
		{
			placeholder->flag |= FLAGS(i).code;
			(*format)++;
			i = 0;
		}
		else
			++i;
	}
}

//TODO Test width
/**
**
** @param placeholder
** @param format - given string
** @param arg_ptr - va_list
** @return -1 если ширина не указывалась
*/

static int parse_width(t_ph *placeholder, char **format, va_list arg_ptr)
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
				placeholder->flag |= MINUS.code;
				width *= -1;
			}
			(*format)++;
		}
	}
//	if (ft_isdigit(**format))
//	{
//		width = ft_atoi(*format);
//		*format += ft_int_len(width);
//	}
//	if (**format == '*')
//	{
//		width = va_arg(arg_ptr, int);
//		if (width < 0)
//		{
//			placeholder->flag |= MINUS.code;
//			width *= -1;
//		}
//		(*format)++;
//	}
//	if (ft_isdigit(**format))
//	{
//		width = ft_atoi(*format);
//		*format += ft_int_len(width);
//	}
	return (width);
}

/**
 * Parse value after '.' and update width if needed
 * @param placeholder
 * @param format - given string
 * @param arg_ptr - va_list
 * @return
 */

static int	parse_precision(t_ph *placeholder, char **format, va_list arg_ptr)
{
	int 	precision;

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
			placeholder->flag |= MINUS.code;
			precision = -1;
		}
		(*format)++;
	}
	placeholder->width = (ft_isdigit(**format) || (**format == '*')) ?
			parse_width(placeholder, format, arg_ptr) : placeholder->width;
	return (precision);
}

/**
 * TODO: think about parse something after length
 * @param placeholder
 * @param format
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
		length_symbol = LENGTH(i).symbol;
		if (**format == length_symbol)
		{
			(*format)++;
			if (length_symbol == 'l' && **format == 'l' && ((*format)++))
				length |= LENGTH_LONG_LONG;
			else if (length_symbol == 'h' && **format == 'h' && ((*format)++))
				length |= LENGTH_CHAR;
			else
				length |= LENGTH(i).code;
			i = 0;
		}
		else
			i++;
	}
	placeholder->length = length;
}

static void parse_type(t_ph *placeholder, char **format)
{
	placeholder->type = **format;
	(*format) += **format == 0 ? 0 : 1;
}

void		parse_placeholder(t_vec **vec, char **format, int *size, va_list
																		arg_ptr)
{
	t_ph *placeholder;

	if (!(placeholder = (t_ph *)ft_memalloc(sizeof(t_ph))))
		exit(MALLOC_ERR);
	parse_flags(placeholder, format);
	placeholder->width = parse_width(placeholder, format, arg_ptr);
	placeholder->precision = parse_precision(placeholder, format, arg_ptr);
	parse_length(placeholder, format);
	parse_type(placeholder, format);
	processing_types(vec, placeholder, arg_ptr);
}
