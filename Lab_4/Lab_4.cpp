//Розробити функцію, яка обчислює найбільший спільний дільник(НСД) двох заданих натуральних чисел.
//З клавіатури ввести декілька беззнакових цілих чисел.
//Використовуючи розроблену функцію, визначити НСД усіх введених чисел.


#include <stdio.h>
#include <stdlib.h>

#define N 5

int GetNumbers(int kst, int *numbers);
int NSD(int A, int B);
int RecNSD(int nsd, int *numbers, int rec);
void Swap(int *a, int *b);
void Print(int kst, int nsd);

int main()
{
	system("chcp 1251");
	int kst = 0, rec = 0;
	int numbers[N] = { 0 };

	kst = GetNumbers(kst, numbers); // функція повертає кількість чисел
	int nsd = *numbers; 

	if (kst)
	{
		printf("\n\n*Ітераційна функція*\n");
		for (int k = 1; k < kst; k++)
		{
			nsd = NSD(nsd, *(numbers + k));
		}
		Print(kst, nsd);

		printf("\n*Рекурсивна функція*\n\n");
		RecNSD(*numbers, (numbers + 1), rec);
		Print(kst, nsd);
	}
	else
		printf("\nВи не ввели жодного числа, крім 0!\n\n");
	return 0;
}

int GetNumbers(int kst, int *numbers)
{
	printf("\n*Програма для визначення НСД двох чисел*"
		"\n\nМаксимальна кількість введених чисел: %d\n", N);
	printf("\nДля завершення введення введіть 0 замість числа");
	printf("\n------------------------------------------------\n");
	rewind(stdin);

	for (int i = 0; i < N; i++)
	{
		printf("\nВведіть число %d: ", kst + 1);
		scanf_s("%d", (numbers+i));
		if (*(numbers + i) == 0)
			break;
		rewind(stdin);
		kst++;
	}
	return kst;
}

int NSD(int A, int B) // ітераційний варіант функції
{
	int nsd = 0;
	int a = A;
	int b = B;

	while (a != b)
	{
		if (a > b)
			Swap(&a, &b);
		b = b - a;
	}
	nsd = a;

return nsd;
}

int RecNSD(int nsd, int *num, int rec) // рекурсивний варіант функції 
{
	if (*num <= 0) // базис
		return *(num - 1);
	rec++;
	printf("*Виклик функції №%d*\n", rec);;
	int a = nsd;
	int b = *num;

	while (a != b)
	{
		if (a > b)
			Swap(&a, &b);
		b = b - a;
	}
	nsd = a;

	return RecNSD(nsd, num + 1, rec);
}

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Print(int kst, int nsd)
{
	printf("\nНСД заданих %d чисел = %d\n\n", kst, nsd);
}
