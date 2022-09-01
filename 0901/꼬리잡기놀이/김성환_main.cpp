#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int y;
	int x;
};

struct Player {
	int team_no;
	int type;
};

struct Move {
	Node from;
	Node to;
};

int n, m, k;
Player board[20][20];
int route[20][20];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
vector<Node> v_team_head;
vector<Node> v_team_tail;
Node shoot_pos;
int shoot_mode;
int score;

void change_direction(Node pos) {
	// 내가 속한 팀 번호
	int team_no = board[pos.y][pos.x].team_no;

	// 기존의 head와 tail 정보 가져오기
	Node head = v_team_head[team_no];
	Node tail = v_team_tail[team_no];

	// 서로 바꾸기
	v_team_head[team_no] = tail;
	v_team_tail[team_no] = head;

	// board 상에 표시 갱신하기
	board[head.y][head.x].type = 3;
	board[tail.y][tail.x].type = 1;
}

void get_score(Node pos) {
	int team_no = board[pos.y][pos.x].team_no;
	Node head = v_team_head[team_no];

	// 내가 속한 팀의 머리에서 부터 counting 시작
	queue<Node> q_find_pos;
	q_find_pos.push(head);

	int visited[20][20] = {};

	int dist = 1;
	while (!q_find_pos.empty()) {
		Node now = q_find_pos.front();
		q_find_pos.pop();

		// 방문 기록
		visited[now.y][now.x] = 1;

		// 내 위치가 공을 받은 위치면 점수 더하고 중단
		if (now.y == pos.y && now.x == pos.x) {
			score += dist * dist;
			return;
		}

		// 한 번 더 옮겨가야함
		dist++;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (!(0 <= ny && ny < n && 0 <= nx && nx < n))
				continue;
			if (board[ny][nx].type == 0 || board[ny][nx].type == 4 || board[ny][nx].type == 3)
				continue;
			if (visited[ny][nx] != 0)
				continue;
			q_find_pos.push({ ny, nx });
			break;
		}
	}
	score += dist * dist;
	return;
}

void shoot_ball() {
	if (shoot_pos.x == 0 && shoot_mode == 0) {
		// 왼쪽에서 오른쪽으로 슈팅
		while (shoot_pos.x < n) {
			int now_type = board[shoot_pos.y][shoot_pos.x].type;
			if (now_type == 0 || now_type == 4) {
				shoot_pos.x++;
				continue;
			}
			get_score({ shoot_pos.y, shoot_pos.x });
			change_direction({ shoot_pos.y, shoot_pos.x });
			break;
		}
		// 다음 라운드에서 쏠 위치
		shoot_pos = { shoot_pos.y + 1, 0 };
		if (shoot_pos.y == n) {
			shoot_pos.y = n - 1;
			shoot_mode = 1;
		}
	}
	else if (shoot_pos.y == n - 1 && shoot_mode == 1) {
		// 아래서 위로 슈팅
		while (shoot_pos.y >= 0) {
			int now_type = board[shoot_pos.y][shoot_pos.x].type;
			if (now_type == 0 || now_type == 4) {
				shoot_pos.y--;
				continue;
			}
			get_score({ shoot_pos.y, shoot_pos.x });
			change_direction({ shoot_pos.y, shoot_pos.x });
			break;
		}
		// 다음 라운드에서 쏠 위치
		shoot_pos = { n - 1, shoot_pos.x + 1 };
		if (shoot_pos.x == n) {
			shoot_pos.x = n - 1;
			shoot_mode = 2;
		}
	}
	else if (shoot_pos.x == n - 1 && shoot_mode == 2) {
		// 오른쪽에서 왼쪽으로 슈팅
		while (shoot_pos.x >= 0) {
			int now_type = board[shoot_pos.y][shoot_pos.x].type;
			if (now_type == 0 || now_type == 4) {
				shoot_pos.x--;
				continue;
			}
			get_score({ shoot_pos.y, shoot_pos.x });
			change_direction({ shoot_pos.y, shoot_pos.x });
			break;
		}
		// 다음 라운드에서 쏠 위치
		shoot_pos = { shoot_pos.y - 1, n - 1 };
		if (shoot_pos.y == -1) {
			shoot_pos.y = 0;
			shoot_mode = 3;
		}
	}
	else if (shoot_pos.y == 0 && shoot_mode == 3) {
		// 위에서 아래로 슈팅
		while (shoot_pos.y < n) {
			int now_type = board[shoot_pos.y][shoot_pos.x].type;
			if (now_type == 0 || now_type == 4) {
				shoot_pos.y++;
				continue;
			}
			get_score({ shoot_pos.y, shoot_pos.x });
			change_direction({ shoot_pos.y, shoot_pos.x });
			break;
		}
		// 다음 라운드에서 쏠 위치
		shoot_pos = { 0, shoot_pos.x - 1 };
		if (shoot_pos.x == -1) {
			shoot_pos.x = 0;
			shoot_mode = 0;
		}
	}
}

