#include <string>
#include <vector>
#include <unordered_map>
/*
    사전 AEIOU
    길이 5이하 모든 단어
    첫 단어 A
    마지막 단어 U
    수식이 존재할듯
    길이 1 A 1번째
    길이 1 E
    매번 정렬하면 시간초과 위험
    A
    AA
    AAA
    AAAA
    AAAAA
    AAAAE
    AAAAI
    AAAAO
    AAAAU
    AAAE
    AAAEA
    AAAEE
    AAAEI
    AAAEO
    AAAEU
    AAAI
    
    
    5번째 글자 차이 1 AAAAA AAAAE
                  (5+1)
    4번째 글자 차이 6 AAAA AAAE
    3번째 글자 차이 31 (6*5+1) 사이에 30개 존재 (AAA ~ AAE)
    2번째 글자 차이 156 (31*5+1) 사이에 156개 존재 (AA ~ AE)
    1번째 글자 차이 A~I ->1563 1562 /2 (A~E)781 = (156*5) +1 781
    
    
    점화식 구축
    {A:0 , E:1 , I:2 , O:3 , U:4 }
    {첫번째 글자 * 781 + 1} + {두번째 글자 * 156 +1} + {세번째 글자 * 31 +1} + {4번째 글자 * 6 +1} + {5번째 글자 +1}
    
    AAAAE = 1 + 1+ 1+ 1+ 2 = 6 
    AAAE = 1+ 1+ 1+ (6+1) = 10
    I => 1563
    EIO = 782 + 313 + 94 = 1189
    예시 전부 통과 될것으로 보임 
    or 직접 dfs로 A부터 하면서 몇번째인지 구하기
*/
using namespace std;
int result = 0;
int chg_to(char a)
{
    if(a == 'A')
        return 0;
    else if(a == 'E')
        return 1;
    else if(a=='I')
        return 2;
    else if(a=='O')
        return 3;
    else if(a=='U')
        return 4;
}
//unordered_map<string,int> arr;
int mult[5] = {781,156,31,6,1};
int solution(string word) {
    int result = 0;
    for(int i=0;i<word.size();i++)
    {
        result += (chg_to(word[i]) *mult[i])+1;
        
    }
    return result;
    
}
