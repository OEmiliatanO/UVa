#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

constexpr int maxn = 100;
string arr[maxn + 1];

int main()
{
	int M;
	cin >> M;
	while(M--)
	{
		int n, m;
		cin >> n >> m; cin.ignore();
		for (int i = 0; i < m; ++i) getline(cin, arr[i]);

		stable_sort(arr, arr + m, [](const string& lhs, const string& rhs) {
				int l = 0, r = 0;
				for (auto it = lhs.begin(); it != lhs.end(); ++it)
					for (auto comp = it + 1; comp != lhs.end(); ++comp)
						l += (*it > *comp);
				for (auto it = rhs.begin(); it != rhs.end(); ++it)
					for (auto comp = it + 1; comp != rhs.end(); ++comp)
						r += (*it > *comp);
				return l < r;
				});
		
		for (int i = 0; i < m; ++i) cout << arr[i] << '\n';
		if (M) cout << '\n';
	}

	return 0;
}
