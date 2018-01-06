#include "discreture.hpp"
#include <cstdlib>
#include <sstream>
#include <string>



int main()
{
	using std::cout;
	using std::endl;
	using std::stringstream;
	using dscr::multisets;
	using dscr::operator<<;
	std::ios_base::sync_with_stdio(false);

	std::vector<int> total = {3,2,1,1};
	
	cout << "These are all the submultisets of " << total << endl;
	
	auto X = multisets(total);
	int i =  0;
	for (auto& x : X)
	{
		cout << x << endl;
// 		cout << x << " <---" << i << " == " << X.get_index(x) << endl;
// 		multisets::multiset u(total.size());
// 		multisets::construct_multiset(u,total,i);
// 		cout << "Constructed: " << u << endl;
// 		++i;
	}
// 	return 0;
	cout << "And here they are in reverse order: " << endl;
	for (auto it = X.rbegin(); it != X.rend(); ++it)
	{
		cout << *it << endl;
	}
	
	return 0;
}
