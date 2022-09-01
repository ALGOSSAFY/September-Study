#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;


int T, N;

int answer;

int field[13][13];

struct loc {
	int y, x;
	int dir[5];
	// 0~3 연결 가능성, 4 는 함수용 패스 옵션추가
	//   0 : up , 1: down , 2 : left , 3 : right ,   4  : pass
};

void dfs(int curindex, int totalindex, vector <loc> chipdata);


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> T;
	for (int TC = 1; TC <= T; TC++) {
		cin >> N;

		// ------- TC 시작 후 초기화 --------- 
		vector <loc> chiplocs;

		int DAT_up[13] = { 0, };
		int DAT_down[13] = { 0, };
		int DAT_left[13] = { 0, };
		int DAT_right[13] = { 0, };
		int chipN = 0;
		int maxChipN = 0;
		answer = 300; // 칩 갯수 20개, 맵 사이즈 12, 최대 길이 240 보다 큰 300으로 설정

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				cin >> field[y][x];
				if (field[y][x]) {
					chipN++;
					chiplocs.push_back({ y,x });

					// struct 좌표 잘 들어가는지. int[5] 배열 정상적으로 초기화 되어서 출력되는지 확인
					cout << chiplocs.back().y << " " << chiplocs.back().x << " " << chiplocs.back().dir[0] << "\n";

					if (!DAT_up[x])
						DAT_up[x] = y;

					DAT_down[x] = N - y + 1;

					if (!DAT_left[y])
						DAT_left[y] = x;

					DAT_right[y] = N - x + 1;

				}
			}
		}
		//chipN -> 주어진 칩 수, 테두리에 연결가능한 칩 수로 가공

		for (int i = 0; i < chipN; i++) {
			int cy = chiplocs[i].y;
			int cx = chiplocs[i].x;

			//dir info
			//   0 : up , 1: down , 2 : left , 3 : right ,   4  : pass
			if (cy == 1 || cy == N || cx == 1 || cx == N) {
				chiplocs.erase(chiplocs.begin() + i);
				i--, chipN--;
				continue;
			} // 테두리에 있는 애들 삭제. dat 연결 가능 여부 체크하면 영향 X

			int flag = 1;

			if (cy == DAT_up[cx]) {
				chiplocs[i].dir[0] = 1;
				flag = 0;
			}


			if (cy + DAT_down[cx] - 1 == N) {
				chiplocs[i].dir[1] = 1;
				flag = 0;
			}


			if (cx == DAT_left[cy]) {
				chiplocs[i].dir[2] = 1;
				flag = 0;
			}



			if (cx + DAT_right[cy] - 1 == N) {
				chiplocs[i].dir[3] = 1;
				flag = 0;
			}
			//4개 다 해당되지 않는다 -> 가망이 없는 칩이다 버리자.
			if (flag) {
				chiplocs.erase(chiplocs.begin() + i);
				i--, chipN--;
				continue;
			}

		}
		//지금까지, 테두리 없앴고,
		//아무것두 연결 못하는 애들 없앴음.

		//이제 dfs 돌리면 된다~!





		cout << "#" << TC << " " << answer << "\n";
	}



	return 0;
}





