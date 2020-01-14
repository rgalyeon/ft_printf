/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:10:03 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/14 20:31:30 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/**
** Structure for printf's placeholder
** Example: %[flag][width][.precision][length]type
*/

typedef struct	s_ph
{
	u_int8_t flag;
	int width;
	int precision;
	int length;
	int type;
}				t_ph;

/**
** Flags field
** https://en.wikipedia.org/wiki/Printf_format_string
*/

typedef struct s_flag
{
	char		symbol;
	u_int8_t 	code;
}				t_flag;

# define MINUS	(t_flag){'-', 0b00000001}
# define PLUS	(t_flag){'+', 0b00000010}
# define SPACE	(t_flag){' ', 0b00000100}
# define ZERO	(t_flag){'0', 0b00001000}
# define HASH	(t_flag){'#', 0b00010000}

# define FLAGS(i) ((t_flag[5]){MINUS, PLUS, SPACE, ZERO, HASH})[i]

int				ft_printf(const char *format, ...);
int				ft_vfprintf(int fd, const char *format, va_list arg_ptr);
char			*parse_placeholder(char **format, int *size, va_list arg_ptr);


#endif
