#include <iostream>
#include <algorithm>
#include <cstring>

#define lowbit(x) ((x) & (~(x)+1))

using namespace std;

constexpr int maxn = (int)1e6;
int arr[maxn + 5];
int tmp[maxn + 5];

int64_t merge(int *l1, int len1, int *l2, int len2)
{
	int l = 0, r = 0, k = 0;
	int64_t res = 0;

	while (l < len1 && r < len2)
		if (l1[l] > l2[r])
		{
			res += len1 - l;
			tmp[k++] = l2[r++];
		}
		else
			tmp[k++] = l1[l++];

	while (l < len1) tmp[k++] = l1[l++];
	while (r < len2) tmp[k++] = l2[r++];
	memcpy(l1, tmp, sizeof(int) * (len1 + len2));
	return res;
}

int64_t merge_sort(int *l, int *r)
{
	if (r <= l || r - l == 1) return 0;

	int *mid = l + (r-l)/2;
	int64_t res = 0;

	res += merge_sort(l, mid);
	res += merge_sort(mid, r);
	res += merge(l, (mid - l), mid, (r - mid));
	
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	while (cin >> n, n)
	{
		for (int i = 0; i < n; ++i)
			cin >> arr[i];
		cout << merge_sort(arr, arr + n) << '\n';
	}
	return 0;
}
