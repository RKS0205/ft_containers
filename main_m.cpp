#include "rb_tree.hpp"
#include <map>
#include "map.hpp"
#include <sys/time.h>
#include <typeinfo>

int main(void) {
	ft::map<int,int> my_map;

	my_map.insert(ft::map<int,int>::value_type(2, 2));
	my_map.insert(ft::map<int,int>::value_type(3, 3));
	my_map.insert(ft::map<int,int>::value_type(4, 4));
	my_map.insert(ft::map<int,int>::value_type(5, 5));
	my_map.insert(ft::map<int,int>::value_type(1, 1));

	std::map<int,int> original_map;

	original_map.insert(std::map<int,int>::value_type(2, 2));
	original_map.insert(std::map<int,int>::value_type(3, 3));
	original_map.insert(std::map<int,int>::value_type(4, 4));
	original_map.insert(std::map<int,int>::value_type(5, 5));
	original_map.insert(std::map<int,int>::value_type(1, 1));

	ft::map<int,int>::reverse_iterator my_it = my_map.rbegin();
	std::map<int,int>::reverse_iterator original_it = original_map.rbegin();

	std::cout << "MY_MAP | ORIGINAL_MAP\n";
	while (my_it != my_map.rend() && original_it != original_map.rend()) {
		std::cout << my_it->second << "      | " << original_it->second << "\n";
		my_it++;
		original_it++;
	}

}