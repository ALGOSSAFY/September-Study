#include <iostream>

using namespace std;

char cube[3][3][3][6][2];

void run_command(string cmd) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cube[i][j][0][0][1] = cube[i][j][0][0][0];
			cube[i][j][2][1][1] = cube[i][j][2][1][0];
			cube[i][2][j][2][1] = cube[i][2][j][2][0];
			cube[i][0][j][3][1] = cube[i][0][j][3][0];
			cube[0][i][j][4][1] = cube[0][i][j][4][0];
			cube[2][i][j][5][1] = cube[2][i][j][5][0];
		}
	}

	char face = cmd[0];
	char dir = cmd[1];

	if (face == 'U' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2 - j][i][0][0][1] = cube[i][j][0][0][0];
			}
			cube[2-j][2][0][2][1] = cube[2][j][0][5][0];
			cube[2][j][0][5][1] = cube[j][0][0][3][0];
			cube[j][0][0][3][1] = cube[0][2-j][0][4][0];
			cube[0][2-j][0][4][1] = cube[2-j][2][0][2][0];
		}
	}
	else if (face == 'U' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[j][2 - i][0][0][1] = cube[i][j][0][0][0];
			}
			cube[j][0][0][3][1] = cube[2][j][0][5][0];
			cube[0][2 - j][0][4][1] = cube[j][0][0][3][0];
			cube[2 - j][2][0][2][1] = cube[0][2 - j][0][4][0];
			cube[2][j][0][5][1] = cube[2 - j][2][0][2][0];
		}
	}
	else if (face == 'D' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2 - j][i][2][1][1] = cube[i][j][2][1][0];
			}
			cube[2 - j][2][2][2][1] = cube[2][j][2][5][0];
			cube[2][j][2][5][1] = cube[j][0][2][3][0];
			cube[j][0][2][3][1] = cube[0][2 - j][2][4][0];
			cube[0][2 - j][2][4][1] = cube[2 - j][2][2][2][0];
		}
	}
	else if (face == 'D' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[j][2 - i][2][1][1] = cube[i][j][2][1][0];
			}
			cube[j][0][2][3][1] = cube[2][j][2][5][0];
			cube[0][2 - j][2][4][1] = cube[j][0][2][3][0];
			cube[2 - j][2][2][2][1] = cube[0][2 - j][2][4][0];
			cube[2][j][2][5][1] = cube[2 - j][2][2][2][0];
		}
	}
	else if (face == 'F' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2 - j][2][i][2][1] = cube[i][2][j][2][0];
			}
			cube[2 - j][2][2][1][1] = cube[2][2][j][5][0];
			cube[2][2][j][5][1] = cube[j][2][0][0][0];
			cube[j][2][0][0][1] = cube[0][2][2-j][4][0];
			cube[0][2][2-j][4][1] = cube[2 - j][2][2][1][0];
		}
	}
	else if (face == 'F' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[j][2][2-i][2][1] = cube[i][2][j][2][0];
			}
			cube[j][2][0][0][1] = cube[2][2][j][5][0];
			cube[0][2][2 - j][4][1] = cube[j][2][0][0][0];
			cube[2 - j][2][2][1][1] = cube[0][2][2 - j][4][0];
			cube[2][2][j][5][1] = cube[2 - j][2][2][1][0];
		}
	}
	else if (face == 'B' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2 - j][0][i][3][1] = cube[i][0][j][3][0];
			}
			cube[2 - j][0][2][1][1] = cube[2][0][j][5][0];
			cube[2][0][j][5][1] = cube[j][0][0][0][0];
			cube[j][0][0][0][1] = cube[0][0][2 - j][4][0];
			cube[0][0][2 - j][4][1] = cube[2 - j][0][2][1][0];
		}
	}
	else if (face == 'B' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[j][0][2 - i][3][1] = cube[i][0][j][3][0];
			}
			cube[j][0][0][0][1] = cube[2][0][j][5][0];
			cube[0][0][2 - j][4][1] = cube[j][0][0][0][0];
			cube[2 - j][0][2][1][1] = cube[0][0][2 - j][4][0];
			cube[2][0][j][5][1] = cube[2 - j][0][2][1][0];
		}
	}
	else if (face == 'L' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[0][2 - j][i][4][1] = cube[0][i][j][4][0];
			}
			cube[0][2- j][2][1][1] = cube[0][2][j][2][0];
			cube[0][2][j][2][1] = cube[0][j][0][0][0];
			cube[0][j][0][0][1] = cube[0][0][2 - j][3][0];
			cube[0][0][2 - j][3][1] = cube[0][2 - j][2][1][0];
		}
	}
	else if (face == 'L' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[0][j][2 - i][4][1] = cube[0][i][j][4][0];
			}
			cube[0][j][0][0][1] = cube[0][2][j][2][0];
			cube[0][0][2 - j][3][1] = cube[0][j][0][0][0];
			cube[0][2 - j][2][1][1] = cube[0][0][2 - j][3][0];
			cube[0][2][j][2][1] = cube[0][2 - j][2][1][0];
		}
	}
	else if (face == 'R' && dir == '-') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2][2 - j][i][5][1] = cube[2][i][j][5][0];
			}
			cube[2][2 - j][2][1][1] = cube[2][2][j][2][0];
			cube[2][2][j][2][1] = cube[2][j][0][0][0];
			cube[2][j][0][0][1] = cube[2][0][2 - j][3][0];
			cube[2][0][2 - j][3][1] = cube[2][2 - j][2][1][0];
		}
	}
	else if (face == 'R' && dir == '+') {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				cube[2][j][2 - i][5][1] = cube[2][i][j][5][0];
			}
			cube[2][j][0][0][1] = cube[2][2][j][2][0];
			cube[2][0][2 - j][3][1] = cube[2][j][0][0][0];
			cube[2][2 - j][2][1][1] = cube[2][0][2 - j][3][0];
			cube[2][2][j][2][1] = cube[2][2 - j][2][1][0];
		}
	}



	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cube[i][j][0][0][0] = cube[i][j][0][0][1];
			cube[i][j][2][1][0] = cube[i][j][2][1][1];
			cube[i][2][j][2][0] = cube[i][2][j][2][1];
			cube[i][0][j][3][0] = cube[i][0][j][3][1];
			cube[0][i][j][4][0] = cube[0][i][j][4][1];
			cube[2][i][j][5][0] = cube[2][i][j][5][1];
		}
	}
}

void initialize() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cube[i][j][0][0][0] = 'w';
			cube[i][j][2][1][0] = 'y';
			cube[i][2][j][2][0] = 'r';
			cube[i][0][j][3][0] = 'o';
			cube[0][i][j][4][0] = 'g';
			cube[2][i][j][5][0] = 'b';
		}
	}
}

void print_top() {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			cout << cube[i][j][0][0][0];
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		initialize();
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			string cmd;
			cin >> cmd;
			run_command(cmd);
		}
		print_top();
	}

	return 0;
}
