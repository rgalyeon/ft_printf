/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:10:03 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/19 19:27:17 by rgalyeon         ###   ########.fr       */
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

typedef u_int8_t t_bool;

# define TRUE 1
# define FALSE 0

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

typedef char *(*t_ptr)(t_vec **vec, t_ph *placeholder, va_list arg_ptr);

# define _DI processing_di
# define _X processing_x
# define _U processing_u
# define _C processing_c
# define _STR processing_s
# define _P processing_p

# define CHAR 6

# define _PROCESSING_TYPE(i) {_DI, _DI, _X, _U, _X, _X, _C, _STR, _P}[i]
# define PROCESSING_TYPE(i, v, ph, va) (t_ptr[9])_PROCESSING_TYPE(i)(v, ph, va)

/**
** Parameters for alignment
*/

# define FULL_SIZE	align_params[0]
# define ZERO_COUNT	align_params[1]
# define PADDING	align_params[2]



int				ft_printf(const char *format, ...);
int				ft_vfprintf(int fd, const char *format, va_list arg_ptr);
void			parse_placeholder(t_vec **vec, char **format, int *size,
															va_list arg_ptr);
void			processing_types(t_vec **vec, t_ph *placeholder, va_list
arg_ptr);

/**
** Types processing functions
*/

char			*processing_di(t_vec **vec, t_ph *placeholder, va_list arg_ptr);
char			*processing_u(t_vec **vec, t_ph *placeholder, va_list arg_ptr);
char			*processing_x(t_vec **vec, t_ph *placeholder, va_list arg_ptr);
char			*processing_c(t_vec **vec, t_ph *placeholder, va_list arg_ptr);
char			*processing_s(t_vec **vec, t_ph *placeholder, va_list arg_ptr);
char			*processing_p(t_vec **vec, t_ph *placeholder, va_list arg_ptr);

/**
** Utils for project
*/

__int128		max3(__int128 a, __int128 b, __int128 c);
__int128		max2(__int128 a, __int128 b);
int				ft_uint_len(__int128 nb);
char			*ft_itoa_base(__int128 val, int base);

/**
** Utils for development
** TODO: delete when project is done
**/

void	print_placeholder(t_ph *placeholder);

#endif
