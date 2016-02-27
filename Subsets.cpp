#include "Subsets.hpp"
#include "Sequences.hpp"
#include <cassert>

namespace dscr
{
// 	luint ToInteger(const VB& set)
// 	{
// 		assert(set.size() < 64);
// 		luint r = 0;
// 		
// 		for (suint i = 0; i < set.size(); ++i)
// 		{
// 			if (set[i])
// 				r += (luint(1) << i);
// 		}
// 		
// 		return r;
// 	}
// 
// 	const vector<VB>& Subsets(nuint n, nuint r)
// 	{
// 		const nuint size = 64;
// 		static vector<VB> SubsetDone(size, VB(size,false));
// 		static vector<vector<vector<VB> > > SubSets(size,vector<vector<VB> >(size, vector<VB>()));
// 
// 		assert((n < size) && (r < size) && "vector<VB> subsets");
// 		
// 		if (SubsetDone[n][r])
// 			return SubSets[n][r];
// 		
// 		SubSets[n][r].reserve(binomial(n,r));
// 		
// 		VB G(n,0);
// 		for (nuint i = 0; i < r; ++i)
// 			G[i] = 1;
// 		
// 		SubsetIteratorDecreasingOrder<bool> X(n);
// 		
// 		int currentsize;
// 		while (static_cast<unsigned>(currentsize = X.Next(G)) == r)
// 		{
// 				SubSets[n][r].push_back(G);
// 		}
// 
// 		SubsetDone[n][r] = true;
// 
// 		return SubSets[n][r];
// 	}
// 
// 	VB RandomSubset(nuint n)
// 	{
// 		//const nuint numBitsPerInt = sizeof(int)*8-1;
// 		const nuint numBitsPerInt = 4;
// 		VB subset(n, 0);
// 		nuint numtimesIllhavetocallrand = ceil(double(n)/numBitsPerInt);
// 		
// 		//cout << "n = " << n << endl;
// 		//cout << "numBitsPerInt = " << numBitsPerInt << endl;
// 		//cout << "numtimesIllhavetocallrand = " << numtimesIllhavetocallrand << endl;
// 		
// 		for (nuint multiplier = 0; multiplier < numtimesIllhavetocallrand; ++multiplier)
// 		{
// 			int r = rand();
// 			nuint h = std::min((multiplier+1)*numBitsPerInt,n);
// 			for (nuint i = multiplier*numBitsPerInt; i < h; ++i)
// 			{
// 				//cout << "i = " << i << endl;
// 				//cout << "i%num = " << i%numBitsPerInt << endl;
// 				subset[i] = bool((r >> (i%numBitsPerInt))%2);
// 			}
// 			//cout << "------------------------------------" << endl;
// 		}
// 		
// 		return subset;
// 		
// 	}
// 
// 	VB RandomSubset(const VB& set)
// 	{
// 		VB G = RandomSubset(set.size());
// 		for (nuint i = 0; i < G.size(); ++i)
// 		{
// 			G[i] = G[i] && set[i];
// 		}
// 		return G;
// 	}
}
