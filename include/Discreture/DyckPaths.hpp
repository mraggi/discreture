#pragma once

#include "ArithmeticProgression.hpp"
#include "Misc.hpp"
#include "Sequences.hpp"
#include "VectorHelpers.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace dscr
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
///     for (const auto& x : X)
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
///     for (const auto& x : X)
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
template <class IntType, class RAContainerInt = std::vector<IntType>>
class basic_dyck_paths
{
public:
    using value_type = RAContainerInt;
    using dyck_path = value_type;
    using difference_type = long long; // NOLINT
    using size_type = difference_type;
    class iterator;
    using const_iterator = iterator;

    // **************** Begin static functions
    static void next_dyck_path(dyck_path& data)
    {
        size_t m_n = data.size()/2;

        if (m_n == 0)
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

        while (i < m_n && verif == 0)
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
    explicit basic_dyck_paths(IntType n) : m_n(n) {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of dyck_paths
    ///
    /// \return binomial(2n,n)/(n+1)
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return catalan(m_n); }

    IntType get_n() const { return m_n; }

    ////////////////////////////////////////////////////////////
    /// \brief Forward iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator,
                                        const dyck_path&,
                                        boost::forward_traversal_tag>
    {
    public:
        iterator() = default; // empty initializer
        explicit iterator(IntType n) : m_ID(0), m_data(2*n, 1)
        {
            for (size_t i = n; i < m_data.size(); ++i)
                m_data[i] = -1;
        }

        size_type ID() const { return m_ID; }

        bool is_at_end(IntType n) const { return m_ID == catalan(n); }

        void reset(IntType n)
        {
            m_ID = 0;
            m_data.resize(2*n);
            auto r = static_cast<size_t>(n);
            for (size_t i = 0; i < r; ++i)
                m_data[i] = 1;

            for (size_t i = r; i < m_data.size(); ++i)
                m_data[i] = -1;
        }

        static const iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.m_ID = id;
            return it;
        }

    private:
        void increment()
        {
            ++m_ID;

            next_dyck_path(m_data);
        }

        const dyck_path& dereference() const { return m_data; }

        bool equal(const iterator& it) const { return it.ID() == ID(); }

    private:
        size_type m_ID{0};
        dyck_path m_data{};

        friend class boost::iterator_core_access;
    }; // end class iterator

    iterator begin() const { return iterator(m_n); }

    const iterator end() const
    {
        return iterator::make_invalid_with_id(size());
    }

private:
    IntType m_n;

}; // end class basic_dyck_paths

using dyck_paths = basic_dyck_paths<int>;
using dyck_paths_fast =
  basic_dyck_paths<int, boost::container::static_vector<int, 48>>;

} // namespace dscr
