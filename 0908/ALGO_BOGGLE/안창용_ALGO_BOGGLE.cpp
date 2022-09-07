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
	//테케 수 입력
	cin >> T;

	//테케 별 돌려야 하니 크게 for 문

	for (int TC = 1; TC <= T; TC++) {

		//2D array 입력 받기
		for (int R = 0; R < 5; R++) {
			cin >> line;
			for (int C = 0; C < 5; C++) {
				map[R][C] = line[C];
			}
		}


		// 단어 수
		cin >> word_N;


		//단어 별 search 후 결과 출력
		for (int w = 0; w < word_N; w++) {

			cin >> word;
			word_len = word.length();
			flag = 0;

			stack <pair<int, int>> first_stk;
			
			// visited 초기화, 최초 stack 내용물 만들기
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

			//범위밖 유무 확인
			if (nxt_y < 0 || nxt_x < 0 || nxt_y>4 || nxt_x>4)
				continue;


			// 이미 다음에 들어갈 stack 에 있는지 확인
			if (visited[nxt_y][nxt_x] == nxt_index)
				continue;

			//방문 기록 하기
			visited[nxt_y][nxt_x] = nxt_index;

			// 다음 단어랑 같은지 확인 후 스택에 추가
			if (word[nxt_index] == map[nxt_y][nxt_x])
				nxt_stk.push({ nxt_y, nxt_x });
		}
		//맨 첨에 불러오고 팝해버렸으니 손대지 말 것
	}

	// 이제 다음 단어 확인하기 위한 stack 만들기 완료

	//비어있으면 그냥 리턴 시켜버리기
	if (nxt_stk.empty())
		return;
	//안 비어잇는데 다음 단어가 끝이다? flag 1 변경해서 yes 출력하게 하고 return;
	else if (nxt_index + 1 == word_len) {
		flag = 1;  return;
	}

	searchword(nxt_index, nxt_stk);


}