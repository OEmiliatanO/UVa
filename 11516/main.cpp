#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAXM = (int)1e5;

int T;
int n, m;
int arr[MAXM + 1];

int search(int l, int r)
{
	if (l >= r) return l;

	int mid = (l + r) >> 1;

	//cout << "l = " << l << '\n';
	//cout << "r = " << r << '\n';
	//cout << "mid = " << mid << '\n';
	int usecnt = 0;
	for (int i = 0; i < m;)
	{
		int maxcover = arr[i] + mid;
		++usecnt;
		while (i < m && arr[i] <= maxcover) ++i;
	}

	//cout << "usecnt = " << usecnt << '\n';
	if (usecnt <= n) r = mid;
	else l = mid + 1;

	return search(l, r);
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n >> m;
		for (int i = 0; i < m; ++i)
		{
			cin >> arr[i];
		}

		sort(arr, arr + m);
		
		printf("%.1f\n", search(0, arr[m - 1] - arr[0]) / 2.0);
	}
	return 0;
}
