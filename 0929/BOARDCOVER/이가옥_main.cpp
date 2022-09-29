#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int h;
int w;
char MAP[21][21];
int visited[21][21];

vector<Node> whiteNodes;

int dy[4][3] = { {0, 0, 1}, {0, 1, 1}, {0, 1, 1}, {0, 0, 1} };
int dx[4][3] = { {0, 1, 0}, {0, 0, -1}, {0, 0, 1}, {0, 1, 1} };

int ans = 0;

void dfs(int y, int x) {

	int checkFinish = 0;
	for (int i = 0; i < whiteNodes.size(); i++) {
		int wy = whiteNodes[i].y;
		int wx = whiteNodes[i].x;

		if (visited[wy][wx] == 0) {
			y = wy;
			x = wx;
			checkFinish = 1;
			break;
		}
	}

	if (checkFinish == 0) {
		ans += 1;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int flag = 0;

		for (int j = 0; j < 3; j++) {
			int ny = y + dy[i][j];
			int nx = x + dx[i][j];

			if (ny < 0 || ny >= h || nx < 0 || nx >= w) {
				flag = 1;
				break;
			}
			if (visited[ny][nx] != 0) {
				flag = 1;
				break;
			}
			if (MAP[ny][nx] != '.') {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {

			for (int k = 0; k < 3; k++) {
				int ny = y + dy[i][k];
				int nx = x + dx[i][k];
				visited[ny][nx] = 1;
			}

			dfs(y, x);

			for (int k = 0; k < 3; k++) {
				int ny = y + dy[i][k];
				int nx = x + dx[i][k];
				visited[ny][nx] = 0;
			}

		}

	}

}

int main() {
	
	int test = 0;
	cin >> test;

	for (int testcase = 0; testcase < test; testcase++) {

		cin >> h >> w;

		int white = 0;
		for (int i = 0; i < h; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < w; j++) {
				MAP[i][j] = str[j];
				if (MAP[i][j] == '.') {
					white += 1;
					whiteNodes.push_back({ i, j });
				}
				else {
					visited[i][j] = 1;
				}
			}
		}

		if (white % 3 != 0) {
			cout << 0 << "\n";
			whiteNodes.clear();

			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					visited[i][j] = 0;
				}
			}

			continue;
		}

		dfs(0, 0);
		cout << ans << "\n";

		// 초기화
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				visited[i][j] = 0;
			}
		}

		whiteNodes.clear();
		ans = 0;
	}

	return 0;
}
