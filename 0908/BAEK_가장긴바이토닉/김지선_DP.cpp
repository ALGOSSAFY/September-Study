#include <iostream>
using namespace std;

int N;
int arr[1000];
int Larr[1000];
int Rarr[1000];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    //왼쪽 부터 이 숫자일 떄 앞에 작은수로 몇까지 쌓을 수 있는지
    for (int i = 0; i < N; i++) {
        Larr[i] = 1;
        for (int j = 0; j < N; j++) {
            if (arr[j] < arr[i] && Larr[i] < Larr[j] + 1) {
                Larr[i] = Larr[j] + 1;
            }
        }
    }
    //오른쪽도
    for (int i = N - 1; i >= 0; i--) {
        Rarr[i] = 1;
        for (int j = N - 1; j >= 0; j--) {
            if (arr[i] > arr[j] && Rarr[j] + 1 > Rarr[i]) {
                Rarr[i] = Rarr[j] + 1;
            }
        }
    }
    //합쳐보기
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (ans < Larr[i] + Rarr[i] - 1) {
            ans = Larr[i] + Rarr[i] - 1;
        }
    }
    cout << ans << endl;
}