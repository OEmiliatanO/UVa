#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = 100;

int ages[maxn + 1];

int main()
{
	ios_base::sync_with_stdio(false);
	//cin.tie(0);

	int n;
	while(cin >> n, n)
	{
		for (int i = 0, x; i < n; ++i)
		{
			cin >> x;
			++ages[x];
		}

		for (int i = 1; i <= 100; ++i)
			while(ages[i])
			{
				cout << i << " ";
				--ages[i];
			}
		cout << '\n';
	}

	return 0;
}
