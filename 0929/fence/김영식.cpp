#include <iostream>
#include <string.h>

#define go2
//go1 go2 go3
using namespace std;

//완탐 n*n;
#ifdef go1


int arr[20001];

int main() {

	memset(arr, 0, sizeof(arr));
	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {
		int n;
		cin >> n;
		memset(arr, 0, sizeof(arr));
		for (int j = 0; j < n; j++) {
			cin >> arr[j];
		}

		int ret = 0;
		for (int l = 0; l < n; l++) {  //완탐 n*n;
			int minheight = arr[l];
			for (int r = l; r < n; r++) { //완탐 n*n;
				minheight = min(minheight, arr[r]);
				ret = max(ret, (r - l + 1) * minheight);

			}
		}

		cout << ret<<"\n";
	}
	return 0;
}

#endif

#ifdef go2


int h[20001];
int n;
int solve(int left, int right) {

	if (left == right) return h[left];

	int mid = (left + right) / 2;

	int ret = max(solve(left, mid), solve(mid + 1, right));

	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);

	ret = max(ret, height * 2);

	while (left < lo || hi < right) {
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}

		ret = max(ret, height * (hi - lo + 1));

	}
	return ret;

}
int main() {

	int c; 

	//투포인터 슬라이드 윈도우  psum dp 생각해봤지만 안된다.
	cin >> c;
	for (int i = 0; i < c; i++) {
		
		cin >> n;
		int vmax = 0;
		
		
		for (int i = 0; i < n; i++) {
			
			cin >> h[i];
			
		}
	  cout<< solve(0,n-1)<<endl;


	}

	return 0;
}


#endif
