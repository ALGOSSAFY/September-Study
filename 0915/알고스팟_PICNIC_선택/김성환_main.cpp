#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

struct Edge {
	int from;
	int to;
};

int n, m;
int student_visited[10];
int edge_visited[45];
vector<Edge> v;
int cnt;

void dfs(int level, int start) {
	// base case
	if (level == n / 2) {
		cnt++;
		return;
	}
	// recursive case
	for (int i = start; i < m; i++) {
		if (edge_visited[i] != 0)
			continue;
		Edge now = v[i];
		if (student_visited[now.from] != 0 || student_visited[now.to] != 0)
			continue;
		edge_visited[i] = 1;
		student_visited[now.from] = 1;
		student_visited[now.to] = 1;
		dfs(level + 1, i + 1);
		edge_visited[i] = 0;
		student_visited[now.from] = 0;
		student_visited[now.to] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int C;
	cin >> C;
	for (int tc = 1; tc <= C; tc++) {
		cnt = 0;
		memset(student_visited, 0, sizeof(student_visited));
		memset(edge_visited, 0, sizeof(edge_visited));
		v.clear();

		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int from, to;
			cin >> from >> to;
			v.push_back({ from, to });
		}
		dfs(0, 0);
		cout << cnt << "\n";
	}

	return 0;
}
