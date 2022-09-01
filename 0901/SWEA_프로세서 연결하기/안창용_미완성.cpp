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
	// 0~3 ���� ���ɼ�, 4 �� �Լ��� �н� �ɼ��߰�
	//   0 : up , 1: down , 2 : left , 3 : right ,   4  : pass
};

void dfs(int curindex, int totalindex, vector <loc> chipdata);


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
		int maxChipN = 0;
		answer = 300; // Ĩ ���� 20��, �� ������ 12, �ִ� ���� 240 ���� ū 300���� ����

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				cin >> field[y][x];
				if (field[y][x]) {
					chipN++;
					chiplocs.push_back({ y,x });

					// struct ��ǥ �� ������. int[5] �迭 ���������� �ʱ�ȭ �Ǿ ��µǴ��� Ȯ��
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





		cout << "#" << TC << " " << answer << "\n";
	}



	return 0;
}





