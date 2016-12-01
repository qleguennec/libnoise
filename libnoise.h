/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnoise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:50:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 07:54:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNOISE_H
# define LIBNOISE_H

# ifndef NOISE_VAL_TYPE
#  define NOISE_VAL_TYPE float
# endif

# ifndef NOISE_DIM
#  define NOISE_DIM 2
# endif

# define NOISE_DIM_2		NOISE_DIM * NOISE_DIM

# if (NOISE_DIM == 2)
#  define NEIGHBOURS		{{0, 1}, {0, -1}, {1, 0}, {1, -1}}
# endif

# include <stdlib.h>

typedef NOISE_VAL_TYPE	t_noise_unit;
typedef NOISE_VAL_TYPE	t_noise_val[NOISE_DIM];
typedef unsigned int	t_noise_u32[NOISE_DIM];
typedef int				t_noise_i32[NOISE_DIM];

typedef struct			s_noise
{
	t_noise_val			*grads;
	int					*used;
	unsigned int		ngrads;
	unsigned int		dim[NOISE_DIM];
	unsigned int		k;
	double				seed;
}						t_noise;

size_t					noise_init(t_noise *n, unsigned int nseeds);
t_noise_unit			noise(t_noise *n, t_noise_val x);
void					noise_fill
	(t_noise *n, t_noise_unit scale, void *arr, size_t nel);

#endif
