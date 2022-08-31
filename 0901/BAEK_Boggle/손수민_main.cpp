#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
/*
  Boggle
  글자가 쓰여있는 4*4 그리드내에서 최대한 많은 단어 찾기
  인접한 글자로 만들 수 있음 가로 세로 대각선
  한 주사위 한번에만 사용 가능
  순열 문제 (순서가 달라져도 됨)
  얻을 수 있는 최대 점수
  가장 긴 단어
  찾은 단어의 수
  찾고자 하는 단어의 수 주어짐
  그 다음 보드가 주어짐
*/
const int INF = 987654321;
int score = 0;
string length = "";
int cnt = 0;
int w;
int visited[4][4] = { 0, };
char words[4][4] = { 0, };
vector <string> finding;
unordered_map<string, int>how_many;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

bool calc_range(int x, int y)
{
    if (x >= 0 && x < 4 && y >= 0 && y < 4)
        return true;
    return false;
}

static bool cmp(string a,string b)
{
  if(a.size()>b.size())
    return true;
  if(a.size() == b.size())
  {
    if(a<b)
      return true;
    return false;
  }
  return false; 
}

void find_all_words(int dpth,int x,int y,string word)
{
  how_many[word] =1;
  if(dpth == 8)
    return;
  for(int d=0;d<8;d++)
    {
      int mov_x = x+dx[d];
      int mov_y = y+dy[d];
      if(calc_range(mov_x,mov_y) && !visited[mov_x][mov_y])
      {
        visited[mov_x][mov_y]  =1;
        find_all_words(dpth+1,mov_x,mov_y,word+words[mov_x][mov_y]);
        visited[mov_x][mov_y] = 0;


        
      }

      
    }

  
}
int main() {
  cin>>w;
  for(int i=0;i<w;i++)
    {
      string tmp;
      cin>>tmp;
      finding.push_back(tmp);
      //찾고자 하는 것
    }
  sort(finding.begin() , finding.end(),cmp);
  int b;
  cin>>b;
  for(int i=0;i<b;i++)
    {
      score = 0;
      cnt= 0;
      length = "";
      how_many.clear();
      for(int r=0;r<4;r++)
        {
          string tmp;
          cin>>tmp;
          for(int c=0;c<4;c++)
            {
              words[r][c] = tmp[c];
            }
        }
      for(int r=0;r<4;r++)
        {
        for(int c=0;c<4;c++)
          {
            for(int vr=0;vr<4;vr++)
              for(int vc=0;vc<4;vc++)
                visited[vr][vc] = 0;
            //해당 시작점으로 시작하는 모든 단어들
            visited[r][c] = 1;
            string tmp ="";
            tmp+=words[r][c];
            find_all_words(1,r,c,tmp);
          }

          
        }
      for(int idx= 0;idx<w;idx++)
        {
          string tmp = finding[idx];
          int chk = how_many[tmp];
          int len = tmp.size();
          if(chk)
          {
            cnt++;
            if(len>length.size())
              length = tmp;
            if(len>=3 && len <=4)
            {
              score+=1;
            }
            else if(len == 5)
            {
              score+=2;
            }
            else if(len ==6)
            {

              score+=3;
            }
            else if(len ==7)
            {
              score+=5;
            }
            else if(len == 8)
            {
              score+=11;
            }



            
          }

          
        }
        cout<<score<<' '<<length<<' '<<cnt<<'\n';
    }


}