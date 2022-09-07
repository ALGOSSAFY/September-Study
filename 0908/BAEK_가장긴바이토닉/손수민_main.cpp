#include <iostream>
using namespace std;
int small[1000] = {
    0,
};
int big[1000] = {
    0,
};
int arr[1000] = {
    0,
};
int n;
int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  //0~n-1까지의 최장 증가 수열 길이
  //n-1~0까지의 최장 증가 수열 길이
  small[0] = 0;
  big[n - 1] = 0;
    int result =-1;
    for(int i=0;i<n;i++)
      {
        result = max(result, small[i]+big[i]);
        
      }
    for(int i=1;i<n;i++)
      {
        int j = i;
        while(j>=1)
        {
          j--;
        if(arr[j] < arr[i])
        {
          small[i] = max(small[i],small[j]+1);
        }
        else if(arr[j] == arr[i])
        {
          small[i] = max(small[i],small[j]);
        }
        }
        
      }
    for(int i=n-2;i>=0;i--)
      {
        int j=i;
        while(j<n-1)
        {
          j++;
        if(arr[j] < arr[i])
        {
          big[i] = max(big[i],big[j]+1);
        }
        else if(arr[j] == arr[i])
        {
          big[i] = max(big[i],big[j]);
        }
      }


        
      }

    for(int i=0;i<n;i++)
      {
        result = max(result,small[i]+big[i]);
      }

  
  cout<<result+1<<endl;



  
}