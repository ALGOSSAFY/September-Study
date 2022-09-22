#include <string>
#include <vector>

using namespace std;


int person[360001]; //100시간*3600

inline int parse(string s){ //inline 버려
    int ret=0;
    int h=stoi(s.substr(0,2));
    int m=stoi(s.substr(3,2));
    int sec=stoi(s.substr(6,2));
    
    ret=h*3600+60*m+sec;
    
    return ret;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    //최악 360000*300000...?  //이걸 사네
    //play time 99:00:00 adv 55:00:00
    //logs 50:00:00 * 300000 => 180000*300000 폭발
  
    for(int i=0;i<logs.size();i++){
        int start=parse(logs[i].substr(0,8));
        int end = parse(logs[i].substr(9));
        
        for(int i=start;i<end;i++){
            person[i]++;
        }
    }
    int len=parse(adv_time);
    int playlen=parse(play_time);
    //init 
    long long sum=0;
    long long maxsum=0;
    int itr=0;
    for(int i=0;i<len;i++){
        sum+=person[i];
    }
    maxsum=sum;

    for(int i=len;i<playlen;i++){
       //슬라이드 윈도우 
      
        sum+=person[i];
        sum-=person[i-len];
        if(sum>maxsum){
            maxsum=sum;
            itr=i-len+1;
        }
    }
    
    if(itr/3600<=9){
        answer+="0";
    }
    answer+= to_string(itr/3600);
    itr= itr%3600;
    answer+=":";
    if(itr/60<=9){
        answer+="0";
    }
    answer+= to_string(itr/60);
    itr= itr%60;
    answer+=":";
    if(itr<=9){
        answer+="0";
    }
    answer+= to_string(itr);
    
    return answer;
}
