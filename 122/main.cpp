#include <iostream>
#include <utility>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAXN = 300;

map<string, int> PATH;

void prtlevel()
{
	vector<int> output[301];
	for (auto it = PATH.begin(); it != PATH.end(); ++it)
	{
		output[it->first.size()].emplace_back(it->second);
	}

	if (output[1].size()) cout << output[1][0];
	for (int i = 2; i < 301; ++i)
	{
		for (auto it = output[i].begin(); it != output[i].end(); ++it)
			cout << " " << *it;
	}
	cout << '\n';
}

bool isVaild()
{
	if (PATH.size() == 0) return true;
	auto it = PATH.begin(); 
	if (it->first != "A") return false;
	++it;

	for (; it != PATH.end(); ++it)
	{
		string temp = it->first;
		temp = temp.substr(0, temp.size() - 1);
		if (PATH.find(temp) == PATH.end())
			return false;
	}
	return true;
}

int main()
{
	string s;
	bool oneAssign = true;
	while(cin >> s)
	{
		if (s == "()")
		{
			if (isVaild() && oneAssign)
				prtlevel();
			else
				cout << "not complete\n";
			
			oneAssign = true;
			PATH.clear();
			continue;
		}
		
		int v;
		char _;
		string path;
		stringstream ss;

		ss << s;
		ss >> _ >> v >> _ >> path;
		path = "A" + path.substr(0, path.size() - 1);

		oneAssign &= (PATH.find(path) == PATH.end());
		PATH[path] = v;
	}		
}
