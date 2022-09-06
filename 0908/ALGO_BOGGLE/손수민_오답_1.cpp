#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
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
  3차원 배열을 통해서 해당 인덱스에서 해당 단어를 얻지 못한 다는 것을 알면 더이상 탐색 안함
*/
char words[5][5];
bool dp[5][5][10] = {0,};
//0있음 
//1없음
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
bool calc_range(int x, int y) {
  if (x >= 0 && x < 5 && y >= 0 && y < 5)
    return true;
  return false;
}
int i_x;
int i_y;
bool chk( int x, int y, int l, int size, string question) {
  if(l==size-1)
    return 0;

  for(int d=0;d<8;d++)
    {
      int mov_x = x+dx[d];
      int mov_y = y+dy[d];
      if(calc_range(mov_x,mov_y) && words[mov_x][mov_y] == question[l+1] && !dp[mov_x][mov_y][l+1] )
        //여기서 안되면 1로 만들어서 안갈 수 있음 
      {
        //범위안에 있고
        //원하는 단어와 같고
        //갈수 있다 생각함
        return dp[x][y][l] = min(dp[x][y][l] , chk(mov_x,mov_y,l+1,size,question));
        //해당 점에서 가고 0이면 만들 수 있다는 뜻
        //1이어도 끝까지가서 0이면 만들 수 있다는 뜻
      }

      
    }
  return dp[x][y][l] = 1;
  //해당 l부터 못만듬
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
    int q;
    cin >> q;
    for (int idx = 0; idx < q; idx++) {
      string question;
      cin >> question;
      int size = question.size();
      bool found_flag = false;
      for(int x=0;x<5;x++)
        for(int y=0;y<5;y++)
          for(int k=0;k<10;k++)
            dp[x][y][k] = 0;
      for(int r=0;r<5&&!found_flag;r++)
        {
        for(int c=0;c<5&&!found_flag;c++)
          {
            if(words[r][c] == question[0])
            {
              dp[r][c][0] = 1;
              if(!chk(r,c,0,size,question))
              {
                found_flag = true;
              }

              
            }

            
          }
          
        }
        if(found_flag)
        {
          cout<<question<<" YES\n";
        }
        else
        {
          cout<<question<<" NO\n";
        }

      
    }
  }
}