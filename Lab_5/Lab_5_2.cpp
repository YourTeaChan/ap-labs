//Розробити функцію зі змінною кількістю параметрів, які(можливо, окрім першого) є символьними рядками(реченнями).
//Функція повинна перетворити й надрукувати речення так, щоб «заховати» всі слова, які містять вказану літеру.
//Наприкінці треба вказати, в якому з речень таких слів найбільше.
//У програмі треба використати допоміжну функцію, яка у заданому символьному рядку міняє всі символи слова, 
//що містять вказану літеру, на відповідну кількість символів ? і повертає кількість «захованих» слів.
//Варіант 2: використання списку параметрів

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int GetSentences(char* letter, int kst, char* sentence, ...);
void Function_2(char* letter, const char* par, char* sentence, ...);
int Change(char* letter, char* sentence);
void Print(char* sentence);

const char ukruppercase[] = { "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ" };
const char ukrlowercase[] = { "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя" };

int main()
{
	system("chcp 1251");
	
	int kst = 0;
	char letter[2] = { 0 };
	char sentence_1[N] = { 0 };
	char sentence_2[N] = { 0 };
	char sentence_3[N] = { 0 };
	char sentence_4[N] = { 0 };
	char(*p)[N] = &sentence_1;
	char(**pp)[N]  = &p;
	
	kst = GetSentences(letter, kst, sentence_1, sentence_2, sentence_3, sentence_4);
	if (kst == 0)
	{
		printf("\nВи не ввели жодного речення!\n");
		return 0;
	}
	printf("\n-------------------------------------------------------\nВаріант 2\n");
	Function_2(letter, "SPPS", sentence_1, &sentence_2, &sentence_3, sentence_4);
	return 0;
}

int GetSentences(char* letter, int kst, char* sentence, ...)
{
	char** s = &sentence;
	printf("\nВведіть 4 речення (для завершення введення натисніть Enter):\n");
	for (int i = 0; i < 4; i++, s++)
	{
		printf("\nВведіть речення №%d\n", kst + 1);
		gets_s(*s, N);
		if (**s == '\0')
			break;
		kst++;
	}
	printf("\n\nВведіть букву, слова з якою необхідно замінити на \"?\": ");
	gets_s(letter, 2);
	while (strchr(ukrlowercase, *letter) == NULL && strchr(ukruppercase, *letter) == NULL)
	{
		printf("\nВи не ввели українську літеру. Спробуйте ще раз: ");
		gets_s(letter, 2);
	}
	return kst;
}

void Function_2(char* letter, const char *par, char *sentence, ...)
{
	const char* pr = par;
	const char** p = &par;
	int numb_of_sent = 0, sent = 0;
	int k_max = 0, k_w;
	p++;
	while (*pr)
	{
		if(**p == '\0')
			break;
		switch (*pr)
		{
		case 'S':
		{
			k_w = Change(letter, *(char**)p);
			sent++;
			Print(*(char**)p);

			if (k_w >= k_max)
			{
				if (k_w > k_max)
				{
					k_max = k_w;
					numb_of_sent = sent;
				}
				else
					k_max = 0;
			}
			p = (const char**)((char**)p + 1);
			break;
		}
		case 'P':
		{
			k_w = Change(letter, **(char(**)[N])p);
			sent++;
			Print(**(char(**)[N])p);

			if (k_w >= k_max)
			{
				if (k_w > k_max)
				{
					k_max = k_w;
					numb_of_sent = sent;
				}
				else
					k_max = 0;
			}
			p = (const char**)((char(**)[N])p + 1);
			break;
		}
		}
		pr++;
	}
	printf("\n-------------------------------------------------------\n");
	if (k_max)
		printf("\nНайбільша кількість слів - %d - захована в реченні №%d.\n", k_max, numb_of_sent);
	else
		printf("\nНемає речення з найбільшою кількістю захованих слів.\n");
}

int Change(char* letter, char* sentence)
{
	char** s = &sentence;
	int k_w = 0, k = 0;
	char* p_el = *s;
	char* p_end = p_el;
	char let[2] = { 0 };

	if (strchr(ukrlowercase, *letter) != NULL) //враховуємо великі і малі літери
	{
		*let = ukruppercase[strchr(ukrlowercase, *letter) - ukrlowercase];
	}
	else
	{
		*let = ukrlowercase[strchr(ukruppercase, *letter) - ukruppercase];
	}

	do
	{
		while (*p_end != '\0' && *p_end != ' ' && *p_end != ',' && *p_end != ';' && *p_end != ':' &&
			*p_end != '.' && *p_end != '!' && *p_end != '?' && *p_end != '(' && *p_end != ')')
		{
			if (*p_end == *letter || *p_end == *let)
				k++;
			p_end++;
		}
		if (k)
		{
			while (p_el != p_end)
			{
				*p_el = '?';
				p_el++;
			}
			k_w++;
		}
		while (*p_end == ' ' || *p_end == ',' || *p_end == ';' || *p_end == ':' ||
			*p_end == '.' || *p_end == '!' || *p_end == '?' || *p_end == '(' || *p_end == ')')
			p_end++;
		p_el = p_end;
		k = 0;

	} while (*p_el != '\0');
	return k_w;
}

void Print(char* sentence)
{
	printf("\n");
	puts(sentence);
}