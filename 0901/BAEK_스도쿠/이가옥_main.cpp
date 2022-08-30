#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int MAP[9][9] = { 0 };
vector<Node> zero;
bool isPossible(int y, int x, int num) {

	// 가로줄 체크
	for (int i = 0; i < 9; i++) {
		if (MAP[y][i] == num) return false;
	}

	// 세로줄 체크
	for (int i = 0; i < 9; i++) {
		if (MAP[i][x] == num) return false;
	}

	// 3X3 체크
	// 0, 1, 2 / 3, 4, 5 / 6, 7, 8
	//    0         1         2
	int ty = (y / 3) * 3;
	int tx = (x / 3) * 3;
	for (int i = ty; i < ty + 3; i++) {
		for (int j = tx; j < tx + 3; j++) {
			if (MAP[i][j] == num) return false;
		}
	}

	// 가능!
	return true;
}

int flag = 0;
void dfs(int idx) {

	// 기저조건
	// 스도쿠가 모두 채워짐!
	if (idx == zero.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << MAP[i][j] << " ";
			}
			cout << "\n";
		}
		// 스도쿠가 모두 채워졌다는 것을 기록!
		flag = 1;
		return;
	}

	int y = zero[idx].y;
	int x = zero[idx].x;

	// 재귀구성
	for (int i = 1; i <= 9; i++) {
		if (isPossible(y, x, i)) {
			MAP[y][x] = i;

			dfs(idx + 1);

			// 스도쿠가 이미 채워졌는데, 계속해서 for문이 돌아가는 현상 방지
			if (flag == 1) return;

			// 만약, 갔다가 안되면 돌아와서 다시 원래대로 돌려주기!
			MAP[y][x] = 0;

		}
	}

}

int main() {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 0) zero.push_back({ i, j });
		}
	}

	// 0인 좌표만 dfs 돌려주기 
	for (int i = 0; i < zero.size(); i++) {
		dfs(i);
	}

	return 0;
}
