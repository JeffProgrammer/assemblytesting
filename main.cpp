#include <iostream>
#include <stdlib.h>

#ifdef _WIN32
	#define SUPPORT_MSVC_INLINE_ASM
#endif

char helloWorld[] = "Hello World!\n";

void helloASM() {
#ifdef SUPPORT_MSVC_INLINE_ASM
	__asm
	{
		mov eax, offset helloWorld
		push eax
		call printf;
		add esp, 4;
	}
#else
	printf("%s", helloWorld);
#endif
}

int add2Numbers(int a, int b) {
#ifdef SUPPORT_MSVC_INLINE_ASM
	__asm {
		mov eax, a
		mov ecx, b
		add eax, ecx
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

#ifdef SUPPORT_MSVC_INLINE_ASM
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

/**
 * Gets the amount of words there are within a string.
 * @param string The string to test.
 * @return the count of words.
 */
int getWordCount(const char *string) {
#ifdef SUPPORT_MSVC_INLINE_ASM
	// Register eax: The string pointer.
	// Register ecx: The word count.
	int count = 0;
	__asm {
		mov eax, string;
		xor ecx, ecx; //< Xoring with itself is setting it to 0 more efficiently.

		cmp [eax], cl;
		je Done;
		inc ecx;  //< Guarentee at least 1 character is present.

	Loopy:
		cmp [eax], 0x0;
		je Done;

		cmp [eax], 0x20;
		jne Continue;

		inc ecx;

	Continue:
		inc eax;
		jmp Loopy;

	Done:
		mov count, ecx;
	}
	return count;
#else
	int count = !!(*string);
	while ((*string) != 0x0) {
		if ((*string) == 0x20)
			count++;
		++string;
	}
	return count;
#endif
}


int main(int argc, const char **argv) {
	helloASM();

	int x = add2Numbers(4, 9);
	printf("x is: %d\n", x);

	int t = addZeroToN(5);
	printf("t is: %d\n", t);

	int wc = getWordCount("Hi nobody my name is bob");
	printf("word count of \"Hi nobody my name is bob\": %d\n", wc);
	printf("word count of empty string: %d\n", getWordCount(""));
	printf("word count of single word: %d\n", getWordCount("hi"));

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}