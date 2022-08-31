#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int y;
	int x;
};

int board[10][10];
int DAT_row[10][10];
int DAT_col[10][10];
int DAT_box[10][10];
vector<Node> v_zero;
int possible_cnt;

int get_box_num(int y, int x) {
	// 현재 위치가 (y,x)일 때, 몇 번째 상자에 해당하는지 반환
	// 1-indexing을 사용하고 있기 때문에 1을 빼고 더하는 작업 필요
	int box_num = ((y-1) / 3) * 3 + ((x-1) / 3) + 1;
	return box_num;
}

bool isValidNum(int y, int x, int num) {
	// (y,x)에 num을 두려고 할때
	// 해당하는 행, 열, 상자에 이미 num이 있으면 둘 수 없음
	if (DAT_row[y][num] == 1)
		return false;
	if (DAT_col[x][num] == 1)
		return false;
	if (DAT_box[get_box_num(y,x)][num] == 1)
		return false;
	return true;
}

void setNum(int y, int x, int num) {
	// (y, x)에 num을 두고, 관련된 정보를 갱신하기
	DAT_row[y][num]++;
	DAT_col[x][num]++;
	DAT_box[get_box_num(y, x)][num]++;
	board[y][x] = num;
}

void eraseNum(int y, int x, int num) {
	// (y, x)에 num을 삭제하고, 관련된 정보를 갱신하기
	DAT_row[y][num]--;
	DAT_col[x][num]--;
	DAT_box[get_box_num(y, x)][num]--;
	board[y][x] = 0;
}

void print_board() {
	// 출력하기
	for (int row = 1; row <= 9; row++) {
		for (int col = 1; col <= 9; col++) {
			cout << board[row][col] << " ";
		}
		cout << "\n";
	}
}

void dfs(int level) {
	// base case
	// v_zero에 들어있는 모든 미결정 위치에 대해 결정을 내렸다면
	// 유효한 스도쿠 판 완성
	if (level == v_zero.size()) {
		possible_cnt++;
		if (possible_cnt == 1)
			// 한 가지 경우만 출력하라기에
			// 혹시 다른 가능한 경우가 생겼을 때 출력 방지 위해
			// 첫 번째 경우만 출력
			print_board();
		return;
	}

	// recursive case
	// 현재 now라는 미결정 위치에 대해 1 ~ 9 중 가능한 숫자 고르기
	Node now = v_zero[level];
	for (int num = 1; num <= 9; num++) {
		// now의 위치에 num을 넣을 수 있는지 확인
		if (!isValidNum(now.y, now.x, num))
			continue;
		// now의 위치에 num 입력
		setNum(now.y, now.x, num);
		// now는 결정 완료, 다음 미결정 위치로 이동
		dfs(level + 1);
		// 다른 num 가능성 확인위해, 현재 사용한 num 지우기 
		eraseNum(now.y, now.x, num);
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 입력을 받으면서
	// 1. board에 숫자 입력
	// 2. 숫자가 정해지지 않은 위치를 v_zero에 저장
	// 3. 현재 row, col, box에 num이 추가되면서 생기는 변경사항 적용
	for (int row = 1; row <= 9; row++) {
		for (int col = 1; col <= 9; col++) {
			int num;
			cin >> num;
			// 1. board에 숫자 입력
			board[row][col] = num;
			//2. 숫자가 정해지지 않은 위치를 v_zero에 저장
			if (num == 0) {
				v_zero.push_back({ row, col });
				continue;	// 0에 대한 정보는 입력하지 않아도 무관하여 continue;
			}
			// 3. 현재 row, col, box에 num이 추가되면서 생기는 변경사항 적용
			DAT_row[row][num]++;
			DAT_col[col][num]++;
			DAT_box[get_box_num(row,col)][num]++;
		}
	}

	dfs(0);

	return 0;
}
