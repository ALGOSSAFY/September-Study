#include <iostream>
#include <vector>

using namespace std;

struct coord {
	int y;
	int x;
};

vector <coord> blank;
int arr[9][9];

bool isvalid = false;
//depth : 빈칸 수
//자식노드: 1~9

bool validChk(int nowy, int nowx) {
	bool isrow = true;
	bool iscol = true;
	bool issqr = true;
	for (int i = 0; i < 9; i++) {
		if (nowx == i)
			continue;
		if (arr[nowy][nowx] == arr[nowy][i]) {
			isrow = false;
			break;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (nowy == i)
			continue;
		if (arr[nowy][nowx] == arr[i][nowx]) {
			iscol = false;
			break;
		}
	}
	// 012 345 678
	for (int i = nowy - (nowy % 3); i < nowy - (nowy % 3) + 3; i++) {
		for (int j = nowx - (nowx % 3);j < nowx - (nowx % 3) + 3; j++) {
			if (nowy == i && nowx == j)
				continue;
			if (arr[i][j] == arr[nowy][nowx]) {
				issqr = false;
				break;
			}
		}
	}

	return isrow & iscol & issqr;
}


//스토쿠채우기
void fillSdoku(int node) {
	if (node == blank.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		exit(0);
		return;
	}

	for (int i = 1; i <= 9; i++) {
		int y = blank[node].y;
		int x = blank[node].x;

		arr[y][x] = i;
		if (validChk(y, x) == true) {
			fillSdoku(node + 1);
		}
		
		arr[y][x] = 0;
		
	}
}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 0) {
				blank.push_back({ i, j });
			}
		}
	}

	fillSdoku(0);

}
