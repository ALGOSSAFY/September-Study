#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;
int arr[9][9] = {0,};
int cols[9][10] = {0,}; //해당 col에 있는 1부터 9까지의 수
int rows[9][10] = {0,}; //해당 row에 있는 1부터 9까지의 수
int rect[9][10] = {0,}; //해당 칸에 있는 1부터 9까지의 수
int result[9][9] = {0,};
int end_x,end_y;
int possible[9][9][10] = {0,};
int to_rect[9][9] = {0,};



int chg_to_num(int x,int y)
{
  if(x>=0 && x<=2)
  {
    if(y>=0 && y<=2)
      return 0;
    else if(y>=3 && y<=5)
      return 1;
    else if(y>=6 && y<=8)
      return 2;

    
  }
  else if(x>=3 && x<=5)
  {
      if(y>=0 && y<=2)
      return 3;
    else if(y>=3 && y<=5)
      return 4;
    else if(y>=6 && y<=8)
      return 5;

    
  }
  else if(x>=6 && x<=8)
  {
    if(y>=0 && y<=2)
      return 6;
    else if(y>=3 && y<=5)
      return 7;
    else if(y>=6 && y<=8)
      return 8;

    
  }

  
}
bool chk_finished()
{
  //모든 행 열의 합이 다 1
  //그냥 다 더하기?
  int chk = 0;
  for(int i=0;i<9;i++)
    {
      for(int j=1;j<=9;j++)
        {
          chk+=cols[i][j];
          chk+=rows[i][j];
          chk+=rect[i][j];
        }
    }
  if(chk == 243)
    return true;
  return false;  
}
void possible_num(int x, int y)
{
  int rec = to_rect[x][y];
  vector<int>arr(10,0);
  for(int i=1;i<10;i++)
    {
      arr[i] += rows[x][i];
      arr[i] += cols[y][i];
      arr[i] +=rect[rec][i];


      
    }
  vector<int>result;
  for(int i=1;i<10;i++)
    {
      possible[x][y][i] = arr[i];
    }
  //가능한 모든 정보가 되어있음 
  //0이면 넣어도 되는 것
  //return result;
}


bool found_flag = false;
void dfs(int x,int y)
{
  

  if(found_flag)
    return;
  if(chk_finished() && !found_flag)
  {
    //resut에 복사 및 종료
    for(int i=0;i<9;i++)
      for(int j=0;j<9;j++)
        result[i][j] = arr[i][j];
    found_flag = true;
    return;
  }
  //못찾은 상태로 끝부분이면 return
  if(x>=end_x && y>=end_y+1)
    return;
  for(int i=x;i<9;i++)
    {
      if(i>x) y=0;
    for(int j=y;j<9;j++)
      {
        if(arr[i][j] == 0 )
        {
          int rec = to_rect[i][j];
          for(int idx =1;idx<=9;idx++)
            {
              if(possible[i][j][idx] == 0 && rect[rec][idx] ==0  && rows[i][idx] ==0 &&  cols[j][idx] ==0 )
              {
              int num = idx;
              arr[i][j] = num;
              rect[rec][num]++;
              rows[i][num]++;
              cols[j][num]++;
              dfs(i,j+1);
              arr[i][j] = 0;
              rect[rec][num]--;
              rows[i][num]--;
              cols[j][num]--;


                
              }
    

              
            }

          
        }




        
      }
  



      
    }


  
}
int main() {
  for(int i=0;i<9;i++)
    for(int j=0;j<9;j++)
      to_rect[i][j] = chg_to_num(i,j);
  for(int i=0;i<9;i++)
    {
    for(int j=0;j<9;j++)
      {
        cin>>arr[i][j];
        if(arr[i][j])
        {
        cols[j][arr[i][j]]++;
        rows[i][arr[i][j]]++;
        int rec = to_rect[i][j];
        rect[rec][arr[i][j]]++;
        }
        else
        {
          end_x = i;
          end_y = j;
          
        }
      }
      

    }
  for(int i=0;i<9;i++)
    for(int j=0;j<9;j++)
      possible_num(i,j);
  dfs(0,0);
  for(int i=0;i<9;i++)
    {
      for(int j=0;j<9;j++)
        {
          cout<<result[i][j]<<' ';
        }
      cout<<endl;



      
    }

  
}