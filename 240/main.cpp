#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#pragma warning(disable:4996)
#define INF 0x7f7f7f7f

using namespace std;

constexpr int MAXR = 10;
constexpr int MAXCHARA = 26;

typedef struct node
{
	node* sons[MAXR + 1];
	int soncnt, freq, order;

	node() { soncnt = freq = order = 0; };
	node(int feq) { freq = feq, soncnt = 0; };
	node(int feq, int ord) { freq = feq, soncnt = 0, order = ord; };
}node;

typedef struct cmp
{
	bool operator()(node* lhs, node* rhs)
	{
		return (lhs->freq == rhs->freq ? lhs->order > rhs->order : lhs->freq > rhs->freq);
	}
}cmp;

int R, N, freq[MAXCHARA + 1];
string huffcode[MAXCHARA + 1];
int ans, tot;

void travel(node* now, string s = "")
{
	if (now == nullptr) return;
	if (now->soncnt == 0)
	{
		if (now->order != INF)
		{
			huffcode[now->order] = s;
			ans += s.size() * freq[now->order];
		}
		return;
	}

	for (int i = 0; i < now->soncnt; ++i)
	{
		string cps = s + (char)('0' + i);
		travel(now->sons[i], cps);
	}
}
void del(node* now)
{
	if (now == nullptr) return;
	for (int i = 0; i < now->soncnt; ++i)
	{
		del(now->sons[i]);
	}
	delete now;
	return;
}

int main()
{
	int t = 1;
	while (~scanf("%d", &R) && R)
	{
		ans = tot = 0;
		node* root = nullptr;
		priority_queue<node*, vector<node*>, cmp> pq;

		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			scanf("%d", freq + i);
			tot += freq[i];
			pq.emplace(new node(freq[i], i));
		}

		{
			unsigned long k = 0;
			while (k * (R - 1) + R < (unsigned long)N) ++k;
			//printf("grow to %lu\n", k * (R - 1) + R);
			while (pq.size() < k * (R - 1) + R)
			{
				pq.emplace(new node(0, INF));
			}
		}

		while (pq.size() >= (unsigned long)R)
		{
			node* nexNd;
			node* newnode = new node(0, INF);
			for (int i = 0; i < R; ++i)
			{
				nexNd = pq.top(); pq.pop();
				newnode->order = min(newnode->order, nexNd->order);
				newnode->freq += nexNd->freq;
				newnode->sons[newnode->soncnt++] = nexNd;
			}
			pq.emplace(newnode);
		}
		root = pq.top(); pq.pop();

		travel(root);

		printf("Set %d; average length %.2f\n", t++, (double)ans / tot);
		for (int i = 0; i < N; ++i)
		{
			cout << "    " << (char)('A' + i) << ": " << huffcode[i] << '\n';
		}

		del(root);

		putchar('\n');
	}
	return 0;
}
