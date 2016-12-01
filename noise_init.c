/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:59:17 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/30 22:53:49 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"
#include <limits.h>

static size_t	fill
	(t_noise *n
	 , t_noise_val x)
{
	size_t			i;
	unsigned int	j;
	unsigned long	h;

	j = 0;
	i = 0;
	h = (unsigned long)x[0] * n->k % n->p % n->ngrads;
	while (i < NOISE_DIM)
	{
		if (n->grads[h][i])
		{
			i = 0;
			j++;
			h = (h + j * j) % n->ngrads;
		}
		else
			i++;
	}
	i = 0;
	while (i < NOISE_DIM)
	{
		n->grads[h][i] = x[i];
		i++;
	}
	return (j);
}

static size_t		fill_grads
	(t_noise *n
	 , unsigned int nfill)
{
	size_t			i;
	size_t			j;
	t_noise_val		x;
	unsigned int	cols;
	unsigned int	r;

	i = 0;
	cols = 0;
	while (i < nfill)
	{
		j = 0;
		while (j < NOISE_DIM)
		{
			r = rand();
			x[j] = r / (r + 1);
			j++;
		}
		cols += fill(n, x);
	}
	return (cols);
}

size_t				noise_init
	(t_noise *n
	 , unsigned int nseeds)
{
	size_t			cols;
	unsigned int	step;
	unsigned long	seed;

	if (((unsigned int)RAND_MAX - 1) % nseeds)
		return (-1);
	if (n->ngrads % nseeds)
		return (-1);
	step = (RAND_MAX - 1) / nseeds;
	seed = step;
	cols = 0;
	while (seed < (unsigned int)UINT_MAX - 1)
	{
		srand(seed);
		cols += fill_grads(n, n->ngrads / nseeds);
		seed += step;
	}
	return (cols);
}
