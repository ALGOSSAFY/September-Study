#include <iostream>
#include <stack>
#include <string>

using namespace std;



char map[5][5];

int visited[5][5]; 
int T;
string line;

int word_N;
string word;
int word_len;
int flag;
string answer[2] = { " NO\n", " YES\n" };

int movY[8]= {-1,-1,-1, 0 , 0, 1, 1, 1};
int movX[8]= {-1, 1, 0, -1, 1, -1,0, 1};

stack <pair<int, int>> stk;


void searchword(int index, stack <pair<int, int>> cur_stk);

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//���� �� �Է�
	cin >> T;

	//���� �� ������ �ϴ� ũ�� for ��

	for (int TC = 1; TC <= T; TC++) {

		//2D array �Է� �ޱ�
		for (int R = 0; R < 5; R++) {
			cin >> line;
			for (int C = 0; C < 5; C++) {
				map[R][C] = line[C];
			}
		}


		// �ܾ� ��
		cin >> word_N;


		//�ܾ� �� search �� ��� ���
		for (int w = 0; w < word_N; w++) {

			cin >> word;
			word_len = word.length();
			flag = 0;

			stack <pair<int, int>> first_stk;
			
			// visited �ʱ�ȭ, ���� stack ���빰 �����
			for (int R = 0; R < 5; R++) {
				for (int C = 0; C < 5; C++) {
					visited[R][C] = -1;
					if (map[R][C] == word[0]) {
						first_stk.push({ R,C });
					}	
				}
			}

			searchword(0, first_stk);

			cout << word << answer[flag] ;
		}
	}
	return 0;
}





void searchword(int index, stack <pair<int, int>> cur_stk) {

	stack <pair<int, int>> nxt_stk;
	int nxt_index = index + 1;

	while (!cur_stk.empty()) {
		int cur_y = cur_stk.top().first;
		int cur_x = cur_stk.top().second;
		cur_stk.pop();



		for (int i = 0; i < 8; i++) {

			int nxt_y = cur_y + movY[i];
			int nxt_x = cur_x + movX[i];

			//������ ���� Ȯ��
			if (nxt_y < 0 || nxt_x < 0 || nxt_y>4 || nxt_x>4)
				continue;


			// �̹� ������ �� stack �� �ִ��� Ȯ��
			if (visited[nxt_y][nxt_x] == nxt_index)
				continue;

			//�湮 ��� �ϱ�
			visited[nxt_y][nxt_x] = nxt_index;

			// ���� �ܾ�� ������ Ȯ�� �� ���ÿ� �߰�
			if (word[nxt_index] == map[nxt_y][nxt_x])
				nxt_stk.push({ nxt_y, nxt_x });
		}
		//�� ÷�� �ҷ����� ���ع������� �մ��� �� ��
	}

	// ���� ���� �ܾ� Ȯ���ϱ� ���� stack ����� �Ϸ�

	//��������� �׳� ���� ���ѹ�����
	if (nxt_stk.empty())
		return;
	//�� ����մµ� ���� �ܾ ���̴�? flag 1 �����ؼ� yes ����ϰ� �ϰ� return;
	else if (nxt_index + 1 == word_len) {
		flag = 1;  return;
	}

	searchword(nxt_index, nxt_stk);


}