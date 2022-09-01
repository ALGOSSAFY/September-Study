#include <iostream>

#include <vector>

#include <unordered_map>

#include <queue>

#include <algorithm>
using namespace std;
int n, m, k;
int grid[20][20] = { 0, }; //��Ʈ�� ���� �� �浹 üũ
int all_team[20][20] = { 0, }; //�� ���� ����
int teams[6][400] = { 0, }; //�� ���� ��ǥ �̵���
int routes[6][20][20] = { 0, }; //�� ���� ��Ʈ ���� -> ����
unordered_map<int, pair<int, int>> to_grid[6]; //�� ����ȣ�� ���� ��Ʈ ��ȣ�� ��ǥ�� ��ȯ
int route_length[6] = { 0, };//�� ���� ��Ʈ���� => ���� �����ϴµ� ���
int team_dir[6] = { 0, };//�� ���� ���� ����
int team_mems[6] = { 0, }; //�� ���� ��
int chk_team[20][20] = { 0, };



//���� ������ ���ؼ�
//��尡 �������� ������ - ���� 
//��尡 �������� ũ�� + ��ⷯ
//grid�� ���� k��°�� �°�
//�ο��� �� ī�����ϰ� ������� ������� 
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
				//������ �̵����̱� ��
				grid[i][j] = 1;
				if (tmp <= 3)
					all_team[i][j] = tmp;
				//��δ� ���ʿ䰡 ����
			}

		}


	}
	int team_ = 1;
	//1������ �ִ� 5��
	//1. ��Ʈ �ʱ�ȭ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j])
			{
				int num = 0;


				make_route(team_, i, j, num);
				//dfs�� �ؾߵ�
				//0���� ä��鼭 ���� ��Ʈ�� �� �� 3���� �迭�� �ʱ�ȭ
				//����� �õ�

				team_++;
			}
			//��Ʈ�ʱ�ȭ �Ϸ�

			//�̵� ���� �ʱ�ȭ
			if (all_team[i][j])
			{
				//������ ���� ���
				//�� �������
				//�� ��ȣ �ϴ� ���� ���
				int team_bunho = chk_team[i][j];
				//�ش� ����ȣ�� �� ����
				int tmp = routes[team_bunho][i][j];
				teams[team_bunho][tmp] = all_team[i][j];
				team_mems[team_bunho] += 1;
				//�� �迭�� �ֱ� �Ϸ� -> ��ⷯ �������� �Դٰ��� �ϱ�
			}
		}
	}
	//2. ������� �� �� �ֵ� ����ȭ grid�� �ֱ�
	for (int idx = 1; idx <= m; idx++)
	{
		for (int i = 0; i < route_length[idx]; i++)
		{
			if (teams[idx][i] == 1)
			{
				//�ϴ� ����
				//���⼭ ��������̶� �� �� ��� ��ȣȭ
				//���غ���

				int added_dir = modular(i, 1, route_length[idx]);
				int subbed_dir = modular(i, -1, route_length[idx]);
				//������
				if (teams[idx][added_dir] == 0)
				{
					//������ ������� 
					//���������� �� ����ŭ ī��Ʈ
					team_dir[idx] = 1;

					while (teams[idx][subbed_dir] != 1 && teams[idx][subbed_dir])
					{
						//������ �ƴҶ�����
						teams[idx][subbed_dir] = teams[idx][modular(subbed_dir, 1, route_length[idx])] + 1;
						subbed_dir = modular(subbed_dir, -1, route_length[idx]);
						//��Ʈ�� ���̲��� ���� ���
					}
				}
				else if (teams[idx][subbed_dir] == 0)
				{
					team_dir[idx] = -1;
					while (teams[idx][added_dir] != 1 && teams[idx][added_dir])
					{
						//������ �ƴҶ�����
						teams[idx][added_dir] = teams[idx][modular(added_dir, -1, route_length[idx])] + 1;
						added_dir = modular(added_dir, 1, route_length[idx]);
						//��Ʈ�� ���̲��� ���� ���
					}
				}


			}
		}

	}

	//�̵����� V ���� ��Ʈ V �ٶ�
	int score = 0;
	int round = 1;
	k = 20;
	while (k--)
	{
		int chk_grid[20][20] = { 0, };
		int team_grid[20][20] = { 0, };
		//üũ�� �׸���
		//�̵�
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
		//��� �� �̵� ����
		//���� �ٲٴ� �͵� �ߵǴ� �� ���� 
		//�̵� �ߵ�
		int de = 1;


		//�̵��� üũ �׸��忡 �ӽ÷� �ϱ� 

		//�������� 
		int catch_team = 0;
		if (round >= 1 && round <= n)
		{
			int chk_row = round - 1;
			for (int c = 0; c < n; c++)
			{
				if (chk_grid[chk_row][c])
				{
					//����� ����
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
					//����� ����
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
		//��ȹ���� ��� �Ӹ���� ������� �ٲ�
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



		//������⵵ �ٲ�
		round++;
		round %= 4 * n;
		if (round == 0)
			round++;
	}
	cout << score;
}