#include <iostream>
#include <string>

using namespace std;

char dir[] = { 'A', 'E', 'I', 'O', 'U' };
int cnt = 0;
int result = 0;

void dfs(string str, string word) {

	if (str == word) {
		result = cnt;
	}

	if (str.length() >= 5) {
		return;
	}

	for (int i = 0; i < 5; i++) {
		char next = dir[i];
		cnt += 1;
		dfs(str + next, word);
	}

}

int solution(string word) {
	int answer = 0;

	dfs("", word);
    
	answer = result;
	return answer;
}
