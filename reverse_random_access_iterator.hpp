#ifndef REVERSE_RANDOM_ACCESS_ITERATOR_HPP
#define REVERSE_RANDOM_ACCESS_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
	template <class T>
	struct reverse_random_access_iterator
	{
		public:
			typedef T	iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::value_type	value_type;
			typedef typename iterator_traits<T>::pointer	pointer;
			typedef typename iterator_traits<T>::reference	reference;

			reverse_random_access_iterator() : _ptr(NULL){}
			explicit reverse_random_access_iterator( iterator_type x = iterator_type()) : _ptr(x.base()){}
			reverse_random_access_iterator(const reverse_random_access_iterator &x) : _ptr(x._ptr) {}
			template <typename Iter>
			reverse_random_access_iterator(const reverse_random_access_iterator<Iter> &x) : _ptr(x.base()) {}
			~reverse_random_access_iterator(void) {}

			const pointer base(void) const {
				return (_ptr);
			}

			reference operator*() const {
				pointer temp = _ptr;
				return *--temp;
			}

			pointer operator->() {
				return &(this->operator*());
			}

			reverse_random_access_iterator& operator++() {
				_ptr--;
				return *this;
			}

			reverse_random_access_iterator operator++(int) {
				reverse_random_access_iterator tmp = *this;
				--_ptr;
				return tmp;
			}

			reverse_random_access_iterator& operator--() {
				_ptr++;
				return *this;
			}

			reverse_random_access_iterator operator--(int) {
				reverse_random_access_iterator tmp = *this;
				++_ptr;
				return tmp;
			}

			reverse_random_access_iterator operator+(difference_type d) const{
				reverse_random_access_iterator tmp(_ptr - d);
				return tmp;
			}

			reverse_random_access_iterator& operator+=(difference_type d){
				_ptr -= d;
				return *this;
			}

			reverse_random_access_iterator operator-(difference_type d) const{
				reverse_random_access_iterator tmp(_ptr + d);
				return tmp;
			}

			reverse_random_access_iterator& operator-=(difference_type d){
				this->_ptr += d;
				return *this;
			}

			difference_type operator-(reverse_random_access_iterator const & rhs) const {
				return this->_ptr + rhs._ptr;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}

		private:
			pointer	_ptr;
	};

	template <typename Iterator>
	inline bool operator==(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	inline bool operator!=(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	inline bool operator<(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	inline bool operator<=(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	inline bool operator>(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	inline bool operator>=(const reverse_random_access_iterator<Iterator>& lhs,
						const reverse_random_access_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

}

#endif