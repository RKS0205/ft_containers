#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "utility.hpp"

#define BLACK 0
#define RED 1

namespace ft
{
	template <typename Key, typename T> 
	struct Node
	{
		public:
			Node<Key, T>	*parent;
			ft::pair<const Key, T>	*value;
			Node<Key, T>	*left;
			Node<Key, T>	*right;
			Node<Key, T>	*nil;
			Node<Key, T>	*root;
			int 	color;

			Node<Key, T> *leftMost(Node<Key, T> *node) {
				while (node->left != node->nil)
					node = node->left;
				return (node);
			}

			Node<Key, T> *rightMost(Node<Key, T> *node) {
				while (node->right != node->nil)
					node = node->right;
				return (node);
			}

			Node<Key, T> *getRoot(Node<Key, T> *node) {
				while (node->parent != node->nil)
					node = node->parent;
				return (node);
			}

			Node<Key, T> *nextNode(Node<Key, T> *x) {
				if (x == x->nil) {
					return (rightMost(x->root));
				}
				if (x->right != x->nil) {
					return (leftMost(x->right));
				}
				Node<Key, T> *y = x->parent;
				while (y != y->nil && x == y->right) {
					x = y;
					y = y->parent;
				}
				return (y);
			}

			Node<Key, T> *previousNode(Node<Key, T> *x) {
				if (x == x->nil) {
					return (rightMost(x->root));
				}
				if (x->left != x->nil) {
					return (rightMost(x->left));
				}
				Node<Key, T> *y = x->parent;
				while (y != y->nil && x == y->left) {
					x = y;
					y = y->parent;
				}
				return (y);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class RB_Tree {
		public:
			typedef Key key_type;
			typedef T mapped_type;			
			typedef ft::pair<const Key, T> value_type;

			RB_Tree (Compare comp = Compare(), Allocator alloc = Allocator()) {
				_alloc = alloc;
				_NIL = new Node<Key, T>;
				_NIL->right = _NIL;
				_NIL->left = _NIL;
				_NIL->parent = _NIL;
				_NIL->nil = _NIL;
				_NIL->color = BLACK;
				_NIL->root = _NIL;
				_NIL->value = _alloc.allocate(1);
				_alloc.construct(_NIL->value, value_type());
				_size = 0;
				_root = _NIL;
				_alloc = alloc;
				_comp = comp;
			}

			~RB_Tree() {
				if (_size > 0)
					deallocator(_root);
			}

			void deallocator(Node<Key, T> *node) { 
				if (node != _NIL) {
					deallocator(node->left);
					deallocator(node->right);
					freeNode(node);
					_size--;
				}
			}

			Node<Key, T> *newNode(Key key, T value) {
				Node<Key, T> *new_node = new Node<Key, T>;
				new_node->right = _NIL;
				new_node->left = _NIL;
				new_node->parent = _NIL;
				new_node->nil = _NIL;
				new_node->root = _root;
				new_node->color = BLACK;
				new_node->value = _alloc.allocate(1);
				_alloc.construct(new_node->value, value_type(key, value));
				return (new_node);
			}

			void freeNode(Node<Key, T> *node) {
				_alloc.deallocate(node->value, 1);
				delete node;
			}

			Node<Key, T> *findNode(Key key) const {
				Node<Key, T> *temp = _root;
					while (temp != _NIL) {
						if (!_comp(key, temp->value->first) && !_comp(temp->value->first, key)) {	
							return (temp);
						}
						else if (_comp(key, temp->value->first)) {
							temp = temp->left;
						}
						else if (!(_comp(key, temp->value->first))){
							temp = temp->right;
						}
					}
				return (temp);
			}

			void leftRotate(Node<Key, T> *x) {
				Node<Key, T> *y = x->right;
				x->right = y->left;

				if (y->left != _NIL)
					y->left->parent = x;
				y->parent = x->parent ;

				if (x->parent == _NIL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left= y;
				else
					x->parent->right = y ;

				y->left= x ;
				x->parent = y;
			}

			void rightRotate(Node<Key, T> *x) {
				Node<Key, T> *y = x->left;
				x->left = y->right;

				if (y->right != _NIL)
					y->right->parent = x;
				y->parent = x->parent ;

				if (x->parent == _NIL)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right= y;
				else
					x->parent->left = y;

				y->right= x;
				x->parent = y;
			}

			void insert(value_type value) {
				Node<Key, T> *node = newNode(value.first, value.second);
				Node<Key, T> *temp;
				if (_root == _NIL) {
					_size++;
					_root = node;
					_NIL->root = _root;
					return ;
				}
				else {
					temp = _root;
					while (temp != _NIL) {
						if (!_comp(node->value->first, temp->value->first) && !_comp(temp->value->first, node->value->first)) {	
							freeNode(node);
							return ;
						}
						else if (_comp(node->value->first, temp->value->first)) {
							if (temp->left == _NIL) {
								node->parent = temp;
								node->color = RED;
								temp->left = node;
								_size++;
								break ;
							}
							temp = temp->left;
						}
						else if (!(_comp(node->value->first, temp->value->first))){
							if (temp->right == _NIL){
								node->parent = temp;
								node->color = RED;
								temp->right = node;
								_size++;
								break ; 
							}
							temp = temp->right;
						}
					}
				}
				fixInsert(node);
				_NIL->root = _root;
			}

			void fixInsert(Node<Key, T> *node) {
				Node<Key, T> *y;
				while (node->parent->color == RED) {
					if (node->parent == node->parent->parent->left) {
						y = node->parent->parent->right;
						if (y->color == RED) {
							node->parent->color = BLACK;
							y->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else {
							if (node == node->parent->right) {
								node = node->parent;
								leftRotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rightRotate(node->parent->parent);
						}
					}
					else {
						y = node->parent->parent->left;
						if (y->color == RED) {
							node->parent->color = BLACK;
							y->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else {
							if (node == node->parent->left) {
								node = node->parent;
								rightRotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							leftRotate(node->parent->parent);
						}
					}
				}
			_root->color = BLACK;
			}

			Node<Key, T> *leftMost(Node<Key, T> *node) {
				while (node->left != _NIL)
					node = node->left;
				return (node);
			}

			Node<Key, T> *rightMost(Node<Key, T> *node) {
				while (node->right != _NIL)
					node = node->right;
				return (node);
			}

			void transplant(Node<Key, T> *x, Node<Key, T> *y) {
				if (x->parent == _NIL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			void fixErase(Node<Key, T> *node) {
				Node<Key, T> *temp;

				while (node != _root && node->color == BLACK) {
					if (node == node->parent->left) {
						temp = node->parent->right;

						if (temp->color == RED) {
							temp->color = BLACK;
							node->parent->color = RED;
							leftRotate(node->parent);
							temp = node->parent->right;
						}
						if (temp->left->color == BLACK && temp->right->color == BLACK) {
							temp->color = RED;
							node = node->parent;
						}
						else {
							if (temp->right->color == BLACK) {
								temp->left->color = BLACK;
								temp->color = RED;
								rightRotate(temp);
								temp = node->parent->right;
							}
							temp->color = node->parent->color;
							node->parent->color = BLACK;
							temp->right->color = BLACK;
							leftRotate(node->parent);
							node = _root;
						}
					}
					else {
						temp = node->parent->left;

						if (temp->color == RED) {
							temp->color = BLACK;
							node->parent->color = RED;
							rightRotate(node->parent);
							temp = node->parent->left;
						}
						if (temp->right->color == BLACK && temp->left->color == BLACK) {
							temp->color = RED;
							node = node->parent;
						}
						else {
							if (temp->left->color == BLACK) {
								temp->right->color = BLACK;
								temp->color = RED;
								leftRotate(temp);
								temp = node->parent->left;
							}
							temp->color = node->parent->color;
							node->parent->color = BLACK;
							temp->left->color = BLACK;
							rightRotate(node->parent);
							node = _root;
						}
					}
				}
				node->color = BLACK;
			}

			void erase(Key key) {
				Node<Key, T> *node = findNode(key);
				Node<Key, T> *x , *y;
				int	y_originalColor;

				y = node;
				y_originalColor = y->color;
				if (node->left == _NIL) {
					x = node->right;
    				transplant(node, node->right);
				}
				else if (node->right == _NIL) {
					x = node->left;
    				transplant(node, node->left);
				}
				else {
					y = leftMost(node->right);
					y_originalColor = y->color;
					x = y->right;
					if (y->parent == node)
						x->parent = y;
					else {
						transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				if (y_originalColor == BLACK)
					fixErase(x);
				freeNode(node);
				_size--;
			}

			Node<Key, T> *lower_bound(const key_type &k) const {
				Node<Key, T> *x = _root;
				Node<Key, T> *y = _NIL;

				while (x != _NIL) {
					if (!_comp(x->value->first, k)) {
						y = x;
						x = x->left;
					}
					else {
						x = x->right;
					}
				}
				return (y);
			}

			Node<Key, T> *upper_bound(const key_type &k) const {
				Node<Key, T> *x = _root;
				Node<Key, T> *y = _NIL;

				while (x != _NIL) {
					if (_comp(k, x->value->first)) {
						y = x;
						x = x->left;
					}
					else {
						x = x->right;
					}
				}
				return (y);
			}

			void printBT(const std::string& prefix, const Node<Key, T> *node, bool isLeft)
			{
				if( node != _NIL )
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					std::cout << (node->color ? std::string("R:") : std::string("B:"));
					std::cout << node->value->first << std::endl;

					printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
					printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}

			Node<Key, T> *getRoot(void) {
				return (_root);
			}

			Node<Key, T> *getNil(void) const {
				return (_NIL);
			}

			Allocator getAlloc(void) const {
				return (_alloc);
			}

			size_t getSize(void) const {
				return (_size);
			}

			Compare getComp(void) const {
				return (_comp);
			}

			size_t max_size(void) const {
				return (_alloc.max_size());
			}

			void printBT(void)
			{
				printBT("", _root, false);    
			}


		private:
			Allocator _alloc;
			size_t _size;
			Node<Key, T> *_root;
			Node<Key, T> *_NIL;
			Compare _comp;

	};
}

#endif