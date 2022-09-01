#include <iostream>

#include <vector>

#include <unordered_map>

#include <queue>

#include <algorithm>
using namespace std;
int n, m, k;
int grid[20][20] = { 0, }; //루트의 정보 및 충돌 체크
int all_team[20][20] = { 0, }; //각 팀의 정보
int teams[6][400] = { 0, }; //각 팀의 좌표 이동용
int routes[6][20][20] = { 0, }; //각 팀의 루트 정보 -> 순서
unordered_map<int, pair<int, int>> to_grid[6]; //각 팀번호의 진행 루트 번호를 좌표로 변환
int route_length[6] = { 0, };//각 팀의 루트길이 => 라운드 연산하는데 사용
int team_dir[6] = { 0, };//각 팀의 진행 방향
int team_mems[6] = { 0, }; //각 팀의 수
int chk_team[20][20] = { 0, };



//헤드와 꼬리를 비교해서
//헤드가 꼬리보다 작으면 - 모듈라 
//헤드가 꼬리보다 크면 + 모듈러
//grid에 놓기 k번째에 맞게
//인원수 다 카운팅하고 헤드사람과 꼬리사람 
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool calc_range(int x, int y)
{
	if (x >= 0 && x < n && y >= 0 && y < n)
		return true;
	return false;
}
int modular(int a, int add, int team_num)
{
	if (a + add < 0)
		return(a + add) + team_num;
	return (a + add) % team_num;
}
void make_route(int t, int x, int y, int num)
{
	grid[x][y] = 0;
	to_grid[t][num] = { x,y };
	routes[t][x][y] = num++;
	chk_team[x][y] = t;
	route_length[t] += 1;
	for (int d = 0; d < 4; d++)
	{
		int mov_x = x + dx[d];
		int mov_y = y + dy[d];
		if (calc_range(mov_x, mov_y) && grid[mov_x][mov_y])
		{
			make_route(t, mov_x, mov_y, num);

		}


	}



}
int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int tmp;
			cin >> tmp;
			if (tmp >= 1)
			{
				//무조건 이동선이긴 함
				grid[i][j] = 1;
				if (tmp <= 3)
					all_team[i][j] = tmp;
				//경로는 볼필요가 없음
			}

		}


	}
	int team_ = 1;
	//1팀부터 최대 5팀
	//1. 루트 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j])
			{
				int num = 0;


				make_route(team_, i, j, num);
				//dfs로 해야됨
				//0으로 채우면서 팀의 루트를 각 팀 3차원 배열에 초기화
				//디버깅 시도

				team_++;
			}
			//루트초기화 완료

			//이동 방향 초기화
			if (all_team[i][j])
			{
				//팀원이 있을 경우
				//팀 진행방향
				//팀 번호 일단 먼저 얻기
				int team_bunho = chk_team[i][j];
				//해당 팀번호로 팀 정보
				int tmp = routes[team_bunho][i][j];
				teams[team_bunho][tmp] = all_team[i][j];
				team_mems[team_bunho] += 1;
				//팀 배열에 넣기 완료 -> 모듈러 연산으로 왔다갔다 하기
			}
		}
	}
	//2. 진행방향 각 팀 애들 숫자화 grid에 넣기
	for (int idx = 1; idx <= m; idx++)
	{
		for (int i = 0; i < route_length[idx]; i++)
		{
			if (teams[idx][i] == 1)
			{
				//일단 리더
				//여기서 진행방향이랑 각 팀 멤버 번호화
				//더해보기

				int added_dir = modular(i, 1, route_length[idx]);
				int subbed_dir = modular(i, -1, route_length[idx]);
				//빼보기
				if (teams[idx][added_dir] == 0)
				{
					//이쪽이 진행방향 
					//역방향으로 팀 수만큼 카운트
					team_dir[idx] = 1;

					while (teams[idx][subbed_dir] != 1 && teams[idx][subbed_dir])
					{
						//리더가 아닐때까지
						teams[idx][subbed_dir] = teams[idx][modular(subbed_dir, 1, route_length[idx])] + 1;
						subbed_dir = modular(subbed_dir, -1, route_length[idx]);
						//루트에 팀이꽉차 있을 경우
					}
				}
				else if (teams[idx][subbed_dir] == 0)
				{
					team_dir[idx] = -1;
					while (teams[idx][added_dir] != 1 && teams[idx][added_dir])
					{
						//리더가 아닐때까지
						teams[idx][added_dir] = teams[idx][modular(added_dir, -1, route_length[idx])] + 1;
						added_dir = modular(added_dir, 1, route_length[idx]);
						//루트에 팀이꽉차 있을 경우
					}
				}


			}
		}

	}

	//이동방향 V 각팀 루트 V 바람
	int score = 0;
	int round = 1;
	k = 20;
	while (k--)
	{
		int chk_grid[20][20] = { 0, };
		int team_grid[20][20] = { 0, };
		//체크용 그리드
		//이동
		for (int idx = 1; idx <= m; idx++)
		{
			int tmp[400] = { 0, };
			int dir = team_dir[idx];
			for (int i = 0; i < route_length[idx]; i++)
			{
				int next = modular(i, dir, route_length[idx]);
				tmp[next] = teams[idx][i];
			}
			for (int i = 0; i < route_length[idx]; i++)
			{
				teams[idx][i] = tmp[i];
				if (teams[idx][i])
				{
					int x, y;
					tie(x, y) = to_grid[idx][i];
					chk_grid[x][y] = teams[idx][i];
					team_grid[x][y] = idx;

				}
			}



		}
		//모든 팀 이동 했음
		//방향 바꾸는 것도 잘되는 거 같음 
		//이동 잘됨
		int de = 1;


		//이동후 체크 그리드에 임시로 하기 

		//공던지기 
		int catch_team = 0;
		if (round >= 1 && round <= n)
		{
			int chk_row = round - 1;
			for (int c = 0; c < n; c++)
			{
				if (chk_grid[chk_row][c])
				{
					//사람이 잡음
					score += chk_grid[chk_row][c] * chk_grid[chk_row][c];
					catch_team = team_grid[chk_row][c];
					break;
				}
			}
		}
		else if (round >= n + 1 && round <= 2 * n)
		{
			int chk_c = round - n - 1;
			for (int r = n - 1; r >= 0; r--)
			{
				if (chk_grid[r][chk_c])
				{
					score += chk_grid[r][chk_c] * chk_grid[r][chk_c];
					catch_team = team_grid[r][chk_c];

					break;
					//사람이 잡음
				}
			}

		}
		else if (round >= 2 * n + 1 && round <= 3 * n)
		{
			int chk_r = round - 3 * n;
			chk_r = abs(chk_r);
			for (int c = n - 1; c >= 0; c--)
			{
				if (chk_grid[chk_r][c])
				{
					score += chk_grid[chk_r][c] * chk_grid[chk_r][c];
					catch_team = team_grid[chk_r][c];
					break;
				}

			}


		}
		else
		{
			int chk_c = round - 4 * n;
			chk_c = abs(chk_c);
			for (int r = 0; r < n; r++)
			{
				if (chk_grid[r][chk_c])
				{
					score += chk_grid[r][chk_c] * chk_grid[r][chk_c];
					catch_team = team_grid[r][chk_c];
					break;
				}
			}
		}
		//공획득한 경우 머리사람 꼬리사람 바뀜
		if (catch_team)
		{
			team_dir[catch_team] = -team_dir[catch_team];
			//int num = 1;
			for (int i = 0; i < route_length[catch_team]; i++)
			{
				if (teams[catch_team][i])
				{
					teams[catch_team][i] -= team_mems[catch_team];
					teams[catch_team][i] = abs(teams[catch_team][i]);
					teams[catch_team][i] ++;

				}


			}





		}



		//진행방향도 바뀜
		round++;
		round %= 4 * n;
		if (round == 0)
			round++;
	}
	cout << score;
}