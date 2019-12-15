#include <stdio.h>
#include <string>

using namespace std;

enum State {stNone, stSplash, stComment};
State state;

void do_none(int i, char ch)
{
	if (ch == '/') state = stSplash;
}

void do_slash(int i, char ch)
{
	if (ch == '/') state = stComment;
	else {
		printf("%d: �����⸦ ã�ҽ��ϴ�. \n", i-1);
		state = stNone;
	}
}

void do_comment(int i, char ch)
{
	state = stNone;
}

int main()
{
	string code = "printf(..., 2 / 4); // ������ ��� ���";

	state = stNone;
	for (int i=0; i<code.size(); i++) {
		switch (state) {
			case stNone: do_none(i, code.at(i)); break;
			case stSplash: do_slash(i, code.at(i)); break;
			case stComment: do_comment(i, code.at(i)); break;
		}
	}
}