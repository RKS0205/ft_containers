#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include "rb_tree.hpp"
#include "bidirectional_iterator.hpp"
#include "type_traits.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;
			typedef ft::bidirectional_iterator<Key, T> iterator;
			typedef ft::bidirectional_iterator<Key, T> const_iterator;
			// typedef ft::reverse_bidirectional_iterator<iterator> reverse_iterator;
  			// typedef ft::reverse_bidirectional_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rb_tree(comp, alloc) { }

			~map(void) { }

			iterator begin(void) {
				return (iterator(_rb_tree.leftMost(_rb_tree.getRoot())));
			}

			void insert(const value_type& value) {
				_rb_tree.insert(value);
			}

			void print() {
				_rb_tree.printBT();
			}



		private:
			RB_Tree<Key, T> _rb_tree;
	};
}

#endif