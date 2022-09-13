#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

constexpr int MAXN = 1024000;

int arr[MAXN + 10];
int seg[(MAXN << 2) + 10];
char lazy[(MAXN << 2) + 10];
int n;

void build(int l = 1, int r = n, int now = 1)
{
	if (r < l) return;
	if (l == r) { seg[now] = arr[l]; return; }
#ifdef DEBUGing
	printf("in build(l = %d, r = %d, now = %d)\n", l, r, now);
#endif
	lazy[now] = 0;
	int mid = (r + l) >> 1;
	build(l, mid, now << 1);
	build(mid + 1, r, now << 1 | 1);
	seg[now] = seg[now << 1] + seg[now << 1 | 1];
}

char revertLZ(int now)
{
	return (lazy[now] == 'I' ? 0 : (lazy[now] == '0' ? '1' : (lazy[now] == '1' ? '0' : 'I')));
}
void push(int l, int r, int now)
{
#ifdef DEBUGing
	printf("in push(now = %d)\n", now);
	cout << "lazy[now] = " << lazy[now] << '\n';
#endif
	if (r < l) return;
	if (l == r) return;
	if (lazy[now] == 0) return;

	char ch = lazy[now];
	int mid = (r + l) >> 1;
	if (ch == 'I')
	{
		lazy[now << 1] = revertLZ(now << 1);
		seg[now << 1] = mid - l + 1 - seg[now << 1];
		lazy[now << 1 | 1] = revertLZ(now << 1 | 1);
		seg[now << 1 | 1] = r - mid - seg[now << 1 | 1];
	}
	else if (ch == '0' or ch == '1')
	{
		lazy[now << 1] = ch;
		seg[now << 1] = (mid - l + 1) * (ch - '0');
		lazy[now << 1 | 1] = ch;
		seg[now << 1 | 1] = (r - mid) * (ch - '0');
	}
	lazy[now] = 0;
}

void pull(int now)
{
	seg[now] = seg[now << 1] + seg[now << 1 | 1];
#ifdef DEBUGing
	printf("after pull(now = %d), seg[now] = %d\n", now, seg[now]);
#endif
}

int require(int ql, int qr, int l = 1, int r = n, int now = 1)
{
	if (r < l) return 0;
	
#ifdef DEBUGing
	printf("in require(ql = %d, qr = %d, l = %d, r = %d, now = %d)\n", ql, qr, l, r, now);
#endif

	int mid = l + ((r - l) >> 1);
	if (ql <= l and r <= qr)
	{
#ifdef DEBUGing
		printf("in require(ql = %d, qr = %d, l = %d, r = %d, now = %d), enter (ql<=l and r<-qr) block\n", ql, qr, l, r, now);
		printf("in require(ql = %d, qr = %d, l = %d, r = %d, now = %d), return %d\n", ql, qr, l, r, now, seg[now]);
		printf("seg[%d] = %d\n", now, seg[now]);
#endif
		return seg[now];
	}
	else if (ql > r or qr < l)
		return 0;

	push(l, r, now);

	int res = 0;
	if (ql <= mid) res += require(ql, qr, l, mid, now << 1);
	if (qr > mid) res += require(ql, qr, mid + 1, r, now << 1 | 1);
#ifdef DEBUGing
	printf("in require(ql = %d, qr = %d, l = %d, r = %d, now = %d), return %d\n", ql, qr, l, r, now, res);
#endif
	pull(now);
	return res;
}

void modify(int ql, int qr, char m, int l = 1, int r = n, int now = 1)
{
	if (r < l) return;

#ifdef DEBUGing
	printf("in modify(ql = %d, qr = %d, m = %c, l = %d, r = %d, now = %d)\n", ql, qr, m, l, r, now);
#endif

	if (ql <= l and r <= qr)
	{
		if (m == 'I')
			lazy[now] = revertLZ(now), seg[now] = r - l + 1 - seg[now];
		else
			lazy[now] = m, seg[now] = (r - l + 1) * (m - '0');

#ifdef DEBUGing
		printf("seg[%d] = %d\n", now, seg[now]);
#endif
		return;
	}
	else if (ql > r or qr < l)
		return;
	
	int mid = l + ((r - l) >> 1);
	
	push(l, r, now);
	
	if (ql <= mid) modify(ql, qr, m, l, mid, now << 1);
	if (qr > mid) modify(ql, qr, m, mid + 1, r, now << 1 | 1);

	pull(now);
}

int main()
{
	int T, kase = 1;
	scanf("%d", &T);
	while(T--)
	{
		n = 1;
		memset(lazy, 0, sizeof(char) * ((MAXN << 2) + 10));
		int M;
		scanf("%d", &M);
		while (M--)
		{
			int t;
			char s[52];
			scanf("%d%*c", &t);
			scanf("%[^\n]s", s);
#ifdef DEBUGing
			printf("the string input: %s\n", s);
#endif
			while(t--)
				for (int i = 0; s[i]; ) arr[n++] = s[i++] - '0';
		}

		build(1, --n);
#ifdef DEBUGing
		puts("segment tree built sucessfully");
#endif

		int Q, qes = 1;
		scanf("%d%*c", &Q);
		printf("Case %d:\n", kase++);
		while (Q--)
		{
			int a, b;
			char ch;
			scanf("%c", &ch);
#ifdef DEBUGing
			printf("the input ch = %c\n", ch);
#endif
			scanf("%d %d%*c", &a, &b);
			++a, ++b;
			if (ch == 'F')
			{
				modify(a, b, '1');
			}
			else if (ch == 'E')
			{
				modify(a, b, '0');
			}
			else if (ch == 'I')
			{
				modify(a, b, 'I');
			}
			else//if (ch == 'S')
			{
				printf("Q%d: %d\n", qes++, require(a, b));
			}
		}
	}
	return 0;
}
