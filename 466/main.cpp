#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr int maxn = 10;

int n;
char src[maxn+2][maxn+2];
char res[4][maxn+2][maxn+2];
char target[maxn+2][maxn+2];

void r90()
{
	for (int i = 0, srci = n - 1; i < n; --srci, ++i)
		for (int j = 0, srcj = n - 1; j < n; --srcj, ++j)
			res[0][i][j] = src[i][j];
}

void r180()
{
	for (int i = 0, srci = n - 1; i < n; --srci, ++i)
		for (int j = 0, srcj = n - 1; j < n; --srcj, ++j)
			res[1][i][j] = src[srci][srcj];
}

void r270()
{
	for (int i = 0, srci = n - 1; i < n; --srci, ++i)
		for (int j = 0, srcj = n - 1; j < n; --srcj, ++j)
			res[2][i][j] = src[i][j];
}

void vRef()
{
	for (int i = 0, srci = n - 1; i < n; ++i, --srci)
		for (int j = 0; j < n; ++j)
			res[3][i][j] = src[srci][j];
}

int main()
{
	while(~scanf("%d", &n))
	{
		getchar();
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				scanf("%c", &src[i][j]);

			getchar();

			for (int j = 0; j < n; ++j)
				scanf("%c", &target[i][j]);

			getchar();
		}
		
		r90();
		r180();
		r270();
		vRef();

		for (int k = 0; k < 4; ++k, puts("\n"))
			for (int i = 0; i < n; ++i, putchar('\n'))
				for (int j = 0; j < n; ++j)
					printf("%c", (int)res[k][i][j]);

		putchar('\n');
	}

	return 0;
}
