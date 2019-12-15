#include <stdio.h>
#include <string>

using namespace std;

class State;

class ScannerInterface {
public:
	virtual void setState(State* state) {}

	State* state_none_;
	State* state_slash_;
	State* state_comment_;
};

class State {
public:
	virtual void scan(int index, char ch) = 0;

	virtual void pre(State* prior) {}
	virtual void post(State* next) {}

	ScannerInterface* scanner_;
};

class StateNone : State {
public:
	StateNone(ScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(int index, char ch) 
	{
		if (ch == '/') scanner_->setState(scanner_->state_slash_);
	}
};

class StateSlash : State {
public:
	StateSlash(ScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(int index, char ch) 
	{
		if (ch == '/') scanner_->setState(scanner_->state_comment_);
		else {
			printf("%d: 나누기를 찾았습니다. \n", index-1);
			scanner_->setState(scanner_->state_none_);
		}
	}
};

class StateComment : State {
public:
	StateComment(ScannerInterface* scanner)
	{
		scanner_ = scanner;
	}

	virtual void scan(int index, char ch) 
	{
		scanner_->setState(scanner_->state_none_);
	}
};

class Scanner : ScannerInterface {
public:
	Scanner()
	{
		state_none_ = (State*) new StateNone(this);
		state_slash_ = (State*) new StateSlash(this);
		state_comment_ = (State*) new StateComment(this);
	}

	void scan(string code)
	{
		current_state_ = state_none_;
		for (int i=0; i<code.size(); i++) {
			current_state_->scan(i, code.at(i));
		}
	}

	virtual void setState(State* state) 
	{
		current_state_->post(state);
		state->pre(current_state_);
		current_state_ = state;
	}

private:
	State* current_state_;
};

int main()
{
	Scanner scanner;
	scanner.scan("printf(..., 2 / 4); // 나누기 결과 출력");
}