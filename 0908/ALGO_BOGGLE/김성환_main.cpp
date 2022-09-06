#include <iostream>
#include <string.h>

using namespace std;

char board[5][5];
int cache[5][5][11];

const int dy[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int dx[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

bool inRange(int y, int x) {
	if (0 <= y && y < 5 && 0 <= x && x < 5)
		return true;
	return false;
}

int hasWord(int y, int x, string word) {
	if (!inRange(y, x))
		return 0;
	if (board[y][x] != word[0])
		return 0;
	if (word.length() == 1)
		return 1;
	int& ret = cache[y][x][word.length()];
	if (ret != -1)
		return ret;
	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (hasWord( ny, nx, word.substr(1)) == 1)
			return ret = 1;
	}
	return ret = 0;
}

void solution(string word) {
	memset(cache, -1, sizeof(cache));
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (hasWord( row, col , word) == 1) {
				cout << "YES\n";
				return;
			}
		}
	}
	cout << "NO\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int C;
	cin >> C;
	for (int tc = 1; tc <= C; tc++) {

		string str_row;
		for (int row = 0; row < 5; row++) {
			cin >> str_row;
			for (int col = 0; col < 5; col++) {
				board[row][col] = str_row[col];
			}
		}

		int w;
		cin >> w;
		for (int i = 0; i < w; i++) {
			string word;
			cin >> word;
			cout << word << " ";
			solution(word);
		}
	}

	return 0;
}
