#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int S, N;

struct ele
{
	int n, maxcov, arr[11];
}eles[11];

bool cmp(ele& lhs, ele& rhs)
{
	if (lhs.maxcov == rhs.maxcov)
	{
		if (lhs.n == rhs.n)
		{
			int i = 1;
			int* p = lhs.arr + lhs.n, * q = rhs.arr + rhs.n;
			while(i < lhs.n && i < rhs.n && *(p - i) == *(q - i)) ++i;
			return *(p - i) > *(q - i);
		}
		return lhs.n > rhs.n;
	}
	return lhs.maxcov < rhs.maxcov;
}

int dp[1005];
int main()
{
	while(~scanf("%d", &S) && S)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			memset(dp, 0x7f, sizeof(dp));
			dp[0] = 0;

			scanf("%d", &eles[i].n);
			int* v = eles[i].arr;
			for (int j = 0; j < eles[i].n; ++j)
				scanf("%d", &v[j]);

			for (int j = 0; j < eles[i].n; ++j)
			{
				for (int tg = 1; tg <= v[j] * S; ++tg)
				{
					if (tg - v[j] < 0) continue;
					dp[tg] = min(dp[tg], dp[tg - v[j]] + 1);
					//if (dp[tg] > S) break;
				}
			}
			int j = 1;
			while(dp[j] <= S) ++j;
			eles[i].maxcov = j - 1;

			/*
			for (int tg = 1; tg <= 1001; ++tg)
			{
				for (int j = 0; j < eles[i].n; ++j)
				{
					if (tg - v[j] < 0) break;
					dp[tg] = min(dp[tg], dp[tg - v[j]] + 1);
				}
				if (dp[tg] > S)
				{
					eles[i].maxcov = tg - 1;
					break;
				}
			}
			*/
		}
		
		sort(eles, eles + N, cmp);

		/*
		int bestcov = -1, num = -1;
		for (int i = 0; i < N; ++i)
		{
			if (bestcov < eles[i].maxcov)
			{
				bestcov = eles[i].maxcov;
				num = i;
			}
			else if (bestcov == eles[i].maxcov)
			{
				if (eles[i].n < eles[num].n)
				{
					num = i;
					continue;
				}
				else if (eles[i].n == eles[num].n)
				{
					int j = 1;
					while(j < eles[i].n && j < eles[num].n && eles[i].arr[eles[i].n - j] == eles[num].arr[eles[num].n - j])
						++j;
					if (eles[i].arr[eles[i].n - j] < eles[num].arr[eles[num].n - j])
						num = i;
				}
			}
		}
		*/
		
		printf("max coverage =%4d :", eles[N - 1].maxcov);
		for (int i = 0; i < eles[N - 1].n; ++i)
			printf("%3d", eles[N - 1].arr[i]);
		putchar('\n');
	}
	return 0;
}
