static float
	lerp
	(float2 edges
	 , float x)
{
	edges *= (float2){1.0 - x, x};
	return (edges.x + edges.y);
}

static float
	dot_gradient
	(global float2 *grads
	 , uint ngrads
	 , float seed
	 , int2	n
	 , float2 x)
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
	(global float *dest
	 , global float2 *src
	 , global float2 *grads
	 , uint ngrads
	 , float seed)
{
	float2	d;
	float2	e0;
	float2	e1;
	float2	x;
	int2	n00;
	int2	n01;
	int2	n10;
	int2	n11;
	uint	id;

	id = (uint)get_global_id(0) * (uint)get_global_id(1);
	x = src[id];
	n00.x = x.x;
	n00.y = x.y;
	n01 = n00 + (int2){0, 1};
	n10 = n00 + (int2){1, 0};
	n11 = n00 + (int2){1, 1};
	d = x - n00;
	e0.x = dot_gradient(grads, ngrads, seed, n00, x);
	e0.y = dot_gradient(grads, ngrads, seed, n10, x);
	e1.x = dot_gradient(grads, ngrads, seed, n01, x);
	e1.y = dot_gradient(grads, ngrads, seed, n11, x);
	x = (float2){lerp(e0, d.x), lerp(e1, d.x)};
	dest[id] = lerp(x, d.y);
}
