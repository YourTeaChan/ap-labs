//1) дані та ознака впорядкування: прізвища та ініціали учасників конкурсу; впорядкування за абеткою; 
//2) порядок обходу дерева для друку: нижній (від листків) зліва направо; 
//3) дії над деревом: 3.1) визначити кількість листків сформованого дерева; 
//3.2) вилучити кореневий вузол дерева - на його місце має бути перенесений 
//найбільший елемент лівого піддерева (якщо цей елемент має своє піддерево, 
//то його треба під'єднати на місце елемента, що стає коренем дерева); 
//4) порядок витирання вузлів: прямий (від кореня) справа наліво; 
//5) функція без рекурсії: знаходження кількості вузлів, що є листками.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

typedef struct contest_participants
{
	char* name;
} Data;

typedef struct binary_tree
{
	Data data;
	binary_tree* parent, * right, * left;
} Tree;

void OpenFile(FILE** file, const char* mode);
void CreateTree(FILE* file);
void TreeNode(FILE* file);
void AddNode(Tree** node, Data data);
bool Sorting(const char* name, const char* parentname);
void PrintTree(Tree* node);
int NumberOfLeaves();
int TreeHeight(Tree* node);
void ChangeRoot();
void DeleteTree(Tree* node);
void FreeMemory(Tree* node);
Tree* SearchMaxValue(Tree* node);

Tree* root;

int main()
{
	system("chcp 1251");
	FILE* readfile;
	OpenFile(&readfile, "r");
	CreateTree(readfile);
	printf("\n\nДерево до зміни кореня:\n\n");
	PrintTree(root);
	printf("\n\nКількість листків дерева: %d\n", NumberOfLeaves());
	ChangeRoot();
	printf("\n\nДерево після зміни кореня:\n\n");
	PrintTree(root);
	printf("\n");
	DeleteTree(root);
	_fcloseall();
	return 0;
}

void OpenFile(FILE** file, const char* mode)
{
	char* filename = (char*)malloc(sizeof(char) * N);
	if (mode == "r")
	{
		printf("\nВведіть назву файлу, з якого буде зчитано інформацію: ");
	}
	else
	{
		printf("\nНеправильно вказано мод!\n");
		exit(-1);
	}
	gets_s(filename, N);
	*file = fopen(filename, mode);
	free(filename);
	if (*file == NULL)
	{
		printf("\nФайл не відкрито!\n");
		exit(-2);
	}
	else
	{
		printf("\nФайл успішно відкрито!\n");
	}
}

void CreateTree(FILE* file)
{
	while (!feof(file))
	{
		TreeNode(file);
	}
}

void TreeNode(FILE* file)
{
	Data data;
	char* information = (char*)malloc(sizeof(char) * N);
	fgets(information, N, file);
	int length = strlen(information);
	if (length == 0)
	{
		printf("\nРядок порожній!\n");
		exit(-3);
	}
	else if (information[length - 1] == '\n')
	{
		information[length - 1] = '\0';
	}
	data.name = information;

	AddNode(&root, data);
}

void AddNode(Tree** node, Data data)
{
	Tree* newnode = (Tree*)malloc(sizeof(Tree));
	newnode->data = data;
	static Tree* father = *node;
	if (*node == NULL)
	{
		newnode->left = NULL;
		newnode->right = NULL;
		*node = newnode;
		if (root == NULL)
		{
			root = *node;
		}
		return;
	}
	if (Sorting(data.name, (*node)->data.name))
	{
		AddNode(&(*node)->left, newnode->data);
	}
	else
	{
		AddNode(&(*node)->right, newnode->data);
	}
	free(newnode);
}

bool Sorting(const char* name, const char* parentname)
{
	const char letters[] = " АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщьЮюЯя";	
	const char* right = strchr(letters, *parentname);
	const char* left = strchr(letters, *name);
	while (left == right)
	{
		right = strchr(letters, *(++parentname));
		left = strchr(letters, *(++name));
	}
	if (right > left)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void PrintTree(Tree* node)
{
	if (node == NULL)
	{
		return;
	}
	PrintTree(node->left);
	PrintTree(node->right);
	printf("%s   ", node->data.name);
}

int NumberOfLeaves()
{
	Tree** stack = (Tree**)calloc(TreeHeight(root), sizeof(Tree*));
	Tree* p = root, * next;
	int k = 0, i = 0;
	while (p != NULL)
	{
		if (p->left != NULL)
		{
			next = p->left;
			if (p->right != NULL)
			{
				stack[++i] = p->right;
			}
		}
		else
		{
			if (p->right != NULL)
			{
				next = p->right;
			}
			else
			{
				next = stack[i--];
			}
		}
		if (p->left == NULL && p->right == NULL)
		{
			k += 1;
		}
		p = next;
	}
	free(stack);
	return k;
}

int TreeHeight(Tree* node)
{
	int left, right;
	if (node == NULL)
	{
		return 0;
	}
	left = TreeHeight(node->left);
	right = TreeHeight(node->right);
	return left > right ? left + 1 : right + 1;
}

void ChangeRoot()
{
	Tree* extrimeright = SearchMaxValue(root->left);
	Tree* leftchild;
	Tree* parent = root->left;
	while (parent->right != extrimeright)
	{
		parent = parent->right;
	}
	leftchild = extrimeright->left;
	parent->right = leftchild;
	extrimeright->right = root->right;
	extrimeright->left = root->left;
	root = extrimeright;
}

Tree* SearchMaxValue(Tree* node)
{
	if (node->right != NULL)
	{
		return SearchMaxValue(node->right);
	}
	else
	{
		return node;
	}
}

void DeleteTree(Tree* node)
{
	if (node == NULL)
	{
		return;
	}
	DeleteTree(node->right);
	DeleteTree(node->left);
	FreeMemory(node);
}

void FreeMemory(Tree* node)
{
	free(node->data.name);
	free(node);
}