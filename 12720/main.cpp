#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = (int)1e5;
constexpr long long m = (int)1e9 + 7;

char s[maxn + 1];

int main()
{
	int T;
	scanf("%d", &T); getchar();
	for (int kase = 1; kase <= T; ++kase)
	{
		long long S = 0;
		scanf("%[^\n]s", s); getchar();
		int len = strlen(s);
		printf("Case #%d: ", kase);
		int l = len / 2 - (!(len & 1)), r = len / 2;
		int loffset = 0, roffset = 0;
#ifdef DEBUGing
		cerr << "s: " << s << '\n';
		cerr << "len: " << len << '\n';
		cerr << "l: " << l << ", r: " << r << '\n';
		cerr << "loffset: " << loffset << ", roffset: " << roffset << '\n';
#endif
		if (l == r) loffset = 1, roffset = 1, S ^= (s[l] - '0');
		while (l - loffset != -1 || r + roffset != len)
		{
#ifdef DEBUGing
			cerr << "loffset:" << loffset << '\n';
			cerr << "roffset:" << roffset << '\n';
#endif
			if (loffset == roffset)
			{
#ifdef DEBUGing
				cerr << "loffest == roffset:" << '\n';
				cerr << s[l - loffset] << ' ' << s[r + roffset] << '\n' << '\n';
#endif
				S <<= 1;
				if (s[l - loffset] > s[r + roffset])
				{
					S ^= 1;
					++loffset;
				}
				else
				{
					S ^= (s[r + roffset] - '0');
					++roffset;
				}
			}
			else if (loffset > roffset)
			{
#ifdef DEBUGing
				cerr << "loffest > roffset:" << '\n';
				cerr << s[l - loffset] << ' ' << s[r + roffset] << '\n' << '\n';
#endif
				S <<= 1;
				S ^= (s[r + roffset] - '0');
				++roffset;
			}
			else
			{
#ifdef DEBUGing
				cerr << "loffest < roffset:" << '\n';
				cerr << s[l - loffset] << ' ' << s[r + roffset] << '\n' << '\n';
#endif
				S <<= 1;
				S ^= (s[l - loffset] - '0');
				++loffset;
			}
			S %= m;
		}
		printf("%lld\n", S);
	}
	return 0;
}
