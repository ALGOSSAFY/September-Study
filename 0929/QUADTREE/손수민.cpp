#include <iostream>
#include <string>
using namespace std;
/*
  QUADTREE
  0123에서 2301으로
*/


string make_other(string a,int &idx)
{
  idx+=1;
  string result ="";
  if(idx>=a.size())
    return result;
  if(a[idx] !='x')
  {
    //idx+=1;
    result = a[idx];
    return result;
  }
  else
  {
    //idx+=1;
    string zero = make_other(a,idx);
    string one = make_other(a,idx);
    string two = make_other(a,idx);
    string thr = make_other(a,idx);
    result = 'x'+two+thr+zero+one;
  }
  return result;
  
}
int main() {
  int c;
  cin>>c;
  for(int tc=0;tc<c;tc++)
    {
      string rect;
      cin>>rect;
      if(rect[0] !='x')
      {
        cout<<rect[0]<<'\n';
        continue;
      }
      else
      {
        int idx= -1;
        cout<<make_other(rect,idx)<<'\n';


        
      }



      
    }
}