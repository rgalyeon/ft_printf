/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:10:03 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/15 23:33:23 by rgalyeon         ###   ########.fr       */
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
	long long int width;
	int precision;
	u_int8_t length;
	u_int8_t type;
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

# define MINUS	(t_flag){'-', 0b00000001u}
# define PLUS	(t_flag){'+', 0b00000010u}
# define SPACE	(t_flag){' ', 0b00000100u}
# define ZERO	(t_flag){'0', 0b00001000u}
# define HASH	(t_flag){'#', 0b00010000u}

# define FLAGS(i) ((t_flag[5]){MINUS, PLUS, SPACE, ZERO, HASH})[i]

/**
**
** @param format
** @param ...
** @return
*/

# define LENGTH_LONG_LONG			0b00000001u
# define LENGTH_LONG				0b00000010u
# define LENGTH_SHORT				0b00000100u
# define LENGTH_CHAR				0b00001000u
# define LENGTH_LONG_LONG_DOUBLE	0b00010000u

# define _L		(t_flag){'l', LENGTH_LONG}
# define _S		(t_flag){'h', LENGTH_SHORT}
# define _LLD	(t_flag){'L', LENGTH_LONG_LONG_DOUBLE}

# define LENGTH(i) ((t_flag[3]){_L, _S, _LLD})[i]

# define TYPE		"diouxXcsp"
# define N_TYPES	9

int				ft_printf(const char *format, ...);
int				ft_vfprintf(int fd, const char *format, va_list arg_ptr);
char			*parse_placeholder(char **format, int *size, va_list arg_ptr);


#endif
