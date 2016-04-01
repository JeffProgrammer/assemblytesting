#include <iostream>
#include <stdlib.h>

char helloWorld[] = "Hello World\n";

void helloASM() {
#ifdef _WIN32
	__asm
	{
		; Push hello world pointer into eax register
		mov eax, offset helloWorld
			push eax
			call printf; invoke prinf
			pop ebx
	}
#else
	printf("%s", helloWorld);
#endif
}

int main(int argc, const char **argv) {
	helloASM();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}