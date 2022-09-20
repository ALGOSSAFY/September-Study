#include <string>
#include <vector>

using namespace std;
/*
    양궁대회
    어피치 n발 라이온 n발
    k점 어피치 a 라이온 b
    a==b 어피치 득점 0이면 득점 안함
    최종점수 더 높은 선수 우승자 결정
    화살 개수 n info 어피치 과녁
    라이언 가장 큰 점수 차이 우승 n발 어떻게?
    무조건 지거나 비기는 경우 -1 리턴
    i번째 원소 10-i점 맞힌 화살 개수
    가장 큰 점수 차이 우승 방법 여러개 -> 가장 낮은 점수 더많이 맞힌 경우
*/
int best_cmp =0;
vector<int> apeach_shot;
vector<int> best_ryan(1,-1);
int cmp_apeach_ryan(vector<int>ryan)
{
    int apeach_score = 0;
    int ryan_score = 0;
    for(int i=0;i<11;i++)
    {
        if(apeach_shot[i] ==0 && ryan[i] ==0)
            continue;
        if(apeach_shot[i] >= ryan[i] )
        {
            apeach_score +=(10-i);
        }
        else
        {
            ryan_score +=(10-i);
        }
        
    }
    if(ryan_score > apeach_score)
    {
        return (ryan_score - apeach_score);
    }
    else
        return 0;
}



void ryan_shoot(vector<int> ryan,int n,int now_shoot)
{
    //더 많이 쏠 수 도 있음
    //낮은 점수부터 쏴서 나오면 리턴
    //점수 계산
    //0점
    if(now_shoot ==0)
    {
        ryan[now_shoot] = n;
        return ryan_shoot(ryan,0,-1);
    }
    if(n==0)
    {
        int diff = cmp_apeach_ryan(ryan);
        if(best_cmp < diff)
        {
            best_cmp = diff;
            best_ryan = ryan;
        }
        return;
    }
    for(int i=n;i>=0;i--)
    {
        ryan[now_shoot] = i;
        ryan_shoot(ryan,n-i,now_shoot-1);
        //ryan[now_shoot] = 0;
    }
    
    
}
vector<int> solution(int n, vector<int> info) {
    apeach_shot = info;
    best_cmp = 0;
    vector<int> ryan(11,0);
    ryan_shoot(ryan, n,10);
    return best_ryan;
}