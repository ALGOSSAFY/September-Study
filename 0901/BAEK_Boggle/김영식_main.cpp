//참고하지 마시오
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

char arr[4][4];

int visited[4][4];

int dy[8] = { -1,-1,-1,0,1,1,1,0 };
int dx[8] = { -1,0,1,1,1,0,-1,-1 };

int score[9] = { 0,0,0,1,1,2,3,5,11 };

struct node {
	string s;
	int n;
};
typedef struct node NODE;
bool operator<(NODE a, NODE b) {
	if (a.n > b.n)
		return true;
	if (a.n < b.n)
		return false;
	if (a.s < b.s)
		return true;
	if (a.s > b.s)
		return false;

	return false;

}

vector<NODE> v;
string target; // 탐색 시 비교하는 단어
int sol(int level, int y,int x) {
	
	if (arr[y][x] != target[level])
	{
		return 0;
	}
	if (level == target.length()-1)
	{
		return 1;
	}
	

	for (int i = 0;i < 8;i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
		if (visited[ny][nx]) continue;
		visited[ny][nx] = 1;
		if (sol(level + 1, ny, nx)) {
			return 1;
		}
		visited[ny][nx] = 0; //전탐
	}

	return 0;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++) {
		string s;
		cin >> s;
		v.push_back({ s ,(int)s.length()});

	}
	sort(v.begin(), v.end());
	cin >> n;
  
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < 4;j++) {
			string s;
			cin >> s;
			for (int k = 0;k < 4;k++) {
				arr[j][k] = s[k];
			}
		}
    
		memset(visited, 0, sizeof(int) * 4 * 4);

		int flag = 0;
		int ansCnt = 0;
		int ansScore = 0;
		string longWord;

		for (int j = 0;j < v.size();j++) {
			target = v[j].s;
			for (int y = 0;y < 4;y++) {
				for (int x = 0;x < 4;x++) {
					if (arr[y][x] == v[j].s[0]) {
						memset(visited, 0, sizeof(int) * 4 * 4);
						visited[y][x] = 1;
						if (sol(0, y, x)) {
							if (flag == 0) {
								flag = 1;
								longWord = v[j].s;
							}
							ansCnt++;
							ansScore += score[v[j].n];
							goto abc;

						}
					}
				}
			}
			
		abc:
			continue;

		}
		cout << ansScore << " " << longWord << " " << ansCnt << '\n';


	
	}
	return 0;
}
