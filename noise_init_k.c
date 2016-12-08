/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_init_k.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:59:17 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/08 15:15:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include "../libft/malloc.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>

#define MODULUS		2147483647
#define MULTIPLIER	48271
#define SEED		123456789
#define Q			(MODULUS / MULTIPLIER)
#define R			(MODULUS % MULTIPLIER)

static float
	next_rand
	(int *seed)
{
	const static int		q = MODULUS / MULTIPLIER;
	const static int		r = MODULUS % MULTIPLIER;
	int						t;

	t = MULTIPLIER * (*seed % q) - r * (*seed / q);
	if (t <= 0)
		*seed = t + MODULUS;
	else
		*seed = t;
	return ((float)*seed / MODULUS);
}

static void
	fill_grads
	(cl_float2 *xs
	, size_t nfill)
{
	int				seed;
	size_t			i;

	i = 0;
	seed = SEED;
	while (i < nfill)
	{
		xs[i].x = next_rand(&seed);
		xs[i].y = next_rand(&seed);
		i++;
	}
}

void
	noise_init
	(t_noise *n)
{
	MALLOC0_N(n->grads, n->ngrads);
	fill_grads(n->grads, n->ngrads);
}
