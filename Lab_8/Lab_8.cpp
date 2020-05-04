//Ввести матрицю дійсних чисел (відомо, що кількість рядків матриці не перевищує 25). 
//Потім циклічно зсунути догори рядки введеної матриці так, щоб першим став рядок, 
//середнє значення елементів якого найменше. Надрукувати матрицю після зсування. 
//Застосувати функцію, яка виводить на екран матрицю заданої розмірності.
//Введення з клавіатури

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void GetDimensionOfMatrix();
void GetMatrix(double** matrix);
int MinRowAverageValue(double** matrix);
void RowPermutation(double** matrix, int min_value_row);
void Swap(double** row_1, double** row_2);
void PrintMatrix(double** matrix);
void FreeMemory(double** matrix);

int rows, columns;

int main()
{
	system("chcp 1251");
	GetDimensionOfMatrix();
	double** matrix = (double**)calloc(rows, sizeof(double*));
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = (double*)calloc(columns, sizeof(double));
	}
	GetMatrix(matrix);
	printf("\n\tВведена матриця:\n");
	PrintMatrix(matrix);
	RowPermutation(matrix, MinRowAverageValue(matrix));
	printf("\n\n\tМатриця після зсування:\n");
	PrintMatrix(matrix);
	FreeMemory(matrix);
	return 0;
}

void GetDimensionOfMatrix()
{
	printf("\nВведіть розмірність матриці (максимальна кількість рядків 25):\n");
	printf("\nКількість рядків: ");
	scanf_s("%d", &rows);
	while (rows < 1 || rows > 25)
	{
		printf("\nКількість рядків вказано неправильно! Спробуйте ще раз: ");
		scanf_s("%d", &rows);
	}
	printf("Кількість стовпців: ");
	scanf_s("%d", &columns);
	while (columns < 1)
	{
		printf("\nКількість стовпців вказано неправильно! Спробуйте ще раз: ");
		scanf_s("%d", &columns);
	}
}

void GetMatrix(double** matrix)
{
	printf("--------------------------------------------------------------");
	printf("\nВведіть матрицю:\n\n");
	for (int i = 0; i < rows; i++)
	{	
		printf("Рядок %d: ", i + 1);
		for (int j = 0; j < columns; j++)
		{
			scanf_s("%lf", &matrix[i][j]);
		}
	}
	printf("--------------------------------------------------------------\n");
}

int MinRowAverageValue(double** matrix)
{
	int i, j, min_row = 0;
	double sum, average_value, min_value, *pel, **pr;
	for (i = 0, pr = matrix; i < rows; i++, pr++)
	{
		for (j = 0, sum = 0, pel = *pr; j < columns; j++, pel++)
		{
			sum += *pel;
		}
		average_value = sum / (double)columns;
		if (i == 0)
		{
			min_value = average_value;
		}
		else if (average_value < min_value)
		{
			min_value = average_value;
			min_row = i;
		}
	}
	printf("\n--------------------------------------------------------------\n");
	printf("Найменше середнє значення елементів у рядку %d.", min_row + 1);
	printf("\n--------------------------------------------------------------");
	return min_row;
}

void RowPermutation(double** matrix, int min_value_row)
{
	if (min_value_row == 0)
		return;
	double** pr;
	for (int i = min_value_row; i != 0; i--)
	{
		pr = matrix + i;
		Swap(pr, pr-1);
	}
}

void Swap(double** row_1, double** row_2)
{
	double* tmp = *row_1;
	*row_1 = *row_2;
	*row_2 = tmp;
}

void PrintMatrix(double** matrix)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%7.2lf\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void FreeMemory(double** matrix)
{
	double** pr;
	for (pr = matrix; pr < matrix + rows; pr++)
	{
		free(*pr);
	}
	free(matrix);
}