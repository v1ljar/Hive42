#pragma once

#include "Data.hpp"
#include <iostream>

class Serialization
{
	private:
		Serialization() = delete;
		Serialization(const Serialization& other) = delete;
		Serialization& operator=(const Serialization& other) = delete;
		~Serialization() = delete;
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};