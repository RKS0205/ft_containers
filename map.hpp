#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include "rb_tree.hpp"
#include "bidirectional_iterator.hpp"
#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"

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
			typedef const ft::bidirectional_iterator<Key, T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
  			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map<Key, T, Compare, Alloc>;

				protected:
					Compare comp;
					explicit value_compare(Compare c) : comp(c) {}

				public:
					bool operator()(const value_type& x, const value_type& y) const {
						return (comp(x.first, y.first));
					}
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rb_tree(comp, alloc) { }

			map(const map &x) : _rb_tree(x._rb_tree) {}

			template <class InputIterator>
			map	(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
      		const allocator_type& alloc = allocator_type()) : _rb_tree(comp, alloc) {
				insert(first, last);
			}

			~map(void) { clear(); }

			iterator begin(void) { return (iterator(_rb_tree.leftMost(_rb_tree.getRoot()))); }

			const_iterator begin(void) const { return (const_iterator(_rb_tree.leftMost(_rb_tree.getRoot()))); }

			iterator end(void) { return (iterator(_rb_tree.getNil())); }

			const_iterator end(void) const { return (const_iterator(_rb_tree.getNil())); }

			reverse_iterator rbegin(void) { return (reverse_iterator(this->end())); }

			const_reverse_iterator rbegin(void) const { return (const_reverse_iterator(this->end())); }

			reverse_iterator rend(void) { return (reverse_iterator(this->begin())); }

			const_reverse_iterator rend(void) const { return (const_reverse_iterator(this->begin())); }

			ft::pair<iterator, bool> insert(const value_type& value) {
				iterator x = find(value.first);
				if (x != end())
					return (ft::make_pair(x, false));
				else {
					_rb_tree.insert(value);
					x = find(value.first);
					return (ft::make_pair(x, true));
				}
			}

			iterator insert(iterator position, const value_type &val) {
				(void)position;
				iterator x = find(val.first);
				if (x != end())
					return (x);
				else {
					_rb_tree.insert(val);
					x = find(val.first);
					return (x);
				}
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					insert (*first);
					++first;
				}
			}

			void erase(iterator position) {
				_rb_tree.erase(position->first);
			}

			size_type erase(const key_type &k) {
				if (find(k) != end()) {
					_rb_tree.erase(k);
					return (1);
				}
				return (0);
			}

			void erase(iterator first, iterator last) {
				iterator it;
				while (first != last) {
					it = first;
					++first;
					_rb_tree.erase(it->first);
				}
			}

			iterator find(const key_type &k) {
				iterator it(_rb_tree.findNode(k));
  				return (it);
			}

			const_iterator find(const key_type &k) const {
				const_iterator it(_rb_tree.findNode(k));
  				return (it);
			}

			size_type count(const key_type &k) const {
				const_iterator it = find(k);
				if (it != end()) {
					return (1);
				}
				return (0);
			}

			void clear(void) { _rb_tree.deallocator(_rb_tree.getRoot()); }

			size_type size(void) const { return (_rb_tree.getSize()); }

			size_type max_size(void) const { return(_rb_tree.max_size()); }

			key_compare key_comp(void) const { return (_rb_tree.getComp); }

			value_compare value_comp(void) const { return (value_compare(_rb_tree.getComp)); }

			allocator_type get_allocator(void) const { return (_rb_tree.getAlloc()); }

			bool empty(void) const { return (_rb_tree.getSize() == 0); }

			iterator upper_bound(const key_type &k) {
				return (iterator(_rb_tree.upper_bound(k)));
			}

			const_iterator upper_bound(const key_type &k) const {
				return (const_iterator(_rb_tree.upper_bound(k)));
			}

			iterator lower_bound(const key_type &k) {
				return (iterator(_rb_tree.lower_bound(k)));
			}

			const_iterator lower_bound(const key_type &k) const {
				return (const_iterator(_rb_tree.lower_bound(k)));
			}

			ft::pair<iterator,iterator> equal_range(const key_type &k){
				return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
			}

			ft::pair<const_iterator,const_iterator> equal_range(const key_type &k) const {
				return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
			}

			void swap(map &x) {
				_rb_tree.swap(x._rb_tree);
			}

			mapped_type &operator[](const key_type &k) {
				iterator x = insert(begin(), ft::make_pair(k, mapped_type()));
				return (x->second);
			}

			map &operator=(const map &other) {
				this->clear();
				this->insert(other.begin(), other.end());
				return *this;
			}


		private:
			RB_Tree<Key, T> _rb_tree;
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap(map<Key, T, Compare, Alloc>& lhs,
			map<Key, T, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs) {
		return (lhs._rb_tree == rhs._rb_tree);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs) {
		return (lhs._rb_tree < rhs._rb_tree);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs,
				const map<Key, T, Compare, Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs) {
		return (!(lhs < rhs));
	}
}

#endif