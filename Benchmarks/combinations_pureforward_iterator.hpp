#pragma once

#include "Combinations.hpp"

template <typename T>
class combination_iterator_pureforward
	: public boost::iterator_facade<
	combination_iterator_pureforward<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
public:
	combination_iterator_pureforward() : end(true), n(0), k(0), comb() { } //end

	explicit combination_iterator_pureforward(T n, T k) : end(false), n(n), k(k), hint(k), comb(k)
	{
		assert(k != 0 && n > k);
		std::iota(comb.begin(), comb.end(), 0);
		assert(!end);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		if (hint < 0)
		{
			end = true;
			return;
		}
		if (hint > 0)
		{
			--hint;
			++comb[hint];
			return;
		}
		
		const T last = comb.size()-1;
		for (T i = 0; i < last; ++i)
		{
			if (comb[i]+1 != comb[i+1])
			{
				++comb[i];
				hint = i;
				return;
			}
			comb[i] = i;
		}
		hint = last;
		++comb[last];
		end = (comb[last] == n);
	}

	bool equal(const combination_iterator_pureforward& other) const
	{
		return end == other.end;
	}

	const std::vector<T>& dereference() const
	{
		return comb;
	}

	bool end;
	const T n;
	const T k;
	T hint;
	std::vector<T> comb;
};
