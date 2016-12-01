/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:43:08 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 08:55:40 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"
#include <limits.h>

static void
get_neighbours
	(t_noise_u32 *neighbours
	 , t_noise_val x)
{
	size_t				i;
	size_t				j;
	static t_noise_i32	iter[NOISE_DIM_2] = NEIGHBOURS;

	i = 0;
	while (i < NOISE_DIM_2)
	{
		j = 0;
		while (j < NOISE_DIM)
		{
			neighbours[i][j] = iter[i % NOISE_DIM_2][j] + x[j];
			j++;
		}
		i++;
	}
}

static t_noise_unit
dot_dist_grad
	(t_noise *n
	 , t_noise_val x
	 , t_noise_u32 y)
{
	t_noise_unit	*grad;
	t_noise_unit	ret;
	t_noise_val		dist;
	unsigned int	i;
	double			hash;

	i = 0;
	while (i < NOISE_DIM)
	{
		dist[i] = x[i] - (t_noise_unit)y[i];
		i++;
	}
	i = 0;
	hash = n->seed;
	while (i < NOISE_DIM)
		hash *= x[i++];
	grad = n->grads[HASH(hash)];
	i = 0;
	ret = 0;
	while (i < NOISE_DIM)
	{
		ret += dist[i] * grad[i];
		i++;
	}
	return (ret);
}

static t_noise_unit
lerp
	(t_noise_unit x0
	 , t_noise_unit x1
	 , t_noise_unit x)
{
	t_noise_unit	c;

	c = (x - x0)/(x1 - x0);
	if (c > 1)
		c = 1;
	if (c < 0)
		c = 0;
	c = c * c * c * (c * (c * 6 - 15) + 10);
	return (x0 + c * x0 + x * x1);
}

static t_noise_unit
dot_lerp
	(t_noise *n
	 , t_noise_u32 *neighbours
	 , t_noise_val weights
	 , t_noise_val x)
{
	t_noise_unit	tmp[NOISE_DIM_2];
	unsigned int	i;

	i = 0;
	while (i < NOISE_DIM_2)
	{
		tmp[i] = dot_dist_grad(n, x, neighbours[i]);
		i++;
	}
	i = 0;
	while (i < NOISE_DIM_2)
	{
		tmp[i] = lerp(tmp[i], tmp[i + 1], weights[i % NOISE_DIM]);
		i += 2;
	}
	i = 0;
	while (i < NOISE_DIM)
	{
		tmp[i] = lerp(tmp[i], tmp[i + 1], weights[i % NOISE_DIM]);
		i++;
	}
	return (tmp[0]);
}

t_noise_unit
noise
	(t_noise *n
	 , t_noise_val x)
{
	t_noise_u32		neighbours[NOISE_DIM_2];
	t_noise_val		weights;
	unsigned int	i;

	get_neighbours(neighbours, x);
	i = 0;
	while (i < NOISE_DIM)
	{
		weights[i] = x[i] - (int)x[i];
		i++;
	}
	return (dot_lerp(n, neighbours, weights, x));
}
