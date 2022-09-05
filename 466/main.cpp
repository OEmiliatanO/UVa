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
	for (int i = 0, srcj = 0; i < n; ++srcj, ++i)
		for (int j = 0, srci = n - 1; j < n; --srci, ++j)
			res[0][i][j] = src[srci][srcj];
}

void r180()
{
	for (int i = 0, srci = n - 1; i < n; --srci, ++i)
		for (int j = 0, srcj = n - 1; j < n; --srcj, ++j)
			res[1][i][j] = src[srci][srcj];
}

void r270()
{
	for (int i = 0, srcj = n - 1; i < n; --srcj, ++i)
		for (int j = 0, srci = 0; j < n; ++srci, ++j)
			res[2][i][j] = src[srci][srcj];
}

void vRef()
{
	for (int i = 0, srci = n - 1; i < n; ++i, --srci)
		for (int j = 0; j < n; ++j)
			res[3][i][j] = src[srci][j];
}

bool eq(int k)
{
	bool eq = true;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			eq &= (res[k][i][j] == target[i][j]);
	return eq;
}

int main()
{
	int kase = 1;
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
		
		printf("Pattern %d was ", kase++);

		bool flag = true;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				flag &= (src[i][j] == target[i][j]);
		
		if (flag) { printf("preserved.\n"); continue; }

		r90();
		r180();
		r270();
		vRef();

		if (eq(0))
			printf("rotated 90 degrees.\n");
		else if (eq(1))
			printf("rotated 180 degrees.\n");
		else if (eq(2))
			printf("rotated 270 degrees.\n");
		else if (eq(3))
			printf("reflected vertically.\n");
		else
		{
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					src[i][j] = res[3][i][j];
			r90();
			r180();
			r270();
			if (eq(0))
				printf("reflected vertically and rotated 90 degrees.\n");
			else if (eq(1))
				printf("reflected vertically rotated 180 degrees.\n");
			else if (eq(2))
				printf("reflected vertically rotated 270 degrees.\n");
			else
				printf("improperly transformed.\n");
		}
		
	}

	return 0;
}
