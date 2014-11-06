#pragma warning(disable: 4996)
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <clocale>
#include <cstring>

static const char * const g_lpstrFileName = "INPUT.TXT";

#define BUFFER_CHUNK 20
struct __String
{
	char  *data;
	int    len;
	int    allocated;
};
typedef struct __String String;

static void
__AppendString(String *str, int ch)
{
	if (str == NULL)
		return;
	if (str->data == NULL) {
		str->data = (char *)calloc(1, BUFFER_CHUNK);
		str->len = 0;
		str->allocated = BUFFER_CHUNK;
	} else {
		if (str->allocated < (str->len + 1)) {
			str->allocated += BUFFER_CHUNK;
			str->data = (char *)realloc(str->data, str->allocated);
		}
	}
	str->data[str->len++] = (char)ch;
}

static void
__FreeString(String *str)
{
	if (str) {
		free(str->data);
		str->data = NULL;
		str->len = 0;
		str->allocated = 0;
	}
}

static void
__ClearString(String *str)
{
	memset(str->data, 0, str->allocated);
	str->len = 0;
}

static int
__CheckString(String *str)
{
	int  i;
	char last;

	last = 0x00;
	for (i = 0; i < str->len; ++i) {
		char ch = str->data[i];
		if (isupper((int)ch) && last == ch)
			return 0;
		last = ch;
	}
	return 1;
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
		while (!feof(fd)) { \
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
			} else {
				if (isupper(ch) && ch == last) {
					result = 0;
				}
			}
			buffer[next++] = (char)ch;
			last = ch;
		}
#endif
		fclose(fd);
	} else {
		fprintf(stderr, "Входной файл %s не найден.\n", g_lpstrFileName);
	}
	fprintf(stdout, "Нажмите любую клавишу для продолжения...\n");
	fgetc(stdin);
	return EXIT_SUCCESS;
}



