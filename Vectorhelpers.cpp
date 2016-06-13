#include "Vectorhelpers.hpp"
#include "Probability.hpp"

namespace dscr
{

vector<bool> operator&(const vector<bool>& A, const vector<bool>& B)
{
    size_t size = std::min(A.size(), B.size());
    vector<bool> G;
    for (size_t i = 0; i < size; i++)
        G.push_back(A[i] && B[i]);
    return G;
}

vector<bool> operator|(const vector<bool>& A, const vector<bool>& B)
{
    size_t size = std::min(A.size(), B.size());
    vector<bool> G;
    for (size_t i = 0; i < size; i++)
        G.push_back(A[i] || B[i]);
    return G;
}

std::ostream& operator<<(std::ostream& os, const vector<unsigned>& rhs)
{
    os << "[ ";
    for (size_t i = 0; i < rhs.size(); ++i)
        os << rhs[i] << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<unsigned char>& rhs)
{
    os << "[ ";
    for (size_t i = 0; i < rhs.size(); ++i)
        os << short(rhs[i]) << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<bool>& rhs)
{
    os << "[";
    for (size_t i = 0; i < rhs.size(); ++i)
        os << rhs[i];
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<vector<bool>>& rhs)
{
    if (rhs.size() == 0)
        return os;
    size_t ncols = rhs.size();
    size_t nrows = rhs[0].size();
    for (size_t y = 0; y < nrows; ++y)
    {
        os << "[ ";
        for (size_t x=0; x< ncols; ++x)
        {
            os << rhs[x][y] << " ";
        }
        os << "]";
    }
    
    return os;
}

}

/*
bool operator<=(const Svector<unsigned char>& lhs, const Svector<unsigned char>& rhs)
{
    assert (lhs.size() == rhs.size());
    for (Svector<unsigned char>::const_iterator i = lhs.begin(); i != lhs.end(); ++i)
    {
        if (rhs[i.index()] < *i)
            return false;
    }
    return true;
}

bool operator==(const Svector<unsigned char>& lhs, const Svector<unsigned char>& rhs)
{
    assert (lhs.size() == rhs.size());
    nuint sumalhs = 0;
    for (Svector<unsigned char>::const_iterator i = lhs.begin(); i != lhs.end(); ++i)
    {
        if (rhs[i.index()] != *i)
            return false;
        sumalhs += *i;
    }
    if (sumalhs != Sum(rhs))
        return false;
    return true;
}*/
