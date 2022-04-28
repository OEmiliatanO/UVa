#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

constexpr int MAXM = 500;

int n;
int k, m;
int64_t p[MAXM + 1];
deque<int64_t> S[MAXM + 1];

int64_t search(int64_t l, int64_t r)
{
	if (l >= r) return l;

	int64_t mid = (l + r) >> 1;
	int64_t sum = 0;
	int partition = 1;
	for (int i = 0; i < m; ++i)
	{
		if (sum + p[i] <= mid)
			sum += p[i];
		else
		{
			sum = p[i];
			++partition;
			if (partition > k)
				return search(mid + 1, r);
		}
	}

	return search(l, mid);
}

int main()
{
	cin >> n;
	while(n--)
	{
		int64_t uppbound = 0, lowbound = 0;

		cin >> m >> k;
		for (int i = 0; i < m; ++i)
		{
			S[i].clear();
			cin >> p[i];
			lowbound = max(lowbound, p[i]);
			uppbound += p[i];
		}

		int64_t ans = search(lowbound, uppbound);
		int64_t sum = 0;
		int si = 1;
		for (int i = m - 1; i >= 0; --i)
		{
			if (sum + p[i] <= ans)
			{
				sum += p[i];
				S[si].emplace_front(p[i]);
			}
			else
			{
				sum = p[i];
				S[++si].emplace_front(p[i]);
			}
		}
		
		/*
		cout << "debug:\n";
		for (int i = 1; i <= si; ++i)
		{
			for (auto it : S[i])
				cout << it << " ";
			cout << "\n";
		}
		cout << "------\n";
		*/

		for (int i = si; i >= 1; --i)
		{
			cout << S[i][0] << " \n"[i == 1 && S[i].size() == 1];
			for (size_t j = 1; j < S[i].size(); ++j)
			{
				if (si < k)
				{
					cout << "/ ";
					++si;
				}
				cout << S[i][j] << " \n"[i == 1 && j == S[i].size() - 1];
			}
			if (i > 1) cout << "/ ";
		}
	}
	return 0;
}
