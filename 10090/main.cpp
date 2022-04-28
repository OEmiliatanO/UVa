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
		
		if (n % d || (a < 0 && b < 0))
		{
			printf("failed\n");
			continue;
		}

		a *= n / d, b *= n / d;
		int64_t s1 = n2 / d, s2 = n1 / d;

		//printf("a,b = %lld,%lld\n", a ,b);
		if (a < 0)
		{
			int64_t k = -a / s1 + !!(a % s1);
			a += k * s1, b -= k * s2;
		}
		if (b < 0)
		{
			int64_t k = -b / s2 + !!(b % s2);
			b += k * s2, a -= k * s1;
		}

		if (a < 0 || b < 0)
		{
			printf("failed\n");
			continue;
		}
		//printf("a,b = %lld,%lld\n", a , b);

		int64_t x1 = a - (a/s1) * s1, y1 = b + (a/s1) * s2, x2 = a + (b/s2) * s1, y2 = b - (b/s2) * s2;
		if (x1 * c1 + y1 * c2 < x2 * c1 + y2 * c2)
			printf("%lld %lld\n", x1, y1);
		else
			printf("%lld %lld\n", x2, y2);
	}

	return 0;
}
