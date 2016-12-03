/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_init_k.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:59:17 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 01:43:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include "../libft/malloc.h"
#include "../libft/libft.h"
#include <limits.h>

static int
fill
	(t_noise *n
	 , cl_float2 x
	 , unsigned int k
	 , int *used)
{
	size_t	h;

	h = (size_t)((x.x + x.y) * k) % n->ngrads;
	if (used[h])
		return (0);
	n->grads[h].x = x.x;
	n->grads[h].y = x.y;
	return (1);
}

static int
fill_grads
	(t_noise *n
	 , size_t nfill
	 , unsigned int k)
{
	cl_float2		x;
	int				*used;
	size_t			i;

	i = 0;
	MALLOC_ZERO_N(used, n->ngrads);
	while (i < nfill)
	{
		x.x = rand() / (float)RAND_MAX;
		x.y = rand() / (float)RAND_MAX;
		if (!fill(n, x, k, used))
			return (0);
		i++;
	}
	free(used);
	return (1);
}

int
noise_init_k
	(t_noise *n
	 , unsigned int nseeds
	 , unsigned int k)
{
	unsigned int	seed;
	unsigned int	step;

	if (n->ngrads % nseeds)
		return (0);
	if (!n->grads)
		MALLOC_ZERO_N(n->grads, n->ngrads);
	step = (RAND_MAX - 1) / nseeds;
	seed = step;
	while (nseeds)
	{
		srand(seed);
		if (!fill_grads(n, n->ngrads / nseeds, k))
			return (0);
		seed += step;
		nseeds--;
	}
	return (1);
}
