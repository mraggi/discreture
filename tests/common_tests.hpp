#include <gtest/gtest.h>
#include <iostream>

#include "Probability.hpp"
#include "IntegerInterval.hpp"

template <class Container, class CheckElement>
void test_forward_iteration(const Container& C, CheckElement&& check_elem)
{
    int i = 0;
    for (auto c : C)
    {
        check_elem(c);
        ASSERT_EQ(c,C[i]);
        ++i;
    }
    ASSERT_EQ(C.size(), i);
    
    using elem_type = typename Container::value_type;
    std::set<elem_type> S(C.begin(), C.end());
    ASSERT_EQ(S.size(), C.size());
}

template <class Container, class CheckElement>
void test_reverse_iteration(const Container& C, CheckElement&& check_elem)
{
    int i = C.size()-1;
    for (auto it = C.rbegin(); it != C.rend(); ++it)
    {
        check_elem(*it);
        ASSERT_EQ(*it,C[i]);
        --i;
    }
    ASSERT_EQ(i, -1);
    
    using elem_type = typename Container::value_type;
    std::set<elem_type> S(C.rbegin(), C.rend());
    ASSERT_EQ(S.size(), C.size());
}

template <class Iter, class difference_type>
void dumb_advance(Iter& it, difference_type distance)
{
    while (distance > 0)
    {    
        ++it;
        --distance;
    }
    while (distance < 0)
    {    
        --it;
        ++distance;
    }
}

template <class Container, class CheckElement>
void test_advance_iterator(const Container& C, CheckElement&& check_elem)
{
    int n = C.size();
    
    if (n <= 0)
        return;
    
    int num_times = 2*n;
    
    auto it = C.begin();
    int current = 0;
    for (auto t : dscr::NN(num_times))
    {
        int target = dscr::random::random_int(0,n);
        int distance = target - current;
        
        if (dscr::random::probability_of_true(0.5))
            std::advance(it,distance); 
        else
            dumb_advance(it,distance);
        current = target;
        check_elem(*it);
        ASSERT_EQ(*it,C[current]);
        ASSERT_EQ(*it,*(C.begin() + current));
    }
}

template <class Container, class CheckElement>
void test_advance_reverse_iterator(const Container& C, CheckElement&& check_elem)
{
    int n = C.size();
    
    if (n <= 0)
        return;
    
    int num_times = 2*n;
    
    auto rit = C.rbegin();
    int current = 0;

    for (auto t : dscr::NN(num_times))
    {
        int target = dscr::random::random_int(0,n);
        int distance = target - current;

        if (dscr::random::probability_of_true(0.5))
            std::advance(rit,distance); 
        else
            dumb_advance(rit,distance);
        current = target;
        check_elem(*rit);
        ASSERT_EQ(*rit,C[C.size()-1-current]);
        ASSERT_EQ(*rit,*(C.rbegin()+current));
    }
}


template <class Container, class CheckElement>
void test_container_full(const Container& C, CheckElement&& check_elem)
{
    test_forward_iteration(C,std::forward<CheckElement>(check_elem));
    
    test_reverse_iteration(C,std::forward<CheckElement>(check_elem));
    
    test_advance_iterator(C,std::forward<CheckElement>(check_elem));
    test_advance_reverse_iterator(C,std::forward<CheckElement>(check_elem));
}
