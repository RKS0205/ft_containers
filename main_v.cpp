#include "vector.hpp"
#include <vector>
#include <sys/time.h>
#include <typeinfo>

int main(void) {
	ft::vector<int> my_vector;
	std::vector<int> original_vector;

	my_vector.push_back(10);
	my_vector.push_back(12);
	my_vector.push_back(16);
	my_vector.push_back(25);

	my_vector.insert(my_vector.begin() + 2, 80);

	my_vector.insert(my_vector.begin() + 2, 3, 10);

	my_vector.insert(my_vector.begin(), my_vector.begin() + 2, my_vector.end());

	my_vector.erase(my_vector.begin(), my_vector.begin() + 1);

	my_vector.pop_back();

	my_vector.resize(5);

	original_vector.push_back(10);
	original_vector.push_back(12);
	original_vector.push_back(16);
	original_vector.push_back(25);

	original_vector.insert(original_vector.begin() + 2, 80);

	original_vector.insert(original_vector.begin() + 2, 3, 10);

	original_vector.insert(original_vector.begin(), original_vector.begin() + 2, original_vector.end());

	original_vector.erase(original_vector.begin(), original_vector.begin() + 1);

	original_vector.pop_back();

	original_vector.resize(5);

	ft::vector<int>::iterator it = my_vector.begin();
	std::vector<int>::iterator it2 = original_vector.begin();
	std::cout << "MY_VECTOR | ORIGINAL_VECTOR\n";
	while (it != my_vector.end() && it2 != original_vector.end()) {
		std::cout << *it << "        | " << *it2 << "\n";
		it++;
		it2++;
	}

	std::cout << "\n\nOPERATOR TEST:\n";
	std::cout << "MY_VECTOR: " << my_vector[4] << std::endl;
	std::cout << "OG_VECTOR: " << original_vector[4] << std::endl;

	std::cout << "\n\nSIZE TEST:\n";
	std::cout << "MY_VECTOR: " << my_vector.size() << std::endl;
	std::cout << "OG_VECTOR: " << original_vector.size() << std::endl;

	// struct timeval begin, end;
    // gettimeofday(&begin, 0);

	// for (int i = 0; i < 100000; i++)
	// 	my_vector.insert(my_vector.begin(), 10);

	// gettimeofday(&end, 0);
	// long microseconds = end.tv_usec - begin.tv_usec;
	// std::cout << "TIME MY_VECTOR: " << microseconds << std::endl;

	// struct timeval begin2, end2;

	// gettimeofday(&begin2, 0);

	// for (int i = 0; i < 100000; i++)
	// 	original_vector.insert(original_vector.begin(), 10);

	// gettimeofday(&end2, 0);
	// microseconds = end2.tv_usec - begin2.tv_usec;
	// std::cout << "TIME OG_VECTOR: " << microseconds << std::endl;



	// for (ft::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); *it++)
	// 	std::cout << *it << "\n";
}