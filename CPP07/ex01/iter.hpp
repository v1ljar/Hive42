#pragma once

#include <cstddef>

template<typename A, typename F>
void iter(A* array, const size_t len, F func)
{
	if (!array)
		return ;
	for (size_t i = 0; i < len; i++)
		func(array[i]);
}
