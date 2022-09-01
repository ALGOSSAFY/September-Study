#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;


int T, N;

int answer;
int length;
int field[13][13];
int maxConnected = 0;
int Connected;
struct loc {
	int y, x;
	int dir[5];
	// 0~3 ���� ���ɼ�, 4 �� �Լ��� �н� �ɼ��߰�
	//   0 : up , 1: down , 2 : left , 3 : right ,   4  : pass
};

void dfs(int curindex, int totalchipN, vector <loc> chipdata);


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> T;
	for (int TC = 1; TC <= T; TC++) {
		cin >> N;

		// ------- TC ���� �� �ʱ�ȭ --------- 
		vector <loc> chiplocs;

		int DAT_up[13] = { 0, };
		int DAT_down[13] = { 0, };
		int DAT_left[13] = { 0, };
		int DAT_right[13] = { 0, };
		int chipN = 0;
		maxConnected = 0;
		Connected = 0;
		length = 0;
		answer = 300; // Ĩ ���� 20��, �� ������ 12, �ִ� ���� 240 ���� ū 300���� ����

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				cin >> field[y][x];
				if (field[y][x]) {
					chipN++;
					chiplocs.push_back({ y,x });

					// struct ��ǥ �� ������. int[5] �迭 ���������� �ʱ�ȭ �Ǿ ��µǴ��� Ȯ��
					//cout << chiplocs.back().y << " " << chiplocs.back().x << " " << chiplocs.back().dir[0] << "\n";
					if (!DAT_up[x])
						DAT_up[x] = y;

					DAT_down[x] = N - y + 1;

					if (!DAT_left[y])
						DAT_left[y] = x;

					DAT_right[y] = N - x + 1;

				}
			}
		}
		//chipN -> �־��� Ĩ ��, �׵θ��� ���ᰡ���� Ĩ ���� ����

		for (int i = 0; i < chipN; i++) {
			int cy = chiplocs[i].y;
			int cx = chiplocs[i].x;

			//dir info
			//   0 : up , 1: down , 2 : left , 3 : right ,   4  : pass
			if (cy == 1 || cy == N || cx == 1 || cx == N) {
				chiplocs.erase(chiplocs.begin() + i);
				i--, chipN--;
				continue;
			} // �׵θ��� �ִ� �ֵ� ����. dat ���� ���� ���� üũ�ϸ� ���� X

			int flag = 1;

			if (cy == DAT_up[cx]) {
				chiplocs[i].dir[0] = 1; flag = 0;
			}

			if (cy + DAT_down[cx] - 1 == N) {
				chiplocs[i].dir[1] = 1; flag = 0;
			}

			if (cx == DAT_left[cy]) {
				chiplocs[i].dir[2] = 1; flag = 0;
			}

			if (cx + DAT_right[cy] - 1 == N) {
				chiplocs[i].dir[3] = 1; flag = 0;
			}
			//4�� �� �ش���� �ʴ´� -> ������ ���� Ĩ�̴� ������.
			if (flag) {
				chiplocs.erase(chiplocs.begin() + i);
				i--, chipN--;
				continue;
			}

		}
		//���ݱ���, �׵θ� ���ݰ�,
		//�ƹ��͵� ���� ���ϴ� �ֵ� ������.

		//���� dfs ������ �ȴ�~!


		dfs(0, chipN, chiplocs);


		cout << "#" << TC << " " << answer << "\n";
	}



	return 0;
}





