#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> apeach;
vector<int> ryan;

vector<int> ryanTemp={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int maxSub=-1;

vector<int> answer;
void dfs(int n, int level){
    
    if(n==0 || level==10){
        if(n > 0){
            ryanTemp[level]=n;
        }
        
        // 점수 계산
        int ryanPoint=0;
        int apeachPoint=0;
        for(int i=0; i<apeach.size(); i++){
            if(ryanTemp[i]==0 && apeach[i]==0) continue;
            if(ryanTemp[i]>apeach[i]){
                ryanPoint+=(10-i);
            }
            else{
                apeachPoint+=(10-i);
            }
        }
        
        // 최대 점수차 구하기
        int sub=ryanPoint-apeachPoint;
        if(sub > 0) {
            if(maxSub <= sub){
                
                if(maxSub==sub){
                    int flag=0;
                    for(int i=10; i>=0; i--){
                        if(ryanTemp[i] > ryan[i]) {
                            flag=1;
                            break;
                        }
                        else if(ryanTemp[i] < ryan[i]) {
                            flag=2;
                            break;
                        }
                    }
                    
                    if(flag==2) return;
                }
                
                maxSub=sub;
                ryan=ryanTemp;
            }
            
        }
        
        
        ryanTemp[level]-=n;
        
        return;
    }
    
    
    if(n >= apeach[level]+1){
        ryanTemp[level] = apeach[level]+1;
        dfs(n-ryanTemp[level], level+1);
    }
    
    ryanTemp[level]=0;
    dfs(n, level+1);
    
}


vector<int> solution(int n, vector<int> info) {
    apeach=info;
    
    dfs(n, 0);

    answer=ryan;
    if(answer.empty()){
        answer.push_back(-1);
    }
    
    return answer;
}
