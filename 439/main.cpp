#include <iostream>
#include <cstring>
#include <queue>
#include <utility>

#define UNDEFINED 0x7f7f7f7f

using namespace std;

typedef pair<int, int> pii;

constexpr int MAXN = 10;
constexpr int dir[][2] = {{-1, -2}, {-2, -1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {1, 2}, {2, 1}};

int board[MAXN][MAXN];

bool xyVaild(int x, int y)
{
	return (1 <= x && x <= 8) && (1 <= y && y <= 8);
}

void bfs(int stx, int sty, int edx, int edy)
{
	queue<pii> qu;
	qu.emplace(stx, sty);
	board[stx][sty] = 0;
	while(qu.size())
	{
		int x = qu.front().first, y = qu.front().second; qu.pop();
		if (x == edx && y == edy) break;
		for (int i = 0; i < 8; ++i)
			if (xyVaild(x + dir[i][0], y + dir[i][1]) && board[x + dir[i][0]][y + dir[i][1]] == UNDEFINED)
			{
				board[x + dir[i][0]][y + dir[i][1]] = board[x][y] + 1;
				qu.emplace(x + dir[i][0], y + dir[i][1]);
			}
	}
}

int main()
{
	char stx_c, sty_c, edx_c, edy_c;
	int stx, sty, edx, edy;
	while(~scanf("%c%c %c%c", &stx_c, &sty_c, &edx_c, &edy_c) && ~getchar())
	{
		memset(board, UNDEFINED, sizeof(board));

		stx = stx_c - 'a' + 1, sty = sty_c - '0';
		edx = edx_c - 'a' + 1, edy = edy_c - '0';

		bfs(stx, sty, edx, edy);

		printf("To get from %c%c to %c%c takes %d knight moves.\n", stx_c, sty_c, edx_c, edy_c, board[edx][edy]);
	}
	return 0;
}
