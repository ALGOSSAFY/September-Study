#include <iostream>
#include <string>
using namespace std;
/*
  BOARDCOVER
  H * W 크기
  모든 흰칸은 3칸짜리 L자 모양의 블록으로 덮으려 함



*/
int c;
int H, W;
int arr[20][20] = { 0, };
int dirs[4][3][2] = { {
{0,0},
{1,0},
{0,1}
},{
{0,0},
{-1,0},
{0,-1}
},{
{0,0},
{-1,0},
{0,1}
},{
{0,0},
{1,0},
{0,-1}
} };

bool calc_range(int x, int y)
{
	if (x <= 0 && x < H && y >= 0 && y < W)
		return true;
	return false;
}
bool covered()
{
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			if (arr[r][c] == 0)
				return false;
		}
	}
	return true;
}
void find_next_blank(int &x, int &y)
{
	int sy = y;
	bool found_flag = true;
	for (int i = x; i < H && found_flag; i++)
	{
		if (x < i) sy = 0;
		for (int j = sy; j < W&&found_flag; j++)
		{
			if (arr[i][j] == 0)
			{
				x = i;
				y = j;
				return;


			}


		}
	}






}



int cover(int x, int y)
{
	//언제든지 다 채우면 1리턴
	if (covered())
		return 1;

	//x y부터 cover하기?
	//조합?a
	int result = 0;

	//모든 방향으로 채워보기 + 안 채우기
	// 다음 채울 좌표 전달

	//1. 안 채우기
	//다음 빈칸 찾아야함


	int prev_arr[20][20] = { 0, };
	for (int r = 0; r < H; r++)
		for (int c = 0; c < W; c++)
			prev_arr[r][c] = arr[r][c];
	for (int d = 0; d < 4; d++)
	{

		bool can_cover = true;
		for (int co = 0; co < 3 && can_cover; co++)
		{
			int c_x = x + dirs[d][co][0];
			int c_y = y + dirs[d][co][1];
			if (!calc_range(c_x, c_y) || arr[c_x][c_y])
				can_cover = false;
			else
				arr[c_x][c_y] = 1;


		}
		if (can_cover)
		{
			int n_x = x;
			int n_y = y;
			find_next_blank(n_x, n_y);
			result += cover(n_x, n_y);




		}

		for (int r = 0; r < H; r++)
			for (int c = 0; c < W; c++)
				arr[r][c] = prev_arr[r][c];





	}









	return result;



}
int main() {
	cin >> c;
	for (int i = 0; i < c; i++)
	{
		for (int r = 0; r < 20; r++)
			for (int c = 0; c < 20; c++)
				arr[r][c] = 0;
		cin >> H >> W;
		for (int r = 0; r < H; r++)
		{
			string board;
			cin >> board;
			for (int c = 0; c < W; c++)
			{
				if (board[c] == '#')
				{
					arr[r][c] = 1;
				}
				else
				{
					arr[r][c] = 0;
				}



			}


		}
		//dfs로 구현하기
		bool found_flag = true;
		int result = 0;
		for (int r = 0; r < H && found_flag; r++)
		{
			for (int c = 0; c < W && found_flag; c++)
			{
				if (arr[r][c] == 0)
				{
					//found_flag = false;
					result += cover(r, c);

				}

			}

		}
		cout << result << '\n';



	}







}