#include <iostream>
#include <string.h>
using namespace std;

//string::iterator itr = s.begin();
//cout << reverse(itr) << endl;

string reverse(string::iterator& it) { //iterator에는 변수의 주소값이  void *

	char head = *it;  //iterator 니까 string의 memory 주소값이 it 에 들어가있고 *it를 통해서 char 값에 접근
	
	++it;
	if (head == 'b' || head=='w') {
		return string(1, head);
	}
#if 0

	if (head == 'b' ) {
		return "b";
	}
	if (head == 'w') {
		return "w";
	}
#endif

	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);

	return "x" + lowerLeft + lowerRight + upperLeft + upperRight;

}

string s;

int main() {

	int c;
	cin>>c; 

	//c<50
	for (int i = 0; i < c; i++) {
		
		cin >> s;
		string::iterator itr = s.begin();
		cout << reverse(itr) << endl;

	}

	return 0;
}
