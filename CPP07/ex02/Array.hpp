
#pragma once
#include <stdexcept>

template <typename T>
class Array{
	private:
		T* _data;
		unsigned int _size;

	public:
		Array() : _data(NULL), _size(0) {}

		Array(unsigned int n) : _data(new T[n]()), _size(n) {}

		Array(const Array& other) : _data(NULL), _size(0)
		{
			*this = other;
		}

		Array& operator=(const Array& other)
		{
			if (this != &other)
			{
				delete[] _data;
				_size = other._size;
				_data = new T[_size];
				for (unsigned int i = 0; i < _size; i++)
					_data[i] = other._data[i];
			}
			return *this;
		}

		~Array()
		{
			delete[] _data;
		}

		T& operator[](int index)
		{
			if (index < 0 || index >= static_cast<int>(_size))
				throw std::out_of_range("Index out of bounds");
			return _data[index];
		}

		unsigned int size() const
		{
			return _size;
		}
};