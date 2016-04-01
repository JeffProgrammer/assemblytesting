#include <iostream>
#include <stdlib.h>

char helloWorld[] = "Hello World\n";

int main(int argc, const char **argv) {

	__asm 
	{
		; Push hello world pointer into eax register
		mov eax, offset helloWorld
		push eax
		call printf; invoke prinf
		pop ebx
	}


#ifdef _WIN32
	system("PAUSE");
#endif
	return 0;
}