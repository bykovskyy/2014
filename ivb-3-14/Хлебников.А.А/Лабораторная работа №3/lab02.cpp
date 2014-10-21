#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

/** Задание */
/** Строка состоит из слов, разделенных одним
*** или несколькими пробелами. Поменяйте
*** местами наибольшее по длине слово и наименьшее
***/

struct __Token
{
	int loc;
	int len;
};

static void
__do(char *in);
/** Найти минимальное слови и максимальное */
static void
__find(char *in, struct __Token *min, struct __Token *max);
/** Заменить два слова */
static void
__swap(char *in, struct __Token *first, struct __Token *second);
static int
__is_whitespace();

int
main(int argc, char **argv)
{
	char *buffer = strdup("Now that we've got our ServiceHost created, we need to configure some endpoints");
	fprintf(stdout, "%s\n", buffer);
	__do(buffer);
	fprintf(stdout, "%s\n", buffer);
	free(buffer);
	system("pause");
	return EXIT_SUCCESS;
}

void
__do(char *buffer)
{
	struct __Token min;
	struct __Token max;

	__find(buffer, &min, &max);
	__swap(buffer, &min, &max);
}

#define SKIPWS(In) \
			while (*(In) != 0 && iswspace( (int)(*(In)) )) {    \
		++(In);                                             \
		++id;                                               \
				}

void
__find(char *in, struct __Token *min, struct __Token *max)
{
	char *it = in;
	char *next = it;
	int id = 0;


	memset(min, 0, sizeof(struct __Token));
	memset(max, 0, sizeof(struct __Token));

	SKIPWS(it);
	while (*it != 0) {
		if (iswspace((int)(*it))) {
			int len = it - next;
			if (min->len == 0) {
				min->len = len;
				min->loc = id - len;

				max->len = len;
				max->loc = id - len;
			} else {
				if (len > max->len) {
					max->len = len;
					max->loc = id - len;
				}
				if (len < min->len) {
					min->len = len;
					min->loc = id - len;
				}
			}
			SKIPWS(it);
			next = it;
		}
		++it;
		++id;
	}
}


void
__swap(char *in, struct __Token *first, struct __Token *second)
{
	char *out = (char *)calloc(1, strlen(in) + 1);
	struct __Token *d1 = first;
	struct __Token *d2 = second;
	int i = 0;
	int k = 0;

	/** Ищем ближайший */
	if (first->loc > second->loc)
		d1 = second, d2 = first;

	/** Копируем до первого */
	while (in[i] != 0 && i < d1->loc)
		out[i] = in[i++];

	/** Записываем первое слово */
	k = d2->loc;
	for (i = d1->loc; i < d1->loc + d2->len; ++i) {
		out[i] = in[k++];
	}
	/** Записываем продолжение */
	k = d1->loc + d1->len;
	for (; i < d2->loc - d1->len + d2->len; ++i) {
		out[i] = in[k++];
	}
	/** Записываем второе слово */
	k = d1->loc;
	for (; k < d1->loc + d1->len; ++k, ++i) {
		out[i] = in[k];
	}
	/** Записываем продолжение */
	k = d2->loc + d2->len;
	while (in[i] != 0)
		out[i++] = in[k++];
	/** Копируем временную строку */
	strcpy(in, out);
	/** Освобождаем временную строку*/
	free(out);
}