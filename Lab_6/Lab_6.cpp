#include "Lab_6.h"

int kst;

void List(int stop, Cars* car)
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
		gets_s((car + i)->owner, W);
		printf("\nНомер автомобіля: ");
		gets_s((car + i)->number, B);
		printf("\nМарка: ");
		gets_s((car + i)->brand, B);
		printf("\nНесправності: ");
		gets_s((car + i)->problems, P);
		printf("\n-------------------------------------------------\n");
		rewind(stdin);
		kst++;
	}
}

void QuickSort(Cars* L, Cars* R)
{
	const char letters[] = " АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщьЮюЯя";
	Cars* l, * r;
	l = L;
	r = R;
	const char* c = strchr(letters, *(L->owner)); 
	if (L >= R)
		return;
	do
	{
		int i = 0;
		while ((l->owner[i]) == (r->owner[i])) 
		{
			i++;
			c = strchr(letters, L->owner[i]); 
		}
		while (strchr(letters, (l->owner)[i]) < c)
			l++;
		while (strchr(letters, (r->owner)[i]) > c)
			r--;
		if (l == r)
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

void Swap(Cars* Left, Cars* Right)
{
	Cars buff;
	buff = *Left;
	*Left = *Right;
	*Right = buff;
}

void Results(Cars* car)
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

void Top(Cars* car)
{
	int repeat = 0, max_repeat = 0;
	int k = 0;
	char model[15], max_model[15];

	for (int i = 0; i < kst; i++)
	{
		k = 0;
		if (repeat > max_repeat)
		{
			max_repeat = repeat;
			while (max_model[k] = model[k++]); 
		}
		repeat = 0;
		k = 0;
		while (model[k] = (car + i)->brand[k++]); 
		for (int j = i + 1; j < kst; j++) {
			if (strstr((car + j)->brand, model) != NULL) 
				repeat++;
		}
	}
	if (max_repeat)
		printf("\n\nНайбільше в списку автомобілів марки %s - %d шт.\n\n", max_model, max_repeat + 1);
	else
		printf("\n\nЖодна з марок не повторюється\n\n");
}