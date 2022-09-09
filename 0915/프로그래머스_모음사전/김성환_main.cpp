#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int cnt;
char ch[] = {'A', 'E', 'I', 'O', 'U'};
unordered_map<string, int> mp;

void dfs(int level, string word_target, string word_now){
    mp[word_now] = cnt;
    // base case
    if (level >= 5)
        return;
    // recursive case
    for (int i = 0; i < 5; i++){
        cnt++;
        dfs(level + 1, word_target, word_now + ch[i]);
    }
}

int solution(string word) {
    int answer = 0;
    dfs(0, word, "");
    
    answer = mp[word];
    
    return answer;
}
