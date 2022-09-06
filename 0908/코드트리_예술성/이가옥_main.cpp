#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int n;
int MAP[30][30] = { 0 };
int groupIdx[30][30] = { 0 };

int visited[30][30] = { 0 };
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

vector<int> group_cnt[1000];

// bfs를 이용해서 number로 구성된 그룹 찾기
void find_group(int y, int x, int number, int index) {

	queue<Node> q;

	q.push({ y, x });
	visited[y][x] = 1;
	groupIdx[y][x] = index;
	
	int cnt = 1;
	while (!q.empty()) {

		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			// 범위, 방문여부 체크
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			// 같은 그룹인지 판별
			if (MAP[ny][nx] != number) continue;
			if (visited[ny][nx] != 0) continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
			cnt++;
			groupIdx[ny][nx] = index;
		}
	}

	// number와 같은 숫자로 이루어진 그룹을 찾았다!
	// 해당 그룹 ID에 그룹의 노드 개수를 저장
	group_cnt[index].push_back(cnt);
}


// 방향 배열을 이용해서 해당 node에서 가능한 조화로움 계산
int calc_harmony(int y, int x) {

	int res = 0;
	for (int i = 0; i < 4; i++) {

		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
		if (MAP[y][x] == MAP[ny][nx]) continue;

		// 조화로움 계산

		// 첫번째 그룹과 두번째 그룹의 인덱스 구하기
		int first_group = groupIdx[y][x];
		int second_group = groupIdx[ny][nx];

		// 첫번째 그룹과 두번째 그룹의 칸의 수 구하기
		int first_cnt = group_cnt[first_group][0];
		int second_cnt = group_cnt[second_group][0];

		// 첫번째 그룹과 두번째 그룹의 숫자 값 구하기
		int first_num = MAP[y][x];
		int second_num = MAP[ny][nx];

		res += (first_cnt + second_cnt) * first_num * second_num;
		
		/*cout << res <<"\n";*/
	}
	
	return res;
}

void rotate_X() {
	int MAP_copy[30][30] = { 0 };

	for (int i = 0; i < n; i++) {
		MAP_copy[n / 2][i] = MAP[n / 2][i];
		MAP_copy[i][n / 2] = MAP[i][n / 2];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP_copy[i][j] == 0) continue;
			MAP[n-1-j][i] = MAP_copy[i][j];
		}
	}
}

// 사각형 회전
void rotate_square(int rs, int cs) {

	int MAP_copy[30][30] = { 0 };
	for (int i = 0; i < n/2; i++) {
		for (int j = 0; j < n/2; j++) {
			MAP_copy[i+rs][j+cs] = MAP[i+rs][j+cs];
		}
	}

	for (int i = 0; i < n/2; i++) {
		for (int j = 0; j < n/2; j++) {
			if (MAP_copy[i+rs][j+cs] == 0) continue;
			MAP[j+rs][n/2-1-i+cs] = MAP_copy[i+rs][j+cs];
		}
	}

}

int main() {

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}

	// 1 ~ 3 회전 후 예술 점수 모두 구하기
	int ans = 0;
	for (int k = 0; k < 4; k++) {

		// 그룹 정보(그룹을 이루는 칸의 갯수와 그룹 ID) 저장하기
		int index = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j] != 0) continue;
				find_group(i, j, MAP[i][j], index);
				index++;
			}
		}

		// 조화로움 계산
		int res = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res += calc_harmony(i, j);
			}
		}
		res = res / 2;

		ans += res;

		// 배열 회전
		// 십자 모양 회전 (반시계 90도 회전)
		rotate_X();

		// 십자모양을 제외한 4개의 정사각형 회전(시계 90도 회전)
		rotate_square(0, 0);
		rotate_square(0, n / 2 + 1);
		rotate_square(n / 2 + 1, 0);
		rotate_square(n / 2 + 1, n / 2 + 1);

		// 초기화
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				groupIdx[i][j] = 0;
				visited[i][j] = 0;
			}
		}
		
		for (int i = 0; i < index; i++) {
			group_cnt[i].clear();
		}

	}

	cout << ans << "\n";

	// 그룹 인덱스로 나눠진 것 확인 
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << groupIdx[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";*/

	// 그룹 별 노드의 갯수 저장된 것 확인
	/*for (int i = 0; i < index; i++) {
		cout << group_cnt[i][0] << " ";
	}*/

	return 0;
}
