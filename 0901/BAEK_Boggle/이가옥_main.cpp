#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Word {
	int len;
	string word;
};

int w;
vector<pair<string, int>> words;
char MAP[4][4];

int dy[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dx[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int visited[4][4];

unordered_map<string, int> words_check;
unordered_map<string, int> allWords;

int maxPoint = 0;
int wordCount = 0;

vector<Word> maxLenWords;
bool cmp(Word a, Word b) {
	if (a.len > b.len) return true;
	if (a.len < b.len) return false;
	if (a.word > b.word) return false;
	if (a.word < b.word) return true;
	return false;
}

int calc_point(string str) {
	int len = str.length();

	if (len <= 2) return 0;
	else if (len <= 4) return 1;
	else if (len == 5) return 2;
	else if (len == 6) return 3;
	else if (len == 7) return 5;
	else if (len == 8) return 11;
}

void dfs(int y, int x, int level, string cur) {

	if (level == 8) {
		return;
	}
	
	if (allWords[cur] == 0) {
		allWords[cur] = 1;
	}

	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) continue;
		if (visited[ny][nx] != 0) continue;

		visited[ny][nx] = 1;
		
		dfs(ny, nx, level + 1, cur+MAP[ny][nx]);

		visited[ny][nx] = 0;
	}

}

int main() {

	cin >> w;

	// 단어 사전
	for (int i = 0; i < w; i++) {
		string str;
		cin >> str;
		words.push_back(make_pair(str, 0));

		int len = str.length();
		words_check[str] = 1;
	}

	int b;
	cin >> b;

	for (int t = 0; t < b; t++) {

		// Boggle 보드 생성 
		for (int i = 0; i < 4; i++) {
			string temp;
			cin >> temp;
			for (int j = 0; j < 4; j++) {
				MAP[i][j] = temp[j];
			}
		}

		// dfs - 가능한 단어 모두 찾기 (단어 사전의 최대 길이까지)
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				visited[i][j] = 1;

				string temp;
				temp += MAP[i][j];
				dfs(i, j, 0, temp);

				visited[i][j] = 0;
			}
		}

		// 해시에 사전에 있는 단어가 있다면!
		for (int i = 0; i < words.size(); i++) {
			string target = words[i].first;
			if (allWords[target] == 1) {
				maxPoint += calc_point(target);

				int len = target.length();
				maxLenWords.push_back({ len, target });

				wordCount += 1;
			}
		}

		sort(maxLenWords.begin(), maxLenWords.end(), cmp);
		cout << maxPoint << " " << maxLenWords[0].word << " " << wordCount << "\n";

		// 초기화
		words_check.clear();

		maxPoint = 0;
		wordCount = 0;
		maxLenWords.clear();

		allWords.clear();

	}

	return 0;
}
