#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

struct Node {
	int y;
	int x;
};

struct Group {
	Node start;
	int cnt;
	int num;
	vector<Node> v_adjacents;
};

int n;
int board[29][29];
int board_copy[29][29];
int visited[29][29];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
vector<Group> group_info;
vector<Node> group_adjacents;
Node parent[29][29];

Node Find(Node now) {
	Node now_parent = parent[now.y][now.x];
	if (now_parent.y == now.y && now_parent.x == now.x)
		return now;
	parent[now.y][now.x] = Find(now_parent);
	return parent[now.y][now.x];
}

void Union(Node a, Node b) {
	Node pa = Find(a);
	Node pb = Find(b);

	if (pa.y == pb.y && pa.x == pb.x)
		return;
	parent[pb.y][pb.x] = pa;
}

void duplicate_board() {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			board_copy[row][col] = board[row][col];
		}
	}
}

void rotate_square(Node start, Node end) {
	for (int row = 0; row < n / 2; row++) {
		for (int col = 0; col < n / 2; col++) {
			board_copy[start.y + col][end.x - row] = board[start.y + row][start.x + col];
		}
	}
	for (int row = 0; row < n / 2; row++) {
		for (int col = 0; col < n / 2; col++) {
			board[start.y + row][start.x + col] = board_copy[start.y + row][start.x + col];
		}
	}
}

void rotate_cross() {
	int col_arr[29] = {};
	int row_arr[29] = {};
	for (int i = 0; i < n; i++) {
		col_arr[i] = board[i][n / 2];
		row_arr[i] = board[n / 2][i];
	}
	for (int i = 0; i < n; i++) {
		board[n / 2][i] = col_arr[i];
		board[n - 1 - i][n / 2] = row_arr[i];
	}

}

void rotate_board() {
	duplicate_board();
	int mid = n / 2;
	rotate_square({ 0, 0 }, { mid - 1, mid - 1 });
	rotate_square({ 0, mid + 1 }, { mid - 1, n - 1 });
	rotate_square({ mid + 1, 0 }, { n - 1, mid - 1 });
	rotate_square({ mid + 1, mid + 1 }, { n - 1, n - 1 });
	rotate_cross();

}

int calc_total_harmony() {
	int val = 0;
	for (int i = 0; i < group_info.size(); i++) {
		Group now_group = group_info[i];
		for (int j = i + 1; j < group_info.size(); j++) {
			Group next_group = group_info[j];
			int adjacent_cnt = 0;
			for (int k = 0; k < now_group.v_adjacents.size(); k++) {
				Node now_adjacent = now_group.v_adjacents[k];
				Node pa = Find(now_adjacent);
				Node pb = Find(next_group.start);
				if (pa.y == pb.y && pa.x == pb.x)
					adjacent_cnt++;
			}
			val += (now_group.cnt + next_group.cnt) * now_group.num * next_group.num * adjacent_cnt;
		}
	}
	return val;
}

bool inRange(int y, int x) {
	if (0 <= y && y < n && 0 <= x && x < n)
		return true;
	return false;
}

void bfs(Node start, int num) {
	queue<Node> q;
	q.push(start);

	visited[start.y][start.x] = num;
	int cnt = 1;
	vector<Node> v_adjacents;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (!inRange(ny, nx))
				continue;
			if (board[ny][nx] != num) {
				v_adjacents.push_back({ ny, nx });
				continue;
			}
			if (visited[ny][nx] != 0)
				continue;
			visited[ny][nx] = num;
			Union(start, { ny,nx });
			cnt++;
			q.push({ ny, nx });
		}
	}

	group_info.push_back({ start, cnt, num, v_adjacents });
}

void initialize() {
	memset(visited, 0, sizeof(int) * 29 * 29);
	group_info.clear();
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			parent[row][col] = { row, col };
		}
	}
}

void get_groups() {
	initialize();
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (visited[row][col] != 0)
				continue;
			bfs({ row, col }, board[row][col]);
		}
	}
}

void input() {
	cin >> n;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			cin >> board[row][col];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	int harmony_sum = 0;
	for (int i = 0; i < 4; i++) {
		get_groups();
		harmony_sum += calc_total_harmony();
		if (i == 3)
			break;
		rotate_board();
	}

	cout << harmony_sum;
	return 0;
}
