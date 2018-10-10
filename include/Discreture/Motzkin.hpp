#pragma once

#include "Combinations.hpp"
#include "DyckPaths.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace discreture
{

////////////////////////////////////////////////////////////////////////////////////
/// \brief Class for iterating through all motzkin paths.
/// \param IntType must be a SIGNED integer type.
///
/// Motzkin paths are paths that go from \f$(0,0)\f$ to \f$(0,2n)\f$,
/// which never go below the \f$ y=0\f$ line, in which each step is from
/// \f$(x,y)\f$ to either \f$(x+1,y+1)\f$ or \f$(x+1,y-1)\f$ or \f$(x+1,y)\f$
/// #Example Usage:
///
///		motzkin_paths X(4)
///		for (auto&& x : X)
///			cout << x << endl;
/// Prints out:
///		[ 0 0 0 0 ]
///		[ 1 -1 0 0 ]
///		[ 1 0 -1 0 ]
///		[ 0 1 -1 0 ]
///		[ 1 0 0 -1 ]
///		[ 0 1 0 -1 ]
///		[ 0 0 1 -1 ]
///		[ 1 1 -1 -1 ]
///		[ 1 -1 1 -1 ]
///
///
/// # Example: Parenthesis
///
/// 	motzkin_paths X(4)
/// 	for (auto&& x : X)
/// 		cout << motzkin_paths::to_string(x, "(-)") << endl;
///
/// Prints out:
///		----
///		()--
///		(-)-
///		-()-
///		(--)
///		-(-)
///		--()
///		(())
///		()()
///
/////////////////////////////////////////////////////////////////////////////////////

template <class IntType = int, class RAContainerInt = std::vector<IntType>>
class MotzkinPaths
{
public:
    static_assert(std::is_integral<IntType>::value,
                  "Template parameter IntType must be integral");
    static_assert(std::is_signed<IntType>::value,
                  "Template parameter IntType must be signed");
    using value_type = RAContainerInt;
    using motzkin_path = value_type;
    using difference_type = std::ptrdiff_t;
    using size_type = difference_type;
    using comb_i = typename Combinations<IntType, RAContainerInt>::iterator;
    using dyck_i = typename DyckPaths<IntType, RAContainerInt>::iterator;
    class iterator;
    using const_iterator = iterator;

    static std::string to_string(const motzkin_path& data,
                                 const std::string& delim = "(-)")
    {
        std::string toReturn;

        for (auto i : data)
        {
            auto j = 1 - i;
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
    explicit MotzkinPaths(IntType n) : n_(n) {}

    ////////////////////////////////////////////////////////////
    /// \brief The total number of motzkin_paths
    ///
    /// \return M_n
    ///
    ////////////////////////////////////////////////////////////
    size_type size() const { return motzkin(n_); }

    IntType get_n() const { return n_; }

    iterator begin() const { return iterator(n_); }

    iterator end() const { return iterator::make_invalid_with_id(size()); }

    ////////////////////////////////////////////////////////////
    /// \brief Forward iterator class.
    ////////////////////////////////////////////////////////////
    class iterator
        : public boost::iterator_facade<iterator, const motzkin_path&, boost::forward_traversal_tag>
    {
    public:
        iterator() : data_(), comb_(), dyck_() {} // empty initializer

        explicit iterator(IntType n) : data_(n, 0), comb_(n, 0), dyck_(0) {}

        size_type ID() const { return ID_; }

        static iterator make_invalid_with_id(size_type id)
        {
            iterator it;
            it.ID_ = id;
            return it;
        }

    private:
        void increment()
        {
            ++ID_;
            auto n = data_.size();

            if (ID_ == motzkin(n))
                return;

            ++comb_;
            if (comb_.is_at_end(n))
            {
                ++dyck_;

                if (dyck_.is_at_end(num_nonzero_halved_))
                {
                    num_nonzero_halved_ += 1;

                    dyck_.reset(num_nonzero_halved_);
                }

                comb_.reset(n, 2*num_nonzero_halved_);
            }

            ConvertToMotzkin(); // TODO(mraggi): do this laziliy
        }

        const motzkin_path& dereference() const { return data_; }

        bool equal(const iterator& it) const { return it.ID() == ID(); }

    private:
        size_type ID_{0};
        motzkin_path data_;
        comb_i comb_;
        dyck_i dyck_;
        IntType num_nonzero_halved_{0};

        void ConvertToMotzkin()
        {
            // 				cout << "Converting: " << *comb_ << " and " <<
            // *dyck_
            // << endl;
            for (size_t i = 0; i < data_.size(); ++i)
            {
                data_[i] = 0;
            }

            size_t count = 0;

            for (auto x : (*comb_))
            {
                data_[x] = (*dyck_)[count];
                ++count;
            }
        }

        friend class boost::iterator_core_access;
    }; // end class iterator

private:
    IntType n_;
}; // end class MotzkinPaths

using boost::container::static_vector;

using motzkin_paths = MotzkinPaths<int>;
using motzkin_paths_stack = MotzkinPaths<int, static_vector<int, 48>>;

} // namespace discreture
