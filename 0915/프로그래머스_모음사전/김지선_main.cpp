#include <string>
#include <vector>

using namespace std;
string arr[5] = { "A", "E", "I", "O", "U" };
int answer;
int cnt = 0;

void dfs(string now, string word) {
    if (now == word) {
        answer = cnt;
    }
    if (now.length() > 5) {
        return;
    }
    cnt++;
    for (int i = 0; i < 5; i++) {
        dfs(now + arr[i], word);
    }
}
int solution(string word) {
    dfs("", word);
    return answer;
}
