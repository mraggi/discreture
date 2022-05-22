#include <iostream>
#include <execution>
#include <vector>
#include <boost/iterator/iterator_facade.hpp>

class n_iterator
    : public boost::iterator_facade<n_iterator, const int&, boost::random_access_traversal_tag>
{
public:
    explicit n_iterator(int t = 0) : value_(t) {}

private:
    void increment() { ++value_; }

    void decrement() { --value_; }

    const int& dereference() const { return value_; }

    void advance(int n) { value_ += n; }

    bool equal(const n_iterator& other) const
    {
        return value_ == other.value_;
    }

    int distance_to(const n_iterator& other) const
    {
        return static_cast<int>(other.value_) - value_;
    }

private:
    int value_{0};

    friend class boost::iterator_core_access;
}; // end class iterator

int main()
{
	std::for_each(std::execution::par, n_iterator(0), n_iterator(10), [&](auto i) {
		std::cout << i << '\n';
		});
	std::cout << "done" << std::endl;
	return 0;
}
