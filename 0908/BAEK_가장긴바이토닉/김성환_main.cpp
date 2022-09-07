#include <iostream>
#include <algorithm>

using namespace std;

int arr[1000];
int dp[1000][2];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	dp[0][0] = 1;
	dp[N-1][1] = 1;
	// 각 위치에서 만들어 낼 수 있는 가장 긴 증가하는 수열 크기 계산
	for (int i = 1; i < N; i++) {
		int val= 0;
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i])
				val = max(val, dp[j][0]);
		}
		dp[i][0] = val + 1;
	}
	// 각 위치에서 만들어 낼 수 있는 가장 긴 감소하는 수열 크기 계산
	for (int i = N - 2; i >= 0; i--) {
		int val = 0;
		for (int j = N - 1; j > i; j--) {
			if (arr[j] < arr[i])
				val = max(val, dp[j][1]);
		}
		dp[i][1] = val + 1;
	}

	int max_len = 0;
	for (int i = 0; i < N; i++) {
		max_len = max(max_len, dp[i][0] + dp[i][1] - 1);
	}
	cout << max_len;

	return 0;
}
