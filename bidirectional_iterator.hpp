#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include <iostream>
#include "rb_tree.hpp"
#include "utility.hpp"
#include "iterator_traits.hpp"

namespace ft {
	template <typename Key, typename T>
	class bidirectional_iterator {
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef  std::ptrdiff_t					difference_type;
			typedef  ft::pair<const Key, T>			value_type;
			typedef  value_type*					pointer;
			typedef  value_type& 					reference;

			bidirectional_iterator() : node(NULL) {}
			explicit bidirectional_iterator(Node<Key, T> *node) : node(node) {}
			template <typename k, typename t>
			bidirectional_iterator(const bidirectional_iterator<k, t>& i) : node(i.base()) {}
			~bidirectional_iterator(void) {}

			template <typename k, typename t>
			bidirectional_iterator& operator=(const bidirectional_iterator<k, t>& i) {
				node = i.base();
				return (*this);
			}

			const Node<Key, T> *base(void) const {
				return (node);
			}

			reference operator*(void) const {
				return *(node->value);
			}

			pointer operator->(void) const {
				return (node->value);
			}

			bidirectional_iterator& operator++(void) {
				node = node->nextNode(node);
				return (*this);
			}

			bidirectional_iterator operator++(int) {
				Node<Key, T> *tmp = node;
				node = node->nextNode(node);
				return (bidirectional_iterator(tmp));
			}

			bidirectional_iterator& operator--(void) {
				node = node->previousNode(node);
				return (*this);
			}

			bidirectional_iterator operator--(int) {
				Node<Key, T> *tmp = node;
				node = node->previousNode(node);
				return (bidirectional_iterator(tmp));
			}

		private:
			Node<Key, T> *node;

	};

	template <typename Key, typename T>
	inline bool operator==(const bidirectional_iterator<Key, T>& lhs,
						const bidirectional_iterator<Key, T>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Key, typename T>
	inline bool operator!=(const bidirectional_iterator<Key, T>& lhs,
						const bidirectional_iterator<Key, T>& rhs) {
		return (lhs.base() != rhs.base());
	}

}



#endif