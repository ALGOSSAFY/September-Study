#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Core {
	int y;
	int x;
};

struct Result {
	int cnt;
	int sum;
};

int n;
int MAP[12][12];
vector<Core> cores;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int visited[12][12];

vector<Result> results;

bool cmp(Result a, Result b) {
	if (a.cnt > b.cnt) return true;
	if (a.cnt < b.cnt) return false;
	if (a.sum < b.sum)return true;
	if (a.sum > b.sum) return false;
	return false;
}

void dfs(int idx, int coreCnt, int lineSum, int powerCnt) {

	//if (idx == cores.size()) return;

	if (coreCnt == cores.size()) {
		results.push_back({ powerCnt, lineSum });
		return;
	}

	int y = cores[idx].y;
	int x = cores[idx].x;

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		vector<Core> lineVisited; // core의 전선을 표시 
		int flag = 0; // core가 전원에 닿았는지 확인
		while (true) {

			if (MAP[ny][nx] != 0) break; // 다른 코어 존재
			if (visited[ny][nx] != 0) break; // 전선이 이미 설치
			
			lineVisited.push_back({ ny, nx });

			if (ny == 0 || ny == n - 1 || nx == 0 || nx == n - 1) {
				flag = 1;
				break;
			}

			ny = ny + dy[i];
			nx = nx + dx[i];
		}

		// core의 전선이 전원에 닿은 경우 
		if (flag == 1) {
			for (int j = 0; j < lineVisited.size(); j++) {
				visited[lineVisited[j].y][lineVisited[j].x] = 1;
			}

			int temp = lineVisited.size();
			dfs(idx + 1, coreCnt + 1, lineSum + temp, powerCnt + 1);

			for (int j = 0; j < lineVisited.size(); j++) {
				visited[lineVisited[j].y][lineVisited[j].x] = 0;
			}
		}

	}

	// 남은 코어의 수보다 이미 연결된 코어의 수가 더 크다면 연결안된 경우 굳이 돌려보지 않음!
	if (cores.size() - coreCnt < powerCnt) return;


	// 전원 연결이 되지 않은 코어가 존재할 수 있음!
	dfs(idx + 1, coreCnt + 1, lineSum, powerCnt);

}


int main() {

	int t;
	cin >> t;

	for (int testcase = 1; testcase <= t; testcase++) {

		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> MAP[i][j];

				if (i == 0 || i == n - 1 || j == 0 || j == n - 1) continue;
				if (MAP[i][j] == 1) {
					cores.push_back({ i, j });
				}
			}
		}

		dfs(0, 0, 0, 0);

		sort(results.begin(), results.end(), cmp);
		cout << '#' << testcase << " " << results[0].sum << "\n";

		// 초기화
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				MAP[i][j] = 0;
			}
		}

		cores.clear();
		results.clear();

	}

}


/*
3
7
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
9
0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1
11
0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1
0 0 0 1 0 0 0 0 1 0 0
0 1 0 1 1 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
*/
