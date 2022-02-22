#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int MAXN = 30000;

int arr[MAXN + 1];
priority_queue<int, vector<int>, greater<int> > pqMIN;
priority_queue<int> pqMAX;

int main()
{
	int K;
	scanf("%d", &K);
	while(K--)
	{
		pqMIN = priority_queue<int, vector<int>, greater<int> >();
		pqMAX = priority_queue<int>();
		int N, M, ord = 1, putPos = 1;

		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i)
			scanf("%d", arr + i);
		
		pqMIN.emplace(arr[0]);
		for (int i = 0; i < M; ++i)
		{
			int towhere;
			scanf("%d", &towhere);
			while(putPos < towhere)
			{
				int x = arr[putPos++];
				if (x >= pqMIN.top()) pqMIN.emplace(x);
				else
				{
					pqMAX.emplace(x);
					while(pqMAX.size() >= ord)
					{
						pqMIN.emplace(pqMAX.top());
						pqMAX.pop();
					}
				}
			}
			printf("%d\n", pqMIN.top());

			++ord;
			while(pqMAX.size() < ord - 1)
			{
				pqMAX.emplace(pqMIN.top());
				pqMIN.pop();
			}
		}
		
		if (K > 0) putchar('\n');
	}

	return 0;
}
