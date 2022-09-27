#include <iostream>
#include <string>
#include <vector>
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
{1,0},
{1,-1}
},{
{0,0},
{0,1},
{1,1}
},{
{0,0},
{1,0},
{1,1}
} };

bool calc_range(int x, int y)
{
    if (x >= 0 && x < H && y >= 0 && y < W)
        return true;
    return false;
}
pair<int, int> covered()
{
    pair<int, int> result = { -1,-1 };
    for (int r = 0; r < H; r++)
    {
        for (int c = 0; c < W; c++)
        {
            if (arr[r][c] == 0)
                return { r,c };
        }
    }
    return result;
}



int cover(int x, int y)
{
    if (x >= H || y >= W)
        return 0;
    int result = 0;
    //해당 판에서 빈칸을 바로 찾음
    //안채우는것은?
    pair<int, int> chk = covered();
    if (chk.first == -1 && chk.second == -1)
        return 1;
    int cov_x = chk.first;
    int cov_y = chk.second;
    //다 비어있는지 체크
    vector<int> possible;
    //result += cover(cov_x, cov_y + 1);
    //안 채우고 가보기

    for (int d = 0; d < 4; d++)
    {
        bool can = true;
        for (int co = 0; co < 3; co++)
        {
            int c_x = cov_x + dirs[d][co][0];
            int c_y = cov_y + dirs[d][co][1];
            if (!calc_range(c_x, c_y))
                can = false;
            else if (calc_range(c_x, c_y) && arr[c_x][c_y] == 1)
                can = false;




        }
        if (can)
        {
            possible.push_back(d);
        }




    }
    int prev[20][20] = { 0, };
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            prev[r][c] = arr[r][c];
    for (int i = 0; i < possible.size(); i++)
    {
        int d = possible[i];
        for (int co = 0; co < 3; co++)
        {
            int c_x = cov_x + dirs[d][co][0];
            int c_y = cov_y + dirs[d][co][1];
            arr[c_x][c_y] = 1;

        }
        result += cover(cov_x, cov_y);
        for (int co = 0; co < 3; co++)
        {
            int c_x = cov_x + dirs[d][co][0];
            int c_y = cov_y + dirs[d][co][1];
            arr[c_x][c_y] = 0;

        }



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
        int result = 0;
        result = cover(0,0);
        //모든 빈칸에서 다 시작?
        //하나의 빈칸에서만 시작하면되나
        cout << result << '\n';



    }







}
