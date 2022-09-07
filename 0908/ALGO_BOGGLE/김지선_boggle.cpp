#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

int C, N;
int ydir[] = { 0,0,-1,-1,-1,1,1,1 };
int xdir[] = { -1,1,0,1,-1,0,-1,1 };
int arr[5][5][10];

int dp(int y, int x, int idx, const vector<string>& board, const string& str) {
    //단어 길이 완성
    if (idx >= str.length()) {
        return 1;
    }

    //범위
    if (y < 0 || x < 0 || y >= 5 || x >= 5) {
        return 0;
    }

    // 없는 글자부터 시작하는 일은 없게!
    if (board[y][x] != str[idx]) {
        return 0;
    }

    // -1이 아니고 숫자가 저장되어있다면 저장된 수 리턴해주기
    if (arr[y][x][idx] != -1) {
        return arr[y][x][idx];
    }

    // 숫자 저장되어있지 않다면 0이되서 돌리기 준비
    arr[y][x][idx] = 0;

    // 주위에 글자가 있는지 돌려보자
    for (int i = 0; i < 8; i++) {
        int ny = y + ydir[i];
        int nx = x + xdir[i];

        // 몇번째 글자라고 표시를 해줄거임!!
        if (dp(ny, nx, idx+1, board, str)) {
            arr[y][x][idx]++;
            return arr[y][x][idx];
        }
    }

    return arr[y][x][idx];
}


bool findword(const vector<string>& board, const string& str) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (dp(i, j, 0, board, str)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    for (int t = 1; t <= C; t++) {

        vector <string> board;
        for (int i = 0; i < 5; i++) {
            string str;
            cin >> str;
            board.push_back(str);
        }
        cin >> N;
        for (int n = 0; n < N; n++) {
            string str;
            cin >> str;
            memset(arr, -1, sizeof(arr));
            bool ans = findword(board, str);
            if (ans == true) {
                cout << str << " YES\n";
            }
            else {
                cout << str << " NO\n";
            }
        }
    }
}