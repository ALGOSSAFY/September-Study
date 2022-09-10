#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<string> v;
string s;
int flag = 0;
char ch[5] = {'A','E','I','O','U'};

void make_vector(int level) {
	if (flag == 1)
		return;
	if (level == 5)
		return;

	for (int i = 0; i < 5; i++) {
		s.push_back(ch[i]);
		v.push_back(s);
		make_vector(level + 1);
		s.pop_back();

	}

}

int solution(string word) {
    int answer = 0;
   
	//A**** 10000
	//AA*** 11000
	//AAA** 11100
	//AAAA* 11110
	//AAAAA 11111
	
	//AAAE* 11120 

	//에라 모르겟다 vector 0.5ms
	make_vector(0);
	sort(v.begin(), v.end());
	
    flag = 1;
    answer= find(v.begin(), v.end(), word)-v.begin();
    return answer+1;
}
