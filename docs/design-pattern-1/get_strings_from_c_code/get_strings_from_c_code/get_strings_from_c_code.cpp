#include <iostream>

int main()
{
	bool in_string = false;
	std::string code = "if (text == 'Hello') printf('Hi? \n'); .... ";
	std::string buffer = "";

    char* current = (char*) code.c_str();
	while (*current != 0x00) {
		if (*current == '\'') {
			if (in_string) {
				in_string = false;
				printf("string: %s \n", buffer.c_str());
			} else {
				in_string = true;
				buffer = "";
			}
		} else {
			if (in_string) buffer = buffer + *current;
		}

		current++;
	}
}
