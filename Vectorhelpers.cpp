#include "Vectorhelpers.hpp"
#include "Probability.hpp"

namespace dscr
{

VB operator&(const VB& A, const VB& B)
{
    nuint size = std::min(A.size(), B.size());
    VB G;
    for (nuint i = 0; i < size; i++)
        G.push_back(A[i] && B[i]);
    return G;
}

VB operator|(const VB& A, const VB& B)
{
    nuint size = std::min(A.size(), B.size());
    VB G;
    for (nuint i = 0; i < size; i++)
        G.push_back(A[i] || B[i]);
    return G;
}

std::ostream& operator<<(std::ostream& os, const VUI& rhs)
{
    os << "[ ";
    for (nuint i = 0; i < rhs.size(); ++i)
        os << rhs[i] << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const VUC& rhs)
{
    os << "[ ";
    for (nuint i = 0; i < rhs.size(); ++i)
        os << suint(rhs[i]) << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const VSUI& rhs)
{
    os << "[ ";
    for (nuint i = 0; i < rhs.size(); ++i)
        os << suint(rhs[i]) << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const VB& rhs)
{
    os << "[";
    for (nuint i = 0; i < rhs.size(); ++i)
        os << rhs[i];
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<VB>& rhs)
{
    if (rhs.size() == 0)
        return os;
    nuint ncols = rhs.size();
    nuint nrows = rhs[0].size();
    for (nuint y = 0; y < nrows; ++y)
    {
        os << "[ ";
        for (nuint x=0; x< ncols; ++x)
        {
            os << rhs[x][y] << " ";
        }
        os << "]";
    }
    
    return os;
}

}

/*
bool operator<=(const SVUC& lhs, const SVUC& rhs)
{
    assert (lhs.size() == rhs.size());
    for (SVUC::const_iterator i = lhs.begin(); i != lhs.end(); ++i)
    {
        if (rhs[i.index()] < *i)
            return false;
    }
    return true;
}

bool operator==(const SVUC& lhs, const SVUC& rhs)
{
    assert (lhs.size() == rhs.size());
    nuint sumalhs = 0;
    for (SVUC::const_iterator i = lhs.begin(); i != lhs.end(); ++i)
    {
        if (rhs[i.index()] != *i)
            return false;
        sumalhs += *i;
    }
    if (sumalhs != Sum(rhs))
        return false;
    return true;
}*/