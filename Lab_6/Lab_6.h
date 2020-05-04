#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7
#define W 50
#define P 100
#define B 15

typedef struct List_of_cars
{
	char owner[W];
	char number[B];
	char brand[B];
	char problems[P];
} Cars;

void List(int stop, Cars* сar);
void QuickSort(Cars* L, Cars* R);
void Swap(Cars* Left, Cars* Right);
void Results(Cars* car);
void Top(Cars* car);