void move_team() {
	// 모든 팀 한 칸 씩 이동하기
	for (int team_no = 1; team_no <= m; team_no++) {
		// 현재 이동할 팀에서 움직일 대상을 저장하는 queue
		// {현재 위치, 옮겨갈 위치}
		queue<Move> q_team_move;
		Move head_move;

		// head의 이동정보는 따로 저장해두기
		Node now_head = v_team_head[team_no];
		// head가 다음에 이동할 수 있는 위치 찾기
		for (int i = 0; i < 4; i++) {
			int ny = now_head.y + dy[i];
			int nx = now_head.x + dx[i];
			if (!(0 <= ny && ny < n && 0 <= nx && nx < n))
				continue;
			if (board[ny][nx].type == 0)
				continue;
			// head가 이동할 수 있는 위치라면 저장해두기
			if (board[ny][nx].type == 4 || board[ny][nx].type == 3) {
				head_move = { now_head, {ny, nx} };
				continue;
			}
			// head 다음 사람이 이 자리로 올 수 있다
			if (board[ny][nx].type == 2) {
				q_team_move.push({ { ny,nx }, now_head });
				continue;
			}
		}
		// head가 있던 위치 비워두기
		board[head_move.from.y][head_move.from.x] = { team_no, 4 };

		// from -> to 로 모두 옮길 것이다.
		while (!q_team_move.empty()) {
			Move now = q_team_move.front();
			q_team_move.pop();

			// 내가 다음 위치로 옮겨가게 될 때,
			// 내 자리에 올 대상을 찾기
			for (int i = 0; i < 4; i++) {
				int ny = now.from.y + dy[i];
				int nx = now.from.x + dx[i];
				if (!(0 <= ny && ny < n && 0 <= nx && nx < n))
					continue;
				if (board[ny][nx].type == 0)
					continue;
				// 이동 선 상의 갈 수 있는 위치 (빈칸 == 4) 아니라면
				// 누군가 차지하고 있는 위치
				// 나는 다른 곳으로 옮겨갈테니, 당신은 이 자리로 오라
				if (board[ny][nx].type == 2 || board[ny][nx].type == 3) {
					q_team_move.push({ { ny, nx }, { now.from.y, now.from.x } });
					break;
				}
			}
			// 나의 정보 (팀 번호, 유형)
			int now_team_no = board[now.from.y][now.from.x].team_no;
			int now_type = board[now.from.y][now.from.x].type;
			// 나는 다음 칸으로 이동
			board[now.to.y][now.to.x] = { now_team_no, now_type };
			// 내 자리였던 곳은 비워두기
			board[now.from.y][now.from.x] = { now_team_no, 4 };
			// 내가 tail 이라면 tail의 새로운 위치 정보 갱신
			if (now_type == 3) {
				v_team_tail[now_team_no] = { now.to.y, now.to.x };
				break;
			}

		}
		board[head_move.to.y][head_move.to.x] = { team_no, 1 };
		v_team_head[team_no] = { head_move.to.y, head_move.to.x };


	}
}


void fill_route(Node start, int team_cnt) {
	queue<Node> q;
	q.push(start);

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		if (board[now.y][now.x].type == 1)
			v_team_head.push_back({ now.y, now.x });

		if (board[now.y][now.x].type == 3)
			v_team_tail.push_back({ now.y, now.x });

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			// 범위 벗어나면 continue;
			if (!(0 <= ny && ny < n && 0 <= nx && nx < n))
				continue;
			// 이동 선이 아닌 빈칸이라면 continue;
			if (board[ny][nx].type == 0)
				continue;
			// 이미 방문한 이동 선 상의 위치라면 continue;
			//if (route[ny][nx] != 0)
			if (board[ny][nx].team_no != 0)
				continue;
			// 처음 방문한 이동 선 상 위치
			//route[ny][nx] = team_cnt;
			board[ny][nx].team_no = team_cnt;
			q.push({ ny, nx });
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 각 팀의 head와 tail 나타내기 위한 벡터, 0번 index에 무의미한 값 넣기
	v_team_head.push_back({ -1, -1 });
	v_team_tail.push_back({ -1, -1 });

	// board에 각 칸의 type 입력 받기
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int type;
			cin >> type;
			board[i][j].type = type;
		}
	}

	// 각 팀의 번호 부여하기 위해 각각의 loop를 모두 방문하기
	int team_cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 빈칸이면 continue;
			if (board[i][j].type == 0)
				continue;
			// 이미 경로 번호 (팀 번호)가 부여된 위치라면 continue;
			//if (route[i][j] != 0)
			if (board[i][j].team_no != 0)
				continue;
			team_cnt++;
			//route[i][j] = team_cnt;
			board[i][j].team_no = team_cnt;
			fill_route({ i,j }, team_cnt);
		}
	}

	// 라운드 진행하기
	for (int i = 0; i < k; i++) {

		//cout << "=======round " << i + 1 << "=======\n";
		// 한 칸 씩 이동하기
		move_team();
		//cout << "=========move===========\n";
		//for (int row = 0; row < n; row++) {
		//	for (int col = 0; col < n; col++) {
		//		cout << board[row][col].type << " ";
		//	}
		//	cout << "\n";
		//}


		// 공 쏘기
		shoot_ball();
		//cout << "=========shoot=========\n";
		//for (int row = 0; row < n; row++) {
		//	for (int col = 0; col < n; col++) {
		//		cout << board[row][col].type << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "current score: " << score << "\n";
	}

	cout << score;

	return 0;
}


/*
1. 팀마다 이동 선 따라 이동하기
2. 공 맞추기
	2.1. 점수 관리
	2.2. 방향 바꾸기
*/
