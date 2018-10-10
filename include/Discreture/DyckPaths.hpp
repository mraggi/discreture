#pragma once

#include "ArithmeticProgression.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace discreture
{

////////////////////////////////////////////////////////////////////////////////////
/// \brief Class for iterating through all dyck (dyck) paths.
/// \param IntType must be a SIGNED integer type.
///
/// Dyck paths, also called Catalan Paths, are paths that go from \f$(0,0)\f$ to
/// \f$(0,2n)\f$, which never go below the \f$ y=0\f$ line, in which each step
/// is from \f$(x,y)\f$ to either \f$(x+1,y+1)\f$ or \f$(x+1,y-1)\f$ #Example
/// Usage:
///
///     dyck_paths X(3)
///     for (auto&& x : X)
///         cout << x << endl;
/// Prints out:
///     [ 1 1 1 -1 -1 -1 ]
///     [ 1 1 -1 1 -1 -1 ]
///     [ 1 -1 1 1 -1 -1 ]
///     [ 1 1 -1 -1 1 -1 ]
///     [ 1 -1 1 -1 1 -1 ]
///
/// # Example: Parenthesis
///
///     dyck_paths X(3)
///     for (auto&& x : X)
///         cout << dyck_paths::to_string(x, "()") << endl;
///
/// Prints out:
///     ((()))
///     (()())
///     ()(())
///     (())()
///     ()()()
///
/////////////////////////////////////////////////////////////////////////////////////
template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class DyckPaths
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using dyck_path = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

    // **************** Begin static functions
    static void next_dyck_path(dyck_path& data)
    {
        size_t n_ = data.size()/2;

        if (n_ == 0)
            return;

        if (data[1] != -1)
        {
            size_t loc = 2;

            while (data[loc] != -1)
                ++loc;

            data[loc] = 1;
            data[loc - 1] = -1;

            return;
        }

        size_t verif = 0;
        size_t i = 1;

        while (i < n_ && verif == 0)
        {
            if (data[(2*i) + 1] == 1)
                verif = ((2*i) + 1);

            ++i;
        }

        //          for(nuint i=1; i<t; ++t)
        //          {
        //              if(data[(2*i)+1]==0)
        //                  verif=((2*i)+1);
        //          }

        if (verif == 0)
        {
            return;
        }

        size_t cont = 0;
        auto encontrar = verif + 1;

        for (size_t i = 0; i < verif; ++i)
        {
            if (data[i] == -1)
            {
                data[i] = 1;
                ++cont;
            }
        }

        while (data[encontrar] != -1)
            ++encontrar;

        data[encontrar] = 1;
        data[encontrar - 1] = -1;

        while (cont != 0)
        {
            data[encontrar - 1 - cont] = -1;
            --cont;
        }
    }

    static std::string to_string(const dyck_path& data,
                                 const std::string& delim = "()")
    {
        std::string toReturn;

        for (auto i : data)
        {
            auto j = 1 - (i + 1)/2;
            toReturn.push_back(delim[j]);
        }

        return toReturn;
    }

    // **************** End static functions

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param n is an integer >= 0
    ///
    ////////////////////////////////////////////////////////////
    explicit DyckPaths(IntType n) : n_(n) {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of dyck_paths
    ///
    /// \return binomial(2n,n)/(n+1)
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return catalan(n_); }

    IntType get_n() const { return n_; }

    ////////////////////////////////////////////////////////////
    /// \brief Forward iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const dyck_path&, boost::forward_traversal_tag>
    {
    public:
        iterator() = default; // empty initializer
        explicit iterator(IntType n) : ID_(0), data_(2*n, 1)
        {
            for (size_t i = n; i < data_.size(); ++i)
                data_[i] = -1;
        }

        size_type ID() const { return ID_; }

        bool is_at_end(IntType n) const { return ID_ == catalan(n); }

        void reset(IntType n)
        {
            ID_ = 0;
            data_.resize(2*n);
            auto r = static_cast<size_t>(n);
            for (size_t i = 0; i < r; ++i)
                data_[i] = 1;

            for (size_t i = r; i < data_.size(); ++i)
                data_[i] = -1;
        }

        static const iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.ID_ = id;
            return it;
        }

    private:
        void increment()
        {
            ++ID_;

            next_dyck_path(data_);
        }

        const dyck_path& dereference() const { return data_; }

        bool equal(const iterator& it) const { return it.ID() == ID(); }

    private:
        size_type ID_{0};
        dyck_path data_{};

        friend class boost::iterator_core_access;
    }; // end class iterator

    iterator begin() const { return iterator(n_); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

private:
    IntType n_;

}; // end class DyckPaths

using boost::container::static_vector;

using dyck_paths = DyckPaths<int>;
using dyck_paths_stack = DyckPaths<int, static_vector<int, 48>>;

} // namespace discreture
