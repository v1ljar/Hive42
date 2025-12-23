#pragma once

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
// #include <bits/stdc++.h>

template<typename T>
void easyfind(T array, int nbr)
{
	if (array.empty())
		throw std::invalid_argument("Array cannot be empty!");

	std::vector<int>::iterator res;
	res = find(array.begin(), array.end(), nbr);
	if (res != array.end())
		std::cout << "Found integer " << nbr << " in the given array in position: " << distance(array.begin(), res) << "\n";
	else
		throw std::out_of_range("Integer not found in the givern array!");
}
