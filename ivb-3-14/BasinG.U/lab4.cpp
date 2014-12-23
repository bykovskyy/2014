/*
Variant 4
George Basin
*/

#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <string>

void WriteToStream(std::ofstream * stream, int * buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		*stream << buffer[i];
		if (i + 1 != length)
			*stream << ' ';
	}
	*stream << '\n';
}

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	std::ifstream In = std::ifstream("input.txt");

	int N, pCount = 0, nCount = 0, pOffest = 0, nOffest = 0;
	In >> N;

	int * data = new int[N];
	for (int i = 0; i < N; i++)
	{
		In >> data[i];
		if (data[i] % 2 == 0)
			pCount++;
		else
			nCount++;
	}

	In.close();

	int * p = new int[pCount];
	int * n = new int[nCount];

	for (int i = 0; i < N; i++)
	{
		if (data[i] % 2 == 0)
			p[pOffest++] = data[i];
		else
			n[nOffest++] = data[i];
	}

	std::ofstream Out = std::ofstream("output.txt");

	WriteToStream(&Out, n, nCount);
	WriteToStream(&Out, p, pCount);

	if (pCount >= nCount)
		Out << "YES";
	else
		Out << "NO";

	Out.close();

	delete data, n, p;
	return 0;
}

static int
__IsNullString(String *str)
{
	return str->len == 0;
}

static void
__DoResult(String *str)
{
	int ret = __CheckString(str);
	fprintf(stdout, "Строка \"%s\": %s\n", str->data, (ret ? "Соответствует" : "Не соответствует"));
	__ClearString(str);
}

#define CLEARWS() \
while (!feof(fd)) {
\
	ch = fgetc(fd); \
if (!iswspace(ch)) \
	break; \
}

int
main(int argc, char **)
{
	FILE *fd;
	setlocale(LC_ALL, "Russian");


	fd = fopen(g_lpstrFileName, "r");
	if (fd != NULL) {
#if 0
		String str;
		int ch;
		memset(&str, 0, sizeof(String));
		/** FIXME: CLEARWS(); */
		while (!feof(fd)) {
			ch = fgetc(fd);
			if (iswspace(ch) || ch == EOF) {
				__DoResult(&str);
				CLEARWS();
				if (feof(fd))
					break;
			}
			__AppendString(&str, ch);
		}
		if (!__IsNullString(&str)) {
			__DoResult(&str);
		}
		__FreeString(&str);
#else
		int   last = 0x00;
		int   ch;
		char  buffer[1000];
		int   next = 0;
		int   result = 1;

		memset(buffer, 0, sizeof(buffer));
		while (!feof(fd)) {
			ch = fgetc(fd);
			if (iswspace(ch) || ch == EOF) {
				fprintf(stdout, "Строка \"%s\": %s\n", buffer, (result ? "Соответствует" : "Не соответствует"));
				last = 0x00;
				next = 0;
				result = 1;
				memset(buffer, 0, sizeof(buffer));
				CLEARWS();
				if (feof(fd))
					break;
			}
			else {
				if (isupper(ch) && ch == last) {
					result = 0;
				}
			}
			buffer[next++] = (char)ch;
			last = ch;
		}
#endif
		fclose(fd);
	}
	else {
		fprintf(stderr, "Входной файл %s не найден.\n", g_lpstrFileName);
	}
	fprintf(stdout, "Нажмите любую клавишу для продолжения...\n");
	fgetc(stdin);
	return EXIT_SUCCESS;
}