void dfs(int curindex, int totalchipN, vector <loc> chipdata) {

	if ((Connected + totalchipN - curindex) < maxConnected)
		return;

	if (curindex == totalchipN) {
		if (maxConnected == Connected) {
			if (answer > length)
				answer = length;
		}
		else if (maxConnected < Connected) {
			maxConnected = Connected;
			answer = length;
		}
		return;
	}
	loc curchip = chipdata[curindex];
	int cury = curchip.y;
	int curx = curchip.x;
	int possible_up = curchip.dir[0];
	int possible_down = curchip.dir[1];
	int possible_left = curchip.dir[2];
	int possible_right = curchip.dir[3];

	//   0 : up , 1: down , 2 : left , 3 : right

	// up
	if (possible_up) {
		bitset<13> up_temp_2 = 0;
		bitset<13> up_temp_3 = 0;
		Connected++;
		length += cury - 1;
		for (int i = curindex + 1; i < totalchipN; i++) {
			if (cury < chipdata[i].y) {
				continue;
			}
			else {
				if (curx < chipdata[i].x && chipdata[i].dir[2]) {
					up_temp_2[i] = 1;
					chipdata[i].dir[2] = 0;
				}
				if (chipdata[i].x < curx && chipdata[i].dir[3]) {
					up_temp_3[i] = 1;
					chipdata[i].dir[3] = 0;
				}
			}
		}
		dfs(curindex + 1, totalchipN, chipdata);

		for (int i = curindex; i < 13; i++) {
			if (up_temp_2[i])
				chipdata[i].dir[2] = 1;
			if (up_temp_3[i])
				chipdata[i].dir[3] = 1;
		}

		Connected--;
		length -= cury - 1;
	}

	//down
	if (possible_down) {
		bitset<13> down_temp_2 = 0;
		bitset<13> down_temp_3 = 0;
		Connected++;
		length += (N - cury);
		for (int i = curindex + 1; i < totalchipN; i++) {
			if (cury > chipdata[i].y) {
				continue;
			}
			else {
				if (curx < chipdata[i].x && chipdata[i].dir[2]) {
					down_temp_2[i] = 1;
					chipdata[i].dir[2] = 0;
				}
				if (chipdata[i].x < curx && chipdata[i].dir[3]) {
					down_temp_3[i] = 1;
					chipdata[i].dir[3] = 0;
				}
			}
		}
		dfs(curindex + 1, totalchipN, chipdata);

		for (int i = curindex; i < 13; i++) {
			if (down_temp_2[i])
				chipdata[i].dir[2] = 1;
			if (down_temp_3[i])
				chipdata[i].dir[3] = 1;
		}

		Connected--;
		length -= (N - cury);
	}



	if (possible_left) {
		bitset<13> left_temp_0 = 0;
		bitset<13> left_temp_1 = 0;
		Connected++;
		length += (curx - 1);
		for (int i = curindex + 1; i < totalchipN; i++) {
			loc next = chipdata[i];
			if (curx < next.x) {
				continue;
			}
			else {
				if (next.y > cury && chipdata[i].dir[0]) {
					left_temp_0[i] = 1;
					chipdata[i].dir[0] = 0;
				}
				if (next.y < cury && chipdata[i].dir[1]) {
					left_temp_1[i] = 1;
					chipdata[i].dir[1] = 0;
				}
			}
		}
		dfs(curindex + 1, totalchipN, chipdata);

		for (int i = curindex; i < 13; i++) {
			if (left_temp_0[i])
				chipdata[i].dir[0] = 1;
			if (left_temp_1[i])
				chipdata[i].dir[1] = 1;
		}
		Connected--;
		length -= (curx - 1);
	}


	if (possible_right) {
		bitset<13> right_temp_0 = 0;
		bitset<13> right_temp_1 = 0;
		Connected++;
		length += (N - curx);
		for (int i = curindex + 1; i < totalchipN; i++) {
			loc next = chipdata[i];
			if (curx > next.x) {
				continue;
			}
			else {
				if (next.y > cury && chipdata[i].dir[0]) {
					right_temp_0[i] = 1;
					chipdata[i].dir[0] = 0;
				}
				if (next.y < cury && chipdata[i].dir[1]) {
					right_temp_1[i] = 1;
					chipdata[i].dir[1] = 0;
				}
			}
		}
		dfs(curindex + 1, totalchipN, chipdata);

		for (int i = curindex; i < 13; i++) {
			if (right_temp_0[i])
				chipdata[i].dir[0] = 1;
			if (right_temp_1[i])
				chipdata[i].dir[1] = 1;
		}
		Connected--;
		length -= (N - curx);
	}



	//pass

	dfs(curindex + 1, totalchipN, chipdata);



}