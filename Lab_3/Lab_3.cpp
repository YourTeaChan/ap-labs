//З клавіатури ввести набір даних з інформацією про результати технічного огляду автомобілів:
//<Номер автомобіля>, <Марка>, <Власник>, <Несправності>.Роздрукувати введений список в абетковому порядку.
//Визначити, автомобілів якої марки найбільше в списку техогляду.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct List_of_cars 
{
	char owner[50];
	char number[15];
	char brand[15];
	char problems[100];
} Cars;

int List(int kst, int stop, Cars *сar);
void QuickSort(Cars *L, Cars *R);
void Swap(Cars *Left, Cars *Right);
void Results(int kst, Cars *car);
void Top(int kst, Cars* car);

int main()
{
	system("chcp 1251");
	Cars car[N] = { 0 };
	int stop = 1, kst = 0;

	kst = List(kst, stop, car);
	if (kst) {
		QuickSort(car, car + kst - 1);
		Results(kst, car);
		Top(kst, car);
	}
	else {
		printf("\n\n\t\t\t\tВи не ввели жодного даного\n\n");
	}
	return 0;
}

int List(int kst, int stop, Cars *car)
{
	printf("\nДопустима кількість автомобілів у списку: %d\n", N);
	printf("\n-------------------------------------------------\n");
	for (int i = 0; i < N; i++)
	{
		printf("Для продовження введення введіть будь-яку цифру, для завершення введення введіть 0: ");
		rewind(stdin);
		scanf_s("%d", &stop);
		if (stop == 0)
			break;
		printf("-------------------------------------------------\n");
		rewind(stdin);
		printf("\nПрізвище та ім'я власника: ");
		gets_s((car + i)->owner);
		printf("\nНомер автомобіля: ");
		gets_s((car + i)->number);
		printf("\nМарка: ");
		gets_s((car + i)->brand);
		printf("\nНесправності: ");
		gets_s((car + i)->problems);
		printf("\n-------------------------------------------------\n");
		rewind(stdin);
		kst++;
	}
	return kst;
}

void QuickSort(Cars *L, Cars *R)
{
	const char letters[] = " АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщьЮюЯя";
	Cars *l, *r;
	l = L;
	r = R;
	const char* c = strchr(letters, *(L->owner)); // компаранд - правий елемент
	if (L >= R)
		return;

	do
	{
		int i = 0;
		while ((l->owner[i]) == (r->owner[i])) // якщо букви співпадають
		{
			i++;
			c = strchr(letters, L->owner[i]); // вибираємо наступну букву компаранда для порівняння
		}

		// перевірка, чи букви на своїх місцях відносно компаранда
		while (strchr(letters, (l->owner)[i]) < c)  
			l++;
		while (strchr(letters, (r->owner)[i]) > c) 
			r--;

		if (l == r) // базис
		{
			l++;
			r--;
			break;
		}

		if (l < r)
		{
			Swap(l, r);
			l++;
			r--;
		}
	} while (l < r);
	QuickSort(L, r);
	QuickSort(l, R);
}

void Swap(Cars *Left, Cars *Right)
{
	Cars buff;

	buff = *Left;
	*Left = *Right;
	*Right = buff;
}

void Results(int kst, Cars *car)
{
	printf("\n\n\n\t\t\t\tСписок за алфавітним порядком\t\t\t\n\n");
	printf("-----------------------------------------------------------------------------------------------------------------");
	printf("\n|\t    Власник\t\t|Номер авто|\tМарка\t  |\t\t\tНесправності\t\t\t|");
	printf("\n-----------------------------------------------------------------------------------------------------------------");

	for (int i = 0; i < kst; i++)
	{
		printf("\n|%-31s|%-10s|%-14s|%-53s|", (car + i)->owner, (car + i)->number, (car + i)->brand, (car + i)->problems);
		printf("\n-----------------------------------------------------------------------------------------------------------------");
	}
}

void Top(int kst, Cars* car)
{
	int repeat = 0, max_repeat = 0;
	int k = 0;
	char model[15], max_model[15];

	for (int i = 0; i < kst; i++)
	{
		k = 0;
		if (repeat > max_repeat)
		{
			max_repeat = repeat; // заміна макс.значення повторів
			while (max_model[k] = model[k++]); // копіювання назви марки з макс. повторенням
		}
		repeat = 0;
		k = 0;
		while (model[k] = (car + i)->brand[k++]); // копіювання поточної марки
		for (int j = i + 1; j < kst; j++) {
			if (strstr((car + j)->brand, model) != NULL) // перевірка на наявність однакових марок
				repeat++;
		}
	}

	if (max_repeat)
		printf("\n\nНайбільше в списку автомобілів марки %s - %d шт.\n\n", max_model, max_repeat + 1);
	else
		printf("\n\nЖодна з марок не повторюється\n\n");
}