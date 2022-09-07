#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = (1 << 14);
int offset[16];
int wi[maxn + 1];
int potency[maxn + 1];

int main()
{
#ifdef DEBUGing
	cerr << "debug mode on.\n";
#endif

	for (int i = 0; i < 16; ++i)
		offset[i] = (1 << i);

	int n;
	while(~scanf("%d", &n))
	{
		memset(potency, 0, sizeof(int) * maxn);
		int ans = 0;
		const int tot = (1 << n);
		
		for (int pt = 0; pt < tot; ++pt) 
		{
			scanf("%d", &wi[pt]);
			for (int j = 0; j < n; ++j)
			{
				int adjpt = pt ^ offset[j];
				potency[adjpt] += wi[pt];
			}
		}
#ifdef DEBUGing
		cerr << "n: " << n << '\n';
		cerr << "tot: " << tot << '\n';
		
		cerr << "wi: " << '\n' << '[' << wi[0];
		for (int i = 1; i < tot; ++i)
			cerr << ' ' << wi[i];
		cerr << ']' << '\n';

		cerr << "potency: " << '\n' << '[' << potency[0];
		for (int i = 1; i < tot; ++i)
			cerr << ' ' << potency[i];
		cerr << ']' << '\n';
#endif

		for (int pt = 0; pt < tot; ++pt)
			for (int j = 0; j < n; ++j)
			{
				int adjpt = pt ^ offset[j];
				ans = max(potency[adjpt] + potency[pt], ans);
			}
		printf("%d\n", ans);
	}
	return 0;
}
