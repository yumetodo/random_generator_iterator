#include "random_generator_iterator.hpp"
#include <iostream>
//random generator
static auto engine = create_engine();
int main(int argc, char **argv)
{
	std::cout << "generate: random_generator_iterator" << std::endl;
	for (auto ri = random_generator_iterator<int>(0, 10, engine); ri != random_generator_iterator<int>{}; ++ri) {
		const auto n = *ri;
		std::cout << n << std::endl;
		if (0 == n) ri.stop();
	}
	std::cout << "generate: random_generator_range" << std::endl;
	for (auto&& n : random_generator_range<int>(0, 10, engine)) {
		std::cout << n << std::endl;
		if (0 == n) break;
	}
	std::cout << "generate: random_generator_iterator_with_count" << std::endl;
	for (auto ri = random_generator_iterator_with_count<int>(0, 10, engine); ri != random_generator_iterator_with_count<int>(10); ++ri) {
		std::cout << *ri << std::endl;
	}
	std::cout << "generate: random_generator_range_with_count" << std::endl;
	for (auto&& n : random_generator_range_with_count<int>(10, 0, 10, engine)) {
		std::cout << n << std::endl;
	}

	return 0;
}
