#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <exception>
# include <sstream>
#include <typeinfo>
# include <cmath>
# include "random_access_iterator.hpp"
# include "reverse_random_access_iterator.hpp"
# include "type_traits.hpp"


namespace ft {
	template < class T, class Allocator = std::allocator<T> > 
	class vector {

		public:
			typedef	T value_type;
			typedef	Allocator allocator_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer	pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::random_access_iterator<pointer> iterator;
			typedef ft::random_access_iterator<pointer> const_iterator;
			typedef ft::reverse_random_access_iterator<iterator> reverse_iterator;
  			typedef ft::reverse_random_access_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit vector(const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_ptr = NULL;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_ptr = NULL;
				insert(begin(), n, val);
			}

			template <class InputIterator>
			vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const Allocator& alloc = Allocator()) {
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
				_ptr = NULL;
				this->insert(this->begin(), first, last);
			}

			vector(const vector& other) {
				_alloc = other._alloc;
				this->insert(this->begin(), other.begin(), other.end());
			}

			void clear() {
				for (size_type i = 0; i < this->size(); i++)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}

			void reserve(size_type n) {
				if (n > _capacity) {
					if (n > max_size()) {
						throw std::length_error("length_error");
					}
					pointer tmp = _alloc.allocate(n);
					if (tmp == NULL) {
						throw std::bad_alloc();
					}
					for (size_t i = 0; i < _size; i++) {
						_alloc.construct(tmp + i, _ptr[i]);
						_alloc.destroy(_ptr + i);
					}
					_alloc.deallocate(_ptr, _capacity);
					_ptr = tmp;
					_capacity = n;
  				}
			}

			void assign(size_type n, const value_type& val) {
				this->clear();
				this->insert(this->begin(), n, val);
			}

			template <class InputIterator> 
			void assign(InputIterator first, InputIterator last) {
				this->clear();
				this->insert(this->begin(), first, last);
			}

			void push_back(const value_type& val) {
				reserve(_size + 1);
				this->_alloc.construct(_ptr + this->_size, val);
				_size++;
			}

			void pop_back() {
				if (this->_size > 0){
					this->_alloc.destroy(_ptr + this->_size - 1);
					_size--;
				}
			}

			iterator begin(void) { return iterator(_ptr); }

			const_iterator begin(void) const { return const_iterator(_ptr); }

			iterator end(void) { return iterator(_ptr + _size); }

			const_iterator end(void) const { return const_iterator(_ptr + _size); }

			reverse_iterator rbegin() { return (reverse_iterator(end())); }

			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

			reverse_iterator rend() { return (reverse_iterator((begin()))); }

			const_reverse_iterator rend() const { return (const_reverse_iterator((begin()))); }

			reference front() { return (*(this->begin())); }

			const_reference front() const { return (*(this->begin())); }

			reference back(void) { return (*(end() - 1)); }

			const_reference back(void) const { return (*(end() - 1)); }

			allocator_type get_allocator() const { return (this->_alloc); }

			bool empty(void) const { return (begin() == end()); }

			size_type capacity(void) const { return (_capacity); }

			size_type size() const { return (_size); }

			size_type max_size(void) { return (_alloc.max_size()); }

			void resize(size_type n, value_type val = value_type()) {
				if (n > _capacity) {
					reserve(n);
				}
				while (n < _size) {
					pop_back();
				}
				while (n > _size) {
					push_back(val);
				}
			}

			reference at(size_type n) {
				if (n < 0 || n >= _size)
    				throw std::out_of_range("out_of_range");
				return (*(begin() + n));
			}

			const_reference at(size_type n) const {
				if (n < 0 || n >= _size)
    				throw std::out_of_range("out_of_range");
				return (*(begin() + n));
			}

			iterator erase (iterator position) {
				if (position + 1 != end()) {
					std::copy(position + 1, end(), position);
				}
				--_size;
				_alloc.destroy(_ptr + _size);
				return (position);
			}

			iterator erase (iterator first, iterator last) {
				iterator it(std::copy(last, end(), first));
				while (it != end()) {
					_alloc.destroy(it.base());
					++it;
				}
				_size -= (last - first);
				return (first);
			}

