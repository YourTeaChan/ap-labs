//Розробити функцію, яка міняє в заданому реченні всі малі українські
//та латинські літери на відповідні великі. Використовуючи розроблену функцію, 
//переписати в новий файл великими літерами п'ять перших речень заданого текстового файла 
//(кінець речення - крапка з наступним пробілом, табуляцією чи символом нового рядка).

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 500
#define K 5

void FileFunction(FILE* flow_in, FILE* flow_out, char* sentences);
char* GetUppercaseLetters(char* sentence);
void PrintSentences(FILE* flow_in, FILE* flow_out, char* filename, char* sentences);

int main()
{
	system("chcp 1251");
	char fname_read[30] = { 0 };
	char fname_write[30] = { 0 };
	char sentences[N] = { 0 };
	
	printf("\nВведіть ім'я файлу: ");
	gets_s(fname_read);
	FILE* flow_in;
	flow_in = fopen(fname_read, "r");

	if (flow_in == NULL)
	{
		printf("\nФайл не відкрився!\n");
		return 0;
	}
	else
		printf("\nФайл успішно відкрився!\n");

	printf("\nДайте ім'я новоствореному файлу для запису результату: ");
	gets_s(fname_write);
	FILE* flow_out;
	flow_out = fopen(fname_write, "w");

	PrintSentences(flow_in, flow_out, fname_read, sentences);
	_fcloseall();
	return 0;
}

void FileFunction(FILE* flow_in, FILE* flow_out, char* sentences)
{
	int k = 0;
	char* p;
	char* result;

	while (k < K)
	{
		if (feof(flow_in))
			break;
		fgets(sentences, N, flow_in);
		result = GetUppercaseLetters(sentences);
		printf("%s ", result);
		fprintf(flow_out,"%s ", result);
		k++;
		p = strstr(sentences, ".");
		while (p != NULL && k < K)
		{
			while (*p == '.' || *p == ' ' || *p == '\t' || *p == '\n')
				p++;
			if (*p == '\0')
			{
				printf("\n");
				fprintf(flow_out, "\n");
				break;
			}
			result = GetUppercaseLetters(p);
			printf("%s ", result);
			fprintf(flow_out,"%s ", result);
			p = strstr(p, ".");
			k++;
		}
	}
	printf("\n");
}

char* GetUppercaseLetters(char* sentence)
{
	unsigned char* p = (unsigned char*)sentence;
	static char new_sentence[N];
	char* new_p = new_sentence;

	const char ukruppercase[] = { "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ" };
	const char ukrlowercase[] = { "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя" };

	for (; *p != '.' && *(p + 1) != ' ' || *p != '.' && *(p + 1) != '\t' || *p != '.' && *(p + 1) != '\n'; p++, new_p++)
	{
		if (isalpha(*p))
		{
			*new_p = (char)toupper((*p));
		}
		else if (strchr(ukrlowercase, *p) != NULL)
		{
			char* q = (char*)p;
			*new_p = ukruppercase[strchr(ukrlowercase, *q) - ukrlowercase];
		}
		else
		{
			*new_p = *p;
		}
	}
	*new_p = *p;
	*++new_p = '\0';
	return new_sentence;
}

void PrintSentences(FILE* flow_in, FILE* flow_out, char* filename, char* sentences)
{
	printf("\nВміст файлу %s:\n\n", filename);
	while (fgets(sentences, N, flow_in) != NULL)
	{
		printf("%s", sentences);
	}
	fseek(flow_in, 0L, SEEK_SET);

	printf("\n\nРезультат роботи програми:\n\n");
	FileFunction(flow_in, flow_out, sentences);
}