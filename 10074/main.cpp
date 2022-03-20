#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr int MAXN = 100;

int M, N;
int arr[MAXN + 3][MAXN + 3];


void init()
{
	for (int i = 1; i <= M; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
		}
	}
	/*
	for (int i = 1; i <= M; ++i)
	{
		for(int j = 1; j <= N; ++j)
			cout << arr[i][j] << " ";
		cout << '\n';
	}
	*/
}

int getnum(int sti, int stj, int edi, int edj)
{
	return arr[edi][edj] - arr[sti - 1][edj] - arr[edi][stj - 1] + arr[sti - 1][stj - 1];
}

int main()
{
	while(cin >> M >> N, M && N)
	{
		memset(arr, 0, sizeof(int) * (MAXN + 3) * (MAXN + 3));
		for (int i = 1; i <= M; ++i)
			for (int j = 1; j <= N; ++j)
			{
				cin >> arr[i][j];
			}
		
		//init();
		
		int ans = 0;
		for (int i = 1; i <= M; ++i)
		{
			int sum[MAXN + 3]{};
			for (int j = i; j <= M; ++j)
			{
				int area = 0, len = 0, width = j - i + 1;
				for (int a = 1; a <= N; ++a)
				{
					sum[a] += !arr[j][a];
					area += sum[a];
					++len;
					if (len * width == area)
						ans = max(ans, area);
					else
						area = len = 0;
					/*
					for (int b = j; b <= N; ++b)
					{
						if (getnum(i, j, a, b)) break;
						ans = max(ans, (b - j + 1) * (a - i + 1));
					}
					*/
				}
			}
		}

		cout << ans << '\n';
	}

	return 0;
}
