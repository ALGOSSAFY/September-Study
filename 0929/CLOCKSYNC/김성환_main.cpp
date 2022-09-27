#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

vector<vector<int>> v_connection{
	{0, 1, 2},
	{3, 7, 9, 11},
	{4, 10, 14, 15},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15},
	{3, 14, 15},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13},
};

int clock_list[16];
int path[10];
int min_cnt;

bool check_noon() {
	int clock_cpy[16] = {};
	memcpy(clock_cpy, clock_list, sizeof(clock_list));
	for (int i = 0; i < 10; i++) {
		if (path[i] == 0)
			continue;
		for (int j = 0; j < v_connection[i].size(); j++) {
			int now = v_connection[i][j];
			clock_cpy[now] = (clock_cpy[now] + 3 * path[i]) % 12;
		}
	}
	for (int i = 0; i < 16; i++) {
		if (clock_cpy[i] % 12 == 0)
			continue;
		return false;
	}
	return true;
}

void dfs(int level, int cnt) {
	// base case
	if (level == 10) {
		if (check_noon())
			min_cnt = min(min_cnt, cnt);
		return;
	}
	// recursive case
	for (int i = 0; i <= 3; i++) {
		path[level] = i;
		dfs(level + 1, cnt + i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int C;
	cin >> C;
	for (int tc = 1; tc <= C; tc++) {
		memset(clock_list, 0, sizeof(clock_list));
		min_cnt = 100;

		for (int i = 0; i < 16; i++) {
			cin >> clock_list[i];
		}

		dfs(0, 0);
		if (min_cnt == 100)
			cout << "-1\n";
		else
			cout << min_cnt << "\n";
	}

	return 0;
}
