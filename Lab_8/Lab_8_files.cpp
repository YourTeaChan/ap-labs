//Ввести матрицю дійсних чисел (відомо, що кількість рядків матриці не перевищує 25). 
//Потім циклічно зсунути догори рядки введеної матриці так, щоб першим став рядок, 
//середнє значення елементів якого найменше. Надрукувати матрицю після зсування. 
//Застосувати функцію, яка виводить на екран матрицю заданої розмірності.
//Введення з файлу

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 40
#define K 10

bool OpenFile(FILE** flow_in);
bool GetDimensionOfMatrix(FILE** flow_in); 
void GetMatrix(FILE** flow_in, double** matrix);
int MinRowAverageValue(double** matrix);
void RowPermutation(double** matrix, int min_value_row);
void Swap(double** row_1, double** row_2);
void PrintMatrix(double** matrix);
void FilePrint(FILE* flow_out, double** matrix);
void FreeMemory(double** matrix);

int rows, columns;

int main()
{
	system("chcp 1251");
	FILE* flow_in = NULL, *flow_out = NULL;
	if (OpenFile(&flow_in) == false)
		return 0;
	if(GetDimensionOfMatrix(&flow_in) == false)
		return 0;
	double** matrix = (double**)calloc(rows, sizeof(double*));
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = (double*)calloc(columns, sizeof(double));
	}
	GetMatrix(&flow_in, matrix);
	printf("\n\tВведена матриця:\n");
	PrintMatrix(matrix);
	RowPermutation(matrix, MinRowAverageValue(matrix));
	printf("\n\n\tМатриця після зсування:\n");
	PrintMatrix(matrix);
	FilePrint(flow_out, matrix);
	FreeMemory(matrix);
	_fcloseall();
	return 0;
}

bool OpenFile(FILE** flow_in)
{
	char* file_r = (char*)malloc(sizeof(char) * N);
	printf("\nВведіть назву файлу з матрицею: ");
	gets_s(file_r, N);
	*flow_in = fopen(file_r, "r");
	if (*flow_in != NULL)
	{
		printf("\nФайл успішно відкрито!\n");
		return true;
	}
	else
	{
		printf("\nФайл не відкрився!\n");
		return false;
	}
}

bool GetDimensionOfMatrix(FILE** flow_in)
{
	int r = 0, c = 0, k = 0;
	char* p = (char*)malloc(sizeof(char) * K);
	char* el = p;
	fgets(el, K, *flow_in);
	rows = atoi(el);
	if (rows < 1 || rows > 25)
	{
		printf("\nКількість рядків вказано неправильно!");
		return false;
	}
	while (*el != 'x')
		el++;
	columns = atoi(++el);
	if (columns < 1)
	{
		printf("\nКількість стовпців вказано неправильно!");
		return false;
	}
	printf("\nРозмірність матриці %dx%d\n", rows, columns);
	free(p);
	return true;
}

void GetMatrix(FILE** flow_in, double** matrix)
{
	for (int i = 0;  i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fscanf(*flow_in," %lf", &matrix[i][j]);
		}
	}
}

int MinRowAverageValue(double** matrix)
{
	int i, j, min_row = 0;
	double sum, average_value, min_value, * pel, ** pr;
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
		Swap(pr, pr - 1);
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

void FilePrint(FILE* flow_out, double** matrix)
{
	char* file_w = (char*)malloc(sizeof(char) * N);
	printf("\nВведіть назву файлу, в який буде записано результат: ");
	gets_s(file_w, N);
	flow_out = fopen(file_w, "w");
	if (file_w != NULL)
		printf("\nФайл відкрився!\n");
	else
	{
		while (file_w == NULL)
		{
			printf("\nФайл не відкрився! Спробуйте ще раз: ");
			gets_s(file_w, N);
		}
		printf("\nФайл відкрився!\n");
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fprintf(flow_out, "%7.2lf\t", matrix[i][j]);
		}
		fprintf(flow_out, "\n");
	}
	printf("\nРезультат записано в файл %s\n", file_w);
	fclose(flow_out);
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