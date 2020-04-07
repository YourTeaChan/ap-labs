//Розробити функцію, яка міняє у заданому символьному рядку всі слова, 
//що містять вказану літеру на відповідну кількість символів х. 
//З клавіатури ввести декілька речень.Використовуючи розроблену функцію, 
//«заховати» ті слова з введених речень, в яких зустрічається задана літера.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7
#define S 100

void GetSentences(char arr[][S], int k_rech);
void ChangeX(char arr[][S], char* letter, int k_s);
void Print(char sentence[][S], int k_rech);

int main(void)
{
	system("chcp 1251");
	int k_s = 0; 
	char sentence[N][S];
	char letter[2];
	int stop = 1;

	printf("\nВведіть кілька речень (максимальна кількість - %d)\n", N);
	while (k_s < N)
	{
		printf("\nДля введення введіть значення, не рівне нулю: ");
		scanf_s("%d", &stop);
		if (k_s == 0 && stop == 0)
		{
			printf("\nВи не ввели жодного речення!\n");
			return 0;
		}
		if (stop == 0)
			break;
		GetSentences(sentence, k_s);
		k_s++;
	} 

	printf("\nВведіть букву, слова з якою заміняться у реченнях на \"x\": ");
	rewind(stdin);
	gets_s(letter);
	printf("\n\n");

	ChangeX(sentence, letter, k_s);
	Print(sentence, k_s);
}

void GetSentences(char arr[][S], int k_s) 
{
	printf("\nВведіть речення:\n");
	rewind(stdin);
	gets_s(arr[k_s], S);
}

void ChangeX(char arr[][S], char *letter, int k_s)
{
	char(*p_s)[S]; // вказівник на речення
	char *p_el, *p_end;
	int k = 0;

	for (int i = 0; i < k_s; i++)
	{
		p_s = arr + i;
		p_el = *p_s;
		p_end = p_el;

		while (*p_end != '\0')
		{
			while (*p_end != ' ' && *p_end != '.' && *p_end != '!' && *p_end != '?' && 
				*p_end != ',' && *p_end != '-' && *p_end != ':' && *p_end != ';' &&
				*p_end != '(' && *p_end != ')')
			{
				if (*p_end == *letter)
					k++;
				p_end++;
			}

			if (k)
			{
				while (p_el < p_end) // заміна слова на "х"
				{
					*p_el = 'x';
					p_el++;
				}
			}
			
			// пошук початку наступного слова
			while (*p_end == ' ' || *p_end == '.' || *p_end == '!' || *p_end == '?' ||
				*p_end == ',' || *p_end == '-' || *p_end == ':' || *p_end == ';' || 
				*p_end == '(' || *p_end == ')')
				p_end++;

			p_el = p_end;
			k = 0;
		}
	}
}

void Print(char sentence[][S], int k_s)
{
	printf("*Результат*\n\n");
	for (int i = 0; i < k_s; i++)
		puts(*(sentence + i));
}
