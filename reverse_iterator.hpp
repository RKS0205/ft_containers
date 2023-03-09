#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
	template <class Iter>
	struct reverse_iterator
	{
		public:
			typedef Iter	iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::difference_type	difference_type;
			typedef typename iterator_traits<Iter>::value_type	value_type;
			typedef typename iterator_traits<Iter>::pointer	pointer;
			typedef typename iterator_traits<Iter>::reference	reference;

			reverse_iterator() : current(){}
			explicit reverse_iterator( iterator_type x = iterator_type()) : current(x){}
			reverse_iterator(const reverse_iterator &x) : current(x.current) {}
			template <typename Iterator>
			reverse_iterator(const reverse_iterator<Iterator> &x) : current(x.base()) {}
			~reverse_iterator(void) {}

			iterator_type base(void) const {
				iterator_type copy = current;
				return (copy);
			}

			reference operator*() const {
				iterator_type temp = current;
				temp--;
				return (*temp);
			}

			pointer operator->() const {
				return &(operator*());
			}

			reverse_iterator& operator++() {
				current--;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			}

			reverse_iterator& operator--() {
				current++;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			}

			reverse_iterator operator+(difference_type d) const{
				reverse_iterator tmp(current - d);
				return tmp;
			}

			reverse_iterator& operator+=(difference_type d){
				current -= d;
				return *this;
			}

			reverse_iterator operator-(difference_type d) const{
				reverse_iterator tmp(current + d);
				return tmp;
			}

			reverse_iterator& operator-=(difference_type d){
				this->current += d;
				return *this;
			}

			difference_type operator-(reverse_iterator const & rhs) const {
				return this->current + rhs.current;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}

		protected:
			iterator_type current;
	};

	template <typename Iterator>
	inline bool operator==(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	inline bool operator!=(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	inline bool operator<(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	inline bool operator<=(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	inline bool operator>(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	inline bool operator>=(const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

}

#endif