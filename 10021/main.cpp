#include <iostream>
#include <utility>
#include <queue>
#include <cstring>
#include <tuple>
#include <set>

using namespace std;

typedef pair<int, int> pii;

constexpr int MAXN = 10;
constexpr int STATECNT = 7;
constexpr int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

int X, Y, stx, sty, edx, edy;
int MAP[MAXN + 2][MAXN + 2][STATECNT][STATECNT];

constexpr int DOWN = -1, N = -2, E = -3, S = 2, W = 3, UP = 1;
void move(int& face, int& point, int to)
{
	if (face == DOWN)
		face = -to;
	else if (face == UP)
		face = to;
	else if (to == -face) 
		face = UP;
	else if (to == face) 
		face = DOWN;
	
	if (point == DOWN)
		point = -to;
	else if (point == UP)
		point = to;
	else if (to == -point)
		point = UP;
	else if (to == point)
		point = DOWN;
}
typedef tuple<int, int, int, int> tiiii;
bool CANTGO[MAXN + 2][MAXN + 2][MAXN + 2][MAXN + 2];
bool isvalid(int x, int y)
{
	return (1 <= x && x <= X) && (1 <= y && y <= Y);
}
bool bfs()
{
	int magic[4] = {N, E, S, W};
	queue<tiiii> qu;
	qu.emplace(stx, sty, DOWN, N);
	MAP[stx][sty][DOWN + 3][N + 3] = 0;
	while(qu.size())
	{
		tiiii now = qu.front(); qu.pop();
		int x = get<0>(now), y = get<1>(now);
		int f = get<2>(now), p = get<3>(now);
		if (x == edx && y == edy && f == DOWN) 
		{
			printf("%d\n", MAP[x][y][f + 3][p + 3]);
			return true;
		}
		int c = MAP[x][y][f + 3][p + 3];
		//printf("now: %d %d %d %d\n", x, y, f, p);
		//printf("now cost: %d\n", c);
		for (int i = 0; i < 4; ++i)
		{
			int nexx = x + dir[i][0], nexy = y + dir[i][1];
			if (CANTGO[x][y][nexx][nexy] || !isvalid(nexx, nexy)) continue;
			int nexf = f, nexp = p;
			move(nexf, nexp, magic[i]);
			if (MAP[nexx][nexy][nexf + 3][nexp + 3] > c + 1)
			{
				MAP[nexx][nexy][nexf + 3][nexp + 3] = c + 1;
				//printf("\tnex: %d %d %d %d\n", nexx, nexy, nexf, nexp);
				qu.emplace(nexx, nexy, nexf, nexp);
			}
		}
	}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(MAP, 0x3f, sizeof(int) * (MAXN + 2) * (MAXN + 2) * (STATECNT) * (STATECNT));
		memset(CANTGO, 0, sizeof(bool) * (MAXN + 2) * (MAXN + 2) * (MAXN + 2) * (MAXN + 2));
		scanf("%d %d", &X, &Y);
		scanf("%d %d %d %d", &stx, &sty, &edx, &edy); getchar();
		char s[101]{};
		
		bool flag = false;
		while(~scanf("%100[^\n]s", s))
		{
			getchar();
			int a, b;
			if (s[0] == 0) break;
			if (s[0] == 'h')
			{
				flag = true;
			}
			else if(s[0] == 'v')
			{
				flag = false;
			}
			else
			{
				sscanf(s, "%d %d", &a, &b);
				//printf("debug: %d %d %d\n", flag, a, b);
				if (flag) CANTGO[a][b][a][b + 1] = CANTGO[a][b + 1][a][b] = true;
				else CANTGO[a][b][a + 1][b] = CANTGO[a + 1][b][a][b] = true;
			}
			s[0] = 0;
		}
		if (!bfs())
		{
			puts("No solution\n");
		}
		else
		{
			if (T) puts("");
		}
	}
	return 0;
}
