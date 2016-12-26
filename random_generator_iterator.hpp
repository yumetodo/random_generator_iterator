#ifndef INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
#define INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
#include "random.hpp"
template<typename T>
class random_generator_iterator
#if __cplusplus < 201500 //C++17ではstd::iteratorは消える
    : std::iterator<std::input_iterator_tag, T>
#endif
{
public:
#if __cplusplus < 201500  
    using iterator_category = typename base_type::iterator_category;
    using value_type = typename base_type::value_type;
    using difference_type = typename base_type::difference_type;
    using pointer = typename base_type::pointer;
    using reference = typename base_type::reference;
#els
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
#endif
	using distribution = uniform_normal_distribution<value_type>;
private:
	distribution dist_;
	std::reference_wrapper<std::mt19937> engine_;
	bool next_is_end_;
#if __cplusplus < 201500
    using base_type = std::iterator<std::input_iterator_tag, T>;
#endif
public:
	random_generator_iterator() = delete;
	random_generator_iterator(const random_generator_iterator&) = delete;
	random_generator_iterator(random_generator_iterator&&) = default;
	random_generator_iterator& operator=(const random_generator_iterator&) = delete;
	random_generator_iterator& operator=(random_generator_iterator&&) = default;

	random_generator_iterator(value_type min, value_type max, std::mt19937& mt)
		: dist_(min, max), engine_(mt), next_is_end_(false)
	{}
	void stop() noexcept { next_is_end_ = true; }
	reference operator*() { return dist_(engine_); }
	reference operator++() noexcept { return *this; }
 };
#endif //INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
