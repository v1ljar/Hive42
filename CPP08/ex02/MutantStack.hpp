#pragma once

#include <stack>
#include <deque>
#include <iterator>
#include <cstddef>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack() = default;
		MutantStack(const MutantStack& other) {
			*this = other;
		};
		MutantStack& operator=(const MutantStack& other) {
			if (this != &other) {
				std::stack<T>::operator=(other);
			}
			return *this;
		};
		~MutantStack() = default;

		class iterator {
			public:
				using iterator_category = std::bidirectional_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = T*;
				using reference = T&;

				explicit iterator(typename std::deque<T>::iterator it) : _it(it) {}

				reference operator*() const { return *_it; }
				pointer operator->() { return &(*_it); }

				iterator& operator++() {
					++_it;
					return *this;
				}

				iterator operator++(int) {
					iterator tmp = *this;
					++_it;
					return tmp;
				}

				iterator& operator--() {
					--_it;
					return *this;
				}

				iterator operator--(int) {
					iterator tmp = *this;
					--_it;
					return tmp;
				}

				bool operator==(const iterator& other) const { return _it == other._it; }
				bool operator!=(const iterator& other) const { return _it != other._it; }

			private:
				typename std::deque<T>::iterator _it;
		};

		iterator begin() {
			return iterator(this->c.begin());
		}

		iterator end() {
			return iterator(this->c.end());
		}
};