#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
	template <class T>
	struct random_access_iterator
	{
		public:
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::value_type	value_type;
			typedef typename iterator_traits<T>::pointer	pointer;
			typedef typename iterator_traits<T>::reference	reference;

			random_access_iterator(pointer ptr = pointer()) : _ptr(ptr){}
			random_access_iterator(const random_access_iterator &x) : _ptr(x.base()) {}
			template <typename Iter>
			random_access_iterator(const random_access_iterator<Iter> &x) : _ptr(x.base()) {}
			~random_access_iterator(void) {}

			const pointer base(void) const {
				return (_ptr);
			}

			reference operator*() const {
				return *_ptr;
			}

			pointer operator->() {
				return _ptr;
			}

			random_access_iterator& operator++() {
				_ptr++;
				return *this;
			}

			random_access_iterator operator++(int) {
				random_access_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			random_access_iterator& operator--() {
				_ptr--;
				return *this;
			}

			random_access_iterator operator--(int) {
				random_access_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			random_access_iterator operator+(difference_type d) const{
				random_access_iterator tmp(this->_ptr + d);
				return tmp;
			}

			random_access_iterator& operator+=(difference_type d){
				this->_ptr += d;
				return *this;
			}

			random_access_iterator operator-(difference_type d) const{
				random_access_iterator tmp(this->_ptr - d);
				return tmp;
			}

			random_access_iterator& operator-=(difference_type d){
				this->_ptr -= d;
				return *this;
			}

			difference_type operator-(random_access_iterator const & rhs) const {
				return this->_ptr - rhs._ptr;
			}

			reference operator[](difference_type n) const {
				return *(this->_ptr + n);
			}

		private:
			pointer	_ptr;
	};

	template <typename Iterator>
	inline bool operator==(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	inline bool operator!=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	inline bool operator<(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	inline bool operator<=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	inline bool operator>(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	inline bool operator>=(const random_access_iterator<Iterator>& lhs,
						const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

}

#endif