#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
  PICNIC
  서로 친구인 학생들끼리만 짝을 지어 줘야 함
  
*/
int arr[10][10] = {0,};
int visited[10] = {0,};
int dfs(int dpth, int n,int sr,int sc)
{
  if(dpth == n)
    return 1;
  int result = 0;
  for(int r=sr;r<n;r++)
    {
      if(r>sr) sc= 0;
      for(int c=sc;c<n;c++)
        {
          if(arr[r][c] ==1 && visited[r] ==0 && visited[c] ==0)
          {
            visited[r] =1;
            visited[c] = 1;
            result += dfs(dpth+2,n,r,c);
            visited[r] = 0;
            visited[c] = 0;


            
          }


          
        }



      
    }


  return result;
  
}
int main() {
  int c;
  cin>>c;
  for(int ts= 0;ts<c;ts++)
    {
      int n,m;
      cin>>n>>m;
      for(int r=0;r<10;r++)
        for(int c=0;c<10;c++)
          arr[r][c] = 0;
      for(int idx=0;idx<m;idx++)
        {
          int a,b;
          cin>>a>>b;
          arr[a][b] = 1;
          //arr[b][a] = 1;
        }
        //2개의 조합을 모두 구하기
      cout<<dfs(0,n,0,0)<<'\n';

      
    }
}