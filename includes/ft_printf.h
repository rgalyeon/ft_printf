/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:10:03 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/23 15:55:33 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "utils.h"

# define DEFAULT_PREC 6

/*
** Structure for printf's placeholder
** Example: %[flag][width][.precision][length]type
*/

typedef u_int8_t	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct		s_ph
{
	u_int8_t		flag;
	int				width;
	int				precision;
	u_int8_t		length;
	u_int8_t		type;
}					t_ph;

/*
** Flags field
** https://en.wikipedia.org/wiki/Printf_format_string
*/

typedef struct		s_flag
{
	char		symbol;
	u_int8_t	code;
}					t_flag;

static t_flag g_flag[] =
{
	{'-', 0b00000001u},
	{'+', 0b00000010u},
	{' ', 0b00000100u},
	{'0', 0b00001000u},
	{'#', 0b00010000u},
};

# define MINUS	0
# define PLUS	1
# define SPACE	2
# define ZERO	3
# define HASH	4

/*
** Length field
*/

# define LENGTH_LONG_LONG			0x1u
# define LENGTH_LONG				0x2u
# define LENGTH_SHORT				0x4u
# define LENGTH_CHAR				0x8u
# define LENGTH_LONG_DOUBLE			0x10u

static t_flag		g_length[] =
{
	{'l', LENGTH_LONG},
	{'h', LENGTH_SHORT},
	{'L', LENGTH_LONG_DOUBLE}

};

/*
** Defines for type
*/

typedef struct		s_type
{
	char			type;
	void			(*function)(t_vec **, t_ph *placeholder, va_list args);
}					t_type;

# define TYPE	"diouxXcspf"
# define CHAR	6

/*
** Parameters for alignment
*/

# define FULL_SIZE	0
# define ZERO_PAD	1
# define PAD		2

/*
** Main functions
*/

int					ft_printf(const char *format, ...);
int					ft_vfprintf(int fd, const char *format, va_list arg_ptr);
void				parse_placeholder(t_vec **vec, char **format, int *size,
															va_list arg_ptr);
void				processing_types(t_vec **vec, t_ph *placeholder, va_list
																	arg_ptr);

/*
** Types processing functions
*/

void				processing_di(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_u(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_x(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_c(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_s(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_p(t_vec **vec, t_ph *pholder, va_list arg_ptr);
void				processing_f(t_vec **vec, t_ph *pholder, va_list arg_ptr);

static t_type		g_type[] =
{
	{'d', processing_di},
	{'i', processing_di},
	{'o', processing_x},
	{'u', processing_u},
	{'x', processing_x},
	{'X', processing_x},
	{'c', processing_c},
	{'s', processing_s},
	{'p', processing_p},
	{'f', processing_f}
};

/*
** Utils for project
*/

__int128			max2(__int128 a, __int128 b);
int					ft_uint_len(__int128 nb);
char				*ft_itoa_base(__int128 val, int base);

/*
** Utils for development
** TODO: delete when project is done
*/

void				print_placeholder(t_ph *placeholder);

#endif
