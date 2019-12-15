#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	string code = "printf(..., 2 / 4); // 나누기 결과 출력";
	char ch_prev = 0;

	for (int i=0; i<code.size(); i++) {
		char ch = code.at(i);

		char ch_next = 0;
		if (i < (code.size() -1)) ch_next = code.at(i + 1);

		if ((ch == '/') && (ch_prev != '/') && (ch_next != '/')) {
			printf("%d: 나누기를 찾았습니다. \n", i);
		}

		ch_prev = ch;
	}
}