#pragma once

#include <vector>
#include "Misc.hpp"
#include <cassert>
#include <algorithm>
#include <list>

namespace dscr
{
	// Typedefs
	typedef vector<bool> VB;
	typedef vector<char> VC;
	typedef vector<sint> VSI;
	typedef vector<int> VI;
	typedef vector<lint> VLI;

	typedef vector<nuint> VUI;
	typedef vector<suint> VSUI;
	typedef vector<size_t> VLUI;
	typedef vector<uchar> VUC;

	typedef vector<double> VR;

	//////////////////////////////////////
	/// \brief Bitwise and for vector<bool>
	//////////////////////////////////////
	VB operator&(const VB& A, const VB& B);
	
	//////////////////////////////////////
	/// \brief Bitwise or for vector<bool>
	//////////////////////////////////////
	VB operator|(const VB& A, const VB& B);

	////////////////////////////////////
	/// \brief Converts a vector<U> into a vector<T>, provided U can be converted to T
	////////////////////////////////////	
	template<class T, class U> 
	vector<T> Convert(const vector<U>& G)
	{
		auto n = G.size();
		vector<T> toReturn(n,0);
		for (size_t i = 0; i  < n; ++i)
		{
			toReturn[i] = static_cast<T>(G[i]);
		}
		return toReturn;
	}

	////////////////////////////////////
	/// \brief prints out a space separated vector.
	////////////////////////////////////
	template <class T> 
	std::ostream& operator<<(std::ostream& os, const vector<T>& rhs)
	{
		os << "[ ";
		for (const auto& x : rhs)
			os << x << " ";
		os << "]";
		return os;
	}
	
	////////////////////////////////////
	/// \brief prints out a space separated list.
	////////////////////////////////////
	template <class T> 
	std::ostream& operator<<(std::ostream& os, const std::list<T>& rhs)
	{
		os << "[ ";
		for (const auto& x : rhs)
			os << x << " ";
		os << "]";
		return os;
	}

	////////////////////////////////////
	/// \brief Find the minimum value of a vector.
	////////////////////////////////////
	template <class T> 
	T min(const vector<T>& v)
	{
		assert (v.size() > 0);
		T m = v[0];
		for (size_t i = 1; i < v.size(); ++i)
		{
			if (v[i] < m)
				m = v[i];
		}
		return m;
	}

	////////////////////////////////////
	/// \brief Find the max value of a vector.
	////////////////////////////////////
	template <class T> 
	T max(const vector<T>& v)
	{
		assert (v.size() > 0);
		T m = v[0];
		for (size_t i = 1; i < v.size(); ++i)
		{
			if (v[i] > m)
				m = v[i];
		}
		return m;
	}

	////////////////////////////////////
	/// \brief Find the minimum index of a vector.
	////////////////////////////////////
	template <class T> 
	size_t argmin(const vector<T>& v)
	{
		assert (v.size() > 0);
		T m = v[0];
		size_t bestisofar = 0;
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (v[i] < m)
			{
				m = v[i];
				bestisofar = i;
			}
		}
		return bestisofar;
	}

	////////////////////////////////////
	/// \brief Find the maximum index of a vector.
	////////////////////////////////////
	template <class T> 
	size_t argmax(const vector<T>& v)
	{
		assert (v.size() > 0);
		T m = v[0];
		size_t bestisofar = 0;
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (m < v[i])
			{
				m = v[i];
				bestisofar = i;
			}
		}
		return bestisofar;
	}


	////////////////////////////////////
	/// \brief vector coordinate-wise addition.
	////////////////////////////////////
	template<class T>
	inline vector<T> operator+(const vector<T>& U, const vector<T>& V)
	{
		assert(U.size() == V.size());
		auto toReturn = U;
		for (size_t i = 0; i < U.size(); ++i)
		{
			toReturn[i] += V[i];
		}
		return toReturn;
	}


	////////////////////////////////////
	/// \brief inplace vector coordinate-wise addition.
	////////////////////////////////////
	template<class T>
	inline void operator+=(vector<T>& U, const vector<T>& V)
	{
		assert(U.size() == V.size());
		for (size_t i = 0; i < U.size(); ++i)
		{
			U[i] += V[i];
		}
	}

	////////////////////////////////////
	/// \brief inplace vector coordinate-wise division by a number.
	////////////////////////////////////
	template<class T, class NumType>
	inline void operator/=(vector<T>& U, NumType t)
	{
		//assert(U.size() == V.size());
		for (size_t i = 0; i < U.size(); ++i)
		{
			U[i] /= t;
		}
	}
	
	////////////////////////////////////
	/// \brief inplace vector coordinate-wise multiplication by a number.
	////////////////////////////////////
	template<class T, class NumType>
	inline void operator*=(vector<T>& U, NumType t)
	{
		//assert(U.size() == V.size());
		for (size_t i = 0; i < U.size(); ++i)
		{
			U[i] *= t;
		}
	}
	
	////////////////////////////////////
	/// \brief coordinate-wise multiplication by a number.
	////////////////////////////////////
	template<class T, class NumType>
	inline vector<T> operator*(vector<T> U, NumType t)
	{
		//assert(U.size() == V.size());
		U *= t;
		return U;
	}
	
	////////////////////////////////////
	/// \brief coordinate-wise division by a number.
	////////////////////////////////////
	template<class T, class NumType>
	inline vector<T> operator/(vector<T> U, NumType t)
	{
		//assert(U.size() == V.size());
		U /= t;
		return U;
	}

	//////////////////////////
	/// \brief returns a vector W such that for each coordinate i, W[i] = min(V[i],U[i])
	//////////////////////////
	template<class T>
	inline vector<T> mincac(const vector<T>& U, const vector<T>& V)
	{
		assert(U.size() == V.size());
		vector<T> toReturn(U.size());
		for (size_t i = 0; i < U.size(); ++i)
		{
			toReturn[i] = std::min(U[i], V[i]);
		}
		return toReturn;
	}
	
	//////////////////////////
	/// \brief returns a vector W such that for each coordinate i, W[i] = max(V[i],U[i])
	//////////////////////////
	template<class T>
	inline vector<T> maxcac(const vector<T>& U, const vector<T>& V)
	{
		assert(U.size() == V.size());
		vector<T> toReturn(U.size());
		for (size_t i = 0; i < U.size(); ++i)
		{
			toReturn[i] = std::max(U[i], V[i]);
		}
		return toReturn;
	}

// 	std::ostream& operator<<(std::ostream& os, const VUI& rhs);
// 	std::ostream& operator<<(std::ostream& os, const VSUI& rhs);

	/////////////////////////////
	/// \brief Specialization for vector printouts for vector<unsigned char>
	/////////////////////////////
	std::ostream& operator<<(std::ostream& os, const VUC& rhs);
	
	/////////////////////////////
	/// \brief Specialization for vector printouts for vector<bool> so that it doesn't print out spaces
	/////////////////////////////
	std::ostream& operator<<(std::ostream& os, const VB& rhs);

	/////////////////////////////
	/// \brief Lexicographic compare vector A and B
	/// \return A <= B in lexicographic order.
	/////////////////////////////
	template <class T>
	bool operator<=(const vector<T>& A, const vector<T>& B)
	{
		size_t a = A.size();
		assert (a == B.size());
		
		for (size_t i = 0; i < a; ++i)
		{
			if (A[i] > B[i])
				return false;
		}
		return true;
	}

	/////////////////////////////
	/// \brief Equality comparison of vectors
	/// \return A <= B in lexicographic order.
	/////////////////////////////
	template <class T>
	bool operator==(const vector<T>& A, const vector<T>& B)
	{
		size_t a = A.size();
		if (B.size() != a) return false;
		
		for (size_t i = 0; i < a; ++i)
		{
			if (A[i] != B[i])
				return false;
		}
		return true;
	}

	// TODO: Move this to an appropiate place and give it a proper name
	///////////////////////////
	/// \brief Given a subset S, written in combination form (1,2,4), returns the same subset written in subset form (01101)
	///////////////////////////
	template <class T>
	VB CombinationToSubset(const vector<T>& C, size_t size)
	{
		VB toReturn(size,0);
		for (size_t i = 0; i < C.size(); ++i)
		{
			assert (C[i] < size);
			toReturn[C[i]] = 1;
		}
		return toReturn;
	}

	///////////////////////////
	/// \brief Function composition
	/// 
	/// \return f o g
	///////////////////////////
	template <class vecT, class UIntType>
	vecT compose(const vecT& f, const vector<UIntType>& g)
	{
// 		typename vecT::value_type u(0);
		vecT toReturn(g.size());
		for (size_t i = 0; i < g.size(); ++i)
		{
			assert(g[i] < f.size());
			toReturn[i] = f[g[i]];
		}
		return toReturn;
	}
	
	template <class T>
	bool AreTheyAllDifferent(const vector<T>& G)
	{
		vector<T> copyG = G;
		std::sort(copyG.begin(), copyG.end());
		
		for (size_t i = 0; i < copyG.size()-1; ++i)
		{
			if (G[i] == G[i+1])
			{
				return false;
			}
		}
		return true;
	}
/*
// 	template <class T>
// 	bool AreTheyAllDifferent(const vector<T>& G, size_t maxnumber)
// 	{
// 		VB chosen(maxnumber,false);
// 		for (size_t i = 0; i < G.size(); ++i)
// 		{
// 			if (chosen[G[i]])
// 			{
// 				return false;
// 			} 
// 			chosen[G[i]] = true;
// 		}
// 		return true;
// 	}


	void Normalize(VR& W);
	size_t ChooseIndexWithProbabilityNormalized(const vector<double>& W);

	template<class T>
	vector<double> Normalized(const vector<T>& W)
	{
		double s = Sum(W);
		vector<double> toReturn = Convert<double, T>(W);
		for (size_t i=0; i < W.size(); ++i)
		{
			toReturn[i] /= s;
		}
		return toReturn;
	}
	
	/// Assumes W is a vector w_0 < w_1 < ... < w_n = 1, and we choose r in (0,1) uniformly at random, then pick the first i for which w_i > r.
	size_t ChooseIndexWithProbabilityPartialSums(const vector<double>& W);

	template <class T>
	size_t ChooseIndexWithProbability(const vector<T>& W)
	{
		vector<double> WR = Normalized(W);
		return ChooseIndexWithProbabilityNormalized(WR);
	}
	
	void PartialSums(vector<double>& W);

	template <class T>
	class LexicographicOrder
	{
	public:
		bool operator()(const vector<T>& lhs, const vector<T>& rhs) const
		{
			size_t size = lhs.size();
			for (size_t i = 0; i < size; ++i)
			{
				if (lhs[i] < rhs[i])
					return true;
				if (lhs[i] > rhs[i])
					return false;
			}
			return false;
		}
	};*/

}