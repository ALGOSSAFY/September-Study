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

//���� �� �� �ֳ� ���� ����ϱ�!
bool haveNum(int y, int x) {
    
    //����, ���� �� ���� �ȵǴ� �� �ĳ���!
    for (int i = 0; i < 9; i++) {
        if (arr[y][i] == arr[y][x] && i != x) {
            return false;
        }
        if (arr[i][x] == arr[y][x] && i != y) {
            return false;
        }
    }

    //3x3 �迭�ȿ� �ȵǴ°� �ĳ���
    
    //���� ��� 3x3�迭�� �ҼӵǾ��ִ��� �˾ƺ���
    int s_y = y / 3;
    int s_x = x / 3;

    for (int i = 3 * s_y; i < 3 * (s_y + 1); i++) {
        for (int j = 3 * s_x; j < 3 * (s_x + 1); j++) {
            if (arr[i][j] == arr[y][x] && i != y && j != x) {
                return false;
            }
        }
    }

    //�ѹ��� ������ �������� ��Ƴ��Ҵ�!!
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

    //1~9���� �� �־�� �Ǻ��ϱ�
    for (int i = 1; i <= 9; i++) {
        arr[v[now].y][v[now].x] = i;
        //���ڸ� �־�� �̰� �´��� �˾ƺ��� �Լ��� ������
        if (haveNum(v[now].y,v[now].x)) {
            //���� ���ڰ� �־������� ���� ĭ����!
            dfs(now + 1);
        }
        //�� ���������!!
        if (perfect) {
            return;
        }
    }

    //�ᱹ ���� ���������� ������ ��� �ʱ�ȭ ��������!
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