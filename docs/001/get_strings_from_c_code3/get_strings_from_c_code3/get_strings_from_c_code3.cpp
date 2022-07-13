#include <iostream>

using namespace std;

class State;

class StringScannerInterface {
public:
	string buffer;

	State* state_white_space;
	State* state_slash;
	State* state_string;
	State* state_comment;
	State* state_escape;

	virtual void setState(State* value) = 0;
};

class State {
public:
	virtual void scan(char ch) = 0;
	void pre(State* prior) {}
	virtual void post(State* next) {}

	StringScannerInterface* scanner_ = nullptr;
};

class StateWhiteSpace : public State {
public:
	StateWhiteSpace(StringScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(char ch)
	{
		switch (ch) {
			case '/': scanner_->setState(scanner_->state_slash); break;
			case '"': scanner_->setState(scanner_->state_string); break;
		}
	}
};

class StateSlash : public State {
public:
	StateSlash(StringScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(char ch)
	{
		switch (ch) {
			case '/': scanner_->setState(scanner_->state_comment); break;
			default: scanner_->setState(scanner_->state_white_space); 
		}
	}
};

class StateComment : public State {
public:
	StateComment(StringScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(char ch)
	{
		if (ch == '\n') scanner_->setState(scanner_->state_white_space); 
	}
};

class StateEscape : public State {
public:
	StateEscape(StringScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(char ch)
	{
		scanner_->buffer = scanner_->buffer + ch;
		scanner_->setState(scanner_->state_string); 
	}
};

class StateString : public State {
public:
	StateString(StringScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(char ch)
	{
		switch (ch) {
			case '\\': scanner_->setState(scanner_->state_escape); break;
			case '"': scanner_->setState(scanner_->state_white_space); break;
			default: scanner_->buffer = scanner_->buffer + ch;
		}
	}

	virtual void pre(State* prior)
	{
		if (prior != scanner_->state_escape) scanner_->buffer = "";
	}

	virtual void post(State* next) 
	{ 
		printf("String: %s \n", scanner_->buffer.c_str());
	}
};

class StringScanner : StringScannerInterface {
public:
	StringScanner()
	{
		state_white_space = new StateWhiteSpace(this);
		state_slash = new StateSlash(this);
		state_string = new StateString(this);
		state_comment = new StateComment(this);
		state_escape = new StateEscape(this);
	}

	void scan(string code)
	{
		state_ = state_white_space;

		char* current = (char*) code.c_str();
		while (*current != 0x00) {
			state_->scan(*current);
			current++;
		}
	}

private:
	State* state_;

	virtual void setState(State* value)
	{
		// 상태가 변하기 전에 후처리
		state_->post(value);

		// 상태로 진입하기 전에 전처리
		value->pre(state_);

		state_ = value;
	}
};

int main()
{
	StringScanner scanner;
	scanner.scan(
		"// 주석 \"주석 안에 따옴표\" \n char text[1024] = \"문자열...\\\" <-- 문자열 안의 따옴표\"; ..."
	);
}
