#include <iostream>
#include <vector>
using namespace std;

struct Pos {
    int y, x;
};
int arr[9][9];
int cnt = 0;
bool perfect = false;
vector<Pos>v;

//값이 들어갈 수 있나 없나 계산하기!
bool haveNum(int y, int x) {
    
    //가로, 세로 줄 먼저 안되는 건 쳐내자!
    for (int i = 0; i < 9; i++) {
        if (arr[y][i] == arr[y][x] && i != x) {
            return false;
        }
        if (arr[i][x] == arr[y][x] && i != y) {
            return false;
        }
    }

    //3x3 배열안에 안되는걸 쳐내자
    
    //먼저 어디 3x3배열에 소속되어있는지 알아보자
    int s_y = y / 3;
    int s_x = x / 3;

    for (int i = 3 * s_y; i < 3 * (s_y + 1); i++) {
        for (int j = 3 * s_x; j < 3 * (s_x + 1); j++) {
            if (arr[i][j] == arr[y][x] && i != y && j != x) {
                return false;
            }
        }
    }

    //한번도 가지가 안쳐지고 살아남았다!!
    return true;
}

void dfs(int now) {
    if (now == cnt) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        perfect = true;
        return;
    }

    //1~9까지 다 넣어보고 판별하기
    for (int i = 1; i <= 9; i++) {
        arr[v[now].y][v[now].x] = i;
        //숫자를 넣어보고 이게 맞는지 알아보는 함수를 만들자
        if (haveNum(v[now].y,v[now].x)) {
            //만약 숫자가 넣어졌으면 다음 칸으로!
            dfs(now + 1);
        }
        //다 만들어졌다!!
        if (perfect) {
            return;
        }
    }

    //결국 값을 지정해주지 못했을 경우 초기화 시켜주자!
    arr[v[now].y][v[now].x] = 0;
    return;
}
int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 0) {
                cnt++;
                v.push_back({ i,j });
            }
        }
    }
    dfs(0);
}