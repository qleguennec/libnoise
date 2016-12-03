#include "libnoise.h"

float
lerp
	(local float2 edges
	 , local float x)
{
	return (edges * (float2){1.0 - x, x});
}

float
dot_gradient
	(global constant float2 *grads
	 , global constant uint ngrads
	 , local float seed
	 , local int2	n
	 , local float2 x)
{
	float2	grad;
	float2	d;

	seed *= x.x + x.y;
	if (seed < 0)
		seed = - seed;
	grad = grads[(int)seed % ngrads];
	d = x - n;
	d *= grad;
	return (d.x + d.y);
}

kernel void
noise2
	(global constant float *dest
	 , global constant float2 *src
	 , global constant float2 *grads
	 , global constant uint ngrads,
	 , global constant float seed)
{
	float2	d;
	float2	x;
	float2	e0;
	float2	e1;
	int2	i;
	int2	n00;
	int2	n01;
	int2	n10;
	int2	n11;
	uint	id;

	id = get_local_id{0} * get_local_id{1};
	x = src[id];
	out = data + get_local_id(0) * get_local_id(1);
	n0 = as_int2(x);
	n01 = n0 + (int2){0, 1};
	n10 = n0 + (int2){1, 0};
	n11 = n0 + (int2){1, 1};
	d = *out - n0;
	e0.x = dot_gradient(grads, ngrads, seed, n00, x);
	e0.y = dot_gradient(grads, ngrads, seed, n10, x);
	e1.x = dot_gradient(grads, ngrads, seed, n01, x);
	e1.y = dot_gradient(grads, ngrads, seed, n11, x);
	i = (float2){lerp(e0, d.x), lerp(e1, d.x)};
	dest[id] = lerp(i, d.y);
}
