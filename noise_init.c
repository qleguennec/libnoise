/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 01:38:56 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 01:42:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include <time.h>

void
noise_init
	(t_noise *n
	 , unsigned int nseeds)
{
	srand(time(NULL));
	while (!noise_init_k(n, nseeds, rand()))
		;
}
