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
#if __cplusplus < 201500
private:
	using base_type = std::iterator<std::input_iterator_tag, T>;
public:
	using iterator_category = typename base_type::iterator_category;
	using value_type = typename base_type::value_type;
	using difference_type = typename base_type::difference_type;
	using pointer = typename base_type::pointer;
	using reference = typename base_type::reference;
#else
public:
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
		if (this->pimpl_->next_is_end) this->is_end_iterator_ = true;
		return *this;
	}
	random_generator_iterator operator++(int) noexcept
	{
		const auto re = *this;
		if (this->pimpl_->next_is_end) this->is_end_iterator_ = true;
		return re;
	}
	constexpr bool operator==(const random_generator_iterator& r) const noexcept { return this->is_end_iterator_ == r.is_end_iterator_; }
	constexpr bool operator!=(const random_generator_iterator& r) const noexcept { return !(*this == r); }
};
template<typename T>
class random_generator_iterator_with_count 
#if __cplusplus < 201500 //C++17ではstd::iteratorは消える
	: public std::iterator<std::input_iterator_tag, T>
#endif
{
#if __cplusplus < 201500
private:
	using base_type = std::iterator<std::input_iterator_tag, T>;
public:
	using iterator_category = typename base_type::iterator_category;
	using value_type = typename base_type::value_type;
	using difference_type = typename base_type::difference_type;
	using pointer = typename base_type::pointer;
	using reference = typename base_type::reference;
#else
public:
	using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;
#endif
private:
	std::size_t count_;
	random_generator_iterator<value_type> it_;
public:
	random_generator_iterator_with_count() = delete;
	constexpr random_generator_iterator_with_count(std::size_t n) noexcept : count_(n), it_() {}
	random_generator_iterator_with_count(const random_generator_iterator_with_count&) = delete;
	random_generator_iterator_with_count(random_generator_iterator_with_count&&) = default;
	random_generator_iterator_with_count& operator=(const random_generator_iterator_with_count&) = delete;
	random_generator_iterator_with_count& operator=(random_generator_iterator_with_count&&) = default;
	random_generator_iterator_with_count(value_type min, value_type max, std::mt19937& mt)
		: count_(), it_(min, max, mt) {}
	value_type operator*() { return *(this->it_); }
	random_generator_iterator_with_count& operator++() noexcept
	{
		++this->count_;
		return *this;
	}
	random_generator_iterator_with_count operator++(int) noexcept
	{
		const auto re = *this;
		++this->count_;
		return re;
	}
	constexpr bool operator==(const random_generator_iterator_with_count& r) const noexcept { return this->count_ == r.count_; }
	constexpr bool operator!=(const random_generator_iterator_with_count& r) const noexcept { return !(*this == r); }
};
template<typename T>
class random_generator_range {
public:
	using value_type = T;
	using iterator = random_generator_iterator<value_type>;
private:
	value_type min_;
	value_type max_;
	std::reference_wrapper<std::mt19937> mt_;
public:
	random_generator_range() = delete;
	random_generator_range(const random_generator_range&) = delete;
	random_generator_range(random_generator_range&&) = default;
	random_generator_range& operator=(const random_generator_range&) = delete;
	random_generator_range& operator=(random_generator_range&&) = delete;
	random_generator_range(value_type min, value_type max, std::mt19937& mt)
		: min_(min), max_(max), mt_(mt) {}
	iterator begin() noexcept { return{ min_, max_, mt_.get() }; }
	constexpr iterator end() const noexcept { return{}; }
};
#endif //INCLUDE_RANDOM_GENERATOR_ITERATOR_HPP_
