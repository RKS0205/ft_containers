#include "vector.hpp"
#include <vector>

int main(void) {
	ft::vector<int> a;
	std::vector<int> b;

	a.push_back(10);
	a.push_back(12);
	a.push_back(16);
	a.push_back(25);

	b.push_back(10);
	b.push_back(12);
	b.push_back(16);
	b.push_back(25);

	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); *it++)
		std::cout << *it << "\n";

	std::cout << "\n";
	
	for (std::vector<int>::iterator it = b.begin(); it != b.end(); *it++)
		std::cout << *it << "\n";
}