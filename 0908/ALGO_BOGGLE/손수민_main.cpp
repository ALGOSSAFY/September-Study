#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
/*
  알고스팟 BOGGLE
  모든 칸을 보며 시작 단어가 있으면 탐색
  지나간 단어도 가능하니까
  지나간 단어로 역행도 가능
  배열에 단어 정보와 좌표를 저장해놓음
  점화식
  최대 10개의 단어니까 해당 단어와 근처 있는 좌표와
  중복연산막기?
  시간초과 나는 이유 - 매번 갈 필요가 없는 곳을 연산하기 때문
  3차원 배열을 통해서 해당 인덱스에서 해당 단어를 얻지 못한 다는 것을 알면
  더이상 탐색 안함
  // testcase
4
URLPM
XPRET
GIAET
XTNZY
XOQRS
10
PRETTY
GIRL
REPEAT
KARA
PANDORA
GIAZAPX
REPEAT
KARA
PANDORA
URLPMPMPMM
NNNNS
NEEEN
NEYEN
NEEEN
NNNNN
4
YESR
SNNNNNNN
EEEEEEEEE
NEYN
NNNNN
NEEEN
NEYEN
NEEEN
NSNNN
1
YES
AAAAA
AAAAA
AAAAA
AAAAA
AAAAB
4
ABABABABAA
AAAAAAAAAB
ABABABABBA
BAAAAAAABA

result
PRETTY YES
GIRL YES
REPEAT YES
KARA NO
PANDORA NO
GIAZAPX YES
REPEAT YES
KARA NO
PANDORA NO
URLPMPMPMM NO
YESR NO
SNNNNNNN YES
EEEEEEEEE YES
NEYN NO
YES YES
ABABABABAA YES
AAAAAAAAAB YES
ABABABABBA NO
BAAAAAAABA YES


*/
char words[5][5];
int dp[5][5][11] = {
};
// dp[r][c][l] => 해당 l부터 만들 수 있나
// 0있음
// 1없음
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
bool calc_range(int x, int y) {
  if (x >= 0 && x < 5 && y >= 0 && y < 5)
    return true;
  return false;
}
bool chk(int x, int y, int l, int size, string question) {
  int &result = dp[x][y][l];
  if(result !=-1)
    return result;
  //dp를 활용해서 바로 리턴
  if(l==size)
    return result=1;
  for(int d=0;d<8;d++)
    {
      int mov_x = x+dx[d];
      int mov_y = y+dy[d];
      if(calc_range(mov_x,mov_y) && words[mov_x][mov_y] == question[l])
      {
        result = chk(mov_x,mov_y,l+1,size,question);
        if(result)
        {
          return result;
          //1이면 바로 리턴
        }




        
      }

      
    }
  //못찾은거임
  return result =0;
  
}
bool chk_word(string question)
{
    int size= question.size();
      for (int r = 0; r < 5 ; r++) {
        for (int c = 0; c < 5 ; c++) {
          if (words[r][c] == question[0] ) {
            dp[r][c][0] = chk(r, c, 1, size, question);
            //dp[r][c][i] 의미 => r,c에서 i번째 단어부터 만들 수 있다
            if(dp[r][c][0] == 1)
            {
              return 1;
              
            }
          }
        }
      }
  return 0;
  
}
int main() {
  int b;
  cin >> b;
  for (int i = 0; i < b; i++) {
    for (int r = 0; r < 5; r++) {
      string tmp;
      cin >> tmp;

      for (int c = 0; c < 5; c++) {
        words[r][c] = tmp[c];
      }
    }
    //단어들을 입력받음
    int q;
    cin >> q;
    for (int idx = 0; idx < q; idx++) {
      string question;
      cin >> question;
      bool found_flag = false;
      memset(dp,-1,sizeof(dp));
      //-1 초기값

      //하나씩 검색하면서 첫 단어가 같을 경우
      found_flag = chk_word(question);
      //cout<<endl;
      if (found_flag) {
        printf("%s YES\n",question.c_str());
        //cout << question << " YES\n";
      } else {
        printf("%s NO\n" , question.c_str());
        //cout << question << " NO\n";
      }
    }
  }
}