			iterator insert(iterator position, const value_type &val) {
				size_type start = 0;
				while (begin() + start != position) {
					start++;
				}
				insert (position, 1, val);
				return (iterator(_ptr + start));
			}

			void insert (iterator position, size_type n, const value_type& val) {
				size_type start = 0;
				while (begin() + start != position) {
					start++;
				}
				if (_capacity == 0) {
					reserve(n);
					_size = n;
					for (size_t i = 0; i < n; i++)
      					_alloc.construct(_ptr + i + start, val);
					return ;
				}
				while (_capacity < (_size + n)) {
   					reserve(_capacity * 2);
  				}
				std::copy(&_ptr[start], &_ptr[_size], &_ptr[start + n]);
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_ptr + start++, val);
				}
				_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				size_type start = 0;
				size_type n = 0;
				while (begin() + start != position) {
					start++;
				}
				while (first + n != last) 
					n++;
				pointer tmp = _alloc.allocate(n);
				std::copy(first, last, tmp);
				if (_capacity == 0) {
					reserve(n);
					_size = n;
					for (size_t i = 0; i < n; i++)
      					_alloc.construct(_ptr + i + start, *(first + i));
					return ;
				}
				while (_capacity < (_size + n)) {
   					reserve(_capacity * 2);
  				}
				std::copy(&_ptr[start], &_ptr[_size], &_ptr[n]);
				std::copy(&tmp[0], &tmp[n], &_ptr[start]);
				_size += n;
			}

			void swap(vector &x) {
				pointer temp_ptr = x._ptr;
  				size_type temp_capacity = x._capacity;
				size_type temp_size = x._size;

				x._ptr = _ptr;
				x._capacity = _capacity;
				x._size = _size;

				_ptr = temp_ptr;
				_capacity = temp_capacity;
				_size = temp_size;
			}

			reference operator[]( size_type n ) { return (*(begin() + n)); }

			const_reference operator[]( size_type n ) const { return (*(begin() + n)); }

			vector	&operator=(const vector &x) {
				this->clear();
				reserve(x._capacity);
				this->insert(this->begin(), x.begin(), x.end());
				return (*this);
			}


		protected:
			std::allocator<T> _alloc;
			size_type _size;
			size_type _capacity;
			pointer _ptr;
	};

	template< class T, class Alloc >
	bool operator== ( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::iterator lIt = lhs.begin(); 
		typename ft::vector<T>::iterator rIt = rhs.begin();
		for (; lIt != lhs.end(); lIt++, rIt++){
			if (*lIt != *rIt || rIt == rhs.end())
				return false;
		}
		return true;
	}

	template< class T, class Alloc >
	bool operator!= ( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T>::iterator lIt = lhs.begin(); 
		typename ft::vector<T>::iterator rIt = rhs.begin();
		for (; lIt != lhs.end(); lIt++, rIt++){
			if (*lIt > *rIt)
				return false;
			else if (*lIt < *rIt)
				return true;
		}
		if (lhs.size() >= rhs.size())
			return false;
		return false;
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T>::iterator lIt = lhs.begin(); 
		typename ft::vector<T>::iterator rIt = rhs.begin();
		for (; lIt != lhs.end(); lIt++, rIt++){
			if (*lIt > *rIt)
				return false;
			else if (*lIt < *rIt)
				return true;
		}
		if (lhs.size() > rhs.size())
			return false;
		return true;
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T>::iterator lIt = lhs.begin(); 
		typename ft::vector<T>::iterator rIt = rhs.begin();
		for (; lIt != lhs.end(); lIt++, rIt++){
			if (*lIt < *rIt)
				return false;
		}
		if (lhs.size() < rhs.size())
			return false;
		return true;
	}
	
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T>::iterator lIt = lhs.begin(); 
		typename ft::vector<T>::iterator rIt = rhs.begin();
		for (; lIt != lhs.end(); lIt++, rIt++){
			if (*lIt < *rIt)
				return false;
		}
		if (lhs.size() < rhs.size())
			return false;
		return true;
	}

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif