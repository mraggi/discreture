#pragma once

#include "Combinations.hpp"
#include "do_not_optimize.hpp"
#include "Probability.hpp"

inline void BM_CombinationsNAP(int n, int k)
{
	dscr::combinations::combination comb(k);
	dscr::combinations::combination::value_type hint = k;
	dscr::combinations::combination::value_type last = k-1;
	std::iota(comb.begin(), comb.end(), 0);
// 	int count = 0;
	do
	{
		DoNotOptimize(comb);
// 		++count;
// 		DoNotOptimize(count);
	} while(dscr::combinations::next_combination(n,comb,hint,last));
}

inline void BM_combinationsIterator(int n, int k, long size)
{
	auto X = dscr::combinations(n,k);
	auto first = X.begin();
	auto last = X.end();
	for ( ; first != last; ++first)
	{
		DoNotOptimize(*first);
	}
}


class algoT_iterator : public boost::iterator_facade<
    algoT_iterator,
    const std::vector<int>&,
    boost::forward_traversal_tag>
{
public:

    algoT_iterator() : m_ID(0), m_data() {} //empty initializer

    algoT_iterator(int n, int k) : m_ID(0),  m_hint(k), m_data(k)
    {
        std::iota(m_data.begin(), m_data.end(), 0);
        if (k == 0)
        {
            m_hint = -1;
        }
    }

    explicit algoT_iterator(long id) : m_ID(id), m_data() {} //ending initializer: for id only. Do not use unless you know what you are doing.
private:

    //prefix
    void increment()
    {
        dscr::combinations::next_combination(m_data, m_hint);
        ++m_ID;
    }

    bool equal(const algoT_iterator& other) const
    {
        return m_ID == other.m_ID;
    }

    const std::vector<int>& dereference() const
    {
        return m_data;
    }

    friend class boost::iterator_core_access;

    long m_ID {0};
    int m_hint {0};
    std::vector<int> m_data;
};

template <class Iter>
void BM_typeSizeIter(int n, int k, long size)
{
	auto first = Iter(n,k);
	auto last = Iter(size);
	for ( ; first != last; ++first)
	{
		DoNotOptimize(*first);
	}
}
