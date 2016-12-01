/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:43:08 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 01:48:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"

static void
get_neighbour
	(t_noise_u32 *neighbour
	 , t_noise_val x
	 , unsigned int sign)
{
	unsigned int	j;

	j = 0;
	while (j < NOISE_DIM)
	{
		if (j % 2)
			(*neighbour)[j] = (unsigned int)x[j];
		else
			(*neighbour)[j] = (sign ? -1 : 1) + (unsigned int)x[j];
		j++;
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
	unsigned long	hash;

	i = 0;
	while (i < NOISE_DIM)
	{
		dist[i] = x[i] - (t_noise_unit)y[i];
		i++;
	}
	i = 0;
	hash = 1;
	while (i < NOISE_DIM)
		hash *= y[i++];
	grad = n->grads[hash];
	ret = 0;
	while (i < NOISE_DIM)
	{
		ret = dist[i] * grad[i];
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

	i = 0;
	while (i < NOISE_DIM_2)
	{
		get_neighbour(&neighbours[i], x, i % 2);
		i++;
	}
	i = 0;
	while (i < NOISE_DIM)
	{
		weights[i] = x[i] - (int)x[i];
		i++;
	}
	return (dot_lerp(n, neighbours, weights, x));
}
