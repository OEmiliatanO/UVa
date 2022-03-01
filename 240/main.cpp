#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define INF 0x7f7f7f7f

using namespace std;

constexpr int MAXR = 10;
constexpr int MAXCHARA = 26;

typedef struct node
{
	node* sons[MAXR + 1];
	char charas[MAXCHARA + 1];
	int soncnt, freq, chcnt, order;

	node() { charas[0] = '.'; soncnt = freq = 0, chcnt = 1; };
	node(int feq, char ch) { charas[0] = ch, freq = feq, chcnt = 1, soncnt = 0; };
	node(int feq, char ch, int ord) { charas[0] = ch, freq = feq, chcnt = 1, soncnt = 0, order = ord; };
}node;

typedef struct cmp
{
	bool operator()(node* lhs, node* rhs)
	{
		return (lhs->freq == rhs->freq ? lhs->order > rhs->order : lhs->freq > rhs->freq);
	}
}cmp;

int R, N, freq[MAXCHARA + 1];

void travel(node* now, string s = "")
{
	if (now == nullptr) return;
	if (now->soncnt == 0)
	{
		if (now->charas[0] != '.')
		{
			huff[now->charas[0] - 'A'] = s;
			
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
    while(~scanf("%d", &R) && R)
    {
		node* root = nullptr;
		priority_queue<node*, vector<node*>, cmp> pq;

		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
	    	scanf("%d", freq + i);
	    	pq.emplace(new node(freq[i], 'A' + i, i));
		}
		
		{
			unsigned long k = 0;
			while(k * (R - 1) + R < (unsigned long)N) ++k;
			//printf("grow to %lu\n", k * (R - 1) + R);
			while(pq.size() < k * (R - 1) + R)
			{
				pq.emplace(new node(0, '.', INF));
			}
		}
		
		while(pq.size() >= (unsigned long)R)
		{
			node* nexNd;
			node* newnode = new node();
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

		
	
		del(root);
	}
	return 0;
}
