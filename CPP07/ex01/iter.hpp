#pragma once

template<typename A, typename V, typename F>
void iter(A* array, const V& len, F& func)
{
	if (!(len > 0))
		return ;
	for (int i = 0; i < len; i++)
	{
		array[0][i] = (func)(array[0][i]);
	}
}

template<typename A, typename V, typename F>
void iter(A* array, const V& len, const F& func)
{
	if (!(len > 0))
		return ;
	for (int i = 0; i < len; i++)
	{
		array[0][i] = (func)(array[0][i]);
	}
}
