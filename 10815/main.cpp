#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> vec;

int main()
{
	string s;
	while(cin >> s)
	{
		string aftpros;
		for (auto it = s.begin(); it != s.end(); *it = tolower(*it), ++it)
			if (!isalpha(*it))
				*it = ' ';

		stringstream ss(s);
		while(ss >> aftpros)
			vec.emplace_back(aftpros);
	}
	sort(vec.begin(), vec.end());
	auto ed = unique(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != ed; ++it)
	{
		if ((*it).empty() || *it == "") continue;
		cout << *it << endl;
	}

	return 0;
}
