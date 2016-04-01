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

int add2Numbers(int a, int b) {
#ifdef _WIN32
	__asm {
		mov eax, a
		mov ebx, b
		add eax, ebx
	}
#else
	return a + b;
#endif
}

int main(int argc, const char **argv) {
	helloASM();

	int x = add2Numbers(4, 9);
	printf("x is: %d\n", x);

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}