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
    //���� ���� �� ������ �� �տ� �������� ����� ���� �� �ִ���
    for (int i = 0; i < N; i++) {
        Larr[i] = 1;
        for (int j = 0; j < N; j++) {
            if (arr[j] < arr[i] && Larr[i] < Larr[j] + 1) {
                Larr[i] = Larr[j] + 1;
            }
        }
    }
    //�����ʵ�
    for (int i = N - 1; i >= 0; i--) {
        Rarr[i] = 1;
        for (int j = N - 1; j >= 0; j--) {
            if (arr[i] > arr[j] && Rarr[j] + 1 > Rarr[i]) {
                Rarr[i] = Rarr[j] + 1;
            }
        }
    }
    //���ĺ���
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (ans < Larr[i] + Rarr[i] - 1) {
            ans = Larr[i] + Rarr[i] - 1;
        }
    }
    cout << ans << endl;
}