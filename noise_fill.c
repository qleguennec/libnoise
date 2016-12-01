/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 01:48:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 02:10:54 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise_intern.h"

static void	next_cell(t_noise_u32 *n, unsigned int *dims)
{
	size_t			dim;

	dim = 0;
	while (dim < NOISE_DIM)
	{
		if ((*n)[dim] >= dims[dim])
		{
			(*n)[dim] = 0;
			(*n)[dim + 1]++;
		}
		dim++;
	}
}

void		noise_fill(t_noise *n, void *arr, size_t nel)
{
	size_t			i;
	t_noise_u32		cell;
	unsigned char	*s;

	i = 0;
	s = arr;
	while (i < NOISE_DIM)
		cell[i++] = 0;
	i = 0;
	while (i < nel)
	{
		next_cell(&cell, (unsigned int *)n->dim);
		*(t_noise_unit *)s = noise(n, (t_noise_unit *)cell);
		s += sizeof(t_noise_val);
		i++;
	}
}
