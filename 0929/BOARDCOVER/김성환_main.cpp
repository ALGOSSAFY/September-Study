#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int y;
	int x;
};

char board[20][20];
int H, W;
int white_cnt;
int board_cnt;

int dy[][3] = {
	{0, 0, 1}, {0, 1, 1}, {0, 1, 1}, {0, 0, 1}
};

int dx[][3] = {
	{0, 1, 0},{0, 0, -1},{0, 0, 1},{0, 1, 1}
};

bool isPossible(int type, Node now) {
	for (int i = 0; i < 3; i++) {
		int ny = now.y + dy[type][i];
		int nx = now.x + dx[type][i];
		if (!(0 <= ny && ny < H && 0 <= nx && nx < W))
			return false;
		if (board[ny][nx] == '#')
			return false;
	}
	return true;
}

void dfs(int level, Node now) {
	// base case
	if (level == white_cnt / 3) {
		board_cnt++;
		return;
	}
	if (now.y + 1 == H && now.x + 1 == W)
		return;
	// recursive case
	if (board[now.y][now.x] == '#') {
		if (now.x + 1 == W)
			dfs(level, { now.y + 1, 0 });
		else
			dfs(level, { now.y, now.x + 1 });
	}
	for (int i = 0; i < 4; i++) {
		if (!isPossible(i, now))
			continue;
		// 채우기
		for (int j = 0; j < 3; j++) {
			int ny = now.y + dy[i][j];
			int nx = now.x + dx[i][j];
			board[ny][nx] = '#';
		}

		// 재귀 호출
		if (now.x + 1 == W)
			dfs(level + 1, { now.y + 1, 0 });
		else
			dfs(level + 1, { now.y, now.x + 1 });

		// 복구하기
		for (int j = 0; j < 3; j++) {
			int ny = now.y + dy[i][j];
			int nx = now.x + dx[i][j];
			board[ny][nx] = '.';
		}

	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int C;
	cin >> C;
	for (int tc = 1; tc <= C; tc++) {
		white_cnt = 0;
		board_cnt = 0;
		cin >> H >> W;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> board[i][j];
				if (board[i][j] == '.')
					white_cnt++;
			}
		}
		
		if (white_cnt % 3 != 0) {
			cout << "0\n";
			continue;
		}
		dfs(0, { 0,0 });
		cout << board_cnt << "\n";
	}


	return 0;
}

