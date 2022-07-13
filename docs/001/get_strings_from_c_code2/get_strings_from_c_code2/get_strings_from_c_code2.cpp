#include <iostream>

enum State {stWhiteSpace, stSplash, stComment, stString, stStringEnd, stEscape};

State state = stWhiteSpace;
std::string buffer = "";

void do_WhiteSpace(char ch)
{
	switch (ch) {
		case '/': state = stSplash; break;
		case '"': state = stString; break;
	}
}

void do_Splash(char ch)
{
	switch (ch) {
		case '/': state = stComment; break;
		default: state = stWhiteSpace;
	}
}

void do_Comment(char ch)
{
	if (ch == '\n') state = stWhiteSpace;
}

void do_String(char ch)
{
	switch (ch) {
		case '\\': state = stEscape; break;
		case '"': state = stStringEnd; break;
		default: buffer = buffer + ch;
	}
}

void do_StringEnd(char ch)
{
	printf("String: %s \n", buffer.c_str());
	buffer = "";
	state = stWhiteSpace;
}

void do_Escape(char ch)
{
	buffer = buffer + ch;
	state = stString;
}

int main()
{
	std::string code = 
		"// 주석 \"주석 안에 따옴표\" \n char text[1024] = \"문자열...\\\" <-- 문자열 안의 따옴표\"; ...";

	char* current = (char*) code.c_str();
	while (*current != 0x00) {
		switch (state) {
			case stWhiteSpace: do_WhiteSpace(*current); break;
			case stSplash: do_Splash(*current); break;
			case stComment: do_Comment(*current); break;
			case stString: do_String(*current); break;
			case stStringEnd: do_StringEnd(*current); break;
			case stEscape: do_Escape(*current); break;
		}

		current++;
	}
}