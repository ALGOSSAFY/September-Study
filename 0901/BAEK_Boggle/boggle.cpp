#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

int w, b;
vector<string>v;
string board[4];
int finalcnt = 0;
int tempcnt;
int score;
int final_score = 0;
int MAX = -987654321;
string MAX_word;
int ydir[] = { 0,0,-1,-1,-1,1,1,1 };
int xdir[] = { -1,1,0,1,-1,0,-1,1 };
int visited[4][30] = { 0, };

void findword(int y, int x, int idx, int cnt) {
    if (v[idx][cnt] == '\0') {
        tempcnt = 1;
        if (MAX <= cnt) {
            MAX = cnt;
            if (MAX == cnt) {
                if (MAX_word.compare(v[idx]) > 0) {
                    MAX_word = v[idx];
                }
                else {
                    MAX_word = v[idx];
                }
            }
            else {
                MAX_word = v[idx];
            }
        }
        if (cnt == 3 || cnt == 4) {
            score = 1;
        }
        else if (cnt == 5) {
            score = 2;
        }
        else if (cnt == 6) {
            score = 3;
        }
        else if (cnt == 7) {
            score = 5;
        }
        else if (cnt == 8) {
            score = 11;
        }
        return;
    }

    for (int i = 0; i < 8; i++) {
        int ny = y + ydir[i];
        int nx = x + xdir[i];
        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) {
            continue;
        }

        if (visited[ny][nx] == 1) {
            continue;
        }

        if (board[ny][nx] == v[idx][cnt]) {
            visited[ny][nx] = 1;
            findword(ny, nx, idx, cnt + 1);
            visited[ny][nx] = 0;
        }
    }
    return;
}

int main() {
    cin >> w;
    for (int i = 0; i < w; i++) {
        string str;
        cin >> str;
        v.push_back(str);
    }
    cin >> b;
    for (int num = 0; num < b; num++) {
        finalcnt = 0;
        final_score = 0;
        MAX = -987654321;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 30; j++) {
                visited[i][j] = 0;
            }
        }
        for (int i = 0; i < 4; i++) {
            cin >> board[i];
        }
        for (int idx = 0; idx < w; idx++) {
            score = 0;
            tempcnt = 0;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (visited[i][j] == 1) {
                        continue;
                    }
                    if (v[idx][0] == board[i][j]) {
                        visited[i][j] = 1;
                        findword(i, j, idx, 1);
                        visited[i][j] = 0;
                    }
                }
            }
            final_score += score;
            finalcnt += tempcnt;
        }
        cout << final_score << " " << MAX_word << " " << finalcnt << endl;
    }
}