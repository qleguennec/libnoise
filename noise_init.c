/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:59:17 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 06:29:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"
#include "../libft/malloc.h"
#include "../libft/libft.h"
#include <limits.h>

static size_t	fill
	(t_noise *n
	 , t_noise_val x)
{
	size_t			i;
	size_t			cols;
	unsigned int	j;
	double			hash;
	unsigned long	h;

	j = 0;
	i = 0;
	cols = 0;
	hash = 1;
	while (i < NOISE_DIM)
		hash += x[i++];
	h = HASH(hash);
	i = 0;
	while (i < NOISE_DIM)
	{
		if (n->used[h])
		{
			i = 0;
			j++;
			cols++;
			h = (h + j * j) % n->ngrads;
		}
		else
		{
			i++;
			n->used[j] = 1;
			j = 0;
		}
	}
	i = 0;
	while (i < NOISE_DIM)
	{
		n->grads[h][i] = x[i];
		i++;
	}
	return (cols);
}

static size_t		fill_grads
	(t_noise *n
	 , unsigned int nfill)
{
	size_t			i;
	size_t			j;
	t_noise_val		x;
	unsigned int	cols;

	i = 0;
	cols = 0;
	while (i < nfill)
	{
		j = 0;
		while (j < NOISE_DIM)
		{
			x[j] = rand() / (t_noise_unit)RAND_MAX;
			j++;
		}
		i++;
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

	if (n->ngrads % nseeds)
		return (-1);
	if (!n->grads)
		MALLOC_N(n->grads, n->ngrads);
	if (!n->used)
		MALLOC_N(n->used, n->ngrads);
	ft_bzero(n->grads, n->ngrads * sizeof(*n->grads));
	ft_bzero(n->used, n->ngrads * sizeof(*n->used));
	step = (RAND_MAX - 1) / nseeds;
	seed = step;
	cols = 0;
	while (nseeds)
	{
		srand(seed);
		cols += fill_grads(n, n->ngrads / nseeds);
		seed += step;
		nseeds--;
	}
	return (cols);
}
