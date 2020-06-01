//У двозв'язний список, організований як черга, занести послідовність символьних рядків, 
//що містять 2-10-ві коди коротких беззнакових чисел. Вилучити зі списку рядки, 
//в яких записані неправильні коди (наприклад: у рядку є інші символи, крім 0 та 1, 
//значення тетради перевищує 9, кількість десяткових цифр більша за 5 тощо). 
//Надрукувати таблицю кодів, що залишилась, та їхніх десяткових значень. 
//Для перевірки 2-10-го коду числа та обчислення його десяткового значення розробити дві окремі функції.
//Версія з файлами

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#define N 25

typedef struct code
{
	char* binarydecimalcode = nullptr;
} Code;

typedef struct code_list
{
	Code data;
	code_list* last, * next;
} List;

void OpenFile(FILE** file, const char* mode);
void CreateList(FILE* file);
Code GetItem(FILE** file);
void AddItem(Code code);
void ClearFromWrongCodes();
bool ThisCodeIsWrong(List* item);
void IsCodesCorrect();
bool IsEmpty();
void DeleteItem(List* item);
int DecimalValuesOfCodes(List* item);
void Print(FILE* file);
void PrintList(FILE* file);
void ClearList();

List* head, * tail;

int main()
{
	system("chcp 1251");
	FILE* readfile, * writefile;
	OpenFile(&readfile, "r");
	CreateList(readfile);
	ClearFromWrongCodes();
	IsCodesCorrect();
	OpenFile(&writefile, "w");
	Print(writefile);
	ClearList();
	_fcloseall();
	return 0;
}

void OpenFile(FILE** file, const char* mode)
{
	char* filename = (char*)malloc(sizeof(char) * N);
	if(mode == "r")
	{
		printf("\nВведіть назву файлу, у якому знаходяться коди: ");
	}
	else if (mode == "w")
	{
		printf("\nВведіть назву файлу, у який буде записано результат: ");
	}
	else
	{
		printf("\nНеправильно введено мод!");
		exit(-3);
	}
	gets_s(filename, N);
	*file = fopen(filename, mode);
	free(filename);
	if (*file == NULL)
	{
		printf("\nФайл не відкрито!\n");
		exit(-1);
	}
	else
	{
		printf("\nФайл успішно відкрито!\n");
	}
}

void CreateList(FILE* file)
{
	while (!feof(file))
	{
		AddItem(GetItem(&file));
	}
}

Code GetItem(FILE** file)
{
	Code newcode;
	char* buffer = (char*)malloc(sizeof(char) * N);
	fgets(buffer, N, *file);
	newcode.binarydecimalcode = buffer;
	return newcode;
}

void AddItem(Code code)
{
	List* newitem = (List*)malloc(sizeof(List));
	static List* prev;
	newitem->data = code;
	newitem->next = NULL;
	if (head == NULL)
	{
		newitem->last = NULL;
		head = tail = newitem;
		prev = newitem;
	}
	else
	{
		prev->next = newitem;
		newitem->last = prev;
		prev = prev->next;
		tail = newitem;
	}
}

void ClearFromWrongCodes()
{
	if (head == NULL)
	{
		return;
	}
	List* p = head;
	List* pnext = p->next;
	for (int i = 0; p != NULL; i++)
	{
		if (ThisCodeIsWrong(p))
		{
			DeleteItem(p);
		}
		p = pnext;
		if (pnext == NULL)
		{
			return;
		}
		pnext = p->next;
	}
}

bool ThisCodeIsWrong(List* item)
{
	const char leks[] = " ";
	char* copycode = (char*)malloc(sizeof(char) * N);
	strcpy(copycode, item->data.binarydecimalcode);
	int length = strlen(copycode);
	if (length == 0)
	{
		printf("\nРядок порожній!\n");
		exit(-1);
	}
	else if (copycode[length - 1] == '\n')
	{
		copycode[length - 1] = '\0';
	}
	strcpy(item->data.binarydecimalcode, copycode);
	char* buff = strtok(copycode, leks);

	for (int k = 1; buff != NULL; k++)
	{
		if (k == 5) // перевірка, чи кількість тетрад не перевищує 4
		{
			return true;
		}
		for (int n = 1, value = 0, num = 3; *buff != '\0'; n++, buff++, num--) // перевірка однієї тетради
		{
			if (*buff != '0' && *buff != '1') // перевірка на наявність неправильних цифр
			{
				return true;
			}
			if (n > 4) // перевірка на на більшу кількість цифр у тетраді
			{
				return true;
			}
			if (*buff == '1') // обрахунок значення тетради
			{
				value += (int)pow(2, num);
			}
			if (value > 9) // перевірка, чи десяткове значення тетради не перевищує 9
			{
				return true;
			}
		}
		buff = strtok(NULL, leks); // перехід на наступну тетраду
	}
	free(copycode);
	return false;
}

void IsCodesCorrect()
{
	if (IsEmpty())
	{
		printf("\n--------------------------------------------------------------------");
		printf("\n\nУ списку немає жодного правильного коду!\n");
		exit(0);
	}
}

bool IsEmpty()
{
	if (head == NULL)
	{
		return true;
	}
	return false;
}

void DeleteItem(List* item)
{
	List* tmp = item;
	if (item == head)
	{
		head = tmp->next;
		if (head == NULL)
		{
			return;
		}
		head->last = NULL;
		free(tmp);
	}
	else if (item == tail)
	{
		tail = tmp->last;
		tail->next = NULL;
		free(tmp);
	}
	else
	{
		tmp->last->next = tmp->next;
		tmp->next->last = tmp->last;
		free(tmp);
	}
}

int DecimalValuesOfCodes(List* item)
{
	const char leks[] = " ";
	char* copycode = (char*)malloc(sizeof(char) * N);
	int decimalvalue = 0, value = 0;
	char* stop;
	strcpy(copycode, item->data.binarydecimalcode);
	char* buff = strtok(copycode, leks);
	while (buff != NULL)
	{
		decimalvalue = strtol(buff, &stop, 2);
		value = decimalvalue + 10 * value;
		buff = strtok(NULL, leks);
	}
	free(copycode);
	return value;
}

void Print(FILE* file)
{
	printf("\n--------------------------------------------------------------------");
	printf("\n\n\t\t***Правильні коди***");
	printf("\n\n Двійково-десяткові\t\t\tДесяткові\n\n");
	PrintList(stdout);
	PrintList(file);
}

void PrintList(FILE* file)
{
	for (List* p = head; p != NULL; p = p->next)
	{
		fprintf(file, " %-30s  \t  %-10d\n", p->data.binarydecimalcode, DecimalValuesOfCodes(p));
	}
}

void ClearList()
{
	List* p = head, * pnext = p->next;
	for (; p != NULL; pnext = p->next)
	{
		free(p);
		p = pnext;
		if (pnext == NULL)
		{
			return;
		}
		pnext = p->next;
	}
}