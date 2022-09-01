#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Word {
	string word;
	int found;
};

struct Node {
	int y;
	int x;
};


struct cmp {
	bool operator()(Word a, Word b) {
		if (a.word.length() > b.word.length())
			return true;
		if (a.word.length() < b.word.length())
			return false;
		if (a.word < b.word)
			return true;
		if (a.word > b.word)
			return false;
		return false;
	}
};


char board[4][4];
int visited[4][4];
vector<Word> v_dict;
unordered_map<string, int> mp_word;
int dy[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dx[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int point[] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };
int point_sum;
int search_cnt;
int len_max;
string len_max_word;
int dict_word_len_max;
int dict_word_len_min;


bool inRange(int y, int x) {
	if (0 <= y && y < 4 && 0 <= x && x < 4)
		return true;
	return false;
}

void dfs(Node now, string cur) {
	// 최소 길이를 충족한 단어를 찾은 단어 목록에 추가 
	if (cur.length() >= dict_word_len_min)
		mp_word[cur]++;
	// base case
	// 단어 사전에 등재된 최대 길이의 단어라면 더 가능한 조합 탐색 하지 않는다
	if (cur.length() >= dict_word_len_max)
		return;

	// recursive case
	// 지금 위치에서 추가할 수 있는 문자를 탐색해본다
	for (int i = 0; i < 8; i++) {
		int ny = now.y + dy[i];
		int nx = now.x + dx[i];
		// 범위 밖이면 continue
		if (!inRange(ny, nx))
			continue;
		// 이미 사용한 문자라면 continue;
		if (visited[ny][nx] != 0)
			continue;
		visited[ny][nx] = 1;
		// 다음 좌표로 이동하면서 해당 문자를 추가하면서 더 깊이 탐색
		dfs({ ny, nx }, cur + board[ny][nx]);
		visited[ny][nx] = 0;
	}
}

void check_result() {

	search_cnt = 0;
	point_sum = 0;
	len_max = 0;

	// 단어 사전에 등재된 단어를 모두 탐색해보며
	// 보드에서 찾아낸 모든 조합 중에 해당 단어가 있는지 확인
	for (int i = 0; i < v_dict.size(); i++) {
		Word now = v_dict[i];	// 단어 사전에 있는 단어
		// 단어가 없으면 다음 단어의 존재 여부 확인하기 위해 continue
		if (mp_word.find(now.word) == mp_word.end() || mp_word[now.word] == 0)
			continue;
		// 단어 사전에 해당 단어 찾았음을 표시
		v_dict[i].found = 1;

		search_cnt++;
		point_sum += point[now.word.length()];
		if (len_max >= now.word.length())
			continue;
		len_max_word = now.word;
		len_max = now.word.length();
	}
}

void solution() {
	// 보드 상 모든 지점을 순회하며
	// 해당 지점으로부터 시작되는 단어 모두 탐색해보기
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			string cur = "";
			visited[row][col] = 1;
			dfs({ row, col }, cur + board[row][col]);
			visited[row][col] = 0;
		}
	}

	check_result();

	// 결과 출력
	cout << point_sum << " ";
	cout << len_max_word << " ";
	cout << search_cnt << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int w;
	int b;
	// 단어 사전 목록 만들기
	cin >> w;
	for (int i = 0; i < w; i++) {
		string word;
		cin >> word;
		v_dict.push_back({ word, 0 });
	}
	// 우선순위 1. 긴 단어, 2. 알파벳 순
	sort(v_dict.begin(), v_dict.end(), cmp());
	dict_word_len_max = (*(v_dict.begin())).word.length();
	dict_word_len_min = (*(v_dict.end() - 1)).word.length();

	cin >> b;
	for (int bc = 0; bc < b; bc++) {

		// 초기화
		// 1. 단어 사전 목록에서 찾은 기록 초기화
		for (int i = 0; i < v_dict.size(); i++)
			v_dict[i].found = 0;
		// 2. 보드에서 찾은 단어 조합 초기화
		mp_word.clear();

		// 보드 입력
		string str_row;
		for (int row = 0; row < 4; row++) {
			cin >> str_row;
			for (int col = 0; col < 4; col++) {
				board[row][col] = str_row[col];
			}
		}

		solution();

	}

	return 0;
}
