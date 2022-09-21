//부끄럼 많은 코딩을 했습니다.
//기본 +1,2차에 수정을 걸쳐 누더기 같음
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int visited[11];

int highscore;
vector<int> infocopy;
vector<int> answer2;
int endn;

void dfs(int level, int now ,int scr) {
    if(scr>highscore){
        highscore=scr;
        for (int j = 0; j <=10; j++) {
           answer2[10-j] = visited[j];
        }
    }
    
    if (level == endn) {

        int score = 0;
        for (int j = 0; j <= 10; j++) {
            if (visited[j] > infocopy[ 10-j]) {
                score += j;

            }
            else if (infocopy[10-j] == 0) {

            }
            else {
                score -= j;
            }

        }

      
        if (score > 0 && score > highscore) {
            highscore = score;
            for (int j = 0; j <=10; j++) {
                answer2[10-j ] = visited[j];
            }
           

        }


        return;
    }


      for (int i = now; i <= 10; i++) {
        //visited[i]++;
        //dfs(level + 1, i);
        //visited[i]--;
        int mem = 0;
        
        if (infocopy[10 - i] == 0) {
            visited[i]++;
            dfs(level + 1, i + 1,scr+i);
            visited[i]--;
        }
        else if (infocopy[10 - i] +1 <= endn - level) {
            mem = infocopy[10 - i]+1;
            visited[i] = mem;
            dfs(level + mem, i + 1,scr+i+i);
            visited[i] = 0;
        }
        else {
            if(infocopy[10-i]==0)
                dfs(level, i + 1,scr);
            
        }

    }

}

vector<int> solution(int n, vector<int> info) {

    endn = n;
    vector<int> answer;
    infocopy = info;
    int prescore=0;
    for (int i = 0; i <= 10; i++) {
        answer2.push_back(0);
        if(info[i]){
            prescore-=10-i;
        }
    }
    
    cout<<prescore<<" ";
    dfs(0, 0,prescore);
    if (highscore == 0) {
        return { -1 };
    }
    else{
        
        int chk=0;
        for(int i=0;i<=10;i++){
            chk+=answer2[i];
            
            
        }
        if(chk!=n){
            answer2[10]=n-chk;
        }
        
        
        
        return answer2;
    }
}
