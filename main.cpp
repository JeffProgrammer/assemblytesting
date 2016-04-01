#include <iostream>
#include <stdlib.h>

char helloWorld[] = "Hello World\n";

int main(int argc, const char **argv) {
#ifdef _WIN32
	__asm 
	{
		; Push hello world pointer into eax register
		mov eax, offset helloWorld
		push eax
		call printf; invoke prinf
		pop ebx
	}
	system("PAUSE");
#else
	printf("%s", helloWorld);
#endif
	return 0;
}