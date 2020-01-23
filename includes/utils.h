/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:04:14 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/23 17:17:46 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# define DBL_MANTISSA_BITS	52u
# define DBL_EXPONENT_BITS	11u
# define DBL_BIAS			1023u
# define LARGER				1
# define EQUAL				0
# define LESS				-1
# define MAX_SIZE			10000
# define C2INT(c)		((!c) ? 0 : c - '0')
# define INT2C(c)		c + '0'
# define MAX_EXPONENT	2047
# define NAN_V			"NaN"
# define INF			"inf"
# define ZERO_V			"0"

typedef struct	s_double64
{
	uint64_t	mantissa : DBL_MANTISSA_BITS;
	uint64_t	exponent : DBL_EXPONENT_BITS;
	uint64_t	sign : 1;
}				t_double64;

typedef union	u_conv
{
	double		d;
	t_double64	u;
}				t_conv;

typedef struct	s_bignum
{
	int			size;
	char		*value;
}				t_bignum;

typedef struct	s_decimal
{
	uint64_t	mantissa;
	int			exponent;
	uint8_t		sign;
}				t_decimal;

/**
** Init functions
*/

t_bignum	*int2bignum(__int128 num);
t_bignum	*str2bignum(char *num, u_int8_t flag_reverse);
void		del_bignum(t_bignum **num);

/**
** Arithmetic operations
*/

t_bignum	 *bignum_add(t_bignum *n1, t_bignum *n2);
t_bignum	*bignum_mul(t_bignum *n1, t_bignum *n2);
t_bignum	*bignum_pow(t_bignum *num, uint64_t p);

/**
** Compare operations
*/

int8_t		bignum_cmp(t_bignum *n1, t_bignum *n2);
void		print_bignum(t_bignum *num, int e);

#endif
