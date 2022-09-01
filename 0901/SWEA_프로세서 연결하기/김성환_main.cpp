#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int y;
    int x;
};

int board[12][12];
int board_copy[12][12];
int N;
vector<Node> v_core_list;
vector<int> v_connection_list[12];
vector<int> v_connection_dir;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int dist_sum;
int dist_sum_min;
int connect_cnt_max;

bool inRange(int y, int x) {
    if (0 <= y && y < N && 0 <= x && x < N)
        return true;
    return false;
}

void copy_board() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            board_copy[row][col] = board[row][col];
    }
}

int make_connection() {
    copy_board();
    dist_sum = 0;

    for (int idx = 0; idx < v_core_list.size(); idx++) {
        int dir = v_connection_dir[idx];
        if (dir == 4)
            continue;
        Node now = v_core_list[idx];
        int dist = 1;
        while (true) {
            int ny = now.y + dy[dir] * dist;
            int nx = now.x + dx[dir] * dist;
            if (!inRange(ny, nx)) {
                dist_sum += dist - 1;
                break;
            }
            if (board_copy[ny][nx] != 0)
                return 0;
            board_copy[ny][nx] = 1;
            dist++;
        }
    }
    return 1;
}

void choose_connection(int idx, int try_connect) {
    // base case
    if (idx == N) {
        if (connect_cnt_max > try_connect)
            return;
        if (!make_connection())
            return;
        if (connect_cnt_max < try_connect) {
            connect_cnt_max = try_connect;
            dist_sum_min = dist_sum;
        }
        else
            dist_sum_min = min(dist_sum_min, dist_sum);
        return;
    }
    // recursive case
    for (int i = 0; i < v_connection_list[idx].size(); i++) {
        v_connection_dir.push_back(v_connection_list[idx][i]);
        choose_connection(idx + 1, try_connect + 1);
        v_connection_dir.pop_back();
    }
    v_connection_dir.push_back(4);
    choose_connection(idx + 1, try_connect);
    v_connection_dir.pop_back();

}

void find_connection() {
    for (int idx = 0; idx < v_core_list.size(); idx++) {
        Node now = v_core_list[idx];

        for (int dir = 0; dir < 4; dir++) {
            int dist = 1;
            while (true) {
                int ny = now.y + dy[dir] * dist;
                int nx = now.x + dx[dir] * dist;
                if (!inRange(ny, nx)) {
                    v_connection_list[idx].push_back(dir);
                    break;
                }
                if (board[ny][nx] == 1)
                    break;
                dist++;
            }
        }
    }
}

void solution() {
    find_connection();
    choose_connection(0, 0);
}

void input() {
    cin >> N;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> board[row][col];
            if (board[row][col] == 0)
                continue;
            if (row == 0 || row == N - 1 || col == 0 || col == N - 1)
                continue;
            v_core_list.push_back({ row, col });
        }
    }
}

void initialize() {
    v_core_list.clear();
    for (int i = 0; i < 12; i++)
        v_connection_list[i].clear();
    connect_cnt_max = 0;
    dist_sum_min = 2147483647;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        initialize();
        input();
        solution();
        cout << "#" << tc << " " << dist_sum_min << "\n";
    }

    return 0;
}
