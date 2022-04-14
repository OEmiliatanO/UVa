#include <cmath>
#include <iostream>

using namespace std;

#define int64_t long long

int64_t n, c1, n1, c2, n2, a, b;

int64_t exgcd(int64_t a, int64_t b, int64_t& X, int64_t& Y)
{
	if (b == 0)
	{
		X = 1, Y = 0;
		return a;
	}
	int64_t r = exgcd(b, a % b, Y, X);
	Y -= a / b * X;
	return r;
}

int main()
{
	while(~scanf("%lld", &n) && n)
	{
		scanf("%lld %lld %lld %lld", &c1, &n1, &c2, &n2);
		int64_t d = exgcd(n1, n2, a, b);
		
		if (n % d || a < 0 && b < 0)
		{
			printf("failed\n");
			continue;
		}

		if (c1 > c2)
		{
			while (a > 0)
			{
				a -= n2 / d;
				b += n1 / d;
			}
			a += n2 / d;
			b -= n1 / d;
		}
		else
		{
			while (b > 0)
			{
				b -= n1 / d;
				a += n2 / d;
			}
			b += n1 / d;
			a -= n2 / d;
		}
	}
	return 0;
}
