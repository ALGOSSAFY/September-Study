#include <string>
#include <vector>
#include <string.h>

using namespace std;

vector<int> requirement;
int arr[11];
int res[11];
int diff_max = 0;
int target_lowest = 11;
int cnt_max = 0;
int flag = 0;

void getScore(int n, vector<int> info){
    int apeach = 0;
    int lion = 0;
    int cnt = 0;
    int target_low = 11;
    int shots = 0;
    for (int i = 0; i < info.size() - 1; i++){
        if (info[i] == 0 && arr[i] == 0)
            continue;
        if (info[i] >= arr[i])
            apeach += 10 - i;
        else{
            lion += 10 - i;
            target_low = 10 - i;
            shots += arr[i];
            cnt = arr[i];
        }
    }
    if (shots < n){
        target_low = 0;
        cnt = n - shots;
        arr[10] = cnt;
    }
    if (apeach >= lion)
        return;
    // lion이 이기는 상황
    if (diff_max > lion - apeach)
        return;
    // 점수차가 최대인 상황
    if (diff_max < lion - apeach){
        flag = 1;
        diff_max = lion - apeach;
        target_lowest = target_low;
        cnt_max = cnt;
        memcpy(res, arr, sizeof(arr));
        return;
    }
    // 점수차가 기존 최대 점수차와 동일한 상황
    if (target_lowest < target_low)
        return;
    // 기존보다 같거나 낮은 점수 과녁 맞춘 상황
    if (target_lowest > target_low){
        flag = 1;
        target_lowest = target_low;
        cnt_max = cnt;
        memcpy(res, arr, sizeof(arr));
        return;
    }
    // 기존과 같은 최저 점수의 과녁 맞춘 상황
    if (cnt_max >= cnt)
        return;
    // 가장 낮은 점수의 과녁을 가장 많이 맞춘 상황
    flag = 1;
    cnt_max = cnt;
    memcpy(res, arr, sizeof(arr));
}

void dfs(int n, vector<int> info, int level, int shots){
    // base case
    if (n-info[10] <= shots && shots <= n){
        getScore(n, info);
        arr[10] = 0;
    }
    if (shots > n)
        return;
    if (level == 10)
        return;
    // recursive case
    // (10 - level) 점 획득
    arr[level] = requirement[level];
    dfs(n, info, level + 1, shots + requirement[level]);
    // (10 - level) 점 포기
    arr[level] = 0;
    dfs(n, info, level + 1, shots);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    
    for (int i = 0; i < info.size() - 1; i++){
        requirement.push_back(info[i] + 1);        
    }
    dfs(n, info, 0, 0);
    if (flag == 0)
        answer.push_back(-1);
    else{
        for (int i = 0; i < info.size(); i++){
            answer.push_back(res[i]);
        }
    }
    return answer;
}

/*
0. 라이언 우승
1. 가장 큰 점수 차
2. 가장 낮은 점수 많이 맞힌 경우
*/
