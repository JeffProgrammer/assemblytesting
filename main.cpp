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

/**
 int total = 0;
 for (int i = 0; i < n; i++)
	total += i;
 return total;
 */
int addZeroToN(int n) {
	int total = 0;

#ifdef _WIN32
	__asm {
		mov ecx, n;
		mov eax, total;

	Loopy:
		add eax, ecx;
		dec ecx;
		jnz Loopy;

		mov total, eax;
	}
#else
	for (int i = 0; i < n; i++)
		total += i;
#endif
	return total;
}


int main(int argc, const char **argv) {
	helloASM();

	int x = add2Numbers(4, 9);
	printf("x is: %d\n", x);

	int t = addZeroToN(5);
	printf("t is: %d\n", t);

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}