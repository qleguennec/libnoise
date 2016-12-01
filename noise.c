/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:43:08 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 06:37:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"
#include <limits.h>

static void
get_neighbours
	(t_noise_u32 *neighbours
	 , t_noise_val x)
{
	t_noise_i32		iter;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < NOISE_DIM)
		iter[i++] = 0;
	i = 0;
	while (i < NOISE_DIM_2)
	{
		j = i % 3;
		if (iter[j] == 0)
			iter[j] = 1;
		else if (iter[j] == 1)
			iter[j] = -1;
		else if (iter[j] == -1)
			iter[j] = 0;
		j = 0;
		while (j < NOISE_DIM)
		{
			if (iter[j] == -1 && x[j] <= 1.0)
				neighbours[i][j] = 0;
			else
				neighbours[i][j] = iter[j] + (unsigned int)x[j];
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
	hash = 1;
	while (i < NOISE_DIM)
		hash *= (x[i++]);
	hash *= n->seed;
	grad = n->grads[HASH(hash)];
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
	x = (x - x0)/(x1 - x0);
	if (x < x0)
		x = x0;
	else if (x > x1)
		x = x1;
	return (x * x * (3 - 2 * x));
}

static t_noise_unit
dot_lerp
	(t_noise *n
	 , t_noise_u32 *neighbours
	 , t_noise_val weights
	 , t_noise_val x)
{
	t_noise_unit	tmp[NOISE_DIM_2];
	t_noise_unit	l0;
	t_noise_unit	l1;
	unsigned int	i;

	i = 0;
	while (i < NOISE_DIM_2)
	{
		tmp[i] = dot_dist_grad(n, x, neighbours[i]);
		i++;
	}
	l0 = lerp(tmp[0], tmp[1], weights[0]);
	i = 1;
	while (i < NOISE_DIM)
	{
		l1 = lerp(tmp[i], tmp[i + 1], weights[i - 1]);
		l0 = lerp(l0, l1, weights[i - 1]);
		i++;
	}
	return (l0);
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
