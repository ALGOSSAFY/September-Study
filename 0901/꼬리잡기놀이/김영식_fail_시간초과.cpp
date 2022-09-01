#include <iostream>
#include <vector>
#include <string.h>


using namespace std;
int tmpsy, tmpsx;
struct node {
	int sy;
	int sx;
	int ty;
	int tx;
	
};

struct tmpnode {
	int y;
	int x;
};
vector<tmpnode> tpv;
int visited[20][20];
int MAP[20][20];
int arr[20][20];
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };
int n, m, k;
int teamNum = 0;
vector<node> v;
void init_map(int y, int x) {

	if (MAP[y][x] == 0) {

		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		if (visited[ny][nx]) continue;
		if (MAP[ny][nx] == 0) continue;
		arr[ny][nx] = teamNum;
		visited[ny][nx] = 1;
		if (MAP[y][x] == 3) {
			v.push_back({ tmpsy,tmpsx,y,x });
			
		}
		init_map(ny, nx);

	}
}

void change_ht(int n) {
	//n´Â arrÀÇ ¹øÈ£¿Í ¿¬µ¿
	int tempy = v[n].sy;
	int tempx = v[n].sx;
	v[n].sy = v[n].ty;
	v[n].sx = v[n].tx;
	v[n].ty = tempy;
	v[n].tx = tempx;
	MAP[v[n].ty][v[n].tx] = 3;
	MAP[v[n].sy][v[n].sx] = 1;


}
void move() {

	for (int i = 1; i < v.size(); i++) {
		int y = v[i].sy;
		int x = v[i].sx;

		for (int j = 0; j < 4; j++) {
			int ny = y + dy[j];
			int nx = x + dx[j];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (MAP[ny][nx] == 0 || MAP[ny][nx]==2) continue;

			if (MAP[ny][nx] == 4) {
				MAP[ny][nx] = 1;// head
				MAP[y][x] = 2;

				v[i].sy = ny;
				v[i].sx = nx;
				break;
			}
			else if (MAP[ny][nx] == 3) {
				

				y = v[i].ty;
				x = v[i].tx;
				for (int k = 0; k < 4; k++) {
					ny = y + dy[k];
					nx = x + dx[k];
					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
					if (MAP[ny][nx] == 0 || MAP[ny][nx] == 4 || MAP[ny][nx]==1) continue;
					MAP[ny][nx] = 3;// head

					v[i].ty = ny;
					v[i].tx = nx;

					break;

				}
				MAP[v[i].sy][v[i].sx] = 2;
				MAP[y][x] = 1;
				v[i].sy = y;
				v[i].sx = x;

				
				goto abc;
				

			}
			//break;
		}
		y = v[i].ty;
		x = v[i].tx;
		for (int j = 0; j < 4; j++) {
			int ny = y + dy[j];
			int nx = x + dx[j];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (MAP[ny][nx] == 0 || MAP[ny][nx] == 4) continue;
			//arr[ny][nx]==2
			MAP[ny][nx] =3;// head
			MAP[y][x] = 4;
			
			v[i].ty = ny;
			v[i].tx = nx;
			//break;
		}

	abc:
		continue;

	}
	return;
}

int windScore(int,int,int);
int wind(int stage) {
	int y;
	int x;
	switch ((stage / n) % 4) {
	case 0: //¼­Ç³ ->
		 y= stage % n;

		for (int i = 0; i < n; i++) {
			if (MAP[y][i] == 1) {
				change_ht(arr[y][i]);
				return 1;
			}
			else if (MAP[y][i] == 2 || MAP[y][i] == 3) {
				
				return windScore(arr[y][i],y,i);
			}

		}
		//Å½Áö x 
		return 0;
		break;
	case 1: // ³²Ç³ 
		x = stage % n;

		for (int i = n-1; i >= 0; i--) {
			if (MAP[i][x] == 1) {
				change_ht(arr[i][x]);
				return 1;
			}
			else if (MAP[i][x] == 2 || MAP[i][x] == 3) {
				
				return windScore(arr[i][x],i,x);
			}

		}
		//Å½Áö x 
		return 0;


		break;
	case 2: //µ¿Ç³ <-
		y = stage % n;
		y = n - y-1;
		for (int i = n-1; i >=0; i--) {
			if (MAP[y][i] == 1) {
				change_ht(arr[y][i]);
				return 1;
			}
			else if (MAP[y][i] == 2 || MAP[y][i] == 3) {
				
				return windScore(arr[y][i],y,i);
			}

		}
		//Å½Áö x 
		return 0;


		break;
	case 3: // ºÏÇ³ 
		x = stage % n;
		x = n - x - 1;
		for (int i = 0; i < n; i++) {
			if (MAP[i][x] == 1) {
				change_ht(arr[i][x]);

				return 1;
			}
			else if (MAP[i][x] == 2 || MAP[i][x] == 3) {
				
				return windScore(arr[i][x],i,x);
			}

		}
		//Å½Áö x 
		return 0;




		break;


	}


	return 0;
}

int windScore(int team,int tty,int ttx) {// 

	memset(visited, 0, sizeof(int) * 20 * 20);
	int y=v[team].sy; 
	int x=v[team].sx;
	visited[y][x] = 1;
	int cnt = 1;
	//½ºÅÃ Å¥ 
	int flag = 0;
	while (y != tty || x != ttx) {
		int ny;
		int nx;
		for (int i = 0; i < 4; i++) {
			ny = y + dy[i];
			nx = x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visited[ny][nx] == 1) continue;
			if (MAP[ny][nx] == 0 || MAP[ny][nx] == 4) continue;
			if (MAP[ny][nx] == 2 || MAP[ny][nx] == 3) {
				if (flag == 0 && MAP[ny][nx] == 3) {
					flag = 1;
					continue;
				}
				flag = 1;
				y = ny;
				x = nx;
				visited[y][x] = 1;
				break;

			}
		}

		cnt++;
	}
	change_ht(team);
	return cnt;
}
int main() {
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				tpv.push_back({ i,j });
			}
		}
	}

	//int teamNum = 0;
	//int tmpsy, tmpsx;
	v.push_back({ 0,0,0,0 });//dummy
	
	for (auto i : tpv) {
		teamNum++;
		tmpsy = i.y;
		tmpsx = i.x;
		arr[i.y][i.x] = teamNum;
		visited[i.y][i.x] = 1;
		init_map(i.y, i.x);

	}

	int stage = 0;

	long long ans = 0;
	while (stage < k) {

		move();
		int ret = wind(stage);

		ans += (long long) ret * ret;
	
		stage++;
	}



	cout << ans;

	return 0;
}