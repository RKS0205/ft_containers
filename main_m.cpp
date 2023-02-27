#include "rb_tree.hpp"
#include <map>
#include "map.hpp"
#include <sys/time.h>
#include <typeinfo>

int main(void) {
	ft::map<int,int> test;
	ft::map<int,int>::iterator it;

	test.insert(ft::map<int,int>::value_type(2, 2));
	test.insert(ft::map<int,int>::value_type(3, 3));
	test.insert(ft::map<int,int>::value_type(4, 4));
	test.insert(ft::map<int,int>::value_type(5, 5));
	test.insert(ft::map<int,int>::value_type(1, 1));
	it = test.begin();
	std::cout << it->second << std::endl;

	std::map<int,int> test2;
	std::map<int,int>::iterator it2;

	test2.insert(std::map<int,int>::value_type(2, 2));
	test2.insert(std::map<int,int>::value_type(3, 3));
	test2.insert(std::map<int,int>::value_type(4, 4));
	test2.insert(std::map<int,int>::value_type(5, 5));
	test2.insert(std::map<int,int>::value_type(1, 1));
	it2 = test2.begin();
	std::cout << it2->second << std::endl;
}