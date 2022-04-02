#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;
vector<int> dp, L, path;

int main()
{
	int x;
	while(~scanf("%d", &x)) arr.emplace_back(x);

	L.resize(arr.size());
	L[0] = 1;

	int ans = 0;
	if (arr.size()) dp.emplace_back(arr[0]);
	for (int i = 1; i < arr.size(); ++i)
	{
		if (arr[i] > dp.back())
		{
			dp.emplace_back(arr[i]);
			L[i] = dp.size();
		}
		else
		{
			auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
			*it = arr[i];
			L[i] = (it - dp.begin() + 1);
		}
		ans = max(ans, L[i]);
	}
	
	printf("%d\n-\n", ans);
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		if (L[i] == ans)
		{
			path.emplace_back(arr[i]);
			--ans;
		}
	}

	for (auto it = path.rbegin(); it != path.rend(); ++it)
		printf("%d\n", *it);
	/*
	printf("::debug\n");
	for (auto& it : dp)
	{
		printf("%d ", it);
	}
	puts("");
	*/

	return 0;
}
