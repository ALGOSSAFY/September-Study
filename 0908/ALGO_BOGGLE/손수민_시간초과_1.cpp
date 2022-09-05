#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
/*
  알고스팟 BOGGLE
  모든 칸을 보며 시작 단어가 있으면 탐색
  지나간 단어도 가능하니까
  지나간 단어로 역행도 가능
  배열에 단어 정보와 좌표를 저장해놓음
*/
char words[5][5];
struct info {
  char c;
  int x;
  int y;
};
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
bool calc_range(int x, int y) {
  if (x >= 0 && x < 5 && y >= 0 && y < 5)
    return true;
  return false;
}
bool chk(info making[11], int x, int y, int l, int size, string question) {
  //메모이제이션 배열 ,x좌표 , y좌표, 현재 깊이 , 종료 깊이 , 체크해야하는 다음
  //question
  bool result = false;
  if (l == size)
    return result = true;

  for (int d = 0; d < 8; d++) {
    int mov_x = x + dx[d];
    int mov_y = y + dy[d];
    if (making[l - 1].c == question[l] && l >= 2) {
      making[l + 1] = {making[l - 1].c, making[l - 1].x, making[l - 1].y};
      result =
          chk(making, making[l - 1].x, making[l - 1].y, l + 1, size, question);
      if (result)
        return true;
    }

    if (calc_range(mov_x, mov_y)) {
      if (question[l] == words[mov_x][mov_y]) {
        making[l + 1] = {words[mov_x][mov_y], mov_x, mov_y};
        result = chk(making, mov_x, mov_y, l + 1, size, question);
        if (result)
          return result = true;
      }
    }
  }

  return result;
}

int main() {
  int b;
  cin >> b;
  for (int i = 0; i < b; i++) {
    info making[11] = {
        {0, 0, 0},
    };
    for (int r = 0; r < 5; r++) {
      string tmp;
      cin >> tmp;

      for (int c = 0; c < 5; c++) {
        words[r][c] = tmp[c];
      }
    }
    int q;
    cin >> q;
    for (int idx = 0; idx < q; idx++) {
      string question;
      cin >> question;
      int size = question.size();
      bool found_flag = false;
      for (int r = 0; r < 5 && !found_flag; r++) {
        for (int c = 0; c < 5 && !found_flag; c++) {
          if (question[0] == words[r][c] && !found_flag) {
            making[1] = {words[r][c], r, c};
            if (chk(making, r, c, 1, size, question)) {
              found_flag = true;
              break;
            }
          }
        }
      }
      if (found_flag) {
        cout << question << " YES\n";
      } else {
        cout << question << " NO\n";
      }
    }
  }
}