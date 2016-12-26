#ifndef INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
#define INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
#include "random.hpp"
#include <memory>
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
	struct impl {
		distribution dist;
		std::reference_wrapper<std::mt19937> engine;
		bool next_is_end;
		impl() = default;
		impl(const impl&) = delete;
		impl(impl&&) = default;
		impl& operator=(const impl&) = delete;
		impl& operator=(impl&&) = default;
		impl(value_type min, value_type max, std::mt19937& mt) : dist(min, max), engine(mt), next_is_end(false) {}
		value_type generate() { return this->dist(this->engine.get()); }
	};
	std::unique_ptr<impl> pimpl_;
	bool is_end_iterator_;
public:
	constexpr random_generator_iterator() noexcept : pimpl_(), is_end_iterator_(true) {};
	random_generator_iterator(const random_generator_iterator&) = delete;
	random_generator_iterator(random_generator_iterator&&) = default;
	random_generator_iterator& operator=(const random_generator_iterator&) = delete;
	random_generator_iterator& operator=(random_generator_iterator&&) = default;

	random_generator_iterator(value_type min, value_type max, std::mt19937& mt)
		: pimpl_(std::make_unique<impl>(min, max, mt)), is_end_iterator_(false)
	{}
	void stop() noexcept { this->pimpl_->next_is_end = true; }
	value_type operator*() { return this->pimpl_->generate(); }
	random_generator_iterator& operator++() noexcept
	{ 
		return *this;
	}
};
#endif //INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
