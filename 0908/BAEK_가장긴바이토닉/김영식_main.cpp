#include <iostream>

using namespace std;

int datleft[1001];// 안씀
int datright[1001];// 안씀 

int dpleft[1001];
int dpright[1001];

int arr[1001];
int n;


/*
LIS(최장 거리 수열 NlogN 알고리즘을 씀) 인줄 알았지만 , 앞 뒤로 탐색을 해야하기때문에 걍 O(n*n) 문제
n<=1000 으로 n*n으로 충분


LIS 참고 사이트 
https://chanhuiseok.github.io/posts/algo-49/

백준 테케

10
1 5 2 1 4 3 4 5 2 1

백준 실행결과 4 ms 


*/ 

int main() {

	cin >> n;

	for (int i = 0; i < n; i++) {

		cin >> arr[i];
	}
	//////입력 끝////


	//왼쪽 LIS : dpleft에서 각 index의 최장거리수열의 길이를 얻는다.
	for (int k = 0; k < n; k++) {
		dpleft[k] = 1;
		for (int i = 0; i < k; i++) {
			if (arr[i] < arr[k]) {
				dpleft[k] = max(dpleft[k], dpleft[i] + 1);
			}
		}
	}

	//오른쪽 LIS:dpright에서 각 index의 최장거리수열의 길이를 얻는다.

	for (int k = n-1; k >= 0; k--) {
		dpright[k] = 1;
		for (int i = n-1; i > k; i--) {
			if (arr[i] < arr[k]) {
				dpright[k] = max(dpright[k], dpright[i] + 1);
			}
		}
	}


	//dpleft와 dpright의 합을 통해 바이토닉수열의 길이를 구 할 수 있다.
	//가장 큰 수 S_k 가 dpleft dpright에 중복되어 들어가므로 합에서 -1 해준다.
	int vmax = 0;
	for (int i = 0; i < n; i++) {
		if (dpleft[i] + dpright[i] -1> vmax) {

			vmax = dpleft[i] + dpright[i]-1;
		}

	}
	//출력에 각 index 바이토닉 수열 길이중 최대값을 내보낸다
	cout << vmax;
	

	
	return 0;
}
