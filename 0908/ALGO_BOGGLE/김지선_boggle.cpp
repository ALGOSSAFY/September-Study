#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

int C, N;
int ydir[] = { 0,0,-1,-1,-1,1,1,1 };
int xdir[] = { -1,1,0,1,-1,0,-1,1 };
int arr[5][5][10];

int dp(int y, int x, int idx, const vector<string>& board, const string& str) {
    //�ܾ� ���� �ϼ�
    if (idx >= str.length()) {
        return 1;
    }

    //����
    if (y < 0 || x < 0 || y >= 5 || x >= 5) {
        return 0;
    }

    // ���� ���ں��� �����ϴ� ���� ����!
    if (board[y][x] != str[idx]) {
        return 0;
    }

    // -1�� �ƴϰ� ���ڰ� ����Ǿ��ִٸ� ����� �� �������ֱ�
    if (arr[y][x][idx] != -1) {
        return arr[y][x][idx];
    }

    // ���� ����Ǿ����� �ʴٸ� 0�̵Ǽ� ������ �غ�
    arr[y][x][idx] = 0;

    // ������ ���ڰ� �ִ��� ��������
    for (int i = 0; i < 8; i++) {
        int ny = y + ydir[i];
        int nx = x + xdir[i];

        // ���° ���ڶ�� ǥ�ø� ���ٰ���!!
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