#include <iostream>
#include <vector>

using namespace std;

const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}},
};

bool set(vector<vector<int>> &board, int y, int x, int type, int delta){
    bool ok = true;
    // 해당 type에서 세 칸 모두 놓을 수 있는지 확인
    for(int i =0; i < 3; i++){
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        // 범위 벗어나면 못 놓는다
        if (!(0 <= ny && ny < board.size() && 0 <= nx && nx < board[0].size()))
            ok = false;
        // delta : 1 -> 놓기
        // delta : -1 -> 치우기
        else if ((board[ny][nx] += delta) > 1)
            ok = false;
    }
    return ok;
}

int cover(vector<vector<int>>& board){
    // 오른쪽으로 읽어 내려가며 비어있는 칸 찾기
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 0){
                // 비어있는 칸 찾았다
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1)
            break;
    }
    // base case
    // 다 둘러봤는데 빈칸이 없다 -> 다 채워진 판
    if (y == -1)
        return 1;
    // recursive case
    int ret = 0;
    for (int type = 0; type < 4; type++){
        // 해당 type으로 현 위치에 놓아 본다, 놓을 수 있는가?
        if (set(board, y, x, type, 1))
            // 둘 수 있으니깐, 이렇게 놓았을 때 가능한 경우의 수 add
            ret += cover(board);
        // 복구
        set(board, y, x, type, -1);
    }
    return ret;
}

vector<vector<int>> input() {
    vector<vector<int>> board;
    int H, W;
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        vector<int> row;
        for (int j = 0; j < W; j++) {
            char ch;
            cin >> ch;
            if (ch == '#')
                row.push_back(1);
            else if (ch == '.')
                row.push_back(0);
        }
        board.push_back(row);
    }
    return board;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int C;
    cin >> C;
    for (int tc = 1; tc <= C; tc++){
        vector<vector<int>> board = input();
        cout << cover(board) << "\n";
    }

	return 0;
}
