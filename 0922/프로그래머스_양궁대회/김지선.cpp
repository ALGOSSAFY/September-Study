#include <string>
#include <vector>

using namespace std;

int score = 0;
int temp_score;
vector<int> ryan(11, 0);
vector<int> answer(11, 0);

void calculate(vector<int> apeach, vector<int> ryan) {
    int temp_score_a = 0;
    int temp_score_r = 0;
    for (int i = 0; i <= 10; i++) {
        if (apeach[i] >= ryan[i]) {
            if (apeach[i] == 0 && ryan[i] == 0) {
                continue;
            }
            else {
                temp_score_a += 10 - i;
            }
        }
        else {
            temp_score_r += 10 - i;
        }
    }
    if (temp_score_a >= temp_score_r) {
        temp_score = -1;
    }
    else {
        temp_score = temp_score_r - temp_score_a;
    }
    if (temp_score > score) {
        score = temp_score;
        for (int i = 0; i <= 10; i++) {
            answer[i] = ryan[i];
        }
    }
    else if (temp_score == score) {
        for (int i = 10; i >= 0; i--) {
            if (ryan[i] > 0 || answer[i] > 0) {
                if (ryan[i] > answer[i]) {
                    for (int j = 0; j <= 10; j++) {
                        answer[j] = ryan[j];
                    }
                    break;
                }
                else if (ryan[i] < answer[i]) {
                    break;
                }
            }
        }
    }
}

void makevector(int level, int temp_n, vector<int> apeach, vector<int> ryan) {
    if (level == 11 || temp_n == 0) {
        ryan[10] += temp_n;
        calculate(apeach, ryan);
        ryan[10] -= temp_n;
        return;
    }

    if (apeach[level] >= temp_n) {
        makevector(level + 1, temp_n, apeach, ryan);
        return;
    }

    ryan[level] += apeach[level] + 1;
    makevector(level + 1, temp_n - (apeach[level] + 1), apeach, ryan);
    ryan[level] -= apeach[level] + 1;
    makevector(level + 1, temp_n, apeach, ryan);
}

vector<int> solution(int n, vector<int> info) {
    makevector(0, n, info, ryan);
    if (score == 0) {
        return { -1 };
    }
    return answer;
}
