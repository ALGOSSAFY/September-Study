#include <iostream>
#include <vector>
using namespace std;
/*
  3 ->0
  6 ->1
  9 ->2
  12 ->3



*/

int arr[16] ={0,};
vector<vector<int>> buttons = {
{0,1,2},
{3,7,9,11},
{4,10,14,15},
{0,4,5,6,7},
{6,7,8,10,12},
{0,2,14,15},
{3,14,15},
{4,5,7,14,15},
{1,2,3,4,5},
{3,4,5,9,13},
};
//모두다 3이면 된거
//4번 굴리면 안해도 됨
int result = 98754321;
bool chk()
{
  for(int i=0;i<16;i++)
    if(arr[i] !=3)
      return false;
  return true;

  
}
int mod_calc(int a, int b)
{
  if(a+b<0)
    return (a+b)+4;
  return (a+b)%4;
  
}
void push_btn(int a , int pushed)
{
  if(chk())
  {
    result = min(result,pushed);
    return;
  }
  if(a==10)
    return;
  if(pushed>result)
    return;
  for(int i=0;i<4;i++)
    {
      for(int b=0;b<buttons[a].size();b++)
        {
          int change = buttons[a][b];
          arr[change] = mod_calc(arr[change],1);
          push_btn(a+1,pushed+ ((i+1)%4));
          
        }

      
    }

  
}
int main() {
  int c;
  cin>>c;
  for(int tc=0;tc<c;tc++)
    {
      result = 987654321;
      for(int i=0;i<16;i++)
        {
          cin>>arr[i];
          arr[i] /=3;
          arr[i]--;
        }
      
      push_btn(0,0);
      cout<<result;
      
    }
}