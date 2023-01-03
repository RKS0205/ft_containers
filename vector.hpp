#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <exception>
# include <sstream>
# include <cmath>
# include "random_access_iterator.hpp"


namespace ft {
	template < class T, class Allocator = std::allocator<T> > 
	class vector {

		public:
			typedef	T value_type;
			typedef	Allocator allocator_type;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer	pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::random_access_iterator<value_type> iterator;
			typedef ft::random_access_iterator<value_type> const_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			vector(const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_ptr = NULL;
			}

			void push_back(const value_type& val) {
				if (_size + 1 > _capacity) {
					if (_capacity == 0)
						_capacity = 1;
					else
						_capacity *= 2;
					pointer temp = _alloc.allocate(_capacity);
					if (temp == NULL) {
						throw std::bad_alloc();
					}
					for (size_t i = 0; i < _size; i++) {
						_alloc.construct(temp + i, _ptr[i]);
						_alloc.destroy(_ptr + i);
					}
					_alloc.deallocate(_ptr, _capacity);
   					_ptr = temp;
  				}
				this->_alloc.construct(_ptr + this->_size, val);
				_size++;
			}

			iterator begin(void) {
				return iterator(_ptr);
			}

			iterator end(void) {
				return iterator(_ptr + this->_size);
			}

		protected:
			std::allocator<T> _alloc;
			size_t _size;
			size_t _capacity;
			pointer _ptr;
	};
}


#